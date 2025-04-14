//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/attributes/attribute.hh"

namespace tapis::HornICE::qdt {

  //*-- Attribute
  Attribute::Attribute(const hcvc::Predicate *predicate, hcvc::Expr constraint)
      : _predicate(predicate),
        _constraint(std::move(constraint)) {}

  bool Attribute::satisfied_by(const Diagram *diagram) const {
    if(_sat_cache.count(diagram) == 0) {
      std::map<hcvc::Expr, hcvc::Expr> eval_map;
      for(auto &[var, value]: diagram->values()) {
        eval_map[hcvc::VariableConstant::create(var, 0, _constraint->context())] = value;
      }
      auto expr = hcvc::evaluate(_constraint, eval_map);
      if(expr->kind() == hcvc::TermKind::BooleanLiteral) {
        auto exprp = std::dynamic_pointer_cast<hcvc::BooleanLiteral>(expr);
        _sat_cache[diagram] = exprp->value();
        return exprp->value();
      } else {
        std::cout << _constraint << "\n";
        std::cout << "IMPL-UNREACH" << "\n";
        exit(10);
      }
    }
    return _sat_cache.at(diagram);
  }

  //*-- AttributeManager
  const Attribute *AttributeManager::get_attribute(const hcvc::Predicate *predicate, const hcvc::Expr &constraint) {
    auto hash = hcvc::to_string(constraint);
    if(_cache.count(predicate) == 0 || _cache[predicate].count(hash) == 0) {
      _cache[predicate][hash] = new Attribute(predicate, constraint);
    }
    return _cache[predicate][hash];
  }

  //*-- AttributeSynthesizer
  AttributeSynthesizer::~AttributeSynthesizer() = default;

}
