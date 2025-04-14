//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include "smtface/core/term.hh"

namespace smtface::core {

  //*-- Symbol
  class Symbol {
  public:
    explicit Symbol(std::string name);

    virtual ~Symbol();

    //*- properties

    const std::string &name() const;

  private:
    std::string _name;
  };

  //*-- Constant
  class Constant: public Symbol, public Term, public std::enable_shared_from_this<Constant> {
  public:
    Constant(const std::string &name, const Sort *sort, Context &context);

    ~Constant() override;

    //*- properties

    const Sort *sort() const override;

    //*- methods

    void accept(Visitor &visitor) override;

  private:
    const Sort *_sort;
  };

  //*-- Domain
  class Domain {
  public:
    virtual ~Domain();

    //*- methods

    virtual bool accept(const std::vector<const Sort *> &sorts) const = 0;
  };

  //*-- VectorDomain
  class VectorDomain: public Domain {
  public:
    explicit VectorDomain(std::vector<const Sort *> sorts);

    ~VectorDomain() override;

    //*- properties

    const std::vector<const Sort *> &sorts() const;

    //*- methods

    bool accept(const std::vector<const Sort *> &sorts) const override;

  private:
    const std::vector<const Sort *> _sorts;
  };

  //*-- MinMaxDomain
  class MinMaxDomain: public Domain {
  public:
    explicit MinMaxDomain(const Sort *sort, long min = -1, long max = -1);

    ~MinMaxDomain() override;

    //*- methods

    bool accept(const std::vector<const Sort *> &sorts) const override;

  private:
    long _min, _max;
    const Sort *_sort;
  };

  //*-- LambdaDomain
  class LambdaDomain: public Domain {
  public:
    explicit LambdaDomain(std::function<bool(const std::vector<const Sort *> &)> accept_fun);

    ~LambdaDomain() override;

    //*- methods

    bool accept(const std::vector<const Sort *> &sorts) const override;

  private:
    std::function<bool(const std::vector<const Sort *> &)> _accept_fun;
  };

  //*-- Range
  class Range {
  public:
    Range();

    virtual ~Range() = 0;

    //*- methods

    virtual const Sort *range(const std::vector<const Sort *> &sorts) const = 0;
  };

  //*-- SimpleRange
  class SimpleRange: public Range {
  public:
    explicit SimpleRange(const Sort *sort);

    ~SimpleRange() override;

    //*- methods

    const Sort *range(const std::vector<const Sort *> &sorts) const override;

    const Sort *sort() const;

  private:
    const Sort *_sort;
  };

  //*-- LambdaRange
  class LambdaRange: public Range {
  public:
    explicit LambdaRange(std::function<const Sort *(const std::vector<const Sort *> &)> range_fun);

    ~LambdaRange() override;

    //*- methods

    const Sort *range(const std::vector<const Sort *> &sorts) const override;

  private:
    std::function<const Sort *(const std::vector<const Sort *> &)> _range_fun;
  };

  //*-- Function
  class Function: public Symbol {
  public:
    Function(const std::string &name, const Domain *domain, const Range *range, const std::vector<std::string> &tags,
             Context &context);

    ~Function() override;

    //*- properties

    const Domain &domain() const;

    const Range *range() const;

    //*- methods

    bool has_tag(const std::string &tag) const;

    //*- operators

    Expr operator()(const std::vector<Expr> &arguments) const;

  private:
    const Domain *_domain;
    const Range *_range;
    std::unordered_map<std::string, bool> _tags;
    Context &_context;
  };

  //*-- SymbolManager
  class SymbolManager {
  public:
    explicit SymbolManager(Context &context);

    ~SymbolManager();

    //*- methods

    Expr create_fresh_constant(const Sort *sort, const std::string &base = "FC");

    const Function *create_function(const std::string &name, const Domain *domain, const Range *range,
                                    const std::vector<std::string> &tags = {});

    Expr get_constant(const std::string &name);

    const Function *get_function(const std::string &name) const;

    Expr get_or_create_constant(const std::string &name, const Sort *sort);

  private:
    Context &_context;
    std::map<std::string, Expr> _constants;
    std::map<std::string, unsigned long> _fresh_counter;
    std::map<std::string, Function *> _functions;
  };

}
