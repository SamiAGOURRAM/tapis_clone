//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/array_to_epr.hh"

#include <iostream> // TODO:
#include <stack>

namespace smtface::utils {

  //*-- EPRizer
  class EPRizer: public core::Visitor {
  public:
    //*- methods

    Expr eprize(const Expr &expr) {
      expr->accept(*this);
      auto res = result();
      return std::get<1>(res);
    }

    void visit(std::shared_ptr<core::ApplicationTerm> term) override {

      if (term->function()->name() == "sum_range") {
        return _return(std::make_tuple(false, term));
      }
      bool changed = false;
      std::vector<Expr> args;
      const Function *func = term->function();
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
        auto r = result();
        args.push_back(std::get<1>(r));
        if(std::get<0>(r)) {
          changed = true;
        }
      }
      if(term->function()->name() == "select") {
        auto array = std::dynamic_pointer_cast<core::Constant>(args[0]);
        auto sort = (const core::ArraySort *) array->sort();
        auto func = term->context().function(array->name(), {sort->index_sort()}, sort->element_sort());
        return _return(std::make_tuple(true, (*func)({args[1]})));
      } else if(term->function()->name() == "=" && args[0]->sort()->kind() == core::SortKind::array &&
                args[1]->sort()->kind() == core::SortKind::array) {
        unsigned long idx_store = -1;
        unsigned long idx_constant = -1;
        for(unsigned long i = 0; i < args.size(); i++) {
          if(args[i]->kind() == core::TermKind::Application &&
             std::dynamic_pointer_cast<core::ApplicationTerm>(args[i])->function()->name() == "store") {
            idx_store = i;
          } else {
            idx_constant = i;
          }
        }
        if(idx_store == -1) {
          auto array1 = std::dynamic_pointer_cast<core::Constant>(args[0]);
          auto sort1 = (const core::ArraySort *) array1->sort();
          auto array2 = std::dynamic_pointer_cast<core::Constant>(args[1]);
          auto func1 = term->context().function(array1->name(), {sort1->index_sort()}, sort1->element_sort());
          auto func2 = term->context().function(array2->name(), {sort1->index_sort()}, sort1->element_sort());
          auto qv = FreshSymbol(sort1->index_sort());
          return _return(std::make_tuple(true, ForAll({qv}, smtface::Equal((*func1)({qv}), (*func2)({qv})))));
        } else {
          auto array = std::dynamic_pointer_cast<core::Constant>(args[idx_constant]);
          auto sort = (const core::ArraySort *) array->sort();
          auto func1 = term->context().function(array->name(), {sort->index_sort()}, sort->element_sort());
          auto store_term = std::dynamic_pointer_cast<core::ApplicationTerm>(args[idx_store]);
          auto origin_array = std::dynamic_pointer_cast<core::Constant>(store_term->arguments()[0]);
          auto func2 = term->context().function(origin_array->name(), {sort->index_sort()}, sort->element_sort());
          auto qv = FreshSymbol(sort->index_sort());
          return _return(std::make_tuple(true,
                                         ForAll({qv},
                                                smtface::Implies(Not(smtface::Equal(qv, store_term->arguments()[1])),
                                                                 smtface::Equal((*func1)({qv}), (*func2)({qv}))))
                                         && smtface::Equal((*func1)({store_term->arguments()[1]}),
                                                           store_term->arguments()[2])));
        }
      }
      if(changed) {
        return _return(std::make_tuple(true, Apply(func->name(), args, term->context())));
      } else {
        return _return(std::make_tuple(false, term));
      }
    }

    void visit(std::shared_ptr<core::QuantifiedFormula> term) override {
      term->formula()->accept(*this);
      auto r = result();
      if(!std::get<0>(r)) {
        return _return(std::make_tuple(false, term));
      }
      if(term->quantifier() == core::Quantifier::forall) {
        return _return(std::make_tuple(true, ForAll(term->quantified_variables(), std::get<1>(r))));
      } else {
        return _return(std::make_tuple(true, Exists(term->quantified_variables(), std::get<1>(r))));
      }
    }

    void visit(std::shared_ptr<core::Constant> term) override {
      return _return(std::make_tuple(false, term));
    }

    void visit(std::shared_ptr<core::Null> term) override {
      return _return(std::make_tuple(false, term));
    }

    void visit(std::shared_ptr<core::Value> term) override {
      return _return(std::make_tuple(false, term));
    }

  private:
    std::tuple<bool, Expr> result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    void _return(const std::tuple<bool, Expr> &r) {
      _stack.push(r);
    }

    std::stack<std::tuple<bool, core::Expr>> _stack;
  };

  //*-- array_to_epr(expr)
  Expr array_to_epr(const smtface::Expr &expr) {
    EPRizer eprizer;
    return eprizer.eprize(expr);
  }

}
