//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/logic/substituter.hh"

#include "hcvc/context.hh"
#include "hcvc/clause/predicate.hh"

namespace hcvc {

  // Substituter
  Substituter::Substituter(const std::map<Expr, Expr> &map) {
    for(const auto &[key, value]: map) {
      auto kp = std::dynamic_pointer_cast<Constant>(key);
      _var_map[kp->name()] = value;
    }
  }

  Expr Substituter::substitute(const Expr &expr) {
    expr->accept(*this);
    auto res = result();
    return std::get<1>(res);
  }

  void Substituter::visit(std::shared_ptr<OperatorApplication> term) {
    bool changed = false;
    std::vector<Expr> args;
    const Operator *func = term->operat0r();
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      auto r = result();
      args.push_back(std::get<1>(r));
      if(std::get<0>(r)) {
        changed = true;
      }
    }
    if(changed) {
      return _return(std::make_pair(true, term->context().apply(func->name(), args)));
    } else {
      return _return(std::make_pair(false, term));
    }
  }

  void Substituter::visit(std::shared_ptr<Constant> term) {
    if(_var_map.count(term->name()) > 0) {
      return _return(std::make_pair(true, _var_map[term->name()]));
    } else {
      return _return(std::make_pair(false, term));
    }
  }

  void Substituter::visit(std::shared_ptr<BooleanLiteral> term) {
    return _return(std::make_pair(false, term));
  }

  void Substituter::visit(std::shared_ptr<IntegerLiteral> term) {
    return _return(std::make_pair(false, term));
  }

  void Substituter::visit(std::shared_ptr<ArrayLiteral> term) {
    return _return(std::make_pair(false, term));
  }

  void Substituter::visit(std::shared_ptr<QuantifiedFormula> term) {
    term->formula()->accept(*this);
    auto res = result();
    if(std::get<0>(res)) {
      return _return(std::make_pair(true, QuantifiedFormula::create(term->quantifier_kind(),
                                                                    term->quantifiers(),
                                                                    std::get<1>(res), term->context())));
    }
    return _return(std::make_pair(false, term));
  }

  void Substituter::visit(std::shared_ptr<PredicateApplication> term) {
    bool changed = false;
    std::vector<Expr> args;
    auto predicate = term->predicate();
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      auto r = result();
      args.push_back(std::get<1>(r));
      if(std::get<0>(r)) {
        changed = true;
      }
    }
    if(changed) {
      return _return(std::make_pair(true, std::make_shared<PredicateApplication>(predicate, args, term->context())));
    } else {
      return _return(std::make_pair(false, term));
    }
  }

}
