//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/count_quantifier_depth.hh"

#include <iostream> // TODO:
#include <stack>

namespace smtface::utils {

  //*-- EPRizer
  class QuantifierCounter: public core::Visitor {
  public:
    //*- methods

    unsigned long count(const Expr &expr) {
      expr->accept(*this);
      auto res = result();
      return res;
    }

    void visit(std::shared_ptr<core::ApplicationTerm> term) override {
      unsigned long max = 0;
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
        auto r = result();
        max = std::max(max, r);
      }
      return _return(max);
    }

    void visit(std::shared_ptr<core::QuantifiedFormula> term) override {
      term->formula()->accept(*this);
      auto r = result();
      return _return(term->quantified_variables().size() + r);
    }

    void visit(std::shared_ptr<core::Constant> term) override {
      return _return(0);
    }

    void visit(std::shared_ptr<core::Null> term) override {
      return _return(0);
    }

    void visit(std::shared_ptr<core::Value> term) override {
      return _return(0);
    }

  private:
    unsigned long result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    void _return(unsigned long r) {
      _stack.push(r);
    }

    std::stack<unsigned long> _stack;
  };

  //*-- array_to_epr(expr)
  unsigned long count_quantifier_depth(const smtface::Expr &expr) {
    QuantifierCounter qcounter;
    return qcounter.count(expr);
  }

}
