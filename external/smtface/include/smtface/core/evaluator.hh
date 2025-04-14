//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <stack>
#include "smtface/core/term.hh"

namespace smtface::core {

  //*-- Evaluator
  class Evaluator: public Visitor {
  public:
    explicit Evaluator(std::map<Expr, std::variant<Expr, std::vector<Expr>>> map);

    //*- methods

    Expr evaluate(const Expr &expr);


    void visit(std::shared_ptr<ApplicationTerm> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<Null> term) override;

    void visit(std::shared_ptr<Value> term) override;

  private:
    Expr result();

    void _return(const Expr &r);

    std::map<Expr, std::variant<Expr, std::vector<Expr>>> _map;
    std::stack<Expr> _stack;
  };

}
