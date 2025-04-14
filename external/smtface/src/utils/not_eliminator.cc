//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/utils/not_eliminator.hh"

#include <utility>
#include <vector>
#include "smtface/shorthands.hh"

namespace smtface::utils {

  // NotEliminator
  NotEliminator::NotEliminator() = default;

  Expr NotEliminator::eliminate(const Expr &expr) {
    auto res = visit(expr);
    return std::get<1>(res);
  }

  std::tuple<bool, Expr> NotEliminator::visit(const Expr &expr) {
    if(expr->kind() == core::TermKind::Constant || expr->kind() == core::TermKind::Value) {
      return std::make_tuple(false, expr);
    } else if(expr->kind() == core::TermKind::Application) {
      auto exprp = std::dynamic_pointer_cast<core::ApplicationTerm>(expr);
      if(exprp->function()->name() == "=>") {
        return std::make_tuple(true, std::get<1>(visit(!exprp->arguments()[0] || exprp->arguments()[1])));
      }
      if(exprp->function()->name() == "not") {
        if(exprp->arguments()[0]->kind() == core::TermKind::Constant) {
          return std::make_tuple(false, exprp);
        }
        return std::make_tuple(true, negate(exprp->arguments()[0]));
      }

      bool changed = false;
      std::vector<Expr> args;
      for(const auto &arg: exprp->arguments()) {
        auto r = visit(arg);
        args.push_back(std::get<1>(r));
        if(std::get<0>(r)) {
          changed = true;
        }
      }
      if(changed) {
        return std::make_tuple(true, Apply(exprp->function()->name(), args, expr->context()));
      } else {
        return std::make_tuple(false, expr);
      }
    }
    return std::make_tuple(false, smtface::Null(expr->context()));
  }

  core::Expr NotEliminator::negate(const Expr &expr) {
    if(expr->kind() == core::TermKind::Application) {
      auto exprp = std::dynamic_pointer_cast<core::ApplicationTerm>(expr);
      if(exprp->function()->name() == ">") {
        return Apply("<=", exprp->arguments(), expr->context());
      } else if(exprp->function()->name() == ">=") {
        return Apply("<", exprp->arguments(), expr->context());
      } else if(exprp->function()->name() == "<") {
        return Apply(">=", exprp->arguments(), expr->context());
      } else if(exprp->function()->name() == "<=") {
        return Apply(">", exprp->arguments(), expr->context());
      } else if(exprp->function()->name() == "=") {
        if(exprp->arguments()[0]->kind() == core::TermKind::Constant) {
          if(exprp->arguments()[1]->is_true()) {
            return Equal(exprp->arguments()[0], False());
          } else if(exprp->arguments()[1]->is_false()) {
            return Equal(exprp->arguments()[0], True());
          }
        }
        if(exprp->arguments()[1]->kind() == core::TermKind::Constant) {
          if(exprp->arguments()[0]->is_true()) {
            return Equal(exprp->arguments()[1], False());
          } else if(exprp->arguments()[1]->is_false()) {
            return Equal(exprp->arguments()[1], True());
          }
        }
        return Apply(">", exprp->arguments(), expr->context()) || Apply("<", exprp->arguments(), expr->context());
      } else if(exprp->function()->name() == "not") {
        return std::get<1>(visit(exprp->arguments()[0]));
      } else if(exprp->function()->name() == "=>") {
        return std::get<1>(visit(exprp->arguments()[0] && !exprp->arguments()[1]));
      }

      std::vector<Expr> args;
      for(const auto &arg: exprp->arguments()) {
        args.push_back(negate(arg));
      }

      if(exprp->function()->name() == "and") {
        return smtface::Or(args);
      } else if(exprp->function()->name() == "or") {
        return smtface::And(args);
      }
    }
    return expr;
  }

}
