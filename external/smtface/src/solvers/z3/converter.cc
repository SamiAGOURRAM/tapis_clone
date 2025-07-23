//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/solvers/z3/solver.hh"

#include "smtface/shorthands.hh"

namespace smtface::solvers {

  std::map<std::string, std::function<z3::expr(const z3::expr_vector &)>> z3_func_map;

  static void initialize_z3_func_map() {
    // Core theory
    z3_func_map["="] = [](const z3::expr_vector &args) {
      return args[0] == args[1];
    };
    z3_func_map["=>"] = [](const z3::expr_vector &args) {
      return z3::implies(args[0], args[1]);
    };
    z3_func_map["and"] = [](const z3::expr_vector &args) {
      return z3::mk_and(args);
    };
    z3_func_map["distinct"] = [](const z3::expr_vector &args) {
      return z3::distinct(args);
    };
    z3_func_map["ite"] = [](const z3::expr_vector &args) {
      return z3::ite(args[0], args[1], args[2]);
    };
    z3_func_map["not"] = [](const z3::expr_vector &args) {
      return !args[0];
    };
    z3_func_map["or"] = [](const z3::expr_vector &args) {
      return z3::mk_or(args);
    };
    z3_func_map["xor"] = [](const z3::expr_vector &args) {
      return args[0] ^ args[1];
    };
    // Ints theory
    z3_func_map["-"] = [](const z3::expr_vector &args) {
      if(args.size() == 1) {
        return -args[0];
      }
      return args[0] - args[1];
    };
    z3_func_map["+"] = [](const z3::expr_vector &args) {
      auto res = args[0];
      for(unsigned int i = 1, length = args.size(); i < length; i++) {
        res = res + args[i];
      }
      return res;
    };
    z3_func_map["*"] = [](const z3::expr_vector &args) {
      auto res = args[0];
      for(unsigned int i = 1, length = args.size(); i < length; i++) {
        res = res * args[i];
      }
      return res;
    };
    z3_func_map["div"] = [](const z3::expr_vector &args) {
      return args[0] / args[1];
    };
    z3_func_map["mod"] = [](const z3::expr_vector &args) {
      return z3::mod(args[0], args[1]);
    };
    z3_func_map["abs"] = [](const z3::expr_vector &args) {
      return z3::abs(args[0]);
    };
    z3_func_map["<="] = [](const z3::expr_vector &args) {
      return args[0] <= args[1];
    };
    z3_func_map["<"] = [](const z3::expr_vector &args) {
      return args[0] < args[1];
    };
    z3_func_map[">="] = [](const z3::expr_vector &args) {
      return args[0] >= args[1];
    };
    z3_func_map[">"] = [](const z3::expr_vector &args) {
      return args[0] > args[1];
    };
    z3_func_map["select"] = [](const z3::expr_vector &args) {
      return z3::select(args[0], args[1]);
    };
    z3_func_map["store"] = [](const z3::expr_vector &args) {
      return z3::store(args[0], args[1], args[2]);
    };
    // TODO: support real theory operations
  }

  static z3::expr
  call_z3_func(const std::string &name, const z3::expr_vector &args, const z3::func_decl_vector &func_decls,
               const std::map<std::string, unsigned int> &func_decl_map) {
    if(z3_func_map.empty()) {
      initialize_z3_func_map();
    }
    if(z3_func_map.count(name) > 0) {
      return z3_func_map[name](args);
    }
    // TODO: check if exists
    return func_decls[func_decl_map.at(name)](args);
  }

  //*-- Z3Converter
Z3Converter::Z3Converter(Context &context, z3::context &z3_context)
    : _context(context),
      _z3_context(z3_context),
      _remembered_z3_expr(z3_context),
      // Initialize m_sum_range_func with a temporary value. It will be properly defined next.
      m_sum_range_func(_z3_context.function("temp_sum_name", _z3_context.int_sort(), _z3_context.int_sort())) {

    z3::sort array_sort = _z3_context.array_sort(_z3_context.int_sort(), _z3_context.int_sort());
    z3::sort int_sort = _z3_context.int_sort();
    
    // Use the correct `recfun` overload for your Z3 version
    const unsigned arity = 3;
    z3::sort domain[arity] = { array_sort, int_sort, int_sort };
    // Assign the real recursive function declaration to our member variable
    m_sum_range_func = z3::recfun("sum_range", arity, domain, int_sort);

    z3::expr a = _z3_context.constant("a_rec", array_sort);
    z3::expr i = _z3_context.constant("i_rec", int_sort);
    z3::expr j = _z3_context.constant("j_rec", int_sort);
    z3::expr_vector params(_z3_context);
    params.push_back(a);
    params.push_back(i);
    params.push_back(j);
    
    z3::expr body = z3::ite(i >= j, _z3_context.int_val(0),
                           z3::select(a, j - 1) + m_sum_range_func(a, i, j - 1));

    // FIX: Use `recdef` as shown in your example. It's a member of z3::context.
    _z3_context.recdef(m_sum_range_func, params, body);
}

  core::Context &Z3Converter::context() const {
    return _context;
  }

  z3::expr Z3Converter::encode_expr(const core::Expr &expr) {
    z3::func_decl_vector func_decls(_z3_context);
    std::map<std::string, unsigned int> func_decl_map;
    return encode_expr(expr, func_decls, func_decl_map);
  }

