//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <iostream>
#include <map>
#include <string>
#include "hcvc/logic/term.hh"
#include "hcvc/program/type.hh"

namespace hcvc {

  class Operator;

  //*-- Context
  class Context {
  public:
    Context();

    ~Context();

    //*- properties

    /// Get false.
    inline Expr get_false() {
      return _false;
    }

    /// Get true.
    inline Expr get_true() {
      return _true;
    }

    /// Get the type manager.
    inline TypeManager &type_manager() {
      return _type_manager;
    }

    //*- methods

    /// Apply an operator.
    Expr apply(const std::string &op_name, const std::vector<Expr> &arguments);

  private:
    TypeManager _type_manager;
    std::map<std::string, Operator *> _operators;

    Expr _true;
    Expr _false;

    //*- friends

    friend class Operator;
  };

}
