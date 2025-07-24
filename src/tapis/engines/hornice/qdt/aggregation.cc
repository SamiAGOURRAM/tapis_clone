// In: src/tapis/engines/hornice/qdt/aggregation.cc
#include "tapis/engines/hornice/qdt/aggregation.hh"
#include "hcvc/program/variable.hh"
#include "hcvc/logic/substituter.hh"
#include <cassert>

namespace tapis::HornICE::qdt {

  const std::vector<AggregationInfo*> AggregationManager::s_empty_vector;

  AggregationManager::AggregationManager(QuantifierManager& quantifier_manager)
      : _context(nullptr), _quantifier_manager(quantifier_manager) {}

  AggregationManager::~AggregationManager() {
    clear();
  }
  
  void AggregationManager::clear() {
    for (auto const& [predicate, infos] : _aggregations) {
      for (auto* info : infos) {
        delete info;
      }
    }
    _aggregations.clear();
    _sub_maps.clear();
  }

  void AggregationManager::set_predicates(const std::set<const hcvc::Predicate*>& predicates) {
    _predicates = predicates;
  }
  
  void AggregationManager::resetup() {
      clear();
      setup();
  }

  const std::vector<AggregationInfo*>& AggregationManager::get_aggregations(const hcvc::Predicate* p) const {
    auto it = _aggregations.find(p);
    if (it != _aggregations.end()) {
        return it->second;
    }
    return s_empty_vector;
  }
  
  hcvc::Expr AggregationManager::substitute(const hcvc::Predicate* predicate, hcvc::Expr body) {
      if (_sub_maps.count(predicate)) {
          return hcvc::substitute(body, _sub_maps.at(predicate));
      }
      return body;
  }


void AggregationManager::setup() {
    assert(_context != nullptr && "Context must be set before setup");

    for (const auto* predicate : _predicates) {
        _aggregations[predicate] = {};
        _sub_maps[predicate] = {};

        std::vector<const hcvc::Variable*> arrays_in_pred;
        std::vector<const hcvc::Variable*> int_vars_in_pred;

        for (const auto* param : predicate->parameters()) {
            if (param->type()->is_array()) {
                arrays_in_pred.push_back(param);
            } else if (param->type()->is_int() && !param->is_data()) {
                int_vars_in_pred.push_back(param);
            }
        }

        if (arrays_in_pred.empty()) continue;

        std::vector<const hcvc::Variable*> all_bounds = int_vars_in_pred;

        const auto& quantifier_infos = _quantifier_manager.quantifiers(predicate);
        for (const auto* info : quantifier_infos) {
            all_bounds.push_back(info->quantifier);
        }

        std::vector<const hcvc::Variable*> lower_bounds = all_bounds;
        lower_bounds.push_back(nullptr);
        std::vector<const hcvc::Variable*> upper_bounds = all_bounds;

        for (const auto* array : arrays_in_pred) {
            for (const auto* lower_var : lower_bounds) {
                for (const auto* upper_var : upper_bounds) {
                    if (upper_var == nullptr) continue;
                    if (lower_var == upper_var) continue;

                    auto* info = new AggregationInfo();
                    info->type = AggregationType::SUM;
                    info->predicate = predicate;
                    info->array = array;
                    info->lower_bound = lower_var;
                    info->upper_bound = upper_var;

                    std::string lower_name = (lower_var) ? lower_var->name() : "0";
                    std::string upper_name = upper_var->name();
                    std::string agg_var_name = "!s_" + array->name() + "_" + lower_name + "_" + upper_name;

                    info->variable = hcvc::Variable::create(agg_var_name, context().type_manager().int_type(), context(), true);
                    info->variable->set_is_data();

                    auto array_term = hcvc::VariableConstant::create(array, 0, context());
                    auto lower_term = (lower_var) ? hcvc::VariableConstant::create(lower_var, 0, context()) : hcvc::IntegerLiteral::get("0", context().type_manager().int_type(), context());
                    auto upper_term = hcvc::VariableConstant::create(upper_var, 0, context());

                    // The method is `apply("sum", ...)`
                    auto sum_term = context().apply("sum", {array_term, lower_term, upper_term});

                    auto synthetic_var_const = hcvc::VariableConstant::create(info->variable, 0, context());
                    _sub_maps.at(predicate)[synthetic_var_const] = sum_term;

                    _aggregations.at(predicate).push_back(info);
                }
            }
        }
    }
}
}