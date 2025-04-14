//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <stack>
#include "smtface/core/term.hh"

namespace smtface::core {

  // Printer
  class Printer: public Visitor {
  public:
    explicit Printer();

    //*- methods

    std::string to_string(const Expr &expr);

    void visit(std::shared_ptr<ApplicationTerm> term) override;

    void visit(std::shared_ptr<QuantifiedFormula> term) override;

    void visit(std::shared_ptr<Constant> term) override;

    void visit(std::shared_ptr<Null> term) override;

    void visit(std::shared_ptr<Value> term) override;

  private:
    std::string result();

    void _return(const std::string &r);

    std::stack<std::string> _stack;
  };

}
