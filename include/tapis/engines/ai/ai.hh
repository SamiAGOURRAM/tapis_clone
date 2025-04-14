//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include "apronxx/apronxx.hh"
#include "hcvc/module.hh"

namespace tapis::ai {

  class AbstractInterpreter {
  public:
    AbstractInterpreter(hcvc::Module *module, const std::set<hcvc::Weakness> &weaknesses);

    std::map<const hcvc::Predicate *, hcvc::Expr> analyze(apron::manager &manager);

  private:
    hcvc::Module *_module;
    std::set<const hcvc::Predicate *> _predicates;
    hcvc::ClauseSet _clauses;
  };

}
