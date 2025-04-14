//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/program/state.hh"

#include <stack>
#include <utility>
#include "hcvc/program/variable.hh"
#include "hcvc/logic/term.hh"
#include "tapis/engines/options.hh"

namespace hcvc {

  //*-- State
  State::State(const hcvc::Predicate *predicate, std::map<const Variable *, Expr> values, std::string hash)
      : _predicate(predicate),
        _values(std::move(values)),
        _hash(std::move(hash)),
        _formula_computed(false) {}

  hcvc::Expr State::to_formula(Context &context) const {
    if(!_formula_computed) {
      auto formula = context.get_true();
      for(auto [variable, value]: _values) {
        if(value->type()->is_array()) {
          auto array = std::dynamic_pointer_cast<ArrayLiteral>(value);
          auto elem_sort = dynamic_cast<const ArrayType *>(array->type())->element_type();
          auto var = VariableConstant::create(variable, 0, context);
          for(unsigned long i = 0; i < array->values().size(); i++) {
            formula = formula &&
                      context.apply("[]", {var, IntegerLiteral::get(std::to_string(((long) i)), elem_sort, context)}) ==
                      array->values()[i];
          }
        } else {
          formula = formula && (VariableConstant::create(variable, 0, context) == value);
        }
      }
      _formula = formula;
      _formula_computed = true;
    }
    return _formula;
  }

  //*-- Implication
  Implication::Implication(const hcvc::Clause *clause, std::vector<const State *> antecedents,
                           const hcvc::State *consequent)
      : _clause(clause),
        _antecedents(std::move(antecedents)),
        _consequent(consequent) {}

  //*-- PartialReachabilityGraph
  PartialReachabilityGraph::PartialReachabilityGraph() = default;

  PartialReachabilityGraph::~PartialReachabilityGraph() = default;

