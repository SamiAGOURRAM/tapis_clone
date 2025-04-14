//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "z3++.h"
#include "smtface/core/context.hh"
#include "smtface/core/sort.hh"
#include "smtface/core/term.hh"
#include "smtface/core/solver.hh"
#include "smtface/solvers/z3/converter.hh"
#include "smtface/solvers/z3/model.hh"

namespace smtface::solvers {

  //*-- Z3Solver
  class Z3Solver: public core::Solver {
  public:
    explicit Z3Solver(core::Context &context);

    ~Z3Solver() override;

    //*- properties

    inline Z3Converter &converter() {
      return _converter;
    }

    //*- methods

    std::optional<core::Model> get_model(const core::Expr &formula) override;

    bool is_sat(const core::Expr &formula) override;

    void remember(const core::Expr &expr) override;

    core::Expr simplify(const core::Expr &formula) override;

    core::Expr qe(const core::Expr &formula);

  private:
    z3::context _z3_context;
    z3::solver _z3_solver;
    Z3Converter _converter;
  };

}
