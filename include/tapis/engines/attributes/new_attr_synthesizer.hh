//
// Copyright (c) 2025 Wael-Amine Boutglay
//

#pragma once

#include "attribute.hh"
#include "enumerator.hh"

namespace tapis::HornICE::qdt {

  //*-- NewAttributeSynthesizer
  class NewAttributeSynthesizer: public AttributeSynthesizer {
  public:
    inline explicit NewAttributeSynthesizer(QuantifierManager& quantifier_manager, 
                         AggregationManager& aggregation_manager)
      : _quantifier_manager(quantifier_manager),
        _aggregation_manager(aggregation_manager) {}

    ~NewAttributeSynthesizer() override;

    //*- methods

    void set_predicate(const std::set<const hcvc::Predicate *> &predicates) override;

    void setup() override;

    std::pair<std::set<const Attribute *>, std::set<const Attribute *>>
    attributes(const hcvc::Predicate *predicate) const override;

    bool generate_attributes(DiagramPartialReachabilityGraph *sample) override;

  private:
    std::set<const hcvc::Predicate *> _predicates;
    std::map<const hcvc::Predicate *, std::set<const Attribute *>> _init_index_attributes;
    std::map<const hcvc::Predicate *, std::set<const Attribute *>> _init_data_attributes;
    std::map<const hcvc::Predicate *, std::vector<Enumerator *>> _index_enumerators;
    std::map<const hcvc::Predicate *, std::vector<Enumerator *>> _data_enumerators;
    QuantifierManager &_quantifier_manager;
    AggregationManager& _aggregation_manager;  // Add this member

  };

}
