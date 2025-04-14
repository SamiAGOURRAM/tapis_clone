//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/qdt/general_qdt/classifier.hh"

#include <cassert>
#include <cmath>
#include <utility>
#include "rope.hh"
#include "tapis/engines/options.hh"
#include "tapis/engines/attributes/enumerator.hh"
#include "tapis/engines/attributes/new_attr_synthesizer.hh"

namespace tapis::HornICE::qdt::GeneralQDT {

  //*-- Classifier
  Classifier::Classifier(const hcvc::ClauseSet &clause_set,
                         std::set<const hcvc::Predicate *> predicates,
                         QuantifierManager &quantifier_manager)
      : qdt::Classifier(clause_set, std::move(predicates), quantifier_manager),
        _working_set(nullptr) {
    _attr_synthesizer = new NewAttributeSynthesizer(this->quantifier_manager());
    _attr_synthesizer->set_context(&this->quantifier_manager().context());
    _attr_synthesizer->set_predicate(this->predicates());
    _attr_synthesizer->set_manager(new AttributeManager());
    _attr_synthesizer->setup();
  }

  Classifier::~Classifier() {
    delete _working_set;
  }

  class DTNode {
  public:
    explicit DTNode(hcvc::Context &context) : _context(context) {}

    const hcvc::Predicate *predicate;
    DiagramClass label = DiagramClass::unknown;
    const Attribute *attribute = nullptr;
    std::list<const Diagram *> pos;
    std::list<const Diagram *> neg;
    std::vector<const Diagram *> unclass;
    DTNode *left = nullptr;
    DTNode *right = nullptr;
    std::pair<std::list<const Attribute *>, std::list<const Attribute *>> attributes;
    hcvc::Context &_context;

    hcvc::Expr to_formula() {
      if(label == DiagramClass::positive) {
        return _context.get_true();
      } else if(label == DiagramClass::negative) {
        return _context.get_false();
      } else {
        return (attribute->constraint() && left->to_formula()) ||
               (!attribute->constraint() && right->to_formula());
      }
    }
  };

  void Classifier::resetup_attributes() {
    delete _attr_synthesizer;
    _attr_synthesizer = new NewAttributeSynthesizer(this->quantifier_manager());
    _attr_synthesizer->set_context(&this->quantifier_manager().context());
    _attr_synthesizer->set_predicate(this->predicates());
    _attr_synthesizer->set_manager(new AttributeManager());
    _attr_synthesizer->setup();
  }

