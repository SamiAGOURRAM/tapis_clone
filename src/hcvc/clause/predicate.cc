//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/clause/predicate.hh"

#include <utility>
#include "hcvc/context.hh"
#include "hcvc/program/function.hh"

namespace hcvc {

  //*-- Predicate
  Predicate::Predicate(std::string name, PredicateKind kind)
      : _name(std::move(name)), _kind(kind) {}

  Predicate::~Predicate() = default;

  bool Predicate::may_require_quantifiers() const {
    for(const auto &parameter: this->parameters()) {
      if(parameter->type()->is_array()) {
        return true;
      }
    }
    return false;
  }

  //*-- InvariantPredicate
  InvariantPredicate::InvariantPredicate(std::string name, std::vector<Variable *> parameters)
      : Predicate(std::move(name), PredicateKind::invariant),
        _parameters(std::move(parameters)) {}

  InvariantPredicate::~InvariantPredicate() = default;

  const std::vector<Variable *> &InvariantPredicate::parameters() const {
    return _parameters;
  }

  InvariantPredicate *
  InvariantPredicate::create(hcvc::Function *function, const std::string &name, std::vector<Variable *> parameters) {
    auto pred = new InvariantPredicate(name, std::move(parameters));
    function->module()->_predicates[name] = pred;
    return pred;
  }

  //*-- FunctionPreconditionPredicate
  FunctionPreconditionPredicate::FunctionPreconditionPredicate(Function *function)
      : Predicate(function->name() + "@pre", PredicateKind::precondition),
        _function(function) {
    for(auto parameter: function->parameters()) {
      _parameters.push_back(parameter);
      if(parameter->type()->is_array()) {
        _parameters.push_back(parameter->size_variable());
      }
    }
  }

  FunctionPreconditionPredicate::~FunctionPreconditionPredicate() = default;

  const std::vector<Variable *> &FunctionPreconditionPredicate::parameters() const {
    return _parameters;
  }

  FunctionPreconditionPredicate *FunctionPreconditionPredicate::create(Function *function) {
    auto pred = new FunctionPreconditionPredicate(function);
    function->module()->_predicates[pred->name()] = pred;
    return pred;
  }

  //*-- FunctionSummaryPredicate
  FunctionSummaryPredicate::FunctionSummaryPredicate(Function *function)
      : Predicate(function->name() + "@summary", PredicateKind::summary),
        _function(function) {
    for(auto parameter: function->parameters()) {
      if(parameter->is_modified()) {
        _parameters.push_back(parameter->entry_value_holder());
      } else {
        _parameters.push_back(parameter);
      }
      if(parameter->type()->is_array()) {
        _parameters.push_back(parameter->size_variable());
      }
    }
    if(function->return_variable() != nullptr) {
      _parameters.push_back(function->return_variable());
    }
    for(auto parameter: function->parameters()) {
      if(parameter->is_modified()) {
        _parameters.push_back(parameter);
      }
    }
  }

  FunctionSummaryPredicate::~FunctionSummaryPredicate() = default;

  const std::vector<Variable *> &FunctionSummaryPredicate::parameters() const {
    return _parameters;
  }

  FunctionSummaryPredicate *FunctionSummaryPredicate::create(Function *function) {
    auto pred = new FunctionSummaryPredicate(function);
    function->module()->_predicates[pred->name()] = pred;
    return pred;
  }

  //*-- PredicateApplication
  PredicateApplication::PredicateApplication(Predicate *predicate, std::vector<Expr> arguments, Context &context)
      : Term(TermKind::PredApp, context),
        _predicate(predicate),
        _arguments(std::move(arguments)) {}

  PredicateApplication::~PredicateApplication() = default;

  const Type *PredicateApplication::type() const {
    return this->context().type_manager().bool_type();
  }

  void PredicateApplication::accept(Visitor &visitor) {
    std::shared_ptr<PredicateApplication> ptr(shared_from_this());
    visitor.visit(ptr);
  }

}
