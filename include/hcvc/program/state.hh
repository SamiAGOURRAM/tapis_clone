//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <list>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include "smtface/shorthands.hh"
#include "hcvc/clause/clause.hh"
#include "hcvc/clause/predicate.hh"

namespace hcvc {

  //*-- State
  class State {
  public:
    State(const Predicate *predicate, std::map<const Variable *, Expr> values, std::string hash);

    //*- properties

    inline const std::string &hash() const {
      return _hash;
    }

    inline const Predicate *predicate() const {
      return _predicate;
    }

    inline const std::map<const Variable *, Expr> &values() const {
      return _values;
    }

    //*- methods

    hcvc::Expr to_formula(Context &context) const;

  private:
    const Predicate *_predicate;
    std::map<const Variable *, Expr> _values;
    std::string _hash;
    mutable bool _formula_computed;
    mutable hcvc::Expr _formula;
  };

  //*-- Implication
  class Implication {
  public:
    Implication(const Clause *clause, std::vector<const State *> antecedents, const State *consequent);

    //*- properties

    inline const Clause *clause() const {
      return _clause;
    };

    inline std::vector<const State *> antecedents() const {
      return _antecedents;
    };

    inline const State *consequent() const {
      return _consequent;
    };

    inline bool is_goal() const {
      return _consequent == nullptr;
    }

    inline std::map<const Variable *, Expr> values() const {
      return _values;
    }

    inline void add_value(const Variable *var, Expr val) const {
      _values[var] = val;
    }

    inline void set_has_values() const {
      _has_values = true;
    }

    inline bool has_values() const {
      return _has_values;
    }

  private:
    const Clause *_clause;
    std::vector<const State *> _antecedents;
    const State *_consequent;
    mutable bool _has_values = false;
    mutable std::map<const Variable *, Expr> _values;
  };

  //*-- StateClass
  enum class StateClass: int {
    negative = -1,
    unknown = 0,
    positive = 1
  };

  //*-- HornForceResult
  typedef std::pair<std::list<const State *>, std::list<const State *>> HornForceResult;

  //*-- PartialReachabilityGraph
  class PartialReachabilityGraph {
  public:
    PartialReachabilityGraph();

    virtual ~PartialReachabilityGraph();

    //*- properties

    const std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &
    classifications() const {
      return _classifications;
    }

    //*- methods

    bool add_implication(const Implication *implication);

    bool add_implication(const std::vector<const State *> &antecedents, const State *consequent);

    bool horn_sat(const std::vector<const State *> &Statees, StateClass classification);

    HornForceResult horn_force(const std::vector<const State *> &States, StateClass classification);

    inline StateClass get_classification(const State *state) const {
      if(_classifications.count(state) > 0) {
        return _classifications.at(state).first;
      }
      return StateClass::unknown;
    }

  private:
    std::pair<bool, HornForceResult>
    _propagate_classification(const std::vector<const Implication *> &implications,
                              std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &target);

    std::pair<bool, HornForceResult>
    _propagate_classification(const std::vector<const Implication *> &implications);

    std::pair<bool, HornForceResult>
    _general_horn_force(const std::vector<const State *> &States, StateClass classification,
                        std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &target);


    void _add_state(const State *state);

    std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> _classifications;
    std::unordered_map<const Predicate *, std::set<const State *>> _states;
    std::unordered_map<const State *, std::set<const Implication *>> _in_impls;
    std::unordered_map<const State *, std::set<const Implication *>> _out_impls;

    std::set<const Implication *> _implications;
  };

  //*-- StateManager
  class StateManager: public PartialReachabilityGraph {
  public:
    StateManager();

    ~StateManager() override;

    //*- methods

    const State *get_state(const Predicate *predicate, const std::map<const Variable *, Expr> &values);

    const Implication *
    get_implication(const Clause *clause, std::vector<const State *> antecedents, const State *consequent);

  private:
    std::unordered_map<std::string, const State *> _states;
    std::unordered_map<std::string, const Implication *> _implications;
    std::unordered_map<const Predicate *, std::set<const State *>> _pred_states;
  };

}
