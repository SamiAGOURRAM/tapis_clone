//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/logic/evaluator.hh"

#include "hcvc/context.hh"
#include "hcvc/clause/predicate.hh"

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
