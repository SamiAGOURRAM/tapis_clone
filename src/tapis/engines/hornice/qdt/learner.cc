//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/qdt/learner.hh"

#include "hcvc/logic/smtface.hh"
#include "tapis/engines/options.hh"

namespace tapis::HornICE::qdt {

  //*-- Learner
  Learner::Learner(hcvc::Module *module, const hcvc::ClauseSet &clauses, QuantifierManager &quantifier_manager,
                   Classifier *classifier, bool quantify)
      : HornICE::Learner(module),
        _quantifier_manager(quantifier_manager),
        _diagram_manager(_quantifier_manager, module->context()),
        _quantify(quantify),
        _predicates(clauses.predicates()),
        _classifier(classifier) {}

  Learner::~Learner() = default;

  std::optional<std::unordered_map<const hcvc::Predicate *, LambdaDefinition>>
  Learner::synthesize(std::set<const hcvc::Implication *> counterexamples) {
    _counterexamples.insert(counterexamples.begin(), counterexamples.end());
    bool more_quantifier_variable = false;
    do {
      bool increase_quantifiers = false;
      for(const auto &counterexample: counterexamples) {
        if(!_set.add_implication(counterexample)) {
          return std::nullopt;
        }
        std::vector<const Diagram *> antecedents;
        std::vector<const Diagram *> consequents;
        for(auto state: counterexample->antecedents()) {
          auto &diagrams = _diagram_manager.get_diagrams(state);
          for(auto diagram: diagrams) {
            antecedents.push_back(diagram);
          }
        }
        if(counterexample->consequent() != nullptr) {
          auto &diagrams = _diagram_manager.get_diagrams(counterexample->consequent());
          for(auto diagram: diagrams) {
            consequents.push_back(diagram);
          }
        }
        if(!consequents.empty()) {
          for(auto consequent: consequents) {
            if(!_diagram_set.add_implication(antecedents, consequent)) {
              increase_quantifiers = true;
            }
          }
        } else {
          if(!_diagram_set.add_implication(antecedents, nullptr)) {
            increase_quantifiers = true;
          }
        }
        if(increase_quantifiers) {
          break;
        }
      }
      if(increase_quantifiers) {
        std::cout << "Number of quantifier variables incremented" << std::endl;
        more_quantifier_variable = true;
        _quantifier_manager.increase(1);
        _diagram_manager.clear();
        _diagram_set = DiagramPartialReachabilityGraph();
        _set = hcvc::PartialReachabilityGraph();
        counterexamples = _counterexamples;
      } else {
        break;
      }
    } while(true);

#ifndef NDEBUG
    std::cout << "Datapoints: " << _set.classifications().size() << " - Diagrams: "
              << _diagram_set.classifications().size() << "\n";
#endif

    if(more_quantifier_variable) {
      _classifier->resetup_attributes();
    }

    auto classifier_res = _classifier->classify(_diagram_set);
    if(!classifier_res.has_value()) {
      return std::nullopt;
    }

    auto solution = *classifier_res;
    std::unordered_map<const hcvc::Predicate *, LambdaDefinition> hypothesis;
#ifndef NDEBUG
    std::cout << "Learner.propose!" << "\n";
#endif
    for(auto &[predicate, formula]: solution) {
      hypothesis.emplace(predicate,
                         LambdaDefinition(predicate, _quantifier_manager.quantify(predicate, formula, !_quantify)));
#ifndef NDEBUG
      std::cout << "    -" << predicate->name() << ": " << hypothesis.at(predicate).body() << "\n";
#endif
    }
    return hypothesis;
  }

}
