//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <utility>
#include "smtface/core/context.hh"
#include "smtface/core/term.hh"

namespace smtface::core {

  //*-- Interpolator
  class Interpolator {
  public:
    explicit Interpolator(core::Context &context);

    virtual ~Interpolator();

    //*-- methods

    virtual core::Expr binary_interpolant(const core::Expr &A, const core::Expr &B) = 0;

  private:
    core::Context &_context;
  };

}
