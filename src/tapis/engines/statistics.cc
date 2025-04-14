//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "tapis/engines/statistics.hh"

namespace tapis {

  Statistics _statistics;

  //*-- get_statistics()
  Statistics &get_statistics() {
    return _statistics;
  }

}
