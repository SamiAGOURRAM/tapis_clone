//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/theories/arrays.hh"

#include "smtface/shorthands.hh"

namespace smtface::theories {

  //*-- initialize_arrays_theory()
  void initialize_arrays_theory(core::Context &context) {
    // select
    auto select_accept_fun = [](const std::vector<const core::Sort *> &sorts) -> bool {
      if(sorts.size() != 2) {
        return false;
      }
      if(sorts[0]->kind() != core::SortKind::array) {
        return false;
      }
      auto array_sort = (const core::ArraySort *) sorts[0];
      return *sorts[1] == *array_sort->index_sort();
    };
    auto select_domain = new core::LambdaDomain(select_accept_fun);
    auto select_range_fun = [](const std::vector<const core::Sort *> &sorts) -> const core::Sort * {
      auto array_sort = (const core::ArraySort *) sorts[0];
      return array_sort->element_sort();
    };
    auto select_range = new core::LambdaRange(select_range_fun);
    context.function("select", select_domain, select_range, {"theory", "array-theory"});
    // store
    auto store_accept_fun = [](const std::vector<const core::Sort *> &sorts) -> bool {
      if(sorts.size() != 3) {
        return false;
      }
      if(sorts[0]->kind() != core::SortKind::array) {
        return false;
      }
      auto array_sort = (const core::ArraySort *) sorts[0];
      return (*sorts[1] == *array_sort->index_sort()) && (*sorts[1] == *array_sort->index_sort());
    };
    auto store_domain = new core::LambdaDomain(store_accept_fun);
    auto store_range_fun = [](const std::vector<const core::Sort *> &sorts) -> const core::Sort * {
      return sorts[0];
    };
    auto store_range = new core::LambdaRange(store_range_fun);
    context.function("store", store_domain, store_range, {"theory", "array-theory"});
  }

}
