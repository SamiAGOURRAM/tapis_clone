//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <stack>
#include "hcvc/logic/term.hh"

namespace hcvc {

  // Substituter
  class Substituter: public Visitor {
  public:
    explicit Substituter(const std::map<Expr, Expr> &map);

    //*- methods

    Expr substitute(const Expr &expr);

    void visit(std::shared_ptr<OperatorApplication> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<BooleanLiteral> term) override;

    void visit(std::shared_ptr<IntegerLiteral> term) override;

    void visit(std::shared_ptr<ArrayLiteral> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<PredicateApplication> term) override;

  private:
    inline std::pair<bool, Expr> result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    inline void _return(std::pair<bool, Expr> r) {
      _stack.emplace(std::move(r));
    }

    std::map<std::string, Expr> _var_map;
    std::stack<std::pair<bool, Expr>> _stack;
  };

}
