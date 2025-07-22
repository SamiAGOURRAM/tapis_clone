//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/logic/evaluator.hh"

#include "hcvc/context.hh"
#include "hcvc/clause/predicate.hh"
#include "hcvc/logic/printer.hh"
#include <iostream>              
#include <cstdlib>

namespace hcvc {

  static std::map<std::string, std::function<Expr(const std::vector<Expr> &)>> func_eval_map;

  static void initialize_func_eval_map() {
    // Core theory
    func_eval_map["="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral && args[1]->kind() == TermKind::BooleanLiteral) {
        auto a1 = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<BooleanLiteral>(args[1]);
        if(a1->value() == a2->value()) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      } else if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(a1->value() == a2->value()) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("=", args);
    };
    func_eval_map["=>"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral && args[1]->kind() == TermKind::BooleanLiteral) {
        auto a1 = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<BooleanLiteral>(args[1]);
        if(args[0]->type() == args[1]->type()) {
          if(a1->value() && !a2->value()) {
            return args[0]->context().get_false();
          }
          return args[0]->context().get_true();
        }
      }
      return args[0]->context().apply("=>", args);
    };
    func_eval_map["and"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::BooleanLiteral;
      })) {
        bool res = true;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<BooleanLiteral>(arg);
          if(!argp->value()) {
            res = false;
            break;
          }
        }
        if(res) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("and", args);
    };
    func_eval_map["distinct"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral && args[1]->kind() == TermKind::BooleanLiteral) {
        auto a1 = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<BooleanLiteral>(args[1]);
        if(a1->value() != a2->value()) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      } else if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(a1->value() != a2->value()) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("distinct", args);
    };
    func_eval_map["ite"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral) {
        auto a = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        if(a) {
          return args[1];
        } else {
          return args[2];
        }
      }
      return args[0]->context().apply("ite", args);
    };
    func_eval_map["not"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral) {
        auto a = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        if(a->value()) {
          return args[0]->context().get_false();
        } else {
          return args[0]->context().get_true();
        }
      }
      return args[0]->context().apply("not", args);
    };
    func_eval_map["or"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::BooleanLiteral;
      })) {
        bool res = false;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<BooleanLiteral>(arg);
          if(argp->value()) {
            res = true;
            break;
          }
        }
        if(res) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("or", args);
    };
    func_eval_map["xor"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::BooleanLiteral && args[1]->kind() == TermKind::BooleanLiteral) {
        auto a1 = std::dynamic_pointer_cast<BooleanLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<BooleanLiteral>(args[1]);
        if(a1->value() != a2->value()) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("xor", args);
    };
    // Ints theory
    func_eval_map["-"] = [](const std::vector<Expr> &args) {
      if(args.size() == 1) {
        if(args[0]->kind() == TermKind::IntegerLiteral) {
          auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
          auto res = -std::atol(a1->value().c_str());
          return IntegerLiteral::get(std::to_string(res), a1->type(), a1->context());
        }
      }
      if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        auto res = std::atol(a1->value().c_str()) - std::atol(a2->value().c_str());
        return IntegerLiteral::get(std::to_string(res), a1->type(), a1->context());
      }
      return args[0]->context().apply("-", args);
    };
    func_eval_map["+"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::IntegerLiteral;
      })) {
        long res = 0;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<IntegerLiteral>(arg);
          res += std::atol(argp->value().c_str());
        }
        return IntegerLiteral::get(std::to_string(res), args[0]->type(), args[0]->context());
      }
      return args[0]->context().apply("+", args);
    };
    func_eval_map["*"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::IntegerLiteral;
      })) {
        long res = 1;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<IntegerLiteral>(arg);
          res *= std::atol(argp->value().c_str());
        }
        return IntegerLiteral::get(std::to_string(res), args[0]->type(), args[0]->context());
      }
      return args[0]->context().apply("*", args);
    };
    func_eval_map["/"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::IntegerLiteral;
      })) {
        auto arg0 = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[0])->value());
        auto arg1 = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[1])->value());
        return IntegerLiteral::get(std::to_string(arg0 / arg1), args[0]->type(), args[0]->context());
      }
      return args[0]->context().apply("/", args);
    };
    func_eval_map["mod"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::IntegerLiteral;
      })) {
        auto arg0 = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[0])->value());
        auto arg1 = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[1])->value());
        return IntegerLiteral::get(std::to_string(arg0 % arg1), args[0]->type(), args[0]->context());
      }
      return args[0]->context().apply("mod", args);
    };
    func_eval_map["<="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(std::atol(a1->value().c_str()) <= std::atol(a2->value().c_str())) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("<=", args);
    };
    func_eval_map["<"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(std::atol(a1->value().c_str()) < std::atol(a2->value().c_str())) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply("<", args);
    };
    func_eval_map[">="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(std::atol(a1->value().c_str()) >= std::atol(a2->value().c_str())) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply(">=", args);
    };
    func_eval_map[">"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::IntegerLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto a1 = std::dynamic_pointer_cast<IntegerLiteral>(args[0]);
        auto a2 = std::dynamic_pointer_cast<IntegerLiteral>(args[1]);
        if(std::atol(a1->value().c_str()) > std::atol(a2->value().c_str())) {
          return args[0]->context().get_true();
        } else {
          return args[0]->context().get_false();
        }
      }
      return args[0]->context().apply(">", args);
    };
    func_eval_map["[]"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::ArrayLiteral && args[1]->kind() == TermKind::IntegerLiteral) {
        auto arr = std::dynamic_pointer_cast<ArrayLiteral>(args[0])->values();
        auto idx = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[1])->value());
        if(0 <= idx && idx < arr.size()) {
          return arr[idx];
        } else {
          return IntegerLiteral::get(std::to_string(0), args[1]->type(), args[0]->context());
        }
      }
      return IntegerLiteral::get(std::to_string(0), args[1]->type(), args[0]->context());
    };

