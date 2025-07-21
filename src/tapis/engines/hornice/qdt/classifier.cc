//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/qdt/classifier.hh"

namespace tapis::HornICE::qdt {

  //*-- Classifier
  Classifier::Classifier(const hcvc::ClauseSet &clause_set,
                         std::set<const hcvc::Predicate *> predicates,
                         QuantifierManager &quantifier_manager, 
                         AggregationManager &aggregation_manager)
      : _clause_set(clause_set),
        _predicates(std::move(predicates)),
        _quantifier_manager(quantifier_manager), 
        _aggregation_manager(aggregation_manager) {}

  Classifier::~Classifier() = default;

}
