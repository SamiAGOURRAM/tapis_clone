//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

namespace hcvc {

  //*-- Weakness
  enum class Weakness {
    assertion_violation, // related to CWE-617: Reachable Assertion
    specification_violation, // related to CWE-617: Reachable Assertion
    buffer_over_read, // CWE-126
    buffer_under_read, // CWE-127
    buffer_over_write, // related to CWE-787
    buffer_under_write, // related to CWE-787
  };

}
