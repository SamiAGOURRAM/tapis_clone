//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/qdt/diagram.hh"

#include <stack>
#include <utility>
#include "hcvc/program/variable.hh"
#include "tapis/engines/options.hh"

namespace tapis::HornICE::qdt {

  //*-- Diagram
  Diagram::Diagram(const hcvc::Predicate *predicate, std::map<const hcvc::Variable *, hcvc::Expr> values,
                   std::string hash, z3::context &context)
      : _predicate(predicate),
        _values(std::move(values)),
        _hash(std::move(hash)),
        _constant(context.bool_const((std::string("!d!") + std::to_string(_dc++)).c_str())){}

  unsigned long Diagram::_dc = 0;

  //*-- DiagramManager
  DiagramManager::DiagramManager(tapis::HornICE::qdt::QuantifierManager &quantifier_manager, hcvc::Context &context)
      : _quantifier_manager(quantifier_manager),
        _context(context) {}

  const std::list<const Diagram *> &DiagramManager::get_diagrams(const hcvc::State *state) {
    std::set<const hcvc::Variable *> _skip_variables;
    for(auto var: state->predicate()->parameters()) {
      if(var->type()->is_array() && var->is_shadow()) {
        _skip_variables.insert(var);
      }
    }
    if(_state_diagrams.count(state) == 0) {
      bool has_array = false;
      for(auto &[var, _]: state->values()) {
        if(var->type()->is_array()) {
          has_array = true;
          break;
        }
      }
      if(has_array) {
        std::list<std::map<QuantifierInfo *, unsigned long>> combinations;
        std::map<QuantifierInfo *, unsigned long> max_sizes;
        // get each quantifier range 0..max_size
        for(auto qi: _quantifier_manager.quantifiers(state->predicate())) {
          max_sizes[qi] = std::stol(
              std::dynamic_pointer_cast<hcvc::IntegerLiteral>(state->values().at(qi->size_variable))->value());
        }
        // make combinations for each array's quantifiers
        std::map<hcvc::Variable *, std::list<std::map<QuantifierInfo *, unsigned long>>> array_combinations;
        for(auto parameter: state->predicate()->parameters()) {
          if(parameter->type()->is_array()) {
            if(_skip_variables.count(parameter) > 0) {
              if(get_options().ice.qdt.abstract_summary_input_arrays) {
                continue;
              }
            }
            std::list<std::map<QuantifierInfo *, unsigned long>> array_combination;
            for(unsigned long i = 0;
                i < _quantifier_manager._array_quantifiers[state->predicate()][parameter].size(); i++) {
              auto qi = _quantifier_manager._array_quantifiers[state->predicate()][parameter][i];
              if(i == 0) {
                for(unsigned long j = 0; j < max_sizes[qi]; j++) {
                  array_combination.emplace_back(std::map<QuantifierInfo *, unsigned long>({{qi, j}}));
                }
              } else {
                auto qi_1 = _quantifier_manager._array_quantifiers[state->predicate()][parameter][i - 1];
                std::list<std::map<QuantifierInfo *, unsigned long>> new_comp;
                for(auto comp: array_combination) {
                  for(unsigned long k = 0; k < max_sizes[qi]; k++) {
                    if(comp[qi_1] <= k) {
                      auto c = comp;
                      c[qi] = k;
                      new_comp.emplace_back(c);
                    }
                  }
                }
                array_combination = new_comp;
              }
            }
            array_combinations[parameter] = array_combination;
          }
        }
        // make the combinations
        unsigned long i = 0;
        for(const auto &[array, combs]: array_combinations) {
          if(i == 0 || combinations.empty()) {
            for(const auto &comb: combs) {
              combinations.push_back(comb);
            }
          } else {
            std::list<std::map<QuantifierInfo *, unsigned long>> new_comp;
            for(const auto &old: combinations) {
              for(const auto &comb: combs) {
                auto c = old;
                c.insert(comb.begin(), comb.end());
                new_comp.push_back(c);
              }
            }
            combinations = new_comp;
          }
          i++;
        }

        for(auto &comb: combinations) {
          auto values = state->values();
          for(unsigned long i = 0, sizei = _quantifier_manager.quantifiers(state->predicate()).size(); i < sizei; i++) {
            auto qi = _quantifier_manager.quantifiers(state->predicate())[i];
            values[qi->quantifier] = hcvc::IntegerLiteral::get(std::to_string(comb[qi]), qi->quantifier->type(),
                                                               _context);
            values[qi->accessor] = std::dynamic_pointer_cast<hcvc::ArrayLiteral>(
                state->values().at(qi->array))->values().at(comb[qi]);
          }
          auto diagram = _get_diagram(state->predicate(), values);
          _state_diagrams[state].push_back(diagram);
        }
        if(combinations.empty()) {
          std::cout << "IMPL-UNREACH" << "\n";
          exit(10);
        }
      } else {
        auto diagram = _get_diagram(state->predicate(), state->values());
        _state_diagrams[state].push_back(diagram);
      }
    }
    return _state_diagrams.at(state);
  }

