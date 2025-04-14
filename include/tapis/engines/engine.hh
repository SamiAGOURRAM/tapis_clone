//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/module.hh"

namespace tapis {

  //*-- Engine
  class Engine {
  public:
    Engine(hcvc::Module *module, hcvc::ClauseSet &clauses);

    virtual ~Engine();

    //*- properties

    /// Get the module to be verified.
    inline hcvc::Module *module() const {
      return _module;
    }

    /// Get the clauses to be satisfied by the searched invariants/summaries.
    inline const hcvc::ClauseSet &clauses() const {
      return _clauses;
    }

    //*- methods

    virtual void solve() = 0;

  private:
    hcvc::Module *_module;
    hcvc::ClauseSet _clauses;
  };

}
