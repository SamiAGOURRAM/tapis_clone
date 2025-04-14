//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/theories/core.hh"

#include "smtface/shorthands.hh"

namespace smtface::theories {

  //*-- initialize_core_theory()
  void initialize_core_theory(core::Context &context) {
    // not
    auto not_domain = new core::MinMaxDomain(get_register().get_sort_manager().Bool(), 1, 1);
    context.function("not", not_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // =>
    auto implies_domain = new core::MinMaxDomain(get_register().get_sort_manager().Bool(), 2, 2);
    context.function("=>", implies_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // and
    auto and_domain = new core::MinMaxDomain(get_register().get_sort_manager().Bool(), 2);
    context.function("and", and_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // or
    auto or_domain = new core::MinMaxDomain(get_register().get_sort_manager().Bool(), 2);
    context.function("or", or_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // xor
    auto xor_domain = new core::MinMaxDomain(get_register().get_sort_manager().Bool(), 2, 2);
    context.function("xor", xor_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // =
    auto eq_accept_fun = [](const std::vector<const core::Sort *> &sorts) -> bool {
      if(sorts.size() != 2) {
        return false;
      }
      return sorts[0] == sorts[1];
    };
    auto eq_domain = new core::LambdaDomain(eq_accept_fun);
    context.function("=", eq_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // distinct
    auto distinct_accept_fun = [](const std::vector<const core::Sort *> &sorts) -> bool {
      if(sorts.size() != 2) {
        return false;
      }
      return sorts[0] == sorts[1];
    };
    auto distinct_domain = new core::LambdaDomain(distinct_accept_fun);
    context.function("distinct", distinct_domain, get_register().get_sort_manager().Bool(), {"theory", "core-theory"});
    // ite
    auto ite_accept_fun = [](const std::vector<const core::Sort *> &sorts) -> bool {
      if(sorts.size() != 3) {
        return false;
      }
      return sorts[0] == get_register().get_sort_manager().Bool() && sorts[1] == sorts[2];
    };
    auto ite_domain = new core::LambdaDomain(ite_accept_fun);
    auto ite_range_fun = [](const std::vector<const core::Sort *> &sorts) -> const core::Sort * {
      // assert(sorts.size() = 3);
      return sorts[1];
    };
    auto ite_range = new core::LambdaRange(ite_range_fun);
    context.function("ite", ite_domain, ite_range, {"theory", "core-theory"});
  }

}
