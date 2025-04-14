//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "opensmt/opensmt2.h"
#include "smtface/core/term.hh"
#include "smtface/core/solver.hh"
#include "smtface/solvers/opensmt/converter.hh"

namespace smtface::solvers {

  //*-- OpenSMTModel
  class OpenSMTModel: public core::ModelObj {
  public:
    OpenSMTModel(std::unique_ptr<Model> model, OpenSMTConverter &converter);

    ~OpenSMTModel() override;

    //*- properties

    std::shared_ptr<Model> osmt_model();

    //*- methods

    core::Expr eval(const core::Expr &expr) override;

    core::Expr to_expr(const std::map<std::string, core::Expr> &variables) override;

  private:
    std::shared_ptr<Model> _model;
    OpenSMTConverter &_converter;
  };

}
