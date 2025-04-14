//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <set>
#include "smtface/core/symbol.hh"
#include "smtface/core/term.hh"
#include "smtface/core/interpolator.hh"
#include "smtface/core/register.hh"
#include "smtface/core/solver.hh"

namespace smtface {

  //*-- Context
  typedef core::Context Context;

  //*-- Expr
  typedef core::Expr Expr;

  //*-- Function
  typedef core::Function Function;

  //*-- Solver
  typedef core::Interpolator Interpolator;

  //*-- Model
  typedef core::Model Model;

  //*-- Solver
  typedef core::Solver Solver;

  //*-- Sort
  typedef const core::Sort *Sort;

  //*-- Add()
  Expr Add(const Expr &a, const Expr &b);

  Expr Add(const std::vector<Expr> &arguments);

  Expr Add(const Expr &a, const Expr &b, Context &context);

  Expr Add(const std::vector<Expr> &arguments, Context &context);

  //*-- And()
  Expr And(const Expr &a, const Expr &b);

  Expr And(const std::vector<Expr> &arguments);

  Expr And(const Expr &a, const Expr &b, Context &context);

  Expr And(const std::vector<Expr> &arguments, Context &context);

  //*-- Apply()
  Expr Apply(const std::string &name, const std::vector<Expr> &arguments);

  Expr Apply(const std::string &name, const std::vector<Expr> &arguments, Context &context);

  //*-- Apply()
  Expr Apply(const std::string &name, const std::vector<Expr> &arguments);

  Expr Apply(const std::string &name, const std::vector<Expr> &arguments, Context &context);

  //*-- ArraySort()
  const core::ArraySort *ArraySort(Sort index_sort, Sort element_sort);

  //*-- BOOL()
  Sort BOOL();

  //*-- current_context()
  Context &current_context();

  //*-- Equal()
  Expr Equal(const Expr &a, const Expr &b);

  Expr Equal(const Expr &a, const Expr &b, Context &context);

  //*-- Evaluate()
  Expr Evaluate(const Expr &expr, const std::map<Expr, std::variant<Expr, std::vector<Expr>>> &map = {});

  //*-- Exists()
  Expr Exists(const std::vector<Expr> &variables, const Expr &formula);

  Expr Exists(const std::vector<Expr> &variables, const Expr &formula, Context &context);

  //*-- False()
  Expr False();

  Expr False(Context &context);

  //*-- ForAll()
  Expr ForAll(const std::vector<Expr> &variables, const Expr &formula);

  Expr ForAll(const std::vector<Expr> &variables, const Expr &formula, Context &context);

  //*-- FreshSymbol()
  Expr FreshSymbol(Sort sort, const std::string &base = "FC");

  Expr FreshSymbol(Sort sort, Context &context, const std::string &base = "FC");

  //*-- FunctionSort()
  const core::FunctionSort *FunctionSort(const std::vector<Sort> &domain, Sort range);

  //*-- get_atomics()
  std::set<Expr> get_atomics(const Expr &f);

  //*-- get_register()
  core::Register &get_register();

  //*-- get_variables()
  std::set<Expr> get_variables(const Expr &f);

  //*-- GEq()
  Expr GEq(const Expr &a, const Expr &b);

  Expr GEq(const Expr &a, const Expr &b, Context &context);

  //*-- GT()
  Expr GT(const Expr &a, const Expr &b);

  Expr GT(const Expr &a, const Expr &b, Context &context);

  //*-- Implies()
  Expr Implies(const Expr &a, const Expr &b);

  Expr Implies(const Expr &a, const Expr &b, Context &context);

  //*-- Int()
  Expr Int(long num);

  Expr Int(const std::string &raw);

  Expr Int(long num, Context &context);

  Expr Int(const std::string &raw, Context &context);

  //*-- INT()
  Sort INT();

  //*-- ite()
  Expr ite(Expr cond, Expr cons, Expr altern);

  //*-- LEq()
  Expr LEq(const Expr &a, const Expr &b);

  Expr LEq(const Expr &a, const Expr &b, Context &context);

  //*-- LT()
  Expr LT(const Expr &a, const Expr &b);

  Expr LT(const Expr &a, const Expr &b, Context &context);

  //*-- Mult()
  Expr Mult(const Expr &a, const Expr &b);

  Expr Mult(const Expr &a, const Expr &b, Context &context);

  //*-- Not()
  Expr Not(const Expr &f);

  Expr Not(const Expr &f, Context &context);

  //*-- Null()
  Expr Null();

  Expr Null(Context &context);

  //*-- Or()
  Expr Or(const Expr &a, const Expr &b);

  Expr Or(const std::vector<Expr> &arguments);

  Expr Or(const Expr &a, const Expr &b, Context &context);

  Expr Or(const std::vector<Expr> &arguments, Context &context);

  //*-- pop_context()
  Context *pop_context();

  //*-- push_context()
  Context &push_context(Context *context = nullptr);

  //*-- Select()
  Expr Select(const Expr &array, const Expr &index);

  Expr Select(const Expr &array, const Expr &index, Context &context);

  //*-- Store()
  Expr Store(const Expr &array, const Expr &index, const Expr &element);

  Expr Store(const Expr &array, const Expr &index, const Expr &element, Context &context);

  //*-- Substitute()
  Expr Substitute(Expr expr, const std::map<Expr, Expr> &map, const std::map<const Function *, const Function *> &fmap = {});

  //*-- Symbol()
  Expr Symbol(const std::string &name);

  Expr Symbol(const std::string &name, Context &context);

  Expr Symbol(const std::string &name, Sort sort);

  Expr Symbol(const std::string &name, Sort sort, Context &context);

  //*-- ToString()
  std::string ToString(const Expr &expr);

  //*-- True()
  Expr True();

  Expr True(Context &context);

  //*-- Value()
  Expr Value(const std::string &raw, Sort sort);

  Expr Value(const std::string &raw, Sort sort, Context &context);

  //*-- Variable()
  Expr Variable(const std::string &name, Sort sort);

  Expr Variable(const std::string &name, Sort sort, Context &context);

}
