//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/evaluator.hh"

#include <utility>
#include <vector>
#include "smtface/shorthands.hh"

namespace smtface::core {

  static std::map<std::string, std::function<Expr(const std::vector<Expr> &)>> func_eval_map;

  static void initialize_func_eval_map() {
    // Core theory
    func_eval_map["="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == args[1]->sort()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(a1->raw() == a2->raw()) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply("=", args, args[0]->context());
    };
    func_eval_map["=>"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
        auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
        if(args[0]->sort() == args[1]->sort()) {
          if(a1->raw() == "true" && a2->raw() == "false") {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
          return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
        }
      }
      return Apply("=>", args, args[0]->context());
    };
    func_eval_map["and"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::Value &&
               std::dynamic_pointer_cast<Value>(arg)->sort() == get_register().get_sort_manager().Bool();
      })) {
        bool res = true;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<Value>(arg);
          if(argp->raw() == "false") {
            res = false;
            break;
          }
        }
        if(res) {
          return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
        } else {
          return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
        }
      }
      return Apply("and", args, args[0]->context());
    };
    func_eval_map["distinct"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == args[1]->sort()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(a1->raw() != a2->raw()) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply("distinct", args, args[0]->context());
    };
    func_eval_map["ite"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[0]->sort() == get_register().get_sort_manager().Bool()) {
        auto a = std::dynamic_pointer_cast<Value>(args[0]);
        if(a->is_true()) {
          return args[1];
        } else if(a->is_false()) {
          return args[2];
        }
      }
      return Apply("ite", args, args[0]->context());
    };
    func_eval_map["not"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[0]->sort() == get_register().get_sort_manager().Bool()) {
        auto a = std::dynamic_pointer_cast<Value>(args[0]);
        if(a->raw() == "true") {
          return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
        } else {
          return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
        }
      }
      return Apply("not", args, args[0]->context());
    };
    func_eval_map["or"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::Value &&
               std::dynamic_pointer_cast<Value>(arg)->sort() == get_register().get_sort_manager().Bool();
      })) {
        bool res = false;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<Value>(arg);
          if(argp->raw() == "true") {
            res = true;
            break;
          }
        }
        if(res) {
          return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
        } else {
          return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
        }
      }
      return smtface::Null(args[0]->context());
    };
    func_eval_map["xor"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == args[1]->sort()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(a1->raw() != a2->raw()) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply("xor", args, args[0]->context());
    };
    // Ints theory
    func_eval_map["-"] = [](const std::vector<Expr> &args) {
      if(args.size() == 1) {
        if(args[0]->kind() == TermKind::Value && args[0]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto res = -std::atol(a1->raw().c_str());
          return smtface::Value(std::to_string(res), get_register().get_sort_manager().Int());
        }
      }
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          auto res = std::atol(a1->raw().c_str()) - std::atol(a2->raw().c_str());
          return smtface::Value(std::to_string(res), get_register().get_sort_manager().Int());
        }
      }
      return Apply("-", args, args[0]->context());
    };
    func_eval_map["+"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::Value &&
               std::dynamic_pointer_cast<Value>(arg)->sort() == get_register().get_sort_manager().Int();
      })) {
        long res = 0;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<Value>(arg);
          res += std::atol(argp->raw().c_str());
        }
        return smtface::Value(std::to_string(res), get_register().get_sort_manager().Int());
      }
      return Apply("+", args, args[0]->context());
    };
    func_eval_map["*"] = [](const std::vector<Expr> &args) {
      if(std::all_of(args.begin(), args.end(), [](const Expr &arg) {
        return arg->kind() == TermKind::Value &&
               std::dynamic_pointer_cast<Value>(arg)->sort() == get_register().get_sort_manager().Int();
      })) {
        long res = 1;
        for(const auto &arg: args) {
          auto argp = std::dynamic_pointer_cast<Value>(arg);
          res *= std::atol(argp->raw().c_str());
        }
        return smtface::Value(std::to_string(res), get_register().get_sort_manager().Int());
      }
      return Apply("*", args, args[0]->context());
    };
    func_eval_map["div"] = [](const std::vector<Expr> &args) {
      // TODO: this is only of ints
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          auto res = std::atol(a1->raw().c_str()) / std::atol(a2->raw().c_str());
          return smtface::Value(std::to_string(res), get_register().get_sort_manager().Int());
        }
      }
      return Apply("div", args, args[0]->context());
    };
    func_eval_map["mod"] = [](const std::vector<Expr> &args) {
      // TODO:
      return Apply("mod", args, args[0]->context());
    };
    func_eval_map["abs"] = [](const std::vector<Expr> &args) {
      // TODO:
      return Apply("abs", args, args[0]->context());
    };
    func_eval_map["<="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(std::atol(a1->raw().c_str()) <= std::atol(a2->raw().c_str())) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply("<=", args, args[0]->context());
    };
    func_eval_map["<"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(std::atol(a1->raw().c_str()) < std::atol(a2->raw().c_str())) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply("<", args, args[0]->context());
    };
    func_eval_map[">="] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(std::atol(a1->raw().c_str()) >= std::atol(a2->raw().c_str())) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply(">=", args, args[0]->context());
    };
    func_eval_map[">"] = [](const std::vector<Expr> &args) {
      if(args[0]->kind() == TermKind::Value && args[1]->kind() == TermKind::Value) {
        if(args[0]->sort() == get_register().get_sort_manager().Int() &&
           args[1]->sort() == get_register().get_sort_manager().Int()) {
          auto a1 = std::dynamic_pointer_cast<Value>(args[0]);
          auto a2 = std::dynamic_pointer_cast<Value>(args[1]);
          if(std::atol(a1->raw().c_str()) > std::atol(a2->raw().c_str())) {
            return smtface::Value("true", get_register().get_sort_manager().Bool(), args[0]->context());
          } else {
            return smtface::Value("false", get_register().get_sort_manager().Bool(), args[0]->context());
          }
        }
      }
      return Apply(">", args, args[0]->context());
    };
  }

  static Expr call_sub_func(const std::string &name, const std::vector<Expr> &args) {
    if(func_eval_map.empty()) {
      initialize_func_eval_map();
    }
    // TODO: check if exists
    return func_eval_map[name](args);
  }

  // Evaluator
  Evaluator::Evaluator(std::map<Expr, std::variant<Expr, std::vector<Expr>>> map) : _map(std::move(map)) {}

  Expr Evaluator::evaluate(const Expr &expr) {
    expr->accept(*this);
    return result();
  }

  void Evaluator::visit(std::shared_ptr<QuantifiedFormula> term) {
    // TODO: implement
  }

  void Evaluator::visit(std::shared_ptr<ApplicationTerm> term) {
    if(term->function()->name() == "select") {
      term->arguments().at(1)->accept(*this);
      auto index = result();
      return _return(std::get<std::vector<Expr>>(_map[term->arguments().at(0)])[std::stol(
          std::dynamic_pointer_cast<core::Value>(index)->raw())]);
    }
    std::vector<Expr> args;
    for(const auto &arg: term->arguments()) {
      arg->accept(*this);
      args.push_back(result());
    }
    return _return(call_sub_func(term->function()->name(), args));
  }

  void Evaluator::visit(std::shared_ptr<Constant> term) {
    if(_map.count(term) > 0) {
      return _return(std::get<Expr>(_map[term]));
    } else {
      return _return(term);
    }
  }

  void Evaluator::visit(std::shared_ptr<Null> term) {
    return _return(term);
  }

  void Evaluator::visit(std::shared_ptr<Value> term) {
    return _return(term);
  }

  Expr Evaluator::result() {
    auto r = _stack.top();
    _stack.pop();
    return r;
  }

  void Evaluator::_return(const Expr &r) {
    _stack.push(r);
  }

}
