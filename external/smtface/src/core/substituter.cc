//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/substituter.hh"

#include <utility>
#include <vector>
#include "smtface/shorthands.hh"

namespace smtface::core {

  // Substituter
  Substituter::Substituter(const std::map<Expr, Expr> &map, const std::map<const Function *, const Function *> &fmap)
      : _fmap(fmap) {
    for(auto[key, value]: map) {
      auto kp = std::static_pointer_cast<Constant>(key);
      _map[kp->name()] = value;
    }
  }

  Expr Substituter::substitute(const Expr &expr) {
    expr->accept(*this);
    auto res = result();
    return std::get<1>(res);
  }

  void Substituter::visit(std::shared_ptr<ApplicationTerm> term) {
    bool changed = false;
    std::vector<Expr> args;
    const Function *func = term->function();
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      auto r = result();
      args.push_back(std::get<1>(r));
      if(std::get<0>(r)) {
        changed = true;
      }
    }
    if(_fmap.count(func) > 0) {
      changed = true;
      func = _fmap[func];
    }
    if(changed) {
      return _return(std::make_tuple(true, Apply(func->name(), args, term->context())));
    } else {
      return _return(std::make_tuple(false, term));
    }
  }

  void Substituter::visit(std::shared_ptr<QuantifiedFormula> term) {
    term->formula()->accept(*this);
    auto r = result();
    if(!std::get<0>(r)) {
      return _return(std::make_tuple(false, term));
    }
    if(term->quantifier() == Quantifier::forall) {
      return _return(std::make_tuple(true, ForAll(term->quantified_variables(), std::get<1>(r))));
    } else {
      return _return(std::make_tuple(true, Exists(term->quantified_variables(), std::get<1>(r))));
    }
  }

  void Substituter::visit(std::shared_ptr<Constant> term) {
    if(_map.count(term->name()) > 0) {
      return _return(std::make_tuple(true, _map[term->name()]));
    } else {
      return _return(std::make_tuple(false, term));
    }
  }

  void Substituter::visit(std::shared_ptr<Null> term) {
    return _return(std::make_tuple(false, term));
  }

  void Substituter::visit(std::shared_ptr<Value> term) {
    return _return(std::make_tuple(false, term));
  }

  std::tuple<bool, Expr> Substituter::result() {
    auto r = _stack.top();
    _stack.pop();
    return r;
  }

  void Substituter::_return(const std::tuple<bool, Expr> &r) {
    _stack.push(r);
  }

}
