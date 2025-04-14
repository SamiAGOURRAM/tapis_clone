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
#include "tapis/engines/hornice/qdt/general_qdt/classifier.hh"

namespace tapis::HornICE::qdt {

  //*-- Learner
  class Learner: public tapis::HornICE::Learner {
  public:
    Learner(hcvc::Module *module, const hcvc::ClauseSet &clauses, QuantifierManager &quantifier_manager,
            Classifier *classifier, bool quantify = true);

    ~Learner() override;

    //*- methods

    std::optional<std::unordered_map<const hcvc::Predicate *, LambdaDefinition>>
    synthesize(std::set<const hcvc::Implication *> counterexamples) override;

  private:
    bool _quantify;
    hcvc::PartialReachabilityGraph _set;
    DiagramPartialReachabilityGraph _diagram_set;
    std::set<const hcvc::Predicate *> _predicates;
    QuantifierManager &_quantifier_manager;
    DiagramManager _diagram_manager;

    std::set<const hcvc::Implication *> _counterexamples;

    Classifier *_classifier;
  };

}
