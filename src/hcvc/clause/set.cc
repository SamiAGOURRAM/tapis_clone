//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/clause/set.hh"

#include <stack>

namespace hcvc {

  //*-- ClauseSet
  ClauseSet::ClauseSet() = default;

  ClauseSet::ClauseSet(const std::set<const Clause *> &clauses) {
    for(auto clause: clauses) {
      add(clause);
    }
  }

  ClauseSet::ClauseSet(const std::vector<const Clause *> &clauses) {
    for(auto clause: clauses) {
      add(clause);
    }
  }

  ClauseSet::~ClauseSet() = default;

  std::set<const Predicate *> ClauseSet::predicates() const {
    std::set<const Predicate *> predicates;
    for(auto pred_clauses_map: {&_antecedency, &_consequency}) {
      std::set<const Predicate *> to_forget;
      for(auto &[predicate, clauses]: *pred_clauses_map) {
        if(clauses.empty()) {
          to_forget.insert(predicate);
        } else {
          predicates.insert(predicate);
        }
      }
      for(auto predicate: to_forget) {
        pred_clauses_map->erase(predicate);
      }
    }
    return predicates;
  }

  void ClauseSet::add(const Clause *clause) {
    _clauses.insert(clause);
    for(auto &lhs_app: clause->antecedent_preds()) {
      auto casted = std::dynamic_pointer_cast<PredicateApplication>(lhs_app);
      _antecedency[casted->predicate()].insert(clause);
    }
    if(clause->consequent().has_value()) {
      auto casted = std::dynamic_pointer_cast<PredicateApplication>(*clause->consequent());
      _consequency[casted->predicate()].insert(clause);
    }
    if(clause->is_goal()) {
      _goal_clauses.insert(clause);
    } else if(clause->is_induction()) {
      _ind_clauses.insert(clause);
    } else if(clause->is_initiation()) {
      _init_clauses.insert(clause);
    }
  }

  void ClauseSet::add(const Clause *clause, Weakness weakness) {
    add(clause);
    _weakness_clause_map[weakness].insert(clause);
  }

  void ClauseSet::erase(const Clause *clause) {
    _clauses.erase(clause);
    for(auto &lhs_app: clause->antecedent_preds()) {
      auto casted = std::dynamic_pointer_cast<PredicateApplication>(lhs_app);
      _antecedency[casted->predicate()].erase(clause);
    }
    if(clause->consequent().has_value()) {
      auto casted = std::dynamic_pointer_cast<PredicateApplication>(*clause->consequent());
      _consequency[casted->predicate()].erase(clause);
    }
    _init_clauses.erase(clause);
    _goal_clauses.erase(clause);
    _goal_clauses.erase(clause);
  }

  ClauseSet ClauseSet::get_clauses(const std::set<Weakness> &weaknesses) const {
    std::set<const Clause *> clauses;
    std::stack<const Clause *> stack;
    for(auto weakness: weaknesses) {
      if(_weakness_clause_map.count(weakness) > 0) {
        for(auto clause: _weakness_clause_map.at(weakness)) {
          stack.push(clause);
        }
      }
    }
    while(!stack.empty()) {
      // pop
      auto clause = stack.top();
      stack.pop();
      // process
      if(clauses.count(clause) == 0) {
        clauses.insert(clause);
        for(auto &lhs_app: clause->antecedent_preds()) {
          auto casted = std::dynamic_pointer_cast<PredicateApplication>(lhs_app);
          for(auto c: _consequency[casted->predicate()]) {
            stack.push(c);
          }
        }
      }
    }
    return ClauseSet(clauses);
  }

}
