//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "opensmt/opensmt2.h"
#include "smtface/core/interpolator.hh"
#include "smtface/solvers/opensmt/converter.hh"

namespace smtface::solvers {

  //*-- OpenSMTInterpolator
  class OpenSMTInterpolator: public core::Interpolator {
  public:
    OpenSMTInterpolator(core::Context &context, LIALogic &logic);

    ~OpenSMTInterpolator() override;

    //*- methods

    core::Expr binary_interpolant(const core::Expr &A, const core::Expr &B) override;

  private:
    LIALogic &_logic;
    OpenSMTConverter _converter;
  };

}
