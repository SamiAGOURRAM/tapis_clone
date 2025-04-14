//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "tapis/engines/engine.hh"

namespace tapis {

  //*-- HornICEQDT
  class HornICEQDT: public Engine {
  public:
    HornICEQDT(hcvc::Module *module, hcvc::ClauseSet &clauses);

    ~HornICEQDT() override;

    //*- methods

    void solve() override;
  };

}
