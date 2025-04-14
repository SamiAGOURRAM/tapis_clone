//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/module.hh"
#include "hcvc/utils/source.hh"

namespace hcvc {

  //*-- Frontend
  class Frontend {
  public:
    virtual ~Frontend();

    //*- methods

    virtual Module *process(const Source &source) = 0;
  };

}
