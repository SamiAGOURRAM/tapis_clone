//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <optional>
#include <set>
#include <vector>
#include "hcvc/context.hh"
#include "hcvc/clause/predicate.hh"
#include "hcvc/clause/weakness.hh"
#include "hcvc/logic/term.hh"

namespace hcvc {

  class HyperGraph;

  //*-- Clause
  class Clause {
  public:
    Clause(std::vector<Expr> antcedent_preds, std::vector<Expr> phi, std::optional<Expr> consequent, Context &context);

    //*- properties

    inline Context &context() const {
      return _context;
    }

    inline const std::vector<Expr> &antecedent_preds() const {
      return _antecedent_preds;
    }

    inline const std::vector<Expr> &phi() const {
      return _phi;
    }

    inline Expr phi_expr() const {
      if(_phi.empty()) {
        return _context.get_true();
      }
      return _context.apply("and", _phi);
    }

    inline const std::optional<Expr> &consequent() const {
      return _consequent;
    }

    /// Determine whether this is a goal clause.
    inline bool is_goal() const {
      return !_consequent.has_value();
    }

    /// Determine whether this is an induction clause.
    inline bool is_induction() const {
      return !is_goal() && !is_initiation();
    }

    /// Determine whether this is an initiation clause.
    inline bool is_initiation() const {
      return _antecedent_preds.empty();
    }

    void dump() const;

    Expr to_formula() const;

  private:
    Context &_context;
    std::vector<Expr> _antecedent_preds;
    std::vector<Expr> _phi;
    std::optional<Expr> _consequent;
  };

}
