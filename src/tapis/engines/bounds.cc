//
// Copyright (c) 2024 Wael-Amine Boutglay
//

#include "tapis/engines/bounds.hh"

namespace tapis {

  BoundManager _bound_manager;

  //*-- get_outputs()
  BoundManager &get_bounds() {
    return _bound_manager;
  }

}
