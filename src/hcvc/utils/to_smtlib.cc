//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "hcvc/utils/to_smtlib.hh"

namespace hcvc {

  //*-- ToSMTLIB
  ToSMTLIB::ToSMTLIB(hcvc::ClauseSet &clauses)
      : _clauses(clauses) {}

  std::string type2string(const Type *type) {
    if(type->is_int()) {
      return "Int";
    } else if(type->is_bool()) {
      return "Bool";
    } else if(type->is_array()) {
      const auto *array_type = dynamic_cast<const ArrayType *>(type);
      return "(Array Int " + type2string(array_type->element_type()) + ")";
    }
  }

  void ToSMTLIB::transform() {
    std::string result;
    result += "(set-logic HORN)\n";
result += R"((define-fun-rec sum_range ((a (Array Int Int)) (i Int) (j Int)) Int
  (ite (>= i j)
       0
       (+ (select a (- j 1)) (sum_range a i (- j 1)))
  )
)
)";
    for(auto predicate: _clauses.predicates()) {
      result += "(declare-fun " + predicate->name() + " (";
      for(auto parameter: predicate->parameters()) {
        result += type2string(parameter->type()) + " ";
      }
      result += ") Bool)\n";
    }
    for(auto clause: _clauses.to_set()) {
      auto constant_set = get_constants(clause->to_formula());
      std::vector<Expr> constants(constant_set.begin(), constant_set.end());
      auto c = QuantifiedFormula::create(Quantifier::ForAll, constants, clause->to_formula(), clause->context());
      result += "(assert " + to_string(c) + ")\n";
    }
    result += "(check-sat)\n";
    std::cout << result;
  }

}
