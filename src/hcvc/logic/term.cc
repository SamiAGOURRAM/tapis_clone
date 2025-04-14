//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/logic/term.hh"

#include <utility>
#include "hcvc/context.hh"
#include "hcvc/module.hh"
#include "hcvc/logic/evaluator.hh"
#include "hcvc/logic/substituter.hh"
#include "hcvc/logic/printer.hh"
#include "hcvc/program/variable.hh"

namespace hcvc {

  //*-- Term
  Term::Term(TermKind termKind, Context &context)
      : _termKind(termKind),
        _context(context) {}

  Term::~Term() = default;

  //*-- Expr
  Expr operator&&(const Expr &left, const Expr &right) {
    return left->context().apply("and", {left, right});
  }

  Expr operator||(const Expr &left, const Expr &right) {
    return left->context().apply("or", {left, right});
  }

  Expr operator!(const Expr &formula) {
    return formula->context().apply("not", {formula});
  }

  Expr operator+(const Expr &left, const Expr &right) {
    return left->context().apply("+", {left, right});
  }

  Expr operator-(const Expr &left, const Expr &right) {
    return left->context().apply("-", {left, right});
  }

  Expr operator-(const Expr &left) {
    return left->context().apply("-", {left});
  }

  Expr operator*(const Expr &left, const Expr &right) {
    return left->context().apply("*", {left, right});
  }

  Expr operator==(const Expr &left, const Expr &right) {
    return left->context().apply("=", {left, right});
  }

  Expr operator<=(const Expr &left, const Expr &right) {
    return left->context().apply("<=", {left, right});
  }

  Expr operator>(const Expr &left, const Expr &right) {
    return left->context().apply(">", {left, right});
  }

  std::ostream &operator<<(std::ostream &stream, const Expr &formula) {
    Printer p;
    stream << p.to_string(formula);
    return stream;
  }

  std::string to_string(const Expr &formula) {
    return Printer().to_string(formula);
  }

  Expr substitute(const Expr &left, const std::map<Expr, Expr> &map) {
    return Substituter(map).substitute(left);
  }

  Expr evaluate(const Expr &left, const std::map<Expr, Expr> &map) {
    return Evaluator(map).evaluate(left);
  }

  //*-- OperatorApplication
  OperatorApplication::OperatorApplication(const Operator *operat0r, std::vector<Expr> arguments, Context &context)
      : Term(TermKind::OpApp, context),
        _operat0r(operat0r),
        _arguments(std::move(arguments)) {}

  OperatorApplication::~OperatorApplication() = default;

  const Type *OperatorApplication::type() const {
    std::vector<const Type *> arg_types;
    arg_types.reserve(_arguments.size());
    for(const auto &arg: _arguments) {
      arg_types.push_back(arg->type());
    }
    return _operat0r->range().range(arg_types);
  }

