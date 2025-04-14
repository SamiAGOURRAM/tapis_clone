//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <string>
#include <vector>
#include "smtface/core/sort.hh"

namespace smtface::core {

  //*-- Register
  class Register {
  public:
    Register();

    //*- properties

    const std::vector<std::string> supported_solver_names() const;

    SortManager &get_sort_manager();

    //*- statics

    static bool is_initialized();

    static void initialize_if_not();

    static Register *get_register();

  private:
    std::vector<std::string> _supported_solver_names;
    SortManager _sort_manager;
  };

}
