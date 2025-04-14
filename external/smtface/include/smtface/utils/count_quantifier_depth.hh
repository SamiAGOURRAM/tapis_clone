//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "smtface/shorthands.hh"

namespace smtface::utils {

  //*-- count_quantifier_depth(expr)
  unsigned long count_quantifier_depth(const smtface::Expr &expr);

}
