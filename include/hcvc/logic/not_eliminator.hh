//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include <stack>
#include "hcvc/logic/term.hh"

namespace hcvc {

  //*-- NotEliminator
  class NotEliminator {
  public:
    NotEliminator();

    //*- methods

    Expr eliminate(const Expr &expr);

    std::tuple<bool, Expr> visit(const Expr &expr);

    Expr negate(const Expr &expr);
  };

}
