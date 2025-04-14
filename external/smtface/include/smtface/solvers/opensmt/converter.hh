//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "opensmt/opensmt2.h"
#include "smtface/core/context.hh"
#include "smtface/core/sort.hh"
#include "smtface/core/term.hh"

namespace smtface::solvers {

  //*-- OpenSMTConverter
  class OpenSMTConverter {
  public:
    OpenSMTConverter(core::Context &context, LIALogic &logic);

    //*- properties

    core::Context &context() const;

    //*- methods

    core::Expr decode_expr(PTRef expr);

    PTRef encode_expr(const core::Expr &expr);

    const core::Sort *decode_sort(SRef sort);

    SRef encode_sort(const core::Sort *sort);

    void remember(const core::Expr &expr);

  private:
    core::Context &_context;
    LIALogic &_logic;
    std::vector<core::Expr> _remembered_expr;
    std::vector<PTRef> _remembered_osmt_expr;
    std::map<unsigned long, uint32_t> _remember_map;
  };

}
