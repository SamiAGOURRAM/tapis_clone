//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <stack>
#include "hcvc/logic/term.hh"

namespace hcvc {

  // Printer
  class Printer: public Visitor {
  public:
    explicit Printer();

    //*- methods

    std::string to_string(const Expr &expr);

    void visit(std::shared_ptr<OperatorApplication> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<BooleanLiteral> term) override;

    void visit(std::shared_ptr<IntegerLiteral> term) override;

    void visit(std::shared_ptr<ArrayLiteral> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<PredicateApplication> term) override;

  private:
    inline std::string result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    inline void _return(const std::string &r) {
      _stack.push(r);
    }

    std::stack<std::string> _stack;
  };

}