  std::optional<std::unordered_map<const hcvc::Predicate *, hcvc::Expr>>
  Classifier::classify(const tapis::HornICE::qdt::DiagramPartialReachabilityGraph &diag_set) {
    delete _working_set;
    _working_set = new DiagramPartialReachabilityGraph(diag_set);

    // check if attributes are sufficient for classification and generate more otherwise
    while(!are_attributes_sufficient()) {
      //std::cout << "Call Attribute Synthesizer\n";
      delete _working_set;
      _working_set = new DiagramPartialReachabilityGraph(diag_set);
      if(!_attr_synthesizer->generate_attributes(_working_set)) {
        return std::nullopt;
      }
    }
    //}

    // create a root tree for each predicate and prepare data
    std::map<const hcvc::Predicate *, DTNode *> roots;
    for(auto predicate: this->predicates()) {
      roots[predicate] = new DTNode(this->quantifier_manager().context());
      roots[predicate]->predicate = predicate;
      auto attributes = _attr_synthesizer->attributes(predicate);
      roots[predicate]->attributes = std::make_pair(
          std::list<const Attribute *>(attributes.first.begin(),
                                       attributes.first.end()),
          std::list<const Attribute *>(attributes.second.begin(),
                                       attributes.second.end()));
    }
    for(const auto &[diagram, p]: _working_set->classifications()) {
      if(p.first == DiagramClass::positive) {
        roots[diagram->predicate()]->pos.push_back(diagram);
      } else if(p.first == DiagramClass::negative) {
        roots[diagram->predicate()]->neg.push_back(diagram);
      } else {
        roots[diagram->predicate()]->unclass.push_back(diagram);
      }
    }

    // put the root to the working stack
    std::vector<DTNode *> leaves;
    for(auto [_, root]: roots) {
      leaves.push_back(root);
    }

    // learn the trees
    while(!leaves.empty()) {
      for(unsigned long i = 0; i < leaves.size(); i++) {
        auto leaf = leaves[i];
        for(unsigned long j = 0; j < leaf->unclass.size(); j++) {
          auto diagram = leaf->unclass[j];
          if(_working_set->get_classification(diagram) == DiagramClass::positive) {
            leaf->pos.push_back(diagram);
            leaf->unclass.erase(leaf->unclass.begin() + j);
            j--;
          } else if(_working_set->get_classification(diagram) == DiagramClass::negative) {
            leaf->neg.push_back(diagram);
            leaf->unclass.erase(leaf->unclass.begin() + j);
            j--;
          }
        }

        if(leaf->unclass.empty()) {
          if(leaf->neg.empty()) {
            leaf->label = DiagramClass::positive;
            leaves.erase(leaves.begin() + i);
            i--;
            continue;
          } else if(leaf->pos.empty()) {
            leaf->label = DiagramClass::negative;
            leaves.erase(leaves.begin() + i);
            i--;
            continue;
          }
        }

        if(leaf->neg.empty()) {
          if(_working_set->horn_sat(leaf->unclass, DiagramClass::positive)) {
            _working_set->horn_force(leaf->unclass, DiagramClass::positive);
          }
        }
        if(leaf->pos.empty()) {
          if(_working_set->horn_sat(leaf->unclass, DiagramClass::negative)) {
            _working_set->horn_force(leaf->unclass, DiagramClass::negative);
          }
        }
        if(true) {
          //assert(!leaf->attributes.first.empty() || !leaf->attributes.second.empty());
          const Attribute *attribute = nullptr;
          double attribute_gain = 0;
          if(!leaf->attributes.first.empty()) {
            attribute = *leaf->attributes.first.begin();
          } else {
            attribute = *leaf->attributes.second.begin();
          }
          for(auto attr: rope::add(leaf->attributes.first, leaf->attributes.second)) {
            auto ig = gain(attr, leaf->pos, leaf->neg, leaf->unclass);
            if(ig > attribute_gain || (ig == attribute_gain && attr->_level >= attribute->_level)) {
              attribute_gain = ig;
              attribute = attr;
              if(attribute_gain == 1) {
                break;
              }
            }
          }

          if(attribute == nullptr) {
            leaf->label = DiagramClass::negative;
            if(_working_set->horn_sat(leaf->unclass, DiagramClass::negative)) {
              _working_set->horn_force(leaf->unclass, DiagramClass::negative);
            }
            continue;
          }

          leaf->attributes.first.remove(attribute);
          leaf->attributes.second.remove(attribute);

          auto L = new DTNode(leaf->_context);
          auto R = new DTNode(leaf->_context);
          L->predicate = leaf->predicate;
          R->predicate = leaf->predicate;
          leaf->attribute = attribute;
          leaf->left = L;
          leaf->right = R;
          L->attributes = leaf->attributes;
          R->attributes = leaf->attributes;
          std::list<const hcvc::State *> sat_pos, sat_neg, sat_unclass;
          std::list<const hcvc::State *> unsat_pos, unsat_neg, unsat_unclass;
          for(auto diagram: leaf->pos) {
            if(attribute->satisfied_by(diagram)) {
              L->pos.push_back(diagram);
            } else {
              R->pos.push_back(diagram);
            }
          }
          for(auto diagram: leaf->neg) {
            if(attribute->satisfied_by(diagram)) {
              L->neg.push_back(diagram);
            } else {
              R->neg.push_back(diagram);
            }
          }
          for(auto diagram: leaf->unclass) {
            if(attribute->satisfied_by(diagram)) {
              L->unclass.push_back(diagram);
            } else {
              R->unclass.push_back(diagram);
            }
          }

          leaves.erase(leaves.begin() + i);
          leaves.push_back(L);
          leaves.push_back(R);
          i--;
        }
      }
    }

    std::unordered_map<const hcvc::Predicate *, hcvc::Expr> solution;
#ifndef NDEBUG
    std::cout << "Classifier.learn!" << "\n";
#endif
    for(auto [predicate, leaf]: roots) {
      solution.emplace(predicate, leaf->to_formula());
#ifndef NDEBUG
      std::cout << "    -" << predicate->name() << ": " << solution.at(predicate) << "\n";
#endif
    }
    return solution;
  }

