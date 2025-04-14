//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <stack>
#include "hcvc/logic/term.hh"

namespace hcvc {

  // Evaluator
  class Evaluator: public Visitor {
  public:
    explicit Evaluator(const std::map<Expr, Expr> &map);

    //*- methods

    Expr evaluate(const Expr &expr);

    void visit(std::shared_ptr<OperatorApplication> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<BooleanLiteral> term) override;

    void visit(std::shared_ptr<IntegerLiteral> term) override;

    void visit(std::shared_ptr<ArrayLiteral> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<PredicateApplication> term) override;

  private:
    inline Expr result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    inline void _return(Expr r) {
      _stack.emplace(std::move(r));
    }

    std::map<std::string, Expr> _var_map;
    std::stack<Expr> _stack;
  };

}
