//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include <utility>

#include "hcvc/context.hh"
#include "hcvc/logic/operator.hh"

namespace hcvc {

  //*-- Domain
  Domain::~Domain() = default;

  //*-- VectorDomain
  VectorDomain::VectorDomain(std::vector<const Type *> types)
      : _types(std::move(types)) {}

  VectorDomain::~VectorDomain() = default;

  const std::vector<const Type *> &VectorDomain::types() const {
    return _types;
  }

  bool VectorDomain::accept(const std::vector<const Type *> &types) const {
    if(types.size() != _types.size()) {
      return false;
    }
    unsigned long i = 0;
    return std::all_of(types.begin(), types.end(), [&](const Type *type) {
      auto res = types[i] == _types[i];
      i++;
      return res;
    });
  }

  //*-- MinMaxDomain
  MinMaxDomain::MinMaxDomain(const Type *type, long min, long max)
      : _type(std::move(type)),
        _min(min),
        _max(max) {}

  MinMaxDomain::~MinMaxDomain() = default;

  bool MinMaxDomain::accept(const std::vector<const Type *> &types) const {
    if((_min != -1 && types.size() < _min) || (_max != -1 && _max < types.size())) {
      return false;
    }
    return std::all_of(types.begin(), types.end(), [=](const Type *type) {
      return type == _type;
    });
  }

  //*-- LambdaDomain
  LambdaDomain::LambdaDomain(std::function<bool(const std::vector<const Type *> &)> accept_fun)
      : _accept_fun(std::move(accept_fun)) {}

  LambdaDomain::~LambdaDomain() = default;

  bool LambdaDomain::accept(const std::vector<const Type *> &types) const {
    return _accept_fun(types);
  }

  //*-- Range
  Range::Range() = default;


  Range::~Range() = default;

  //*-- ConstantRange
  ConstantRange::ConstantRange(const Type *type)
      : _type(std::move(type)) {}

  ConstantRange::~ConstantRange() = default;

  const Type *ConstantRange::range(const std::vector<const Type *> &types) const {
    return _type;
  }

  const Type *ConstantRange::type() const {
    return _type;
  }

  //*-- LambdaRange
  LambdaRange::LambdaRange(std::function<const Type *(const std::vector<const Type *> &)> range_fun)
      : _range_fun(std::move(range_fun)) {}

  LambdaRange::~LambdaRange() = default;

  const Type *LambdaRange::range(const std::vector<const Type *> &types) const {
    return _range_fun(types);
  }

  //*-- Operator
  Operator::Operator(std::string name, const Domain *domain, const Range *range, Context &context)
      : _name(std::move(name)),
        _domain(domain),
        _range(range),
        _context(context) {}

  Operator::~Operator() {
    delete _domain;
    delete _range;
  }

  Operator *Operator::create(std::string name, const Domain *domain, const Range *range, Context &context) {
    auto op = new Operator(name, domain, range, context);
    context._operators[name] = op;
    return op;
  }

}