  bool Classifier::are_attributes_sufficient() {
    for(auto predicate: this->predicates()) {
      std::map<std::vector<bool>, std::vector<const Diagram *>> eq_classes;
      auto attributes = _attr_synthesizer->attributes(predicate);
      for(auto &[diagram, _]: _working_set->classifications()) {
        if(diagram->predicate() == predicate) {
          std::vector<bool> eq_class;
          eq_class.reserve(attributes.first.size() + attributes.second.size());
          for(auto attr: rope::add(attributes.first, attributes.second)) {
            if(attr->satisfied_by(diagram)) {
              eq_class.push_back(true);
            } else {
              eq_class.push_back(false);
            }
          }
          eq_classes[eq_class].push_back(diagram);
        }
      }

      for(auto &[key, value]: eq_classes) {
        auto classification = DiagramClass::unknown;
        for(auto diagram: value) {
          auto sc = _working_set->get_classification(diagram);
          if(classification != DiagramClass::unknown && sc != DiagramClass::unknown && classification != sc) {
#ifndef NDEBUG
            for(auto &diagram1: value) {
              std::cout << diagram1->hash() << " - " << (int) _working_set->get_classification(diagram1) << "\n";
            }
#endif
            return false;
          }
          if(sc != DiagramClass::unknown) {
            classification = sc;
          }
        }
        if(classification != DiagramClass::unknown) {
          if(_working_set->horn_sat(value, classification)) {
            _working_set->horn_force(value, classification);
          } else {
            return false;
          }
        }
        if(value.size() >= 2) {
          for(unsigned long i = 0; i < value.size() - 1; i++) {
            for(unsigned long j = i + 1; j < value.size(); j++) {
              _working_set->add_implication({value[i]}, value[j]);
              _working_set->add_implication({value[j]}, value[i]);
            }
          }
        }
      }
    }
    return true;
  }

  double Classifier::gain(const tapis::HornICE::qdt::Attribute *attribute, const std::list<const Diagram *> &pos,
                          const std::list<const Diagram *> &neg, const std::vector<const Diagram *> &unclass) {
    // compute entropy
    double all_pos = 0;
    double all_neg = 0;
    double sat_pos = 0;
    double sat_neg = 0;
    double sat_unclass = 0;
    double unsat_pos = 0;
    double unsat_neg = 0;
    double unsat_unclass = 0;
    for(auto diagram: pos) {
      if(attribute->satisfied_by(diagram)) {
        sat_pos += 1;
      } else {
        unsat_pos += 1;
      }
      all_pos += 1;
    }
    for(auto diagram: neg) {
      if(attribute->satisfied_by(diagram)) {
        sat_neg += 1;
      } else {
        unsat_neg += 1;
      }
      all_neg += 1;
    }
    for(auto diagram: unclass) {
      if(attribute->satisfied_by(diagram)) {
        sat_unclass += 1;
      } else {
        unsat_unclass += 1;
      }
      all_neg += 1;
    }
    if((sat_pos == 0 && sat_neg == 0 && sat_unclass == 0) ||
       (unsat_pos == 0 && unsat_neg == 0 && unsat_unclass == 0)) {
      return 0;
    }
    // all entropy
    double all_H;
    if(all_pos == 0 || all_neg == 0) {
      all_H = 0;
    } else {
      auto np = all_pos + all_neg;
      auto pnp = all_pos / np;
      auto nnp = all_neg / np;
      all_H = -std::log2(pnp) * pnp - std::log2(nnp) * nnp;
    }
    // sat entropy
    double sat_H;
    if(sat_pos == 0 || sat_neg == 0) {
      sat_H = 0;
    } else {
      auto np = sat_pos + sat_neg;
      auto pnp = sat_pos / np;
      auto nnp = sat_neg / np;
      sat_H = -std::log2(pnp) * pnp - std::log2(nnp) * nnp;
    }
    // unsat entropy
    double unsat_H;
    if(unsat_pos == 0 || unsat_neg == 0) {
      unsat_H = 0;
    } else {
      auto np = unsat_pos + unsat_neg;
      auto pnp = unsat_pos / np;
      auto nnp = unsat_neg / np;
      unsat_H = -std::log2(pnp) * pnp - std::log2(nnp) * nnp;
    }
    // information gain
    double ig = all_H - (sat_pos + sat_neg) / (all_pos + all_neg) * sat_H -
                (unsat_pos + unsat_neg) / (all_pos + all_neg) * unsat_H;
    return ig;
  }

}
