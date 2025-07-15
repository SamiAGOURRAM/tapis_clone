//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/context.hh"

#include <memory>
#include "hcvc/logic/term.hh"

namespace hcvc {

  void initialize_core_operators(Context &context);

  void initialize_int_operators(Context &context);

  void initialize_array_operators(Context &context);

  //*-- Context
  Context::Context()
      : _type_manager(*this) {
    _true = std::make_shared<BooleanLiteral>(true, *this);
    _false = std::make_shared<BooleanLiteral>(false, *this);
    initialize_core_operators(*this);
    initialize_int_operators(*this);
    initialize_array_operators(*this);
  }

  Context::~Context() = default;

  Expr Context::apply(const std::string &op_name, const std::vector<Expr> &arguments) {
    const Operator *op;
    if(_operators.count(op_name) > 0) {
      op = _operators.at(op_name);
    } else {
      op = nullptr;
    }
    if(op == 0x0 || op == (Operator *) 0x1) {
      return nullptr;
    }

    std::vector<Expr> args;
    if(op_name == "and") {
      std::vector<Expr> working(arguments);
      for(unsigned long i = 0; i < working.size(); i++) {
        auto arg = working[i];
        if(is_true(arg)) {
          continue;
        } else if(is_false(arg)) {
          return arg;
        } else if(is_and(arg)) {
          auto app = std::dynamic_pointer_cast<OperatorApplication>(arg);
          for(const auto &aarg: app->arguments()) {
            working.push_back(aarg);
          }
        } else {
          args.push_back(arg);
        }
      }
      if(args.empty()) {
        return get_true();
      } else if(args.size() == 1) {
        return args[0];
      }
    } else if(op_name == "or") {
      std::vector<Expr> working(arguments);
      for(unsigned long i = 0; i < working.size(); i++) {
        auto arg = working[i];
        if(is_false(arg)) {
          continue;
        } else if(is_true(arg)) {
          return arg;
        } else if(is_or(arg)) {
          auto app = std::dynamic_pointer_cast<OperatorApplication>(arg);
          for(const auto &aarg: app->arguments()) {
            working.push_back(aarg);
          }
        } else {
          args.push_back(arg);
        }
      }
      if(args.empty()) {
        return get_false();
      } else if(args.size() == 1) {
        return args[0];
      }
    } else {
      args = arguments;
    }

    return std::make_shared<OperatorApplication>(op, args, *this);
  }

  //*-- initialize_core_theory()
  void initialize_core_operators(Context &context) {
    // not
    auto not_domain = new MinMaxDomain(context.type_manager().bool_type(), 1, 1);
    Operator::create("not", not_domain, context.type_manager().bool_type(), context);
    // =>
    auto implies_domain = new MinMaxDomain(context.type_manager().bool_type(), 2, 2);
    Operator::create("=>", implies_domain, context.type_manager().bool_type(), context);
    // and
    auto and_domain = new MinMaxDomain(context.type_manager().bool_type(), 2);
    Operator::create("and", and_domain, context.type_manager().bool_type(), context);
    // or
    auto or_domain = new MinMaxDomain(context.type_manager().bool_type(), 2);
    Operator::create("or", or_domain, context.type_manager().bool_type(), context);
    // xor
    auto xor_domain = new MinMaxDomain(context.type_manager().bool_type(), 2, 2);
    Operator::create("xor", xor_domain, context.type_manager().bool_type(), context);
    // =
    auto eq_accept_fun = [](const std::vector<const Type *> &types) -> bool {
      if(types.size() != 2) {
        return false;
      }
      return types[0] == types[1];
    };
    auto eq_domain = new LambdaDomain(eq_accept_fun);
    Operator::create("=", eq_domain, context.type_manager().bool_type(), context);
    // distinct
    auto distinct_accept_fun = [](const std::vector<const Type *> &types) -> bool {
      if(types.size() != 2) {
        return false;
      }
      return types[0] == types[1];
    };
    auto distinct_domain = new LambdaDomain(distinct_accept_fun);
    Operator::create("distinct", distinct_domain, context.type_manager().bool_type(), context);
    // ite
    auto ite_accept_fun = [&](const std::vector<const Type *> &types) -> bool {
      if(types.size() != 3) {
        return false;
      }
      return types[0] == context.type_manager().bool_type() && types[1] == types[2];
    };
    auto ite_domain = new LambdaDomain(ite_accept_fun);
    auto ite_range_fun = [](const std::vector<const Type *> &types) -> const Type * {
      // assert(types.size() = 3);
      return types[1];
    };
    auto ite_range = new LambdaRange(ite_range_fun);
    Operator::create("ite", ite_domain, ite_range, context);
  }

