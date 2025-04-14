//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/has_ite.hh"

#include <queue>

namespace smtface::utils {

  //*-- has_ite(expr)
  bool has_ite(const smtface::Expr &expr) {
    std::queue<smtface::Expr> queue;
    queue.push(expr);
    while(!queue.empty()) {
      // get element
      auto element = queue.front();
      queue.pop();
      // process
      if(element->kind() == core::TermKind::Application) {
        auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(element);
        if(app->function()->name() == "ite") {
          return true;
        } else {
          for(const auto &arg: app->arguments()) {
            queue.push(arg);
          }
        }
      }
    }
    return false;
  }

}
