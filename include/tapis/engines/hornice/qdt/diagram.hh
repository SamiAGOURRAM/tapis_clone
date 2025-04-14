//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "z3++.h"
#include "hcvc/clause/predicate.hh"
#include "hcvc/program/state.hh"
#include "tapis/engines/hornice/qdt/quantifier.hh"

namespace tapis::HornICE::qdt {

  //*-- Diagram
  class Diagram {
  public:
    Diagram(const hcvc::Predicate *predicate, std::map<const hcvc::Variable *, hcvc::Expr> values, std::string hash, z3::context &context);

    //*- properties

    inline const std::string &hash() const {
      return _hash;
    }

    inline const hcvc::Predicate *predicate() const {
      return _predicate;
    }

    inline const std::map<const hcvc::Variable *, hcvc::Expr> &values() const {
      return _values;
    }

    inline const z3::expr &get_const() const {
      return _constant;
    }

  private:
    const hcvc::Predicate *_predicate;
    std::map<const hcvc::Variable *, hcvc::Expr> _values;
    std::string _hash;
    z3::expr _constant;
    static unsigned long _dc;
  };

  //*-- DiagramManager
  class DiagramManager {
  public:
    DiagramManager(QuantifierManager &quantifier_manager, hcvc::Context &context);

    //*- methods

    const std::list<const Diagram *> &get_diagrams(const hcvc::State *state);

    const Diagram *
    _get_diagram(const hcvc::Predicate *predicate, const std::map<const hcvc::Variable *, hcvc::Expr> &values);

    void clear();

  private:
    hcvc::Context &_context;
    tapis::HornICE::qdt::QuantifierManager &_quantifier_manager;
    std::map<std::string, const Diagram *> _diagrams;
    std::map<const hcvc::State *, std::list<const Diagram *>> _state_diagrams;
    z3::context _z3_ctx;
  };

  //*-- DiagramClass
  enum class DiagramClass: int {
    negative = -1,
    unknown = 0,
    positive = 1
  };

  //*-- DiagramImplication
  class DiagramImplication {
  public:
    DiagramImplication(std::vector<const Diagram *> antecedents, const Diagram *consequent);

    //*- properties

    const std::vector<const Diagram *> &antecedents() const {
      return _antecedents;
    }

    const Diagram *consequent() const {
      return _consequent;
    }

    inline bool is_goal() const {
      return _consequent == nullptr;
    }

    inline bool is_fact() const {
      return _antecedents.empty();
    }

  private:
    std::vector<const Diagram *> _antecedents;
    const Diagram *_consequent;
  };

  //*-- DiagramHornForceResult
  typedef std::pair<std::list<const Diagram *>, std::list<const Diagram *>> DiagramHornForceResult;

  //*-- DiagramPartialReachabilityGraph
  class DiagramPartialReachabilityGraph {
  public:
    //*- properties

    const std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &
    classifications() const {
      return _classifications;
    }

    //*- methods

    bool add_implication(const DiagramImplication *implication);

    bool add_implication(const std::vector<const Diagram *> &antecedents, const Diagram *consequent);

    bool horn_sat(const std::vector<const Diagram *> &Statees, DiagramClass classification);

    DiagramHornForceResult horn_force(const std::vector<const Diagram *> &States, DiagramClass classification);

    inline DiagramClass get_classification(const Diagram *state) const {
      if(_classifications.count(state) > 0) {
        return _classifications.at(state).first;
      }
      return DiagramClass::unknown;
    }

    inline const std::set<const DiagramImplication *> &implications() const {
      return _implications;
    }

  private:
    std::pair<bool, DiagramHornForceResult>
    _propagate_classification(const std::vector<const DiagramImplication *> &implications,
                              std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &target);

    std::pair<bool, DiagramHornForceResult>
    _propagate_classification(const std::vector<const DiagramImplication *> &implications);

    std::pair<bool, DiagramHornForceResult>
    _general_horn_force(const std::vector<const Diagram *> &States, DiagramClass classification,
                        std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &target);


    void _add_diagram(const Diagram *state);

    std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> _classifications;
    std::unordered_map<const hcvc::Predicate *, std::set<const Diagram *>> _states;
    std::unordered_map<const Diagram *, std::set<const DiagramImplication *>> _in_impls;
    std::unordered_map<const Diagram *, std::set<const DiagramImplication *>> _out_impls;

    std::set<const DiagramImplication *> _implications;
  };

}
