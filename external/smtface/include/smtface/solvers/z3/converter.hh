//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "z3++.h"
#include "smtface/core/context.hh"
#include "smtface/core/sort.hh"
#include "smtface/core/term.hh"

#include "smtface/shorthands.hh"

namespace smtface::solvers {

  //*-- Z3Converter
  class Z3Converter {
  public:
    Z3Converter(core::Context &context, z3::context &z3_context);

    //*- properties

    core::Context &context() const;

    //*- methods

    core::Expr decode_expr(const z3::expr &expr, const std::map<std::string, smtface::Expr> &scope);

    z3::expr encode_expr(const core::Expr &expr);

    z3::expr encode_expr(const core::Expr &expr, const z3::func_decl_vector &func_decls,
                         const std::map<std::string, unsigned int> &func_decl_map);

    smtface::Sort decode_sort(z3::sort sort);

    z3::sort encode_sort(smtface::Sort sort);

    void remember(const core::Expr &expr);
    z3::func_decl get_sum_range_func() const { return m_sum_range_func; } // Add a getter


  private:
    core::Context &_context;
    z3::context &_z3_context;
    std::vector<core::Expr> _remembered_expr;
    z3::expr_vector _remembered_z3_expr;
    std::map<unsigned long, unsigned> _remember_map;
    z3::func_decl m_sum_range_func; 

  };

}