  bool PartialReachabilityGraph::add_implication(const hcvc::Implication *implication) {
    for(auto &antecedent: implication->antecedents()) {
      _add_state(antecedent);
      _out_impls[antecedent].insert(implication);
    }
    if(implication->consequent() != nullptr) {
      _add_state(implication->consequent());
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

  bool PartialReachabilityGraph::add_implication(const std::vector<const State *> &antecedents,
                                                 const hcvc::State *consequent) {
    auto implication = new Implication(nullptr, antecedents, consequent);
    return add_implication(implication);
  }

  bool PartialReachabilityGraph::horn_sat(const std::vector<const State *> &states, StateClass classification) {
    std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> target(_classifications);
    return std::get<0>(_general_horn_force(states, classification, target));
  }

  HornForceResult
  PartialReachabilityGraph::horn_force(const std::vector<const State *> &states, StateClass classification) {
    return std::get<1>(_general_horn_force(states, classification, _classifications));
  }

  void PartialReachabilityGraph::_add_state(const hcvc::State *state) {
    if(_classifications.count(state) == 0) {
      _classifications[state] = std::make_pair(StateClass::unknown, std::vector<const State *>());
    }
  }

  StateClass _get_classification(const State *state,
                                 const std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &source) {
    if(source.count(state) > 0) {
      return source.at(state).first;
    }
    return StateClass::unknown;
  }

  bool _set_classification(const State *state, StateClass classification,
                           const std::vector<const State *> &affectors,
                           std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &target) {
    if(target.count(state) > 0 && target[state].first != StateClass::unknown &&
       target[state].first != classification) {
      return false;
    }
    target[state] = std::make_pair(classification, affectors);
    return true;
  }

  bool _is_positive(const std::vector<const State *> &antecedents,
                    const std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &source) {
    return std::all_of(antecedents.begin(), antecedents.end(), [&](const State *state) {
      return _get_classification(state, source) == StateClass::positive;
    });
  }

  bool _is_negative(const State *consequent,
                    const std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &source) {
    return consequent == nullptr || _get_classification(consequent, source) == StateClass::negative;
  }

  std::pair<bool, HornForceResult>
  PartialReachabilityGraph::_propagate_classification(const std::vector<const Implication *> &implications,
                                                      std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &target) {
    std::stack<const Implication *> working;
    std::list<const State *> forced_pos;
    std::list<const State *> forced_neg;
    for(auto implication: implications) {
      working.push(implication);
    }
    while(!working.empty()) {
      // fetch an implication
      auto implication = working.top();
      working.pop();
      // process
      std::list<const Implication *> todo;
      const auto &antecedents = implication->antecedents();
      auto consequent = implication->consequent();
      if(_is_positive(antecedents, target)) {
        if(_is_negative(consequent, target)) {
          return std::make_pair(false, HornForceResult());
        }
        auto old_class = _get_classification(consequent, target);
        if(old_class != StateClass::positive) {
          //auto class_kind = _get_classification_kind(implication->antecedents(), target);
          _set_classification(consequent, StateClass::positive, implication->antecedents(), target);
          /*if(implication->antecedents().size() > 0) {
            std::cout << consequent->hash() << "+<:";
            for(auto s : implication->antecedents()) {
              std::cout << s->hash() << "-";
            }
            std::cout << ";\n";
          }*/
          forced_pos.push_back(consequent);
          std::vector<std::set<const Implication *> *> sources{
              &_out_impls[consequent],
              //&_state_implications[consequent].second,
          };
          for(auto source: sources) {
            todo.insert(todo.end(), source->begin(), source->end());
          }
        }
      } else if(_is_negative(consequent, target)) {
        if(_is_positive(antecedents, target)) {
          return std::make_pair(false, HornForceResult());
        }
        std::vector<const State *> unknowns;
        for(auto state: antecedents) {
          if(_get_classification(state, target) == StateClass::negative) {
            unknowns.clear();
            break;
          } else if(_get_classification(state, target) == StateClass::unknown) {
            unknowns.push_back(state);
          }
        }
        if(unknowns.size() == 1) {
          if(!implication->is_goal()) {
            std::vector<const State *> others(antecedents);
            others.erase(std::remove(others.begin(), others.end(), unknowns[0]), others.end());
            others.push_back(consequent);
            //class_kind = _get_classification_kind(others, target);
          }
          std::vector<const State *> affectors;
          for(auto affector: affectors) {
            if(affector != unknowns[0]) {
              affectors.push_back(affector);
            }
          }
          if(consequent != nullptr && consequent != unknowns[0]) {
            affectors.push_back(consequent);
          }
          _set_classification(unknowns[0], StateClass::negative, affectors, target);
          forced_neg.push_back(unknowns[0]);
          std::vector<std::set<const Implication *> *> sources{
              //&_state_implications[unknowns[0]].first,
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

  std::pair<bool, HornForceResult>
  PartialReachabilityGraph::_propagate_classification(const std::vector<const Implication *> &implications) {
    return _propagate_classification(implications, _classifications);
  }

  std::pair<bool, HornForceResult>
  PartialReachabilityGraph::_general_horn_force(const std::vector<const State *> &states, StateClass classification,
                                                std::unordered_map<const State *, std::pair<StateClass, std::vector<const State *>>> &target) {
    std::vector<const Implication *> implications;
    for(auto state: states) {
      if(!_set_classification(state, classification, {}, target)) {
        return std::make_pair(false, HornForceResult());
      }
      std::vector<std::set<const Implication *> *> sources;
      if(classification == StateClass::positive) {
        sources.push_back(&_out_impls[state]);
      } else if(classification == StateClass::negative) {
        sources.push_back(&_in_impls[state]);
      }
      for(auto source: sources) {
        implications.insert(implications.end(), source->begin(), source->end());
      }
    }
    return _propagate_classification(implications, target);
  }

  //*-- StateManager
  StateManager::StateManager() = default;

  StateManager::~StateManager() {
    for(auto [_, implication]: _implications) {
      delete implication;
    }
    for(auto &[_, state]: _states) {
      delete state;
    }
  }

  const State *
  StateManager::get_state(const hcvc::Predicate *predicate, const std::map<const Variable *, Expr> &values) {
    std::string hash = "(" + predicate->name();
    for(const auto &[key, value]: values) {
      hash += ", " + key->name() + "=" + hcvc::to_string(value);
    }
    hash += ")";
    if(_states.count(hash) == 0) {
      auto state = new State(predicate, values, hash);
      _states[hash] = state;
      _pred_states[predicate].insert(state);
      return state;
    }
    return _states[hash];
  }

  const Implication *StateManager::get_implication(const hcvc::Clause *clause, std::vector<const State *> antecedents,
                                                   const hcvc::State *consequent) {
    std::sort(antecedents.begin(), antecedents.end(), [&](const State *a, const State *b) {
      return a->hash().compare(b->hash());
    });
    std::string hash;
    for(const auto &state: antecedents) {
      hash += state->hash();
    }
    hash += "=>";
    if(consequent != nullptr) {
      hash += consequent->hash();
    }
    if(_implications.count(hash) == 0) {
      _implications[hash] = new Implication(clause, antecedents, consequent);
    }
    add_implication(_implications[hash]);
    return _implications[hash];
  }

}
