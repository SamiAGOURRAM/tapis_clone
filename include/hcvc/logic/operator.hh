//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>
#include "hcvc/program/type.hh"

namespace hcvc {

  class Context;

  //*-- Domain
  class Domain {
  public:
    virtual ~Domain();

    //*- methods

    virtual bool accept(const std::vector<const Type *> &types) const = 0;
  };

  //*-- VectorDomain
  class VectorDomain: public Domain {
  public:
    explicit VectorDomain(std::vector<const Type *> types);

    ~VectorDomain() override;

    //*- properties

    const std::vector<const Type *> &types() const;

    //*- methods

    bool accept(const std::vector<const Type *> &types) const override;

  private:
    const std::vector<const Type *> _types;
  };

  //*-- MinMaxDomain
  class MinMaxDomain: public Domain {
  public:
    explicit MinMaxDomain(const Type *type, long min = -1, long max = -1);

    ~MinMaxDomain() override;

    //*- methods

    bool accept(const std::vector<const Type *> &types) const override;

  private:
    long _min, _max;
    const Type *_type;
  };

  //*-- LambdaDomain
  class LambdaDomain: public Domain {
  public:
    explicit LambdaDomain(std::function<bool(const std::vector<const Type *> &)> accept_fun);

    ~LambdaDomain() override;

    //*- methods

    bool accept(const std::vector<const Type *> &types) const override;

  private:
    std::function<bool(const std::vector<const Type *> &)> _accept_fun;
  };

  //*-- Range
  class Range {
  public:
    Range();

    virtual ~Range() = 0;

    //*- methods

    virtual const Type *range(const std::vector<const Type *> &types) const = 0;
  };

  //*-- ConstantRange
  class ConstantRange: public Range {
  public:
    explicit ConstantRange(const Type *type);

    ~ConstantRange() override;

    //*- methods

    const Type *range(const std::vector<const Type *> &types) const override;

    const Type *type() const;

  private:
    const Type *_type;
  };

  //*-- LambdaRange
  class LambdaRange: public Range {
  public:
    explicit LambdaRange(std::function<const Type *(const std::vector<const Type *> &)> range_fun);

    ~LambdaRange() override;

    //*- methods

    const Type *range(const std::vector<const Type *> &types) const override;

  private:
    std::function<const Type *(const std::vector<const Type *> &)> _range_fun;
  };

  //*-- Operator
  class Operator {
  public:
    Operator(std::string name, const Domain *domain, const Range *range, Context &context);

    ~Operator();

    //*- properties

    /// Get the domain of the operator.
    inline const Domain &domain() const {
      return *_domain;
    }

    /// Get the name of the operator.
    inline const std::string &name() const {
      return _name;
    }

    /// Get the range of the operator.
    inline const Range &range() const {
      return *_range;
    }

    //*- statics

    /// Create an operator with given parameters in the given context.
    static Operator *create(std::string name, const Domain *domain, const Range *range, Context &context);

    inline static Operator *create(std::string name, const Domain *domain, const Type *range, Context &context) {
      return Operator::create(std::move(name), domain, new ConstantRange(range), context);
    }

  private:
    std::string _name;
    const Domain *_domain;
    const Range *_range;
    Context &_context;
  };

}