  z3::expr Z3Converter::encode_expr(const Expr &expr, const z3::func_decl_vector &func_decls,
                                    const std::map<std::string, unsigned int> &func_decl_map) {
    // check if cached
    if(_remember_map.count(expr->id()) > 0) {
      auto target_id = _remember_map[expr->id()];
      for(auto e: _remembered_z3_expr) {
        if(e.id() == target_id) {
          return e;
        }
      }
    }
    // encode
    if(expr->kind() == core::TermKind::Constant) {
      auto exprp = std::dynamic_pointer_cast<core::Constant>(expr);
      return _z3_context.constant(exprp->name().c_str(), encode_sort(exprp->sort()));
    } else if(expr->kind() == core::TermKind::Value) {
      auto exprp = std::dynamic_pointer_cast<core::Value>(expr);
      if(exprp->sort() == get_register().get_sort_manager().Bool()) {
        if(exprp->raw() == "false") {
          return _z3_context.bool_val(false);
        } else {
          return _z3_context.bool_val(true);
        }
      } else if(exprp->sort() == get_register().get_sort_manager().Int()) {
        // TODO: deal with hex and bin integers
        return _z3_context.int_val(exprp->raw().c_str());
      } else if(exprp->sort() == get_register().get_sort_manager().Real()) {
        // TODO: check if z3 char float == smtlib char float
        return _z3_context.real_val(exprp->raw().c_str());
      }
    } else if(expr->kind() == core::TermKind::Application) {
      auto exprp = std::dynamic_pointer_cast<core::ApplicationTerm>(expr);

    if (exprp->function()->name() == "sum" || exprp->function()->name() == "sum_range") {
        z3::expr_vector args(_z3_context);
        for(const auto &arg: exprp->arguments()) {
            args.push_back(encode_expr(arg, func_decls, func_decl_map));
        }
        // Apply the function stored in the converter
        return m_sum_range_func(args);
    }
      z3::expr_vector args(_z3_context);
      for(const auto &arg: exprp->arguments()) {
        args.push_back(encode_expr(arg, func_decls, func_decl_map));
      }
      if(exprp->function()->has_tag("theory")) {
        return call_z3_func(exprp->function()->name(), args, func_decls, func_decl_map);
      } else {
        z3::sort_vector domain(_z3_context);
        for(const auto &arg: ((core::VectorDomain &) exprp->function()->domain()).sorts()) {
          domain.push_back(encode_sort(arg));
        }
        auto func = z3::function(exprp->function()->name(), domain, encode_sort(((core::SimpleRange *) exprp->function()->range())->sort()));
        return func(args);
      }
    } else if(expr->kind() == core::TermKind::Quantified) {
      auto exprp = std::dynamic_pointer_cast<core::QuantifiedFormula>(expr);
      z3::expr_vector quantified(_z3_context);
      for(const auto &arg: exprp->quantified_variables()) {
        quantified.push_back(encode_expr(arg, func_decls, func_decl_map));
      }
      if(exprp->quantifier() == core::Quantifier::forall) {
        return z3::forall(quantified, encode_expr(exprp->formula(), func_decls, func_decl_map));
      } else {
        return z3::exists(quantified, encode_expr(exprp->formula(), func_decls, func_decl_map));
      }
    }
    return z3::expr(_z3_context);
  }

  core::Expr Z3Converter::decode_expr(const z3::expr &expr, const std::map<std::string, smtface::Expr> &scope) {
    if(expr.is_false()) {
      return smtface::False();
    } else if(expr.is_true()) {
      return smtface::True();
    } else if(expr.is_app()) {
      if(expr.num_args() == 0) {
        if(expr.is_int() && expr.is_numeral()) {
          // TODO: fix integer > u64
          return smtface::Value(std::to_string(expr.get_numeral_int64()), get_register().get_sort_manager().Int());
        }
        return scope.at(expr.decl().name().str());
      } else {
        std::vector<core::Expr> arguments;
        for(unsigned long i = 0, length = expr.num_args(); i < length; i++) {
          arguments.push_back(decode_expr(expr.arg(i), scope));
        }
        auto name = expr.decl().name().str();
        if(name == "if") {
          name = "ite";
        }
        return smtface::Apply(name, arguments);
      }
    }
    // TODO: everything else
    return smtface::Null(_context);
  }

  smtface::Sort Z3Converter::decode_sort(z3::sort sort) {
    if(sort.is_bool()) {
      return get_register().get_sort_manager().Bool();
    } else if(sort.is_int()) {
      return get_register().get_sort_manager().Int();
    } else if(sort.is_real()) {
      return get_register().get_sort_manager().Real();
    }
    return get_register().get_sort_manager().Bool();
  }

  z3::sort Z3Converter::encode_sort(smtface::Sort sort) {
    if(sort == get_register().get_sort_manager().Bool()) {
      return _z3_context.bool_sort();
    } else if(sort == get_register().get_sort_manager().Int()) {
      return _z3_context.int_sort();
    } else if(sort == get_register().get_sort_manager().Real()) {
      return _z3_context.real_sort();
    } else if(sort->is_array()) {
      auto arr_sort = (smtface::core::ArraySort *) sort;
      return _z3_context.array_sort(encode_sort(arr_sort->index_sort()), encode_sort(arr_sort->element_sort()));
    }
    return _z3_context.bool_sort();
  }

  void Z3Converter::remember(const Expr &expr) {
    if(_remember_map.count(expr->id()) == 0) {
      _remembered_expr.push_back(expr);
      auto encoded = encode_expr(expr);
      _remembered_z3_expr.push_back(encoded);
      _remember_map[expr->id()] = encoded.id();
    }
  }

}
