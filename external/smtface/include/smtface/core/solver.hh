//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <optional>
#include "smtface/core/context.hh"
#include "smtface/core/term.hh"

namespace smtface::core {

  //*-- ModelObj
  class ModelObj {
  public:
    explicit ModelObj(core::Context &context);

    virtual ~ModelObj();

    //*- properties

    //*- methods

    virtual Expr eval(const Expr &expr) = 0;

    virtual Expr to_expr(const std::map<std::string, core::Expr> &variables) = 0;

  private:
    core::Context &_context;
  };

  typedef std::shared_ptr<ModelObj> Model;

  //*-- Solver
  class Solver {
  public:
    explicit Solver(core::Context &context);

    virtual ~Solver();

    //*-- methods

    virtual std::optional<Model> get_model(const core::Expr &formula) = 0;

    virtual bool is_sat(const core::Expr &formula) = 0;

    virtual void remember(const core::Expr &expr);

    virtual core::Expr simplify(const core::Expr &formula) = 0;

  private:
    core::Context &_context;
  };

}
