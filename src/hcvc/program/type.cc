//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "hcvc/program/type.hh"

#include <utility>

namespace hcvc {

  //*-- Type
  Type::Type(hcvc::Context &context)
      : _context(context) {}

  Type::~Type() = default;

  bool Type::is_void() const {
    return false;
  }

  bool Type::is_bool() const {
    return false;
  }

  bool Type::is_int() const {
    return false;
  }

  bool Type::is_array() const {
    return false;
  }

  //*-- VoidType
  VoidType::VoidType(hcvc::Context &context)
      : Type(context) {}

  VoidType::~VoidType() = default;

  bool VoidType::is_void() const {
    return true;
  }

  //*-- PrimitiveType
  PrimitiveType::PrimitiveType(hcvc::Context &context)
      : Type(context) {}

  PrimitiveType::~PrimitiveType() = default;

  //*-- BoolType
  BoolType::BoolType(hcvc::Context &context)
      : PrimitiveType(context) {}

  BoolType::~BoolType() = default;

  bool BoolType::is_bool() const {
    return true;
  }

  //*-- IntType
  IntType::IntType(Signedness signedness, hcvc::Context &context)
      : PrimitiveType(context), _signedness(signedness) {}

  IntType::~IntType() = default;

  bool IntType::is_int() const {
    return true;
  }

  //*-- ArrayType
  ArrayType::ArrayType(const hcvc::Type *element_type, Context &context)
      : Type(context), _element_type(element_type) {}

  ArrayType::~ArrayType() = default;

  bool ArrayType::is_array() const {
    return true;
  }

  //*-- TypeManager
  TypeManager::TypeManager(Context &context)
      : _void_type(new VoidType(context)),
        _bool_type(new BoolType(context)),
        _int_type(new IntType(Signedness::Signed, context)),
        _uint_type(new IntType(Signedness::Unsigned, context)),
        _context(context) {}

  TypeManager::~TypeManager() {
    for(auto &[_, array_type]: _array_types) {
      delete array_type;
    }
    delete _void_type;
    delete _bool_type;
    delete _int_type;
    delete _uint_type;
  }

  const ArrayType *TypeManager::get_array_type(const hcvc::Type *element_type) {
    if(_array_types.count(element_type) == 0) {
      _array_types[element_type] = new ArrayType(element_type, _context);
    }
    return _array_types.at(element_type);
  }

}
