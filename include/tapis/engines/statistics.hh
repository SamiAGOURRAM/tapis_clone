//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

namespace tapis {

  //*-- Statistics
  class Statistics {
    class ICEStatistics {
    public:
      unsigned long iterations = 0; // number of ICE iterations
    };

    class SMTStatistics {
    public:
      unsigned long queries = 0; // number of SMT queries
    };

  public:
    ICEStatistics ice;
    SMTStatistics smt;
  };

  //*-- get_statistics()
  Statistics &get_statistics();

}
