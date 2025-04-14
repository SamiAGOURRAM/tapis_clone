//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/theories/ints.hh"

#include "smtface/shorthands.hh"

namespace smtface::theories {

  //*-- initialize_ints_theory()
  void initialize_ints_theory(core::Context &context) {
    // -
    auto substract_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 1, 2);
    context.function("-", substract_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // +
    auto plus_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("+", plus_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // *
    auto mult_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("*", mult_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // div
    auto div_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("div", div_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // mod
    auto mod_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("mod", mod_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // abs
    auto abs_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 1, 1);
    context.function("abs", abs_domain, get_register().get_sort_manager().Int(), {"theory", "int-theory"});
    // <=
    auto leq_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("<=", leq_domain, get_register().get_sort_manager().Bool(), {"theory", "int-theory"});
    // <
    auto lt_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function("<", lt_domain, get_register().get_sort_manager().Bool(), {"theory", "int-theory"});
    // >=
    auto geq_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function(">=", geq_domain, get_register().get_sort_manager().Bool(), {"theory", "int-theory"});
    // >
    auto gt_domain = new core::MinMaxDomain(get_register().get_sort_manager().Int(), 2, 2);
    context.function(">", gt_domain, get_register().get_sort_manager().Bool(), {"theory", "int-theory"});
  }

}
