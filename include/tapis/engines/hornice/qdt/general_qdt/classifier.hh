//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/clause/set.hh"
#include "tapis/engines/attributes/attribute.hh"
#include "tapis/engines/hornice/qdt/diagram.hh"
#include "tapis/engines/hornice/qdt/classifier.hh"

namespace tapis::HornICE::qdt::GeneralQDT {

  //*-- Classifier
  class Classifier: public qdt::Classifier {
  public:
    Classifier(const hcvc::ClauseSet &clause_set, std::set<const hcvc::Predicate *> predicates,
               QuantifierManager &quantifier_manager, AggregationManager &aggregation_manager);

    ~Classifier() override;

    //*- methods

    void resetup_attributes() override;

    std::optional<std::unordered_map<const hcvc::Predicate *, hcvc::Expr>>
    classify(const DiagramPartialReachabilityGraph &diag_set) override;

    bool are_attributes_sufficient();

    double
    gain(const Attribute *attribute, const std::list<const Diagram *> &pos, const std::list<const Diagram *> &neg,
         const std::vector<const Diagram *> &unclass);

  private:
    AttributeSynthesizer *_attr_synthesizer;
    DiagramPartialReachabilityGraph *_working_set;
    AggregationManager& _aggregation_manager;  // Add this member

  };

}
