//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "smtface/core/sort.hh"

namespace smtface::core {

  class Context;

  class Function;

  //*-- TermKind
  enum class TermKind {
    Application,
    Quantified,
    Constant,
    Null,
    Value
  };

  class ApplicationTerm;

  class QuantifiedFormula;

  class Constant;

  class Null;

  class Value;

  //*-- Visitor
  class Visitor {
  public:

    //*- methods

    virtual void visit(std::shared_ptr<ApplicationTerm> term) = 0;

    virtual void visit(std::shared_ptr<QuantifiedFormula> term) = 0;

    virtual void visit(std::shared_ptr<Constant> term) = 0;

    virtual void visit(std::shared_ptr<Null> term) = 0;

    virtual void visit(std::shared_ptr<Value> term) = 0;
  };

  //*-- Term
  class Term {
  public:
    explicit Term(TermKind kind, Context &context);

    virtual ~Term();

    //*- properties

    Context &context() const;

    unsigned long id() const;

    TermKind kind() const;

    virtual const Sort *sort() const = 0;

    virtual bool is_true() const;

    virtual bool is_false() const;

    virtual bool is_0() const;

    virtual bool is_1() const;

    virtual bool is_and() const;

    virtual bool is_or() const;

    virtual bool is_add() const;

    virtual bool is_not() const;

    virtual bool is_neg_1() const;

    virtual bool is_null() const;

    //*- methods

    virtual void accept(Visitor &visitor) = 0;

  private:
    Context &_context;
    unsigned long _id;
    TermKind _kind;
  };

  //*-- Expr
  typedef std::shared_ptr<Term> Expr;

  Expr operator&&(const Expr &left, Expr right);

  Expr operator||(const Expr &left, Expr right);

  Expr operator!(const Expr &formula);

  Expr operator+(const Expr &left, Expr right);

  Expr operator-(const Expr &left, Expr right);

  Expr operator*(const Expr &left, Expr right);

  Expr operator/(const Expr &left, Expr right);

  Expr operator==(const Expr &left, Expr right);

  Expr operator>>(const Expr &left, const std::map<Expr, Expr> &map); // substitution

  //*-- ApplicationTerm
  class ApplicationTerm: public Term, public std::enable_shared_from_this<ApplicationTerm> {
  public:
    ApplicationTerm(const Function *func, std::vector<Expr> arguments, Context &context);

    ~ApplicationTerm() override;

    //*- properties

    const std::vector<Expr> &arguments() const;

    const Function *function() const;

    const Sort *sort() const override;

    bool is_and() const override;

    bool is_or() const override;

    bool is_add() const override;

    bool is_not() const override;

    bool is_neg_1() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    const Function *_func;
    std::vector<Expr> _arguments;
  };

  //*-- Quantifier
  enum class Quantifier {
    forall,
    exists
  };

  //*-- QuantifiedFormula
  class QuantifiedFormula: public Term, public std::enable_shared_from_this<QuantifiedFormula> {
  public:
    QuantifiedFormula(Quantifier quantifier, std::vector<Expr> qvariables, Expr formula, Context &context);

    ~QuantifiedFormula() override;

    //*- properties

    Quantifier quantifier() const;

    const std::vector<Expr> &quantified_variables() const;

    Expr formula() const;

    const Sort *sort() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    Quantifier _quantifier;
    std::vector<Expr> _qvariables;
    Expr _formula;
  };

  //*-- Null
  class Null: public Term, public std::enable_shared_from_this<Null> {
  public:
    explicit Null(Context &context);

    ~Null() override;

    //*- properties

    const Sort *sort() const override;

    bool is_null() const override;

    //*- methods

    void accept(Visitor &visitor) override;
  };

  //*-- Value
  class Value: public Term, public std::enable_shared_from_this<Value> {
  public:
    Value(std::string raw, const Sort *sort, Context &context);

    ~Value() override;

    //*- properties

    const std::string &raw() const;

    const Sort *sort() const override;

    bool is_true() const override;

    bool is_false() const override;

    bool is_0() const override;

    bool is_1() const override;

    bool is_neg_1() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    std::string _raw;
    const Sort *_sort;
  };

}
