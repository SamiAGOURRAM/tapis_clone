//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/module.hh"

namespace hcvc {

  //*-- VerifierResponse
  enum class VerifierResponse {
    SAFE,
    UNKNOWN,
    UNSAFE,
  };

  //*-- Verifier
  class Verifier {
  public:
    explicit Verifier(Module *module);

    virtual ~Verifier();

    //*- properties

    /// Get the module.
    inline Module *module() const {
      return _module;
    }

    //*- methods

    /// Verify the program.
    virtual VerifierResponse verify() = 0;

  private:
    Module *_module;
  };

}
