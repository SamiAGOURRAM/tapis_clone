//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/clause/clause.hh"

#include <iostream>
#include <memory>
#include <utility>
#include "hcvc/context.hh"
#include "hcvc/program/function.hh"
#include "hcvc/program/variable.hh"

namespace hcvc {

  //*-- Clause
  Clause::Clause(std::vector<Expr> antecedent_preds, std::vector<Expr> phi, std::optional<Expr> consequent,
                 Context &context)
      : _antecedent_preds(std::move(antecedent_preds)),
        _phi(std::move(phi)),
        _consequent(std::move(consequent)),
        _context(context) {}

  void Clause::dump() const {
    auto clause = this;
    std::vector<Expr> el = clause->antecedent_preds();
    el.insert(el.end(), clause->phi().begin(), clause->phi().end());
    std::cout << _context.apply("and", el) << " => ";
    if(clause->consequent()) {
      std::cout << *clause->consequent() << "\n";
    } else {
      std::cout << "⊥" << "\n";
    }
  }

  Expr Clause::to_formula() const {
    Expr res = _context.apply("and", _phi);
    for(const auto &d: _antecedent_preds) {
      res = res && d;
    }
    Expr g = _context.get_false();
    if(_consequent) {
      g = *_consequent;
    }
    return _context.apply("=>", {res, g});
  }

}
