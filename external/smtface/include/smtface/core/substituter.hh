//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <stack>
#include <tuple>
#include "smtface/core/term.hh"

namespace smtface::core {

  //*-- Substituter
  class Substituter: public Visitor {
  public:
    explicit Substituter(const std::map<Expr, Expr> &map, const std::map<const Function *, const Function *> &fmap);

    //*- methods

    Expr substitute(const Expr &expr);

    void visit(std::shared_ptr<ApplicationTerm> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<Null> term) override;

    void visit(std::shared_ptr<Value> term) override;

  private:
    std::tuple<bool, Expr> result();

    void _return(const std::tuple<bool, Expr> &r);

    std::map<std::string, Expr> _map;
    std::map<const Function *, const Function *> _fmap;
    std::stack<std::tuple<bool, Expr>> _stack;
  };

}
