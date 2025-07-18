//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "tapis/engines/hornice/learner.hh"
#include "tapis/engines/attributes/attribute.hh"
#include "tapis/engines/hornice/qdt/general_qdt/classifier.hh"
#include "tapis/engines/hornice/qdt/diagram.hh"
#include "tapis/engines/hornice/qdt/classifier.hh"
#include "tapis/engines/hornice/qdt/quantifier.hh"
#include "tapis/engines/hornice/qdt/aggregation.hh"
#include "tapis/engines/hornice/qdt/general_qdt/classifier.hh"
#include <memory>
#include <set>

namespace tapis::HornICE::qdt {

  class QuantifierManager;
  class AggregationManager;
  class DiagramManager;
  class Classifier;

  //*-- Learner
  class Learner: public tapis::HornICE::Learner {
  public:
    Learner(hcvc::Module *module, const hcvc::ClauseSet &clauses,
            QuantifierManager *quantifier_manager,
            AggregationManager *aggregation_manager,
            Classifier *classifier,
            bool quantify = true);
    
    ~Learner() override;

    //*- methods

    std::optional<std::unordered_map<const hcvc::Predicate *, LambdaDefinition>>
    synthesize(std::set<const hcvc::Implication *> counterexamples) override;

  private:
    bool _quantify;
    hcvc::PartialReachabilityGraph _set;
    DiagramPartialReachabilityGraph _diagram_set;
    std::set<const hcvc::Predicate *> _predicates;
    std::set<const hcvc::Implication *> _counterexamples;

    QuantifierManager* _quantifier_manager;
    AggregationManager* _aggregation_manager;
    Classifier* _classifier;

    DiagramManager _diagram_manager;
  };

}
