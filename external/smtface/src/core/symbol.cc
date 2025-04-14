//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/symbol.hh"

#include <algorithm>
#include <memory>
#include <utility>

namespace smtface::core {

  //*-- Symbol
  Symbol::Symbol(std::string name) : _name(std::move(name)) {}

  Symbol::~Symbol() = default;

  const std::string &Symbol::name() const {
    return _name;
  }

  //*-- Constant
  Constant::Constant(const std::string &name, const Sort *sort, Context &context)
      : Symbol(name), Term(TermKind::Constant, context), _sort(sort) {}

  Constant::~Constant() = default;

  const Sort *Constant::sort() const {
    return _sort;
  }

  void Constant::accept(Visitor &visitor) {
    std::shared_ptr<Constant> ptr(shared_from_this());
    visitor.visit(ptr);
  }

  //*-- Domain
  Domain::~Domain() = default;

  //*-- VectorDomain
  VectorDomain::VectorDomain(std::vector<const Sort *> sorts) : _sorts(std::move(sorts)) {}

  VectorDomain::~VectorDomain() = default;

  const std::vector<const Sort *> &VectorDomain::sorts() const {
    return _sorts;
  }

  bool VectorDomain::accept(const std::vector<const Sort *> &sorts) const {
    if(sorts.size() != _sorts.size()) {
      return false;
    }
    unsigned long i = 0;
    return std::all_of(sorts.begin(), sorts.end(), [&](const Sort *sort) {
      auto res = sorts[i] == _sorts[i];
      i++;
      return res;
    });
  }

  //*-- MinMaxDomain
  MinMaxDomain::MinMaxDomain(const Sort *sort, long min, long max) : _sort(sort), _min(min), _max(max) {}

  MinMaxDomain::~MinMaxDomain() = default;

  bool MinMaxDomain::accept(const std::vector<const Sort *> &sorts) const {
    if((_min != -1 && sorts.size() < _min) || (_max != -1 && _max < sorts.size())) {
      return false;
    }
    return std::all_of(sorts.begin(), sorts.end(), [=](const Sort *sort) {
      return sort == _sort;
    });
  }

  //*-- LambdaDomain
  LambdaDomain::LambdaDomain(std::function<bool(const std::vector<const Sort *> &)> accept_fun)
      : _accept_fun(std::move(accept_fun)) {}

  LambdaDomain::~LambdaDomain() = default;

  bool LambdaDomain::accept(const std::vector<const Sort *> &sorts) const {
    return _accept_fun(sorts);
  }

  //*-- Range
  Range::Range() = default;


  Range::~Range() = default;

  //*-- SimpleRange
  SimpleRange::SimpleRange(const Sort *sort) : _sort(sort) {}

  SimpleRange::~SimpleRange() = default;

  const Sort *SimpleRange::range(const std::vector<const Sort *> &sorts) const {
    return _sort;
  }

  const Sort *SimpleRange::sort() const {
    return _sort;
  }

  //*-- LambdaRange
  LambdaRange::LambdaRange(std::function<const Sort *(const std::vector<const Sort *> &)> range_fun)
      : _range_fun(std::move(range_fun)) {}

  LambdaRange::~LambdaRange() = default;

  const Sort *LambdaRange::range(const std::vector<const Sort *> &sorts) const {
    return _range_fun(sorts);
  }

  //*-- Function
  Function::Function(const std::string &name, const Domain *domain, const Range *range,
                     const std::vector<std::string> &tags, Context &context)
      : Symbol(name), _domain(domain), _range(range), _context(context) {
    for(auto &tag: tags) {
      _tags[tag] = true;
    }
  }

  Function::~Function() {
    delete _domain;
    delete _range;
  }

  const Domain &Function::domain() const {
    return *_domain;
  }

  const Range *Function::range() const {
    return _range;
  }

  bool Function::has_tag(const std::string &tag) const {
    return _tags.count(tag) > 0;
  }

  Expr Function::operator()(const std::vector<Expr> &arguments) const {
    return std::make_shared<ApplicationTerm>(this, arguments, _context);
  }

  //*-- SymbolManager
  SymbolManager::SymbolManager(Context &context) : _context(context) {}

  SymbolManager::~SymbolManager() {
    for(auto &[key, value]: _functions) {
      delete value;
    }
  }

  Expr SymbolManager::create_fresh_constant(const Sort *sort, const std::string &base) {
    if(_fresh_counter.count(base) == 0) {
      _fresh_counter[base] = 0;
    }
    while(_constants.count(base + std::to_string(++_fresh_counter[base])) != 0) {}
    auto name = base + std::to_string(_fresh_counter[base]);
    _constants[name] = std::shared_ptr<Constant>(new Constant(name, sort, _context));
    return _constants[name];
  }

  const Function *SymbolManager::create_function(const std::string &name, const Domain *domain, const Range *range,
                                                 const std::vector<std::string> &tags) {
    if(_functions.count(name) > 0) {
      return nullptr;
    }
    auto func = new Function(name, domain, range, tags, _context);
    _functions[name] = func;
    return func;
  }

  Expr SymbolManager::get_constant(const std::string &name) {
    if(_constants.count(name) > 0) {
      return _constants[name];
    }
    // TODO:
    return Expr();
  }

  const Function *SymbolManager::get_function(const std::string &name) const {
    if(_functions.count(name) == 0) {
      return nullptr;
    }
    return _functions.at(name);
  }

  Expr SymbolManager::get_or_create_constant(const std::string &name, const Sort *sort) {
    if(_constants.count(name) == 0) {
      _constants[name] = std::shared_ptr<Constant>(new Constant(name, sort, _context));
    }
    return _constants[name];
  }

}