  void OperatorApplication::accept(Visitor &visitor) {
    std::shared_ptr<OperatorApplication> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  class OperationExtractor: public Visitor {
  public:
    //*- methods

    std::set<const Operator *> extract(const Expr &expr) {
      expr->accept(*this);
      return _operations;
    }

    void visit(std::shared_ptr<OperatorApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
      _operations.insert(term->operat0r());
    }

    void visit(std::shared_ptr<Constant> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<BooleanLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<IntegerLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<ArrayLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<QuantifiedFormula> term) override {
    }

    void visit(std::shared_ptr<PredicateApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
    }

    std::set<const Operator *> _operations;
  };

  std::set<const Operator *> get_operations(const Expr &left) {
    return OperationExtractor().extract(left);
  }

  //*-- Constant
  Constant::Constant(std::string name, const Type *type, Context &context)
      : Term(TermKind::Constant, context),
        _name(std::move(name)),
        _type(type) {}

  Constant::~Constant() = default;

  const Type *Constant::type() const {
    return _type;
  }

  bool Constant::is_variable_constant() const {
    return false;
  }

  void Constant::accept(Visitor &visitor) {
    std::shared_ptr<Constant> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  class ConstantExtractor: public Visitor {
  public:
    //*- methods

    std::set<Expr> extract(const Expr &expr) {
      expr->accept(*this);
      return _constants;
    }

    void visit(std::shared_ptr<OperatorApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
    }

    void visit(std::shared_ptr<Constant> term) override {
      _constants.insert(term);
    }

    void visit(std::shared_ptr<BooleanLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<IntegerLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<ArrayLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<QuantifiedFormula> term) override {
    }

    void visit(std::shared_ptr<PredicateApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
    }

    std::set<Expr> _constants;
  };

  std::set<Expr> get_constants(const Expr &left) {
    return ConstantExtractor().extract(left);
  }

  std::set<Expr> get_constants(const std::vector<Expr> &exprs) {
    ConstantExtractor ce;
    for(const auto &expr: exprs) {
      ce.extract(expr);
    }
    return ce._constants;
  }

  //*-- VariableConstant
  VariableConstant::VariableConstant(const Variable *variable, unsigned long index, Context &context)
      : Constant(variable->name() + "@" + std::to_string(index), variable->type(), context),
        _variable(variable),
        _index(index) {}

  VariableConstant::~VariableConstant() = default;

  bool VariableConstant::is_variable_constant() const {
    return true;
  }

  class VariableExtractor: public Visitor {
  public:
    //*- methods

    std::set<const Variable *> extract(const Expr &expr) {
      expr->accept(*this);
      return _variables;
    }

    void visit(std::shared_ptr<OperatorApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
    }

    void visit(std::shared_ptr<Constant> term) override {
      if(term->is_variable_constant()) {
        auto vc = std::dynamic_pointer_cast<VariableConstant>(term);
        _variables.insert(vc->variable());
      }
    }

    void visit(std::shared_ptr<BooleanLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<IntegerLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<ArrayLiteral> term) override {
      // do nothing
    }

    void visit(std::shared_ptr<QuantifiedFormula> term) override {
    }

    void visit(std::shared_ptr<PredicateApplication> term) override {
      for(const auto &arg: term->arguments()) {
        arg->accept(*this);
      }
    }

    std::set<const Variable *> _variables;
  };

  std::set<const Variable *> get_variables(const Expr &left) {
    return VariableExtractor().extract(left);
  }

  //*-- Literal
  Literal::Literal(TermKind kind, Context &context)
      : Term(kind, context) {}

  Literal::~Literal() = default;

  //*-- BooleanLiteral
  BooleanLiteral::BooleanLiteral(bool value, Context &context)
      : Literal(TermKind::BooleanLiteral, context),
        _value(value) {}

  BooleanLiteral::~BooleanLiteral() = default;

  const Type *BooleanLiteral::type() const {
    return this->context().type_manager().bool_type();
  }

  void BooleanLiteral::accept(Visitor &visitor) {
    std::shared_ptr<BooleanLiteral> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- IntegerLiteral
  IntegerLiteral::IntegerLiteral(std::string value, const Type *type, Context &context)
      : Literal(TermKind::IntegerLiteral, context),
        _value(std::move(value)),
        _type(type) {}

  IntegerLiteral::~IntegerLiteral() = default;

  const Type *IntegerLiteral::type() const {
    return _type;
  }

  void IntegerLiteral::accept(Visitor &visitor) {
    std::shared_ptr<IntegerLiteral> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- ArrayLiteral
  ArrayLiteral::ArrayLiteral(std::vector<Expr> values, const Type *type, hcvc::Context &context)
      : Literal(TermKind::ArrayLiteral, context),
        _values(std::move(values)),
        _type(type) {}

  ArrayLiteral::~ArrayLiteral() = default;

  const Type *ArrayLiteral::type() const {
    return _type;
  }

  void ArrayLiteral::accept(hcvc::Visitor &visitor) {
    std::shared_ptr<ArrayLiteral> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- QuantifiedFormula
  QuantifiedFormula::QuantifiedFormula(hcvc::Quantifier kind, std::vector<Expr> quantifiers, hcvc::Expr formula,
                                       Context &context)
      : Term(TermKind::QuantifiedFormula, context),
        _kind(kind),
        _quantifiers(std::move(quantifiers)),
        _formula(std::move(formula)) {}

  const Type *QuantifiedFormula::type() const {
    return this->context().type_manager().bool_type();
  }

  void QuantifiedFormula::accept(hcvc::Visitor &visitor) {
    std::shared_ptr<QuantifiedFormula> ptr(shared_from_this());
    visitor.visit(ptr);
  }

}
