//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <tuple>
#include "smtface/core/term.hh"

namespace smtface::utils {

  // NotEliminator
  class NotEliminator {
  public:
    NotEliminator();

    core::Expr eliminate(const core::Expr &expr);

    std::tuple<bool, core::Expr> visit(const core::Expr &expr);

    core::Expr negate(const core::Expr &expr);
  };

}
