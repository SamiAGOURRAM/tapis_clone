//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include "hcvc/logic/operator.hh"
#include "hcvc/program/type.hh"

namespace hcvc {

  class BooleanLiteral;

  class Constant;

  class Context;

  class IntegerLiteral;

  class ArrayLiteral;

  class OperatorApplication;

  class PredicateApplication;

  class QuantifiedFormula;

  class Variable;

  //*-- TermKind
  enum class TermKind {
    OpApp, // operator application
    PredApp, // predicate application
    Constant, // a logical constant/variable
    BooleanLiteral, // boolean literal value
    IntegerLiteral, // integer literal value
    ArrayLiteral, // integer literal value
    QuantifiedFormula // for quantifier formula
  };

  //*-- Visitor
  class Visitor {
  public:

    //*- methods

    virtual void visit(std::shared_ptr<OperatorApplication> term) = 0;

    virtual void visit(std::shared_ptr<Constant> term) = 0;

    virtual void visit(std::shared_ptr<BooleanLiteral> term) = 0;

    virtual void visit(std::shared_ptr<IntegerLiteral> term) = 0;

    virtual void visit(std::shared_ptr<ArrayLiteral> term) = 0;

    virtual void visit(std::shared_ptr<QuantifiedFormula> term) = 0;

    virtual void visit(std::shared_ptr<PredicateApplication> term) = 0;
  };

  //*-- Term
  class Term {
  public:
    Term(TermKind termKind, Context &context);

    virtual ~Term();

    //*-- properties

    /// Get the HCVC context.
    inline Context &context() const {
      return _context;
    }

    /// Get the kind of the term.
    inline TermKind kind() const {
      return _termKind;
    }

    /// Get the type of the term.
    virtual const Type *type() const = 0;

    //*- methods

    virtual void accept(Visitor &visitor) = 0;

  private:
    TermKind _termKind;
    Context &_context;
  };

  //*-- Expr
  typedef std::shared_ptr<Term> Expr;

  Expr operator&&(const Expr &left, const Expr &right);

  Expr operator||(const Expr &left, const Expr &right);

  Expr operator!(const Expr &formula);

  Expr operator+(const Expr &left, const Expr &right);

  Expr operator-(const Expr &left, const Expr &right);

  Expr operator-(const Expr &left);

  Expr operator*(const Expr &left, const Expr &right);

  Expr operator==(const Expr &left, const Expr &right);

  Expr operator<=(const Expr &left, const Expr &right);

  Expr operator>(const Expr &left, const Expr &right);

  std::ostream &operator<<(std::ostream &stream, const Expr &formula);

  std::string to_string(const Expr &formula);

  Expr substitute(const Expr &left, const std::map<Expr, Expr> &map);

  Expr evaluate(const Expr &left, const std::map<Expr, Expr> &map);

  //*-- OperatorApplication
  class OperatorApplication: public Term, public std::enable_shared_from_this<OperatorApplication> {
  public:
    OperatorApplication(const Operator *operat0r, std::vector<Expr> arguments, Context &context);

    ~OperatorApplication() override;

    //*- properties

    inline const std::vector<Expr> &arguments() const {
      return _arguments;
    }

    inline const Operator *operat0r() const {
      return _operat0r;
    }

    const Type *type() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    const Operator *_operat0r;
    std::vector<Expr> _arguments;
  };

  inline bool is_add(const Expr &left) {
    return left->kind() == TermKind::OpApp &&
           std::dynamic_pointer_cast<OperatorApplication>(left)->operat0r()->name() == "+";
  }

  inline bool is_and(const Expr &left) {
    return left->kind() == TermKind::OpApp &&
           std::dynamic_pointer_cast<OperatorApplication>(left)->operat0r()->name() == "and";
  }

  inline bool is_or(const Expr &left) {
    return left->kind() == TermKind::OpApp &&
           std::dynamic_pointer_cast<OperatorApplication>(left)->operat0r()->name() == "or";
  }

  std::set<const Operator *> get_operations(const Expr &left);

  //*-- Constant
  class Constant: public Term, public std::enable_shared_from_this<Constant> {
  public:
    Constant(std::string name, const Type *type, Context &context);

    ~Constant() override;

    //*- properties

    inline const std::string &name() const {
      return _name;
    }

    const Type *type() const override;

    virtual bool is_variable_constant() const;

    //*- methods

    void accept(Visitor &visitor) override;

    /// Create a constant with given parameters.
    inline static Expr create(const std::string &name, const Type *type, Context &context) {
      return std::make_shared<Constant>(name, type, context);
    }

  private:
    std::string _name;
    const Type *_type;
  };

  std::set<Expr> get_constants(const Expr &left);

  std::set<Expr> get_constants(const std::vector<Expr> &exprs);

