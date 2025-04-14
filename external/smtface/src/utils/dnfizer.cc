//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/dnfizer.hh"

#include "smtface/shorthands.hh"

namespace smtface::utils {

  // DNFizer
  DNFizer::DNFizer() = default;

  Expr DNFizer::dnfize(const Expr &expr) {
    auto dec = visit(expr);
    auto f = smtface::False();
    for(auto &c: dec) {
      auto cf = smtface::True();
      for(auto &l: c) {
        cf = cf && l;
      }
      f = f || cf;
    }
    return f;
  }

  std::vector<std::vector<Expr>> DNFizer::visit(const Expr &expr) {
    if(expr->kind() == core::TermKind::Application) {
      auto app = std::dynamic_pointer_cast<smtface::core::ApplicationTerm>(expr);
      std::vector<std::vector<std::vector<Expr>>> args;
      for(auto arg: app->arguments()) {
        args.push_back(visit(arg));
      }
      if(app->is_or()) {
        std::vector<std::vector<Expr>> res;
        for(auto &arg: args) {
          for(auto &argi: arg) {
            res.push_back(argi);
          }
        }
        return res;
      } else if(app->is_and()) {
        std::vector<std::vector<Expr>> res;
        auto merge = [](std::vector<std::vector<Expr>> &first, std::vector<std::vector<Expr>> &second) {
          std::vector<std::vector<Expr>> res;
          for(unsigned long ii = 0; ii < first.size(); ii++) {
            for(unsigned long jj = 0; jj < second.size(); jj++) {
              std::vector<Expr> ci = first[ii];
              ci.insert(ci.end(), second[jj].begin(), second[jj].end());
              res.push_back(ci);
            }
          }
          return res;
        };
        while(args.size() > 1) {
          args[0] = merge(args[0], args[0 + 1]);
          args.erase(args.begin() + 1);
        }
        return args[0];
      }
    }
    std::vector<std::vector<Expr>> res = {{expr}};
    return res;
  }

}
