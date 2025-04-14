//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <set>
#include <unordered_map>
#include "hcvc/verifier.hh"
#include "tapis/engines/hornice/learner.hh"
#include "tapis/engines/hornice/teacher.hh"
#include "tapis/engines/hornice/qdt/quantifier.hh"

namespace tapis::HornICE {

  //*-- HornICE
  class HornICE: public hcvc::Verifier {
  public:
    HornICE(hcvc::Module *module, const hcvc::ClauseSet &clauses, Learner *learner);

    ~HornICE() override;

    //*- methods

    hcvc::VerifierResponse verify() override;

  private:
    Teacher _teacher;
    Learner *_learner;
  };

}
