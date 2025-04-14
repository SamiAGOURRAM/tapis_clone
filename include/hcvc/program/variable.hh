//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <string>
#include "hcvc/program/function.hh"
#include "hcvc/program/type.hh"

namespace hcvc {

  class Function;

  //*-- Variable
  class Variable {
  public:
    Variable(std::string name, const Type *type, Context &context, bool is_shadow = false);

    virtual ~Variable();

    //*- properties

    /// Determine whether this is a data variable (it's an index/numeric variable if not).
    inline bool is_data() const {
      return _is_data;
    }

    /// Determine whether this is a shadow variable (variable not in the source program introduced by the compiler).
    inline bool is_shadow() const {
      return _is_shadow;
    }

    /// Get the name of the variables.
    inline const std::string &name() const {
      return _name;
    }

    /// Get the type of the variable.
    inline const Type *type() const {
      return _type;
    }

    inline Variable *size_variable() const {
      return _size_variable;
    }

    virtual bool is_parameter() const;

    //*- methods

    virtual void carry_size_variable(Variable *size_variable = nullptr);

    /// Mark that this variable is a variable that holds data.
    inline void set_is_data() const {
      _is_data = true;
    }

    //*- statics

    /// Create a variable with given parameters
    inline static Variable *create(std::string name, const Type *type, Context &context, bool is_shadow = false) {
      return new Variable(std::move(name), type, context, is_shadow);
    }

  private:
    std::string _name;
    const Type *_type;
    bool _is_shadow;
    mutable bool _is_data;
    Context &_context;

    Variable *_size_variable;
  };

  //*-- Parameter
  class Parameter: public Variable {
  public:
    Parameter(const std::string &name, const Type *type, bool is_modified, Context &context);

    ~Parameter() override;

    //*- properties

    /// Get the shadow variable that stores the entry value of the parameter.
    inline Variable *entry_value_holder() const {
      return _entry_value_holder;
    }

    /// Get the function for which this is a parameter.
    inline Function *function() const {
      return _function;
    }

    /// Determine whether this parameter is modified in the function body.
    inline bool is_modified() const {
      return _is_modified;
    }

    bool is_parameter() const override;

    //*- methods

    void carry_size_variable(Variable *size_variable = nullptr) override;

    void set_entry_value_holder(Variable *variable) {
      _entry_value_holder = variable;
    }

  private:
    bool _is_modified;
    Function *_function;

    Variable *_entry_value_holder;

    //*- methods

    /// Set the function for which this is a parameter.
    inline void set_function(Function *function) {
      _function = function;
    }

    //*- friends

    friend class Function;
  };

}
