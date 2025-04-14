//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/module.hh"

namespace hcvc {

  //*-- Module
  Module::Module(Context &context)
      : _context(context) {}

  Module::~Module() {
    // free declared functions
    for(const auto &[_, func]: _functions) {
      delete func;
    }
  }

}
