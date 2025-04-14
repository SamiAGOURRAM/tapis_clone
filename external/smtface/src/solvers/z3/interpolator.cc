//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/solvers/z3/interpolator.hh"

#include <list>
#include <set>
#include "smtface/shorthands.hh"

namespace smtface::solvers {

  //*-- Z3Interpolator
  Z3Interpolator::Z3Interpolator(core::Context &context) : core::Interpolator(context),
                                                           _converter(context, _z3_context) {}

  Z3Interpolator::~Z3Interpolator() = default;

  core::Expr Z3Interpolator::binary_interpolant(const core::Expr &A, const core::Expr &B) {
    // initialize spacer
    z3::fixedpoint fp(_z3_context);
    z3::params params(_z3_context);
    params.set("engine", "spacer");
    params.set("xform.inline_linear", false);
    params.set("xform.inline_eager", false);
    fp.set(params);

    //get common variables
    std::list<Expr> all_variables;
    std::set<std::string> _in_all;
    std::list<Expr> common_variables;
    std::set<std::string> _in_A;
    auto A_vars = smtface::get_variables(A);
    for(auto &var_e: A_vars) {
      auto var = std::dynamic_pointer_cast<core::Constant>(var_e);
      all_variables.push_back(var_e);
      _in_A.insert(var->name());
      _in_all.insert(var->name());
    }
    auto B_vars = smtface::get_variables(B);
    for(auto &var_e: B_vars) {
      auto var = std::dynamic_pointer_cast<core::Constant>(var_e);
      if(_in_A.count(var->name()) > 0) {
        common_variables.push_back(var_e);
      }
      if(_in_all.count(var->name()) == 0) {
        all_variables.push_back(var_e);
      }
    }
    all_variables.sort([](const Expr &a, const Expr &b) {
      auto var_a = std::dynamic_pointer_cast<core::Constant>(a);
      auto var_b = std::dynamic_pointer_cast<core::Constant>(b);
      return var_a->name() < var_b->name();
    });
    common_variables.sort([](const Expr &a, const Expr &b) {
      auto var_a = std::dynamic_pointer_cast<core::Constant>(a);
      auto var_b = std::dynamic_pointer_cast<core::Constant>(b);
      return var_a->name() < var_b->name();
    });

    // create interpolant relation
    z3::func_decl_vector rel_vector(_z3_context);
    z3::sort_vector domain(_z3_context);
    z3::expr_vector q_variables(_z3_context);
    for(auto &var: common_variables) {
      domain.push_back(_converter.encode_sort(var->sort()));
      q_variables.push_back(_converter.encode_expr(var));
    }
    auto itp_decl = z3::function("eapv-itp", domain, _z3_context.bool_sort());
    fp.register_relation(itp_decl);
    rel_vector.push_back(itp_decl);
    z3::expr_vector all_q_variables(_z3_context);
    for(auto &var: all_variables) {
      domain.push_back(_converter.encode_sort(var->sort()));
      all_q_variables.push_back(_converter.encode_expr(var));
    }

    // compute interpolant
    auto itp_call = itp_decl(q_variables);
    auto rule_1 = z3::forall(all_q_variables, z3::implies(_converter.encode_expr(A), itp_call));
    fp.add_rule(rule_1, _z3_context.str_symbol("eapv-itp-rule-1"));
    auto query = z3::exists(all_q_variables, itp_call && _converter.encode_expr(B));
    auto result = fp.query(query);
    if(result == z3::unsat) {
      z3::expr answer(_z3_context);
      if(fp.get_answer().is_quantifier()) {
        answer = fp.get_answer().body();
      } else {
        answer = fp.get_answer();
      }
      z3::expr_vector target(_z3_context);
      auto itp_call_2 = answer.arg(0);
      for(unsigned long i = 0, length = itp_call_2.num_args(); i < length; i++) {
        target.push_back(itp_call_2.arg(i));
      }
      auto I = answer.arg(1).substitute(target, q_variables);
      return _converter.decode_expr(I, {});
    }

    return smtface::Null(A->context());
  }

}
