//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/logic/term.hh"

namespace hcvc {

  class Module;

  class Function;

  //*-- PredicateKind
  enum class PredicateKind {
    invariant,
    precondition,
    summary
  };

  //*-- Predicate
  /**
   * An uninterpreted function in the clauses to be synthesized.
   */
  class Predicate {
  public:
    explicit Predicate(std::string name, PredicateKind kind);

    virtual ~Predicate();

    //*- properties

    /// Get the name of the predicate.
    inline const std::string &name() const {
      return _name;
    }

    /// Get the kind of the predicate
    inline PredicateKind kind() const {
      return _kind;
    }

    /// Get the parameter over which the invariant is defined.
    virtual const std::vector<Variable *> &parameters() const = 0;

    /// Determine whether this predicate may need a quantified solution.
    bool may_require_quantifiers() const;

    inline void add_segment_variable(const Variable *var) {
      _segment_variables.insert(var);
    }

    inline const std::set<const Variable *> &segment_variables() const {
      return _segment_variables;
    }

  private:
    std::string _name;
    PredicateKind _kind;
    std::set<const Variable *> _segment_variables;
  };

  //*-- InvariantPredicate
  /**
   * An loop invariant in the clauses to be synthesized.
   */
  class InvariantPredicate: public Predicate {
  public:
    InvariantPredicate(std::string name, std::vector<Variable *> parameters);

    ~InvariantPredicate() override;

    //*- properties

    /// Get the parameter over which the invariant is defined.
    const std::vector<Variable *> &parameters() const override;

    //*- statics

    static InvariantPredicate *create(Function *function, const std::string &name, std::vector<Variable *> parameters);

  private:
    std::vector<Variable *> _parameters;
  };

  //*-- FunctionPreconditionPredicate
  /**
   * An function precondition in the clauses to be synthesized.
   */
  class FunctionPreconditionPredicate: public Predicate {
  public:
    explicit FunctionPreconditionPredicate(Function *function);

    ~FunctionPreconditionPredicate() override;

    //*- properties

    /// Get the function for which this predicate captures the precondition.
    inline Function *function() const {
      return _function;
    }

    const std::vector<Variable *> &parameters() const override;

    //*- statics

    static FunctionPreconditionPredicate *create(Function *function);

  private:
    Function *_function;
    std::vector<Variable *> _parameters;
  };

  //*-- FunctionSummaryPredicate
  /**
   * An function summary in the clauses to be synthesized.
   */
  class FunctionSummaryPredicate: public Predicate {
  public:
    explicit FunctionSummaryPredicate(Function *function);

    ~FunctionSummaryPredicate() override;

    /// Get the function for which this predicate captures the summary.
    inline Function *function() const {
      return _function;
    }

    const std::vector<Variable *> &parameters() const override;

    //*- statics

    static FunctionSummaryPredicate *create(Function *function);

  private:
    Function *_function;
    std::vector<Variable *> _parameters;
  };

  //*-- PredicateApplication
  class PredicateApplication: public Term, public std::enable_shared_from_this<PredicateApplication> {
  public:
    PredicateApplication(Predicate *predicate, std::vector<Expr> arguments, Context &context);

    ~PredicateApplication() override;

    //*- properties

    inline const std::vector<Expr> &arguments() const {
      return _arguments;
    }

    inline Predicate *predicate() const {
      return _predicate;
    }

    const Type *type() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    Predicate *_predicate;
    std::vector<Expr> _arguments;
  };

}
