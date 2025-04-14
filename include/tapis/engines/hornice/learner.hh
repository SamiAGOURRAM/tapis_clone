//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <optional>
#include <unordered_map>
#include "tapis/engines/hornice/teacher.hh"

namespace tapis::HornICE {

  //*-- Learner
  class Learner {
  public:
    explicit Learner(hcvc::Module *module);

    virtual ~Learner();

    //*- properties

    inline hcvc::Module *module() const {
      return _module;
    }

    //*- methods

    virtual std::optional<std::unordered_map<const hcvc::Predicate *, LambdaDefinition>>
    synthesize(std::set<const hcvc::Implication *> counterexamples) = 0;

  private:
    hcvc::Module *_module;
  };

}
