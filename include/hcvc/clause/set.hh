//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <unordered_map>
#include "hcvc/clause/clause.hh"
#include "hcvc/clause/predicate.hh"

namespace hcvc {

  //*-- ClauseSet
  class ClauseSet {
  public:
    ClauseSet();

    explicit ClauseSet(const std::set<const Clause *> &clauses);

    explicit ClauseSet(const std::vector<const Clause *> &clauses);

    virtual ~ClauseSet();

    //*- properties

    /// Get the goal clauses of this set.
    inline const std::set<const Clause *> &goal_clauses() const {
      return _goal_clauses;
    }

    /// Get the induction clauses of this set.
    inline const std::set<const Clause *> &induction_clauses() const {
      return _ind_clauses;
    }

    /// Get the initiation clauses of this set.
    inline const std::set<const Clause *> &init_clauses() const {
      return _init_clauses;
    }

    /// Get the set of predicates appearing in the clauses of the set.
    std::set<const Predicate *> predicates() const;

    //*- methods

    /// Add the given clause to the set.
    void add(const Clause *clause);

    /// Add the given clause as a clause for given weakness to the set.
    void add(const Clause *clause, Weakness weakness);

    /// Remove the given clause if it is in the set.
    void erase(const Clause *clause);

    /// Get clauses relevant to the verification of given weaknesses.
    ClauseSet get_clauses(const std::set<Weakness> &weaknesses) const;

    /// Get the clauses where given predicate in an antecedent.
    const std::set<const Clause *> &get_where_antecedent_is(const Predicate *predicate) const {
      return _antecedency.at(predicate);
    }

    /// Get the clauses where given predicate in the consequent.
    const std::set<const Clause *> &get_where_consequent_is(const Predicate *predicate) const {
      return _consequency.at(predicate);
    }

    /// Get the std::set of this.
    inline const std::set<const Clause *> &to_set() const {
      return _clauses;
    }

  protected:
    std::set<const Clause *> _clauses;

    std::set<const Clause *> _goal_clauses, _ind_clauses, _init_clauses;
    mutable std::unordered_map<const Predicate *, std::set<const Clause *>> _antecedency, _consequency;
    std::unordered_map<Weakness, std::set<const Clause *>> _weakness_clause_map;
  };

}