func_eval_map["sum"] = [](const std::vector<Expr> &args) {
    // We can only evaluate if the arguments are concrete literals
    if (args[0]->kind() == TermKind::ArrayLiteral &&
        args[1]->kind() == TermKind::IntegerLiteral &&
        args[2]->kind() == TermKind::IntegerLiteral) {

      auto arr_literal = std::dynamic_pointer_cast<ArrayLiteral>(args[0]);
      auto start_idx = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[1])->value());
      auto end_idx = std::stol(std::dynamic_pointer_cast<IntegerLiteral>(args[2])->value());
      
      long long total = 0;
      // Sum the elements in the range [start, end)
      // Add safety checks for the bounds
      if (start_idx >= 0 && static_cast<size_t>(end_idx) <= arr_literal->values().size() && start_idx <= end_idx) {
        for (long i = start_idx; i < end_idx; ++i) {
            // Ensure the array element is also a concrete integer
            if (arr_literal->values()[i]->kind() == TermKind::IntegerLiteral) {
              auto elem = std::dynamic_pointer_cast<IntegerLiteral>(arr_literal->values()[i]);
              total += std::stol(elem->value());
            } else {
              // Cannot evaluate if an element is symbolic, so return the original expression
              return args[0]->context().apply("sum", args);
            }
        }
        return IntegerLiteral::get(std::to_string(total), args[0]->context().type_manager().int_type(), args[0]->context());
      }
    }
    // If arguments are not concrete, or bounds are invalid, return the original symbolic expression
    return args[0]->context().apply("sum", args);
  };
  }

  static Expr call_eval_func(const std::string &name, const std::vector<Expr> &args) {
    if(func_eval_map.empty()) {
      initialize_func_eval_map();
    }
    return func_eval_map[name](args);
  }

  // Evaluator
  Evaluator::Evaluator(const std::map<Expr, Expr> &map) {
    for(auto [key, value]: map) {
      auto kp = std::dynamic_pointer_cast<Constant>(key);
      _var_map[kp->name()] = value;
    }
  }

  Expr Evaluator::evaluate(const Expr &expr) {
    // --- START DEBUGGING EXIT ---
    // static int eval_call_count = 0; // A counter that persists across calls
    // eval_call_count++;

    // Printer printer;
    // std::cout << "[DEBUG] Evaluator::evaluate call #" << eval_call_count << " on: " << printer.to_string(expr) << std::endl;

    // // Let's allow a few thousand evaluations before we decide it's an infinite loop.
    // // Adjust this number if needed.
    // if (eval_call_count > 1000) {
    //     std::cout << "\n[FATAL] Evaluator called too many times. Likely infinite loop. Forcing exit." << std::endl;
    //     std::cout << "       Problematic expression was: " << printer.to_string(expr) << std::endl;
    //     exit(1); // Forcefully terminate the entire program with an error code.
    // }
    // --- END DEBUGGING EXIT ---
    
    expr->accept(*this);
    auto res = result();
    return res;
  }

  void Evaluator::visit(std::shared_ptr<OperatorApplication> term) {
    std::vector<Expr> args;
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      args.push_back(result());
    }
    return _return(call_eval_func(term->operat0r()->name(), args));
  }

  void Evaluator::visit(std::shared_ptr<Constant> term) {
    if(_var_map.count(term->name()) > 0) {
      return _return(_var_map[term->name()]);
    } else {
      return _return(term);
    }
  }

  void Evaluator::visit(std::shared_ptr<BooleanLiteral> term) {
    return _return(term);
  }

  void Evaluator::visit(std::shared_ptr<IntegerLiteral> term) {
    return _return(term);
  }

  void Evaluator::visit(std::shared_ptr<ArrayLiteral> term) {
    return _return(term);
  }

  void Evaluator::visit(std::shared_ptr<QuantifiedFormula> term) {
  }

  void Evaluator::visit(std::shared_ptr<PredicateApplication> term) {
  }

}
