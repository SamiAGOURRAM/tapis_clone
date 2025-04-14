//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/learner.hh"

namespace tapis::HornICE {

  //*-- Learner
  Learner::Learner(hcvc::Module *module)
      : _module(module) {}

  Learner::~Learner() = default;

}
