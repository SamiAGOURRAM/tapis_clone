//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "smtface/core/symbol.hh"

namespace smtface::core {

  //*-- Context
  class Context {
  public:
    Context();

    ~Context();

    //*- methods

    Expr apply(const std::string &name, const std::vector<Expr> &arguments);

    Expr constant(const std::string &name);

    Expr constant(const std::string &name, const Sort *sort);

    Expr fresh_constant(const Sort *sort, const std::string &base = "FC");

    const Function *function(const std::string &name, const Domain *domain, const Sort *range,
                             const std::vector<std::string> &tags = {});

    const Function *function(const std::string &name, const Domain *domain, const Range *range,
                             const std::vector<std::string> &tags = {});

    const Function *function(const std::string &name, const std::vector<const Sort *> &domain, const Sort *range,
                             const std::vector<std::string> &tags = {});

    const Function *get_function(const std::string &name) const;

    bool has_function(const std::string &name) const;

    Expr null();

    Expr value(const std::string &raw, const Sort *sort);

    Expr variable(const std::string &name, const Sort *sort);

    //*- internal methods

    unsigned long get_new_term_id();

  private:
    unsigned long _term_ids;
    SymbolManager _symbol_manager;
    std::map<const Sort *, std::map<std::string, Expr>> _values;
    Expr _null_expr;
  };

}