  const Diagram *
  DiagramManager::_get_diagram(const hcvc::Predicate *predicate,
                               const std::map<const hcvc::Variable *, hcvc::Expr> &values) {
    std::string hash = "(" + predicate->name();
    std::map<const hcvc::Variable *, hcvc::Expr> diagram_values;
    for(const auto &[k, v]: values) {
      if(!k->type()->is_array()) {
        hash += "," + k->name() + "=" + hcvc::to_string(v);
        diagram_values[k] = v;
      }
    }
    hash += ")";
    // std::cout << hash << "\n";
    if(_diagrams.count(hash) == 0) {
      _diagrams[hash] = new Diagram(predicate, diagram_values, hash, _z3_ctx);
    }
    return _diagrams[hash];
  }

  void DiagramManager::clear() {
    _diagrams.clear();
    _state_diagrams.clear();
  }

  //*-- DiagramImplication
  DiagramImplication::DiagramImplication(std::vector<const Diagram *> antecedents,
                                         const Diagram *consequent)
      : _antecedents(std::move(antecedents)),
        _consequent(consequent) {}

  //*-- DiagramPartialReachabilityGraph
  bool DiagramPartialReachabilityGraph::add_implication(const DiagramImplication *implication) {
    for(auto &antecedent: implication->antecedents()) {
      _add_diagram(antecedent);
      _out_impls[antecedent].insert(implication);
    }
    if(implication->consequent() != nullptr) {
      _add_diagram(implication->consequent());
      _in_impls[implication->consequent()].insert(implication);
    }
    if(!implication->antecedents().empty() && implication->consequent() != nullptr) {
      _implications.insert(implication);
    }
    if(_propagate_classification({implication}).first) {
      return true;
    }
    return false;
  }

  bool DiagramPartialReachabilityGraph::add_implication(const std::vector<const Diagram *> &antecedents,
                                                        const Diagram *consequent) {
    auto implication = new DiagramImplication(antecedents, consequent);
    return add_implication(implication);
  }

  bool
  DiagramPartialReachabilityGraph::horn_sat(const std::vector<const Diagram *> &diagrams, DiagramClass classification) {
    std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> target(_classifications);
    return std::get<0>(_general_horn_force(diagrams, classification, target));
  }

  DiagramHornForceResult
  DiagramPartialReachabilityGraph::horn_force(const std::vector<const Diagram *> &diagrams,
                                              DiagramClass classification) {
    return std::get<1>(_general_horn_force(diagrams, classification, _classifications));
  }

  void DiagramPartialReachabilityGraph::_add_diagram(const Diagram *state) {
    if(_classifications.count(state) == 0) {
      _classifications[state] = std::make_pair(DiagramClass::unknown, std::vector<const Diagram *>());
    }
  }

  DiagramClass _get_classification(const Diagram *diagram,
                                   const std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &source) {
    if(source.count(diagram) > 0) {
      return source.at(diagram).first;
    }
    return DiagramClass::unknown;
  }

  bool _set_classification(const Diagram *diagram, DiagramClass classification,
                           const std::vector<const Diagram *> &affectors,
                           std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &target) {
    if(target.count(diagram) > 0 && target[diagram].first != DiagramClass::unknown &&
       target[diagram].first != classification) {
      return false;
    }
    target[diagram] = std::make_pair(classification, affectors);
    return true;
  }

  bool _is_positive(const std::vector<const Diagram *> &antecedents,
                    const std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &source) {
    return std::all_of(antecedents.begin(), antecedents.end(), [&](const Diagram *diagram) {
      return _get_classification(diagram, source) == DiagramClass::positive;
    });
  }

