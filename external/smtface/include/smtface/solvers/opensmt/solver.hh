//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "opensmt/opensmt2.h"
#include "smtface/core/context.hh"
#include "smtface/core/sort.hh"
#include "smtface/core/term.hh"
#include "smtface/core/solver.hh"
#include "smtface/solvers/opensmt/converter.hh"
#include "smtface/solvers/opensmt/model.hh"

namespace smtface::solvers {

  //*-- OpenSMTSolver
  class OpenSMTSolver: public core::Solver {
  public:
    explicit OpenSMTSolver(core::Context &context, LIALogic &logic);

    ~OpenSMTSolver() override;

    //*- methods

    std::optional<core::Model> get_model(const core::Expr &formula) override;

    bool is_sat(const core::Expr &formula) override;

    void remember(const core::Expr &expr) override;

    core::Expr simplify(const core::Expr &formula) override;

  private:
    LIALogic &_logic;
    SMTConfig _config;
    MainSolver _solver;
    OpenSMTConverter _converter;
  };

}
