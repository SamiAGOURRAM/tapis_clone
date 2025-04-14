//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <string>
#include <vector>

namespace hcvc {

  class Context;

  //*-- Type
  class Type {
  public:
    explicit Type(Context &context);

    virtual ~Type();

    //*- properties

    /// Get the context of the type.
    inline Context &context() const {
      return _context;
    }

    /// Determine whether this type is the void type.
    virtual bool is_void() const;

    /// Determine whether this type is the boolean type.
    virtual bool is_bool() const;

    /// Determine whether this type is the integer type.
    virtual bool is_int() const;

    /// Determine whether this type is an array type.
    virtual bool is_array() const;

  private:
    Context &_context;
  };

  //*-- VoidType
  class VoidType: public Type {
  public:
    explicit VoidType(Context &context);

    ~VoidType() override;

    //*- properties

    bool is_void() const override;
  };

  //*-- PrimitiveType
  class PrimitiveType: public Type {
  public:
    explicit PrimitiveType(Context &context);

    ~PrimitiveType() override;
  };

  //*-- BoolType
  class BoolType: public PrimitiveType {
  public:
    explicit BoolType(Context &context);

    ~BoolType() override;

    //*- properties

    bool is_bool() const override;
  };

  //*-- Signedness
  enum class Signedness {
    Signed,
    Unsigned
  };

  //*-- IntType
  class IntType: public PrimitiveType {
  public:
    IntType(Signedness signedness, Context &context);

    ~IntType() override;

    //*- properties

    bool is_int() const override;

    inline Signedness signedness() const {
      return _signedness;
    }

  private:
    Signedness _signedness;
  };

  //*-- ArrayType
  class ArrayType: public Type {
  public:
    ArrayType(const Type *element_type, Context &context);

    ~ArrayType() override;

    //*- properties

    /// Get the type of the elements of arrays with this type.
    inline const Type *element_type() const {
      return _element_type;
    }

    bool is_array() const override;

  private:
    const Type *_element_type;
  };

  //*-- TypeManager
  class TypeManager {
  public:
    explicit TypeManager(Context &context);

    ~TypeManager();

    //*- properties

    inline const Type *void_type() const {
      return _void_type;
    }

    inline const Type *bool_type() const {
      return _bool_type;
    }

    inline const Type *int_type() const {
      return _int_type;
    }

    inline const Type *uint_type() const {
      return _uint_type;
    }

    //*- methods

    const ArrayType *get_array_type(const Type *element_type);

  private:
    Type *_void_type;
    Type *_bool_type;
    Type *_int_type;
    Type *_uint_type;
    std::map<const Type *, ArrayType *> _array_types;
    Context &_context;
  };

}
