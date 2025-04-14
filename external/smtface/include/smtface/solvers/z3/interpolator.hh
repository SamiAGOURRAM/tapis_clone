//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "z3++.h"
#include "smtface/core/interpolator.hh"
#include "smtface/solvers/z3/converter.hh"

namespace smtface::solvers {

  //*-- Z3Interpolator
  class Z3Interpolator: public core::Interpolator {
  public:
    explicit Z3Interpolator(core::Context &context);

    ~Z3Interpolator() override;

    //*- methods

    core::Expr binary_interpolant(const core::Expr &A, const core::Expr &B) override;

  private:
    z3::context _z3_context;
    Z3Converter _converter;
  };

}
