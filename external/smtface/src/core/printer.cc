//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/printer.hh"

#include <iostream>
#include <utility>
#include "smtface/shorthands.hh"

namespace smtface::core {

  // Printer
  Printer::Printer() = default;

  std::string Printer::to_string(const Expr &expr) {
    expr->accept(*this);
    return result();
  }

  void Printer::visit(std::shared_ptr<ApplicationTerm> term) {
    auto res = "(" + term->function()->name();
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      res += " " + result();
    }
    return _return(res + ")");
  }

  void Printer::visit(std::shared_ptr<QuantifiedFormula> term) {
    std::string res = "(";
    if(term->quantifier() == Quantifier::forall) {
      res += "forall ";
    } else {
      res += "exists ";
    }
    res += "(";
    for(const auto &var: term->quantified_variables()) {
      auto v = std::dynamic_pointer_cast<Constant>(var);
      res += "(" + v->name() + " ";
      if(v->sort() == INT()) {
        res += "Int";
      } else {
        res += "Bool";
      }
      // TODO: effective sort to string
      res += ")";
    }
    res += ")";
    term->formula()->accept(*this);
    res += " " + result();
    return _return(res + ")");
  }

  // TODO: use unique one
  inline bool _is_special(char c) {
    return c == '_' || c == '+' || c == '-' || c == '*' || c == '&' || c == '|' || c == '!' || c == '~' || c == '<' ||
           c == '>' || c == '=' || c == '/' || c == '?' || c == '.' || c == '$' || c == '^';
  }

  bool _is_simple_symbol(const std::string &symbol) {
    return std::all_of(symbol.begin(), symbol.end(), [](char c) {
      return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || _is_special(c);
    });
  }

  void Printer::visit(std::shared_ptr<Constant> term) {
    if(_is_simple_symbol(term->name())) {
      return _return(term->name());
    } else {
      return _return("|" + term->name() + "|");
    }
  }

  void Printer::visit(std::shared_ptr<Null> term) {
    return _return("<eapv-error>");
  }

  void Printer::visit(std::shared_ptr<Value> term) {
    if(term->sort() == get_register().get_sort_manager().Int()) {
      // TODO: must we allow to have negative values or use (- v) with v >= 0 instead, + will interpreter work properly
      auto val = std::atol(term->raw().c_str());
      if(val < 0) {
        return _return(std::string("(- ") + std::to_string(-val) + ")");
      }
    }
    return _return(term->raw());
  }

  std::string Printer::result() {
    auto r = _stack.top();
    _stack.pop();
    return r;
  }

  void Printer::_return(const std::string &r) {
    _stack.push(r);
  }

}
