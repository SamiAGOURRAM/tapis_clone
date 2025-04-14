//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/solvers/z3/model.hh"

#include <list>
#include "smtface/shorthands.hh"

namespace smtface::solvers {

  //*-- Z3Model
  Z3Model::Z3Model(const z3::model &model, Z3Converter &converter)
      : ModelObj(converter.context()), _model(model), _converter(converter) {}

  Z3Model::~Z3Model() = default;

  z3::model Z3Model::z3_model() {
    return _model;
  }

  core::Expr Z3Model::eval(const core::Expr &expr) {
    auto encoded = _converter.encode_expr(expr);
    auto val = _model.eval(encoded, true);
    return _converter.decode_expr(val, {});
  }

  std::map<smtface::Expr, core::Expr> Z3Model::to_values() {
    std::map<smtface::Expr, core::Expr> values;
    for(unsigned long i = 0; i < _model.num_consts(); i++) {
      auto name = _model.get_const_decl(i).name().str();
      auto var_sym = _converter.decode_expr(_model.get_const_decl(i)(), {});
      values[var_sym] = eval(var_sym);
    }
    return values;
  }

  core::Expr Z3Model::to_expr(const std::map<std::string, core::Expr> &variables) {
    auto f = smtface::True();
    for(unsigned long i = 0; i < _model.num_consts(); i++) {
      auto name = _model.get_const_decl(i).name().str();
      if(variables.count(name) > 0) {
        const auto &var_sym = variables.at(name);
        f = f && smtface::Equal(var_sym, eval(var_sym));
      }
    }
    return f;
  }

}
