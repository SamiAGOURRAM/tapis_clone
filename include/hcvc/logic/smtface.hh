//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <stack>
#include <utility>
#include "smtface/shorthands.hh"
#include "hcvc/logic/term.hh"

namespace hcvc {

  // To_smtface
  class To_smtface: public Visitor {
  public:
    To_smtface(hcvc::Context &hcvc_context, smtface::Context *context = nullptr);

    //*- methods

    smtface::Expr to_smtface(const Expr &expr);

    smtface::Sort to_smtface(const Type *type);

    void visit(std::shared_ptr<OperatorApplication> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<BooleanLiteral> term) override;

    void visit(std::shared_ptr<IntegerLiteral> term) override;

    void visit(std::shared_ptr<ArrayLiteral> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<PredicateApplication> term) override;

  private:
    inline smtface::Expr result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    inline void _return(smtface::Expr r) {
      _stack.emplace(std::move(r));
    }

    Context &_hcvc_context;
    smtface::Context &_smtface_context;
    std::stack<smtface::Expr> _stack;
  };

  //*-- From_smtface
  class From_smtface {
  public:
    From_smtface(const Expr& original);

    From_smtface(hcvc::Context &hcvc_context, std::map<std::string, hcvc::Expr> scope);

    hcvc::Expr from_smtface(smtface::Expr expr);

  private:
    hcvc::Context &_hcvc_context;
    std::map<std::string, hcvc::Expr> _scope;
  };

  inline smtface::Expr to_smtface(const Expr& expr, smtface::Context *context = nullptr) {
    return To_smtface(expr->context(), context).to_smtface(expr);
  }

  inline hcvc::Expr from_smtface(smtface::Expr &expr, const hcvc::Expr& original) {
    return From_smtface(original).from_smtface(expr);
  }

  inline hcvc::Expr from_smtface(smtface::Expr expr, std::map<std::string, hcvc::Expr> scope, hcvc::Context &hcvc_context) {
    return From_smtface(hcvc_context, std::move(scope)).from_smtface(std::move(expr));
  }

}