  //*-- initialize_ints_theory()
  void initialize_int_operators(Context &context) {
    // -
    Operator::create("-", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.empty() || types.size() > 2) {
        return false;
      }
      // check that all argument types are integers
      for(const auto &type: types) {
        if(!type->is_int() || (type->is_int() && type->is_bool())) {
          return false;
        }
      }
      // check that all arguments has the same signedness
      auto ref_type = dynamic_cast<const IntType *>(types[0]);
      for(const auto &type: types) {
        auto casted = dynamic_cast<const IntType *>(type);
        if(casted->signedness() != ref_type->signedness()) {
          return false;
        }
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      return types[0];
    }), context);
    // +
    Operator::create("+", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.size() < 2) {
        return false;
      }
      // check that all argument types are integers
      for(const auto &type: types) {
        if(!type->is_int() || (type->is_int() && type->is_bool())) {
          return false;
        }
      }
      // check that all arguments has the same bitwidth integer type and signedness
      auto ref_type = dynamic_cast<const IntType *>(types[0]);
      for(const auto &type: types) {
        auto casted = dynamic_cast<const IntType *>(type);
        if(casted->signedness() != ref_type->signedness()) {
          return false;
        }
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      return types[0];
    }), context);
    // *
    Operator::create("*", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.size() < 2) {
        return false;
      }
      // check that all argument types are integers
      for(const auto &type: types) {
        if(!type->is_int() || (type->is_int() && type->is_bool())) {
          return false;
        }
      }
      // check that all arguments has the same bitwidth integer type and signedness
      auto ref_type = dynamic_cast<const IntType *>(types[0]);
      for(const auto &type: types) {
        auto casted = dynamic_cast<const IntType *>(type);
        if(casted->signedness() != ref_type->signedness()) {
          return false;
        }
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      return types[0];
    }), context);
    Operator::create("/", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.size() != 2) {
        return false;
      }
      // check that all argument types are integers
      for(const auto &type: types) {
        if(!type->is_int() || (type->is_int() && type->is_bool())) {
          return false;
        }
      }
      // check that all arguments has the same bitwidth integer type and signedness
      auto ref_type = dynamic_cast<const IntType *>(types[0]);
      for(const auto &type: types) {
        auto casted = dynamic_cast<const IntType *>(type);
        if(casted->signedness() != ref_type->signedness()) {
          return false;
        }
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      return types[0];
    }), context);
    Operator::create("mod", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.size() != 2) {
        return false;
      }
      // check that all argument types are integers
      for(const auto &type: types) {
        if(!type->is_int() || (type->is_int() && type->is_bool())) {
          return false;
        }
      }
      // check that all arguments has the same bitwidth integer type and signedness
      auto ref_type = dynamic_cast<const IntType *>(types[0]);
      for(const auto &type: types) {
        auto casted = dynamic_cast<const IntType *>(type);
        if(casted->signedness() != ref_type->signedness()) {
          return false;
        }
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      return types[0];
    }), context);
    // <=
    Operator::create("<=", new LambdaDomain([](const std::vector<const Type *> &types) {
      if(types.size() != 2) {
        return false;
      }
      return types[0] != types[1];
    }), context.type_manager().bool_type(), context);
    // <
    Operator::create("<", new LambdaDomain([](const std::vector<const Type *> &types) {
      if(types.size() != 2) {
        return false;
      }
      return types[0] != types[1];
    }), context.type_manager().bool_type(), context);
    // >=
    Operator::create(">=", new LambdaDomain([](const std::vector<const Type *> &types) {
      if(types.size() != 2) {
        return false;
      }
      return types[0] != types[1];
    }), context.type_manager().bool_type(), context);
    // >
    Operator::create(">", new LambdaDomain([](const std::vector<const Type *> &types) {
      if(types.size() != 2) {
        return false;
      }
      return types[0] != types[1];
    }), context.type_manager().bool_type(), context);
  }

  //*-- initialize_array_operators()
  void initialize_array_operators(Context &context) {
    Operator::create("[]", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
      if(types.empty() || types.size() > 2) {
        return false;
      }
      if(!types[0]->is_array()) {
        return false;
      }
      if(types.size() == 2 && !types[1]->is_int()) {
        return false;
      }
      return true;
    }), new LambdaRange([](const std::vector<const Type *> &types) -> const Type * {
      if(types.size() == 2) {
        return dynamic_cast<const ArrayType *>(types[0])->element_type();
      }
      return types[0];
    }), context);

// sum
  Operator::create("sum", new LambdaDomain([](const std::vector<const Type *> &types) -> bool {
    // sum must have 3 arguments: sum(array, start_index, end_index)
    if (types.size() != 3) {
      return false;
    }
    // The first argument must be an array.
    if (!types[0]->is_array()) {
      return false;
    }
    // The second and third arguments must be integers.
    if (!types[1]->is_int() || !types[2]->is_int()) {
      return false;
    }

    // The array's elements must also be integers for the sum to be valid.
    auto array_type = static_cast<const ArrayType *>(types[0]);
    if (!array_type->element_type()->is_int()) {
        return false;
    }
    return true;
  }), context.type_manager().int_type(), context);
  }

}
