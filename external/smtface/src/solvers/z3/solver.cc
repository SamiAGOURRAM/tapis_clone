//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/solvers/z3/solver.hh"

#include <list>
#include "smtface/shorthands.hh"

namespace smtface::solvers {

  //*-- Z3Solver
  Z3Solver::Z3Solver(Context &context)
      : Solver(context), _z3_solver(_z3_context, "UFLIA"), _converter(context, _z3_context) {
    // TODO: automatically choose the right logic, or give user the choice
    _z3_context.set(":random-seed", 12);
    z3::set_param("model.compact", "false");
  }

  Z3Solver::~Z3Solver() = default;

  std::optional<Model> Z3Solver::get_model(const core::Expr &formula) {
    _z3_solver.reset();
    auto encoded = _converter.encode_expr(formula);
    _z3_solver.add(encoded);
    auto res = _z3_solver.check();
    if(res == z3::check_result::sat) {
      return std::optional<Model>(new Z3Model(_z3_solver.get_model(), _converter));
    }
    return std::nullopt;
  }

  bool Z3Solver::is_sat(const Expr &formula) {
    _z3_solver.reset();
    auto encoded = _converter.encode_expr(formula);
    _z3_solver.add(encoded);
    auto res = _z3_solver.check();
    return res == z3::check_result::sat;
  }

  void Z3Solver::remember(const Expr &expr) {
    _converter.remember(expr);
  }

  core::Expr Z3Solver::simplify(const core::Expr &formula) {
    auto encoded = _converter.encode_expr(formula);
    z3::tactic qe(_z3_context, "ctx-solver-simplify");
    z3::goal g(_z3_context);
    g.add(encoded);
    z3::apply_result result_of_elimination = qe.apply(g);
    z3::goal result_goal = result_of_elimination[0];
    return _converter.decode_expr(result_goal.as_expr(), {});
  }

  core::Expr Z3Solver::qe(const core::Expr &formula) {
    auto variables = smtface::get_variables(formula);
    std::map<std::string, smtface::Expr> scope;
    for(auto &var: variables) {
      auto exprp = std::dynamic_pointer_cast<core::Constant>(var);
      scope.emplace(exprp->name(), exprp);
    }
    auto encoded = _converter.encode_expr(formula);
    z3::params params(_z3_context);
    params.set("qe-nonlinear", true);
    z3::tactic qe = z3::with(z3::tactic(_z3_context, "qe"), params);
    z3::goal g(_z3_context);
    g.add(encoded);
    z3::apply_result result_of_elimination = qe.apply(g);
    z3::goal result_goal = result_of_elimination[0];
    return _converter.decode_expr(result_goal.as_expr(), scope);
  }

}