  bool _is_negative(const Diagram *consequent,
                    const std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &source) {
    return consequent == nullptr || _get_classification(consequent, source) == DiagramClass::negative;
  }

  std::pair<bool, DiagramHornForceResult>
  DiagramPartialReachabilityGraph::_propagate_classification(
      const std::vector<const DiagramImplication *> &implications,
      std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &target) {
    std::stack<const DiagramImplication *> working;
    std::list<const Diagram *> forced_pos;
    std::list<const Diagram *> forced_neg;
    for(auto implication: implications) {
      working.push(implication);
    }
    while(!working.empty()) {
      // fetch an implication
      auto implication = working.top();
      working.pop();
      // process
      std::list<const DiagramImplication *> todo;
      const auto &antecedents = implication->antecedents();
      auto consequent = implication->consequent();
      if(_is_positive(antecedents, target)) {
        if(_is_negative(consequent, target)) {
          return std::make_pair(false, DiagramHornForceResult());
        }
        auto old_class = _get_classification(consequent, target);
        if(old_class != DiagramClass::positive) {
          //auto class_kind = _get_classification_kind(implication->antecedents(), target);
          _set_classification(consequent, DiagramClass::positive, implication->antecedents(), target);
          forced_pos.push_back(consequent);
          std::vector<std::set<const DiagramImplication *> *> sources{
              &_out_impls[consequent],
          };
          for(auto source: sources) {
            todo.insert(todo.end(), source->begin(), source->end());
          }
        }
      } else if(_is_negative(consequent, target)) {
        if(_is_positive(antecedents, target)) {
          return std::make_pair(false, DiagramHornForceResult());
        }
        std::vector<const Diagram *> unknowns;
        for(auto state: antecedents) {
          if(_get_classification(state, target) == DiagramClass::negative) {
            unknowns.clear();
            break;
          } else if(_get_classification(state, target) == DiagramClass::unknown) {
            unknowns.push_back(state);
          }
        }
        if(unknowns.size() == 1) {
          if(!implication->is_goal()) {
            std::vector<const Diagram *> others(antecedents);
            others.erase(std::remove(others.begin(), others.end(), unknowns[0]), others.end());
            others.push_back(consequent);
          }
          std::vector<const Diagram *> affectors;
          for(auto affector: affectors) {
            if(affector != unknowns[0]) {
              affectors.push_back(affector);
            }
          }
          if(consequent != nullptr && consequent != unknowns[0]) {
            affectors.push_back(consequent);
          }
          _set_classification(unknowns[0], DiagramClass::negative, affectors, target);
          forced_neg.push_back(unknowns[0]);
          std::vector<std::set<const DiagramImplication *> *> sources{
              &_in_impls[unknowns[0]],
          };
          for(auto source: sources) {
            todo.insert(todo.end(), source->begin(), source->end());
          }
        }
      }
      for(auto item: todo) {
        working.push(item);
      }
    }
    return std::make_pair(true, std::make_pair(forced_pos, forced_neg));
  }

  std::pair<bool, DiagramHornForceResult>
  DiagramPartialReachabilityGraph::_propagate_classification(
      const std::vector<const DiagramImplication *> &implications) {
    return _propagate_classification(implications, _classifications);
  }

  std::pair<bool, DiagramHornForceResult>
  DiagramPartialReachabilityGraph::_general_horn_force(const std::vector<const Diagram *> &diagrams,
                                                       DiagramClass classification,
                                                       std::unordered_map<const Diagram *, std::pair<DiagramClass, std::vector<const Diagram *>>> &target) {
    std::vector<const DiagramImplication *> implications;
    for(auto state: diagrams) {
      if(!_set_classification(state, classification, {}, target)) {
        return std::make_pair(false, DiagramHornForceResult());
      }
      std::vector<std::set<const DiagramImplication *> *> sources;
      if(classification == DiagramClass::positive) {
        sources.push_back(&_out_impls[state]);
      } else if(classification == DiagramClass::negative) {
        sources.push_back(&_in_impls[state]);
      }
      for(auto source: sources) {
        implications.insert(implications.end(), source->begin(), source->end());
      }
    }
    return _propagate_classification(implications, target);
  }

}
