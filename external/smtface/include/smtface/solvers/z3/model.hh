//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "z3++.h"
#include "smtface/core/term.hh"
#include "smtface/core/solver.hh"
#include "smtface/solvers/z3/converter.hh"

namespace smtface::solvers {

  //*-- Z3Model
  class Z3Model: public core::ModelObj {
  public:
    Z3Model(const z3::model &model, Z3Converter &converter);

    ~Z3Model() override;

    //*- properties

    z3::model z3_model();

    //*- methods

    core::Expr eval(const core::Expr &expr) override;

    std::map<core::Expr, core::Expr> to_values();

    core::Expr to_expr(const std::map<std::string, core::Expr> &variables) override;

  private:
    z3::model _model;
    Z3Converter &_converter;
  };

}
