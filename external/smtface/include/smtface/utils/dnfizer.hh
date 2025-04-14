//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <tuple>
#include "smtface/shorthands.hh"

namespace smtface::utils {

  // DNFizer
  class DNFizer {
  public:
    DNFizer();

    core::Expr dnfize(const core::Expr &expr);

    std::vector<std::vector<Expr>> visit(const core::Expr &expr);
  };

}
