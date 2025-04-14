//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/register.hh"

#include <iostream>

namespace smtface::core {

  Register *_smtface_global_register = nullptr;

  //*-- Register
  Register::Register() {
#ifdef SMTFACE_Z3
    _supported_solver_names.push_back("z3");
#endif
#ifdef SMTFACE_OPENSMT
    _supported_solver_names.push_back("opensmt");
#endif
  }

  const std::vector<std::string> Register::supported_solver_names() const {
    return _supported_solver_names;
  }

  SortManager &Register::get_sort_manager() {
    return _sort_manager;
  }

  bool Register::is_initialized() {
    return _smtface_global_register != nullptr;
  }

  void Register::initialize_if_not() {
    if(!is_initialized()) {
      _smtface_global_register = new Register();
    }
  }

  Register *Register::get_register() {
    initialize_if_not();
    return _smtface_global_register;
  }

}
