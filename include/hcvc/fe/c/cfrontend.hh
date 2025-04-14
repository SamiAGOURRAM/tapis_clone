//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/fe/frontend.hh"

namespace hcvc::fe {

  //*-- CFrontend
  class CFrontend: public Frontend {
  public:
    CFrontend();

    ~CFrontend() override;

    //*- properties

    Module *process(const Source &source) override;

  private:
    hcvc::Context _context;
  };

}