  //*-- VariableConstant
  class VariableConstant: public Constant {
  public:
    VariableConstant(const Variable *variable, unsigned long index, Context &context);

    ~VariableConstant() override;

    //*- properties

    bool is_variable_constant() const override;

    /// Get the variable.
    const Variable *variable() const {
      return _variable;
    }

    //*- methods

    inline unsigned long index() const {
      return _index;
    }

    /// Get the next constant of the variable.
    inline Expr next() {
      return std::make_shared<VariableConstant>(_variable, _index + 1, this->context());
    }

    //*- statics

    /// Create a variable constant with given parameters.
    inline static Expr create(const Variable *variable, unsigned long index, Context &context) {
      return std::make_shared<VariableConstant>(variable, index, context);
    }

  private:
    const Variable *_variable;
    unsigned long _index;
  };

  std::set<const Variable *> get_variables(const Expr &left);

  //*-- Literal
  class Literal: public Term {
  public:
    Literal(TermKind kind, Context &context);

    ~Literal() override;
  };

  //*-- BooleanLiteral
  class BooleanLiteral: public Literal, public std::enable_shared_from_this<BooleanLiteral> {
  public:
    BooleanLiteral(bool value, Context &context);

    ~BooleanLiteral() override;

    //*- properties

    const Type *type() const override;

    /// Get the value of the literal.
    inline bool value() const {
      return _value;
    }

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    bool _value;
  };

  inline bool is_true(const Expr &left) {
    return left->kind() == TermKind::BooleanLiteral &&
           std::dynamic_pointer_cast<BooleanLiteral>(left)->value();
  }

  inline bool is_false(const Expr &left) {
    return left->kind() == TermKind::BooleanLiteral &&
           !std::dynamic_pointer_cast<BooleanLiteral>(left)->value();
  }

  //*-- IntegerLiteral
  class IntegerLiteral: public Literal, public std::enable_shared_from_this<IntegerLiteral> {
  public:
    IntegerLiteral(std::string value, const Type *type, Context &context);

    ~IntegerLiteral() override;

    //*- properties

    const Type *type() const override;

    /// Get the value of the integer in string.
    inline std::string value() const {
      return _value;
    }

    //*- methods

    void accept(Visitor &visitor) override;

    //*- statics

    static Expr get(const std::string &value, const Type *type, Context &context) {
      return std::make_shared<IntegerLiteral>(value, type, context);
    }

  private:
    std::string _value;
    const Type *_type;
  };

  inline bool is_0(const Expr &left) {
    return left->kind() == TermKind::IntegerLiteral &&
           std::dynamic_pointer_cast<IntegerLiteral>(left)->value() == "0";
  }

  inline bool is_1(const Expr &left) {
    return left->kind() == TermKind::IntegerLiteral &&
           std::dynamic_pointer_cast<IntegerLiteral>(left)->value() == "1";
  }

  inline bool is_neg_1(const Expr &left) {
    return left->kind() == TermKind::IntegerLiteral &&
           std::dynamic_pointer_cast<IntegerLiteral>(left)->value() == "-1";
  }

  //*-- ArrayLiteral
  class ArrayLiteral: public Literal, public std::enable_shared_from_this<ArrayLiteral> {
  public:
    ArrayLiteral(std::vector<Expr> values, const Type *type, Context &context);

    ~ArrayLiteral() override;

    //*- properties

    const Type *type() const override;

    /// Get the value of the integer in string.
    inline const std::vector<Expr> &values() const {
      return _values;
    }

    //*- methods

    void accept(Visitor &visitor) override;

    //*- statics

    static Expr get(std::vector<Expr> values, const Type *type, Context &context) {
      return std::make_shared<ArrayLiteral>(std::move(values), type, context);
    }

  private:
    std::vector<Expr> _values;
    const Type *_type;
  };

  //*-- Quantifier
  enum class Quantifier: int {
    ForAll,
    Exists
  };

  //*-- QuantifiedFormula
  class QuantifiedFormula: public Term, public std::enable_shared_from_this<QuantifiedFormula> {
  public:
    QuantifiedFormula(Quantifier kind, std::vector<Expr> quantifiers, Expr formula, Context &context);

    //*- properties

    inline Expr formula() const {
      return _formula;
    }

    inline Quantifier quantifier_kind() const {
      return _kind;
    }

    inline const std::vector<Expr> &quantifiers() const {
      return _quantifiers;
    }

    const Type *type() const override;

    //*- methods

    void accept(Visitor &visitor) override;

    //*- statics

    static Expr create(Quantifier kind, std::vector<Expr> quantifiers, Expr formula, Context &context) {
      return std::make_shared<QuantifiedFormula>(kind, quantifiers, formula, context);
    }

  private:
    Quantifier _kind;
    std::vector<Expr> _quantifiers;
    Expr _formula;
  };

}
