//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include "hcvc/clause/predicate.hh"
#include "hcvc/clause/set.hh"

namespace tapis {

  //*-- Outputs
  class Outputs {
  public:
    std::map<const hcvc::Predicate *, hcvc::Expr> preanalysis_invariants;
    hcvc::ClauseSet clauses;
  };

  //*-- get_outputs()
  Outputs &get_outputs();

}
