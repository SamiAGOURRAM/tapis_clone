//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/verifier.hh"

namespace hcvc {

  //*-- Verifier
  Verifier::Verifier(hcvc::Module *module)
      : _module(module) {}

  Verifier::~Verifier() = default;

}
