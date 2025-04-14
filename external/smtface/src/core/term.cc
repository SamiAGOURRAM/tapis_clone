//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/term.hh"

#include <utility>
#include <smtface/core/context.hh>
#include <smtface/shorthands.hh>

namespace smtface::core {

  //*-- Term
  Term::Term(TermKind kind, Context &context) : _context(context), _id(context.get_new_term_id()), _kind(kind) {}

  Term::~Term() = default;

  Context &Term::context() const {
    return _context;
  }

  unsigned long Term::id() const {
    return _id;
  }

  TermKind Term::kind() const {
    return _kind;
  }

  bool Term::is_false() const {
    return false;
  }

  bool Term::is_true() const {
    return false;
  }

  bool Term::is_0() const {
    return false;
  }

  bool Term::is_1() const {
    return false;
  }

  bool Term::is_and() const {
    return false;
  }

  bool Term::is_not() const {
    return false;
  }

  bool Term::is_or() const {
    return false;
  }

  bool Term::is_add() const {
    return false;
  }

  bool Term::is_neg_1() const {
    return false;
  }

  bool Term::is_null() const {
    return false;
  }

  //*-- Expr
  Expr operator&&(const Expr &left, Expr right) {
    return smtface::Apply("and", {left, std::move(right)});
  }

  Expr operator||(const Expr &left, Expr right) {
    return smtface::Apply("or", {left, std::move(right)});
  }

  Expr operator!(const Expr &formula) {
    return smtface::Apply("not", {formula});
  }

  Expr operator+(const Expr &left, Expr right) {
    return smtface::Apply("+", {left, std::move(right)});
  }

  Expr operator-(const Expr &left, Expr right) {
    return smtface::Apply("-", {left, std::move(right)});
  }

  Expr operator*(const Expr &left, Expr right) {
    return smtface::Apply("*", {left, std::move(right)});
  }

  Expr operator/(const Expr &left, Expr right) {
    return smtface::Apply("/", {left, std::move(right)});
  }

  Expr operator==(const Expr &left, Expr right) {
    return smtface::Apply("=", {left, std::move(right)});
  }

  Expr operator>>(const Expr &left, const std::map<Expr, Expr> &map) {
    return smtface::Substitute(left, map);
  }

  //*-- ApplicationTerm
  ApplicationTerm::ApplicationTerm(const Function *func, std::vector<Expr> arguments, Context &context)
      : Term(TermKind::Application, context), _func(func), _arguments(std::move(arguments)) {}

  ApplicationTerm::~ApplicationTerm() = default;

  const std::vector<Expr> &ApplicationTerm::arguments() const {
    return _arguments;
  }

  const Function *ApplicationTerm::function() const {
    return _func;
  }

  const Sort *ApplicationTerm::sort() const {
    std::vector<const Sort *> arg_sorts;
    for(const auto &arg: _arguments) {
      arg_sorts.push_back(arg->sort());
    }
    return _func->range()->range(arg_sorts);
  }

  bool ApplicationTerm::is_and() const {
    return _func->name() == "and";
  }

  bool ApplicationTerm::is_or() const {
    return _func->name() == "or";
  }

  bool ApplicationTerm::is_add() const {
    return _func->name() == "+";
  }

  bool ApplicationTerm::is_not() const {
    return _func->name() == "not";
  }

  bool ApplicationTerm::is_neg_1() const {
    return _func->name() == "-" && _arguments.size() == 1 && _arguments.front()->is_1();
  }

  void ApplicationTerm::accept(Visitor &visitor) {
    std::shared_ptr<ApplicationTerm> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- QuantifiedFormula
  QuantifiedFormula::QuantifiedFormula(Quantifier quantifier, std::vector<Expr> qvariables, Expr formula,
                                       Context &context)
      : Term(TermKind::Quantified, context), _quantifier(quantifier), _qvariables(std::move(qvariables)),
        _formula(formula) {}

  QuantifiedFormula::~QuantifiedFormula() = default;

  Quantifier QuantifiedFormula::quantifier() const {
    return _quantifier;
  }

  const std::vector<Expr> &QuantifiedFormula::quantified_variables() const {
    return _qvariables;
  }

  Expr QuantifiedFormula::formula() const {
    return _formula;
  }

  const Sort *QuantifiedFormula::sort() const {
    return get_register().get_sort_manager().Bool();
  }

  void QuantifiedFormula::accept(Visitor &visitor) {
    std::shared_ptr<QuantifiedFormula> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- Null
  Null::Null(Context &context) : Term(TermKind::Null, context) {}

  Null::~Null() = default;

  const Sort *Null::sort() const {
    return get_register().get_sort_manager().Null();
  }

  bool Null::is_null() const {
    return true;
  }

  void Null::accept(Visitor &visitor) {
    std::shared_ptr<Null> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- Value
  Value::Value(std::string raw, const Sort *sort, Context &context) : _raw(std::move(raw)), _sort(sort),
                                                                      Term(TermKind::Value, context) {}

  Value::~Value() = default;

  const std::string &Value::raw() const {
    return _raw;
  }

  const Sort *Value::sort() const {
    return _sort;
  }

  bool Value::is_false() const {
    return _raw == "false";
  }

  bool Value::is_true() const {
    return _raw == "true";
  }

  bool Value::is_0() const { // TODO: real, hexa, bin
    return _raw == "0";
  }

  bool Value::is_1() const { // TODO: real, hexa, bin
    return _raw == "1";
  }

  bool Value::is_neg_1() const {
    return _raw == "-1";
  }

  void Value::accept(Visitor &visitor) {
    std::shared_ptr<Value> ptr(shared_from_this());
    visitor.visit(ptr);
  }

}
