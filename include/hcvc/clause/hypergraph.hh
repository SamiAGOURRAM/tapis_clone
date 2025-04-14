//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <unordered_map>
#include "hcvc/clause/clause.hh"
#include "hcvc/clause/predicate.hh"
#include "hcvc/clause/set.hh"

namespace hcvc {

  //*-- HyperGraph
  class HyperGraph: public ClauseSet {
  public:

    //*- methods

    void dump();

    inline void add_to_be_simplified(Predicate *predicate) {
      _to_be_simplified.insert(predicate);
    }

    void simplify(Context &context);

  private:
    std::set<Predicate *> _to_be_simplified;
  };

}
