//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/solver.hh"

#include "smtface/shorthands.hh"

namespace smtface::core {

  //*-- ModelObj
  ModelObj::ModelObj(core::Context &context) : _context(context) {}

  ModelObj::~ModelObj() = default;

  //*-- Solver
  Solver::Solver(Context &context) : _context(context) {}

  Solver::~Solver() = default;

  void Solver::remember(const Expr &expr) {}

}
