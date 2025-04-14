//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <stack>
#include "hcvc/program/variable.hh"
#include "tapis/engines/options.hh"
#include "attribute.hh"
#include "tapis/engines/hornice/qdt/quantifier.hh"

namespace tapis::HornICE::qdt {

  //*-- Enumerator
  class Enumerator {
  public:
    Enumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
               AttributeManager &attribute_manager,
               hcvc::Context &context);

    virtual ~Enumerator();

    //*- properties

    inline const std::set<const Attribute *> &attributes() const {
      return _attributes;
    }

    inline AttributeManager &attribute_manager() {
      return _attribute_manager;
    }

    inline hcvc::Context &context() {
      return _context;
    }

    virtual bool has_terminated() const = 0;

    virtual bool is_finite() const = 0;

    virtual bool is_incremental() const = 0;

    inline const hcvc::Predicate *predicate() const {
      return _predicate;
    }

    inline const std::vector<hcvc::Expr> &terms() const {
      return _terms;
    }

    //*- methods

    virtual void enumerate() = 0;

  private:
    hcvc::Context &_context;
    const hcvc::Predicate *_predicate;
    AttributeManager &_attribute_manager;
    std::vector<hcvc::Expr> _terms;

  protected:
    std::set<const Attribute *> _attributes;
  };

  //*-- EmptyEnumerator
  class EmptyEnumerator: public Enumerator {
  public:
    EmptyEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                    AttributeManager &attribute_manager, hcvc::Context &context);

    ~EmptyEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;
  };

  //*-- BooleanEnumerator
  class BooleanEnumerator: public Enumerator {
  public:
    BooleanEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                      AttributeManager &attribute_manager, hcvc::Context &context);

    ~BooleanEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_terminated;
  };

  //*-- EqualityEnumerator
  class EqualityEnumerator: public Enumerator {
  public:
    EqualityEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                       AttributeManager &attribute_manager, hcvc::Context &context);

    ~EqualityEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_terminated;
  };

  //*-- UpperBoundEnumerator
  class UpperBoundEnumerator: public Enumerator {
  public:
    UpperBoundEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                         AttributeManager &attribute_manager, hcvc::Context &context);

    ~UpperBoundEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_terminated;
  };

  //*-- StrictUpperBoundEnumerator
  class StrictUpperBoundEnumerator: public Enumerator {
  public:
    StrictUpperBoundEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                               AttributeManager &attribute_manager, hcvc::Context &context);

    ~StrictUpperBoundEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_terminated;
  };

  //*-- IntervalEnumerator
  class IntervalEnumerator: public Enumerator {
  public:
    IntervalEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                       AttributeManager &attribute_manager, hcvc::Context &context);

    ~IntervalEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_started;
    long _bound;
    std::list<hcvc::Expr> _bases;
  };

  //*-- DifferenceBoundEnumerator
  class DifferenceBoundEnumerator: public Enumerator {
  public:
    DifferenceBoundEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                              AttributeManager &attribute_manager, hcvc::Context &context);

    ~DifferenceBoundEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_started;
    long _bound;
    std::list<hcvc::Expr> _bases;
  };

  //*-- OctagonEnumerator
  class OctagonEnumerator: public Enumerator {
  public:
    OctagonEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                      AttributeManager &attribute_manager, hcvc::Context &context);

    ~OctagonEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_started;
    long _bound;
    std::list<hcvc::Expr> _bases;
  };

  //*-- OctahedronEnumerator
  class OctahedronEnumerator: public Enumerator {
  public:
    OctahedronEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms, unsigned long n,
                         AttributeManager &attribute_manager, hcvc::Context &context);

    ~OctahedronEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    unsigned long _n;
    bool _has_started;
    long _bound;
    std::list<hcvc::Expr> _bases;
  };

  //*-- PolyhedraEnumerator
  class PolyhedraEnumerator: public Enumerator {
  public:
    PolyhedraEnumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                        AttributeManager &attribute_manager, hcvc::Context &context);

    ~PolyhedraEnumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    bool _has_started;
    long _bound;
  };

  //*-- Kmod0Enumerator
  class Kmod0Enumerator: public Enumerator {
  public:
    Kmod0Enumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                         AttributeManager &attribute_manager, hcvc::Context &context);

    ~Kmod0Enumerator() override;

    //*- properties

    bool has_terminated() const override;

    bool is_finite() const override;

    bool is_incremental() const override;

    //*- methods

    void enumerate() override;

  private:
    long _bound;
  };

  //*-- PropertyAccessAnalyzer
  class PropertyAccessAnalyzer: public hcvc::Visitor {
  public:
    PropertyAccessAnalyzer();

    std::vector<std::pair<std::vector<hcvc::Expr>, std::vector<std::pair<hcvc::Expr, hcvc::Expr>>>>
    analyze(const hcvc::Expr &f);

    void visit(std::shared_ptr<hcvc::OperatorApplication> term) override;

    void visit(std::shared_ptr<hcvc::Constant> term) override;

    void visit(std::shared_ptr<hcvc::BooleanLiteral> term) override;

    void visit(std::shared_ptr<hcvc::IntegerLiteral> term) override;

    void visit(std::shared_ptr<hcvc::ArrayLiteral> term) override;

    void visit(std::shared_ptr<hcvc::QuantifiedFormula> term) override;

    void visit(std::shared_ptr<hcvc::PredicateApplication> term) override;

  private:
    bool _look_accesses;
    std::vector<std::pair<hcvc::Expr, hcvc::Expr>> _accesses;
    std::stack<std::vector<hcvc::Expr>> _stack;
    std::vector<std::pair<std::vector<hcvc::Expr>, std::vector<std::pair<hcvc::Expr, hcvc::Expr>>>> _results;
  };

  //*-- PropertyAttributeAnalyzer
  class PropertyAttributeAnalyzer {
  public:
    PropertyAttributeAnalyzer(QuantifierManager &quantifier_manager, AttributeManager &attribute_manager);

    std::vector<const Attribute *> analyze(const hcvc::ClauseSet &clauses, const hcvc::Predicate *predicate);

  private:
    QuantifierManager &_quantifier_manager;
    AttributeManager &_attribute_manager;
  };

  //*-- PatternExtractor
  class PatternExtractor: public hcvc::Visitor {
  public:
    std::pair<std::vector<hcvc::Expr>, std::vector<hcvc::Expr>> extract(const hcvc::ClauseSet &clauses);

    void visit(std::shared_ptr<hcvc::OperatorApplication> term) override;

    void visit(std::shared_ptr<hcvc::Constant> term) override;

    void visit(std::shared_ptr<hcvc::BooleanLiteral> term) override;

    void visit(std::shared_ptr<hcvc::IntegerLiteral> term) override;

    void visit(std::shared_ptr<hcvc::ArrayLiteral> term) override;

    void visit(std::shared_ptr<hcvc::QuantifiedFormula> term) override;

    void visit(std::shared_ptr<hcvc::PredicateApplication> term) override;

  private:
    std::pair<std::vector<hcvc::Expr>, std::vector<hcvc::Expr>> _results;
  };

  //*-- create_enumerator
  Enumerator *create_enumerator(AttributeDomain domain, const hcvc::Predicate *predicate,
                                const std::vector<hcvc::Expr> &terms,
                                AttributeManager &attribute_manager, hcvc::Context &context);

  //*-- EnumerationAttributeSynthesizer
  class EnumerationAttributeSynthesizer: public AttributeSynthesizer {
  public:
    explicit EnumerationAttributeSynthesizer(QuantifierManager &quantifier_manager);

    ~EnumerationAttributeSynthesizer() override;

    //*- methods

    void set_predicate(const std::set<const hcvc::Predicate *> &predicates) override;

    void setup() override;

    std::pair<std::set<const Attribute *>, std::set<const Attribute *>>
    attributes(const hcvc::Predicate *predicate) const override;

    bool generate_attributes(DiagramPartialReachabilityGraph *sample) override;

  private:
    std::set<const hcvc::Predicate *> _predicates;
    std::set<const Attribute *> _init_idx_attributes;
    std::map<const hcvc::Predicate *, std::vector<Enumerator *>> _index_enumerators;
    std::map<const hcvc::Predicate *, std::vector<Enumerator *>> _data_enumerators;
    QuantifierManager &_quantifier_manager;
  };

}
