//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/hornice/hornice.hh"

#include "tapis/engines/statistics.hh"
#include "tapis/engines/hornice/qdt/learner.hh"

namespace tapis::HornICE {

  //*-- HornICE
  HornICE::HornICE(hcvc::Module *module, const hcvc::ClauseSet &clauses, Learner *learner)
      : hcvc::Verifier(module),
        _teacher(module, clauses),
        _learner(learner) {}

  HornICE::~HornICE() = default;

  hcvc::VerifierResponse HornICE::verify() {
    // ICE loop
    std::set<const hcvc::Implication *> counterexamples; // initially empty
    while(true) {
      get_statistics().ice.iterations++;
      auto learner_res = _learner->synthesize(counterexamples);
      if(!learner_res.has_value()) {
        return hcvc::VerifierResponse::UNSAFE;
      }
      counterexamples = _teacher.check(*learner_res);
      if(counterexamples.empty()) {
        // TODO: store the invariants somewhere
        return hcvc::VerifierResponse::SAFE;
      }
    }
    return hcvc::VerifierResponse::UNKNOWN;
  }

}
