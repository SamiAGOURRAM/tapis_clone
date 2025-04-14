//
// Copyright (c) 2024 Wael-Amine Boutglay
//

#pragma once

namespace tapis {

  //*-- BoundManager
  class BoundManager {
  public:
    inline BoundManager() {
      _max_array_size = 2;
      _max_array_value = 0;
    }

    unsigned long _max_array_size;
    long _max_array_value;
  };

  //*-- get_bounds()
  BoundManager &get_bounds();

}
