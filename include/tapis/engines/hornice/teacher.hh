//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <set>
#include <unordered_map>
#include "hcvc/module.hh"
#include "hcvc/program/state.hh"

namespace tapis::HornICE {

  //*-- LambdaDefinition
  class LambdaDefinition {
  public:
    LambdaDefinition(const hcvc::Predicate *predicate, hcvc::Expr body);

    //*- properties

    inline const hcvc::Predicate *predicate() const {
      return _predicate;
    }

    inline const hcvc::Expr &body() const {
      return _body;
    }

    const hcvc::Predicate *_predicate;
    hcvc::Expr _body;
  };

  //*-- Teacher
  class Teacher {
  public:
    Teacher(hcvc::Module *module, const hcvc::ClauseSet &clauses);

    //*- methods

    std::set<const hcvc::Implication *>
    check(const std::unordered_map<const hcvc::Predicate *, LambdaDefinition> &hypothesis);

  private:
    const hcvc::Implication *
    _check(const hcvc::Clause *clause, const std::unordered_map<const hcvc::Predicate *, LambdaDefinition> &hypothesis,
           const std::function<hcvc::Expr(const hcvc::Expr &)> &size_restriction_func,
           const std::function<hcvc::Expr(const hcvc::Expr &)> &array_restriction_func);

    std::set<const hcvc::Implication *>
    _check(const std::unordered_map<const hcvc::Predicate *, LambdaDefinition> &hypothesis,
           const std::function<hcvc::Expr(const hcvc::Expr &)> &size_restriction_func,
           const std::function<hcvc::Expr(const hcvc::Expr &)> &array_restriction_func);

    bool _check(const std::unordered_map<const hcvc::Predicate *, LambdaDefinition> &hypothesis);

    hcvc::Module *_module;
    std::set<const hcvc::Clause *> _clauses;
    const hcvc::ClauseSet &_clause_set;

    hcvc::StateManager _state_manager;
  };

}
