//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/context.hh"
#include "hcvc/module.hh"

namespace hcvc {

  //*-- ToSMTLIB
  class ToSMTLIB {
  public:
    ToSMTLIB(ClauseSet &clauses);

    //*- methods

    void transform();

  private:
    hcvc::ClauseSet _clauses;
  };

}
