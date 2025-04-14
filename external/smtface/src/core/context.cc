//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/context.hh"

#include "smtface/core/register.hh"

namespace smtface::core {

  //*-- Context
  Context::Context() : _symbol_manager(*this), _term_ids(1) {
    Register::initialize_if_not();
    _null_expr = std::shared_ptr<Null>(new Null(*this));
  }

  Context::~Context() = default;

  Expr Context::apply(const std::string &name, const std::vector<Expr> &arguments) {
    auto func = _symbol_manager.get_function(name);
    if(func != nullptr) {
      // TODO: type checking
      return std::shared_ptr<ApplicationTerm>(new ApplicationTerm(func, arguments, *this));
    }
    return Expr();
  }

  Expr Context::constant(const std::string &name) {
    return _symbol_manager.get_constant(name);
  }

  Expr Context::constant(const std::string &name, const Sort *sort) {
    return _symbol_manager.get_or_create_constant(name, sort);
  }

  Expr Context::fresh_constant(const Sort *sort, const std::string &base) {
    return _symbol_manager.create_fresh_constant(sort, base);
  }

  const Function *Context::function(const std::string &name, const Domain *domain, const Sort *range,
                                    const std::vector<std::string> &tags) {
    return function(name, domain, new SimpleRange(range), tags);
  }

  const Function *Context::function(const std::string &name, const Domain *domain, const Range *range,
                                    const std::vector<std::string> &tags) {
    auto func = _symbol_manager.get_function(name);
    if(func == nullptr) {
      func = _symbol_manager.create_function(name, domain, range, tags);
    }
    return func;
  }

  const Function *Context::function(const std::string &name, const std::vector<const Sort *> &domain, const Sort *range,
                                    const std::vector<std::string> &tags) {
    return function(name, new VectorDomain(domain), new SimpleRange(range), tags);
  }

  const Function *Context::get_function(const std::string &name) const {
    return _symbol_manager.get_function(name);
  }

  bool Context::has_function(const std::string &name) const {
    return _symbol_manager.get_function(name) != nullptr;
  }

  Expr Context::null() {
    return _null_expr;
  }

  Expr Context::value(const std::string &raw, const Sort *sort) {
    if(_values.count(sort) > 0) {
      if(_values[sort].count(raw) > 0) {
        return _values[sort][raw];
      }
    }
    auto val = std::shared_ptr<Value>(new Value(raw, sort, *this));
    _values[sort][raw] = val;
    return val;
  }

  Expr Context::variable(const std::string &name, const Sort *sort) {
    return std::shared_ptr<Constant>(new Constant(name, sort, *this));
  }

  unsigned long Context::get_new_term_id() {
    return _term_ids++;
  }

}
