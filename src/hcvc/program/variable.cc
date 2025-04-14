//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/program/variable.hh"

#include <utility>

namespace hcvc {

  //*-- Variable
  Variable::Variable(std::string name, const Type *type, Context &context, bool is_shadow)
      : _name(std::move(name)),
        _type(type),
        _is_shadow(is_shadow),
        _is_data(false),
        _context(context),
        _size_variable(nullptr) {}

  Variable::~Variable() = default;

  void Variable::carry_size_variable(Variable *size_variable) {
    if(size_variable == nullptr) {
      size_variable = Variable::create("." + _name + "!size", _context.type_manager().int_type(), _context, true);
    }
    _size_variable = size_variable;
  }

  bool Variable::is_parameter() const {
    return false;
  }

  //*-- Parameter
  Parameter::Parameter(const std::string &name, const Type *type, bool is_modified, Context &context)
      : Variable(name, type, context),
        _is_modified(is_modified),
        _function(nullptr),
        _entry_value_holder(nullptr) {
    if(is_modified) {
      _entry_value_holder = hcvc::Variable::create("." + name, type, context, true);
    }
  }

  Parameter::~Parameter() = default;

  void Parameter::carry_size_variable(Variable *size_variable) {
    Variable::carry_size_variable(size_variable);
    if(_is_modified) {
      _entry_value_holder->carry_size_variable(this->size_variable());
    }
  }

  bool Parameter::is_parameter() const {
    return true;
  }

}
