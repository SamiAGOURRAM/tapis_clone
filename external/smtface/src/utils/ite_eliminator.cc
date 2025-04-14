//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/ite_eliminator.hh"

#include <stack>
#include "smtface/utils/has_ite.hh"

namespace smtface::utils {

  //*-- has_immediate_ite(expr)
  std::pair<Expr, unsigned long> has_immediate_ite(const Expr &expr) {
    if(expr->kind() == core::TermKind::Application) {
      auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(expr);
      if(app->function()->name() != "ite") {
        unsigned long i = 0;
        for(const auto &arg: app->arguments()) {
          if(arg->kind() == core::TermKind::Application &&
             std::dynamic_pointer_cast<core::ApplicationTerm>(arg)->function()->name() == "ite") {
            return std::make_pair(arg, i);
          }
          i++;
        }
      }
    }
    return std::make_pair(Null(), 0);
  }

  //*-- IteLifter
  class IteLifter: public core::Visitor {
  public:
    //*- methods

    Expr lift(const Expr &expr) {
      expr->accept(*this);
      auto res = result();
      return std::get<1>(res);
    }

    void visit(std::shared_ptr<core::ApplicationTerm> term) override {
      auto subite_res = has_immediate_ite(term);
      if(subite_res.first->kind() != core::TermKind::Null) {
        auto subite = std::dynamic_pointer_cast<core::ApplicationTerm>(subite_res.first);
        auto subite_index = subite_res.second;
        std::vector<Expr> args_l, args_r;
        for(unsigned long i = 0; i < term->arguments().size(); i++) {
          if(i == subite_index) {
            subite->arguments()[1]->accept(*this);
            args_l.push_back(std::get<1>(result()));
            subite->arguments()[2]->accept(*this);
            args_r.push_back(std::get<1>(result()));
          } else {
            term->arguments()[i]->accept(*this);
            auto arg = std::get<1>(result());
            args_l.push_back(arg);
            args_r.push_back(arg);
          }
        }
        smtface::Apply(term->function()->name(), args_l)->accept(*this);
        auto f_l = std::get<1>(result());
        smtface::Apply(term->function()->name(), args_r)->accept(*this);
        auto f_r = std::get<1>(result());
        auto lifted = smtface::Apply("ite", {subite->arguments()[0], f_l, f_r});
        lifted->accept(*this);
        return _return(result());
      } else if(has_ite(term) and term->function()->name() != "ite") {
        std::vector<Expr> args;
        for(auto &arg: term->arguments()) {
          if(has_ite(arg)) {
            arg->accept(*this);
            args.push_back(std::get<1>(result()));
          } else {
            args.push_back(arg);
          }
        }
        auto lifted = smtface::Apply(term->function()->name(), args);
        lifted->accept(*this);
        return _return(result());
      }
      return _return(std::make_tuple(false, term));
    }

    void visit(std::shared_ptr<core::QuantifiedFormula> term) override {
      // TODO: implement
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

    std::map<std::string, Expr> _map;
    std::stack<std::tuple<bool, core::Expr>> _stack;
  };

  //*-- ite_eliminate(expr)
  Expr ite_eliminate(const Expr &expr) {
    if(expr->kind() == core::TermKind::Application) {
      auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(expr);
      if(app->function()->name() == "ite") {
        return (ite_eliminate(app->arguments()[0]) && ite_eliminate(app->arguments()[1])) ||
               (!ite_eliminate(app->arguments()[0]) && ite_eliminate(app->arguments()[2]));
      }
      return expr;
    }
    return expr;
  }

  //*-- eliminate_ite(expr)
  Expr eliminate_ite(const Expr &expr) {
    IteLifter e;
    return ite_eliminate(e.lift(expr));
  }

}
