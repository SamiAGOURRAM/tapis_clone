//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "tapis/engines/engine.hh"

namespace tapis {

  //*-- Engine
  Engine::Engine(hcvc::Module *module, hcvc::ClauseSet &clauses)
      : _module(module),
        _clauses(clauses) {}

  Engine::~Engine() = default;

}
