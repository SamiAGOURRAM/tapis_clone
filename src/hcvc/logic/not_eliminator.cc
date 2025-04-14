//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "hcvc/logic/not_eliminator.hh"

#include "hcvc/context.hh"

namespace hcvc {

  // NotEliminator
  NotEliminator::NotEliminator() = default;

  Expr NotEliminator::eliminate(const Expr &expr) {
    auto res = visit(expr);
    return std::get<1>(res);
  }

  std::tuple<bool, Expr> NotEliminator::visit(const Expr &expr) {
    if(expr->kind() == TermKind::OpApp) {
      auto exprp = std::dynamic_pointer_cast<OperatorApplication>(expr);
      if(exprp->operat0r()->name() == "=>") {
        return std::make_tuple(true, std::get<1>(visit(!exprp->arguments()[0] || exprp->arguments()[1])));
      }
      if(exprp->operat0r()->name() == "not") {
        if(exprp->arguments()[0]->kind() == TermKind::Constant) {
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
        return std::make_tuple(true, expr->context().apply(exprp->operat0r()->name(), args));
      } else {
        return std::make_tuple(false, expr);
      }
    } else {
      return std::make_tuple(false, expr);
    }
  }

  Expr NotEliminator::negate(const Expr &expr) {
    if(expr->kind() == TermKind::OpApp) {
      auto exprp = std::dynamic_pointer_cast<OperatorApplication>(expr);
      if(exprp->operat0r()->name() == ">") {
        return expr->context().apply("<=", exprp->arguments());
      } else if(exprp->operat0r()->name() == ">=") {
        return expr->context().apply("<", exprp->arguments());
      } else if(exprp->operat0r()->name() == "<") {
        return expr->context().apply(">=", exprp->arguments());
      } else if(exprp->operat0r()->name() == "<=") {
        return expr->context().apply(">", exprp->arguments());
      } else if(exprp->operat0r()->name() == "=") {
        if(exprp->arguments()[0]->kind() == TermKind::Constant) {
          if(is_true(exprp->arguments()[1])) {
            return exprp->arguments()[0] == expr->context().get_false();
          } else if(is_false(exprp->arguments()[1])) {
            return exprp->arguments()[0] == expr->context().get_true();
          }
        }
        if(exprp->arguments()[1]->kind() == TermKind::Constant) {
          if(is_true(exprp->arguments()[0])) {
            return exprp->arguments()[0] == expr->context().get_false();
          } else if(is_false(exprp->arguments()[0])) {
            return exprp->arguments()[0] == expr->context().get_true();
          }
        }
        return expr->context().apply(">", exprp->arguments()) || expr->context().apply("<", exprp->arguments());
      } else if(exprp->operat0r()->name() == "not") {
        return std::get<1>(visit(exprp->arguments()[0]));
      } else if(exprp->operat0r()->name() == "=>") {
        return std::get<1>(visit(exprp->arguments()[0] && !exprp->arguments()[1]));
      }

      std::vector<Expr> args;
      for(const auto &arg: exprp->arguments()) {
        args.push_back(negate(arg));
      }

      if(exprp->operat0r()->name() == "and") {
        return expr->context().apply("or", args);
      } else if(exprp->operat0r()->name() == "or") {
        return expr->context().apply("and", args);
      }
    }
    return expr;
  }

}
