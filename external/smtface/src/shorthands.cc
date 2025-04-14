//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/shorthands.hh"

#include <stack>
#include <utility>
#include "smtface/core/context.hh"
#include "smtface/core/evaluator.hh"
#include "smtface/core/printer.hh"
#include "smtface/core/substituter.hh"
#include "smtface/theories/arrays.hh"
#include "smtface/theories/core.hh"
#include "smtface/theories/ints.hh"

namespace smtface {

  std::stack<Context *> CONTEXT_STACK;

  //*-- Add(expr, expr)
  Expr Add(const Expr &a, const Expr &b) {
    return Add(a, b, a->context());
  }

  Expr Add(const std::vector<Expr> &arguments) {
    return Add(arguments, arguments[0]->context());
  }

  Expr Add(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Add(args, context);
  }

  Expr Add(const std::vector<Expr> &arguments, Context &context) {
    return Apply("+", arguments, context);
  }

  //*-- And()
  Expr And(const Expr &a, const Expr &b) {
    return And(a, b, a->context());
  }

  Expr And(const std::vector<Expr> &arguments) {
    return And(arguments, arguments[0]->context());
  }

  Expr And(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return And(args, context);
  }

  Expr And(const std::vector<Expr> &arguments, Context &context) {
    return Apply("and", arguments, context);
  }

  //*-- Apply()
  Expr Apply(const std::string &name, const std::vector<Expr> &arguments) {
    return Apply(name, arguments, current_context());
  }

  Expr Apply(const std::string &name, const std::vector<Expr> &arguments, Context &context) {
    bool negate = false;
    std::vector<Expr> args;
    if(name == "+") {
      std::vector<Expr> working(arguments);
      for(unsigned long i = 0; i < working.size(); i++) {
        auto arg = working[i];
        if(arg->is_add()) {
          auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(arg);
          for(const auto &aarg: app->arguments()) {
            working.push_back(aarg);
          }
        } else if(!arg->is_0()) {
          args.push_back(arg);
        }
      }
      if(args.size() == 1) {
        return args[0];
      }
    } else if(name == "*") {
      unsigned long count_neg_1 = 0;
      for(auto &aarg: arguments) {
        if(aarg->is_0()) {
          return aarg;
        } else if(aarg->is_neg_1()) {
          count_neg_1++;
        } else if(!aarg->is_1()) {
          args.push_back(aarg);
        }
      }
      negate = (count_neg_1 % 2 == 1);
      if(args.size() == 1) {
        if(negate) {
          return context.apply("-", args);
        } else {
          return args[0];
        }
      }
    } else if(name == "and") {
      std::vector<Expr> working(arguments);
      for(unsigned long i = 0; i < working.size(); i++) {
        auto arg = working[i];
        if(arg->is_true()) {
          continue;
        } else if(arg->is_false()) {
          return arg;
        } else if(arg->is_and()) {
          auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(arg);
          for(const auto &aarg: app->arguments()) {
            working.push_back(aarg);
          }
        } else {
          args.push_back(arg);
        }
      }
      if(args.empty()) {
        return True(context);
      } else if(args.size() == 1) {
        return args[0];
      }
    } else if(name == "or") {
      std::vector<Expr> working(arguments);
      for(unsigned long i = 0; i < working.size(); i++) {
        auto arg = working[i];
        if(arg->is_false()) {
          continue;
        } else if(arg->is_true()) {
          return arg;
        } else if(arg->is_or()) {
          auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(arg);
          for(const auto &aarg: app->arguments()) {
            working.push_back(aarg);
          }
        } else {
          args.push_back(arg);
        }
      }
      if(args.empty()) {
        return False(context);
      } else if(args.size() == 1) {
        return args[0];
      }
    } else {
      args = arguments;
    }
    if(name == "not") {
      auto arg = args[0];
      if(arg->kind() == core::TermKind::Application) {
        auto app = std::dynamic_pointer_cast<core::ApplicationTerm>(arg);
        if(app->function()->name() == "not") {
          return app->arguments()[0];
        }
      }
      args = arguments;
    }
    auto res = context.apply(name, args);
    if(negate) {
      args.push_back(res);
      return context.apply("-", args);
    }
    return res;
  }

  //*-- ArraySort()
  const core::ArraySort *ArraySort(Sort index_sort, Sort element_sort) {
    return get_register().get_sort_manager().array_sort(index_sort, element_sort);
  }

  //*-- BOOL()
  Sort BOOL() {
    return get_register().get_sort_manager().Bool();
  }

  //*-- current_context()
  Context &current_context() {
    if(CONTEXT_STACK.empty()) {
      push_context();
    }
    return *CONTEXT_STACK.top();
  }

  //*-- Equal()
  Expr Equal(const Expr &a, const Expr &b) {
    return Equal(a, b, a->context());
  }

  Expr Equal(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply("=", args, context);
  }

  //*-- Evaluate()
  Expr Evaluate(const Expr &expr, const std::map<Expr, std::variant<Expr, std::vector<Expr>>> &map) {
    core::Evaluator e(map);
    return e.evaluate(expr);
  }

  //*-- Exists()
  Expr Exists(const std::vector<Expr> &variables, const Expr &formula) {
    return Exists(variables, formula, current_context());
  }

  Expr Exists(const std::vector<Expr> &variables, const Expr &formula, Context &context) {
    return std::shared_ptr<core::QuantifiedFormula>(
        new core::QuantifiedFormula(core::Quantifier::exists, variables, formula, context));
  }

  //*-- False()
  Expr False() {
    return False(current_context());
  }

  Expr False(Context &context) {
    return Value("false", BOOL(), context);
  }

  //*-- ForAll()
  Expr ForAll(const std::vector<Expr> &variables, const Expr &formula) {
    return ForAll(variables, formula, current_context());
  }

  Expr ForAll(const std::vector<Expr> &variables, const Expr &formula, Context &context) {
    return std::shared_ptr<core::QuantifiedFormula>(
        new core::QuantifiedFormula(core::Quantifier::forall, variables, formula, context));
  }

  //*-- FreshSymbol()
  Expr FreshSymbol(Sort sort, const std::string &base) {
    return FreshSymbol(sort, current_context(), base);
  }

  Expr FreshSymbol(Sort sort, Context &context, const std::string &base) {
    return context.fresh_constant(sort, base);
  }

  //*-- FunctionSort()
  const core::FunctionSort *FunctionSort(const std::vector<Sort> &domain, Sort range) {
    return get_register().get_sort_manager().function_sort(domain, range);
  }

  //*-- get_atomics()
  std::set<Expr> get_atomics(const Expr &f) {
    std::set<Expr> atomics;
    std::stack<Expr> stack;
    stack.push(f);
    while(!stack.empty()) {
      auto e = stack.top();
      stack.pop();

      if(e->kind() == core::TermKind::Constant) {
        auto exprp = std::dynamic_pointer_cast<core::Constant>(e);
        if(exprp->sort() == BOOL()) {
          atomics.insert(e);
        }
      } else if(e->kind() == core::TermKind::Application) {
        auto exprp = std::dynamic_pointer_cast<core::ApplicationTerm>(e);
        if(exprp->function()->name() == "<=" || exprp->function()->name() == "<" ||
           exprp->function()->name() == ">=" || exprp->function()->name() == ">" ||
           exprp->function()->name() == "=" || exprp->function()->name() == "distinct") {
          atomics.insert(e);
        } else {
          for(const auto &arg: exprp->arguments()) {
            stack.push(arg);
          }
        }
      }
    }
    return atomics;
  }

  //*-- get_register()
  core::Register &get_register() {
    return *core::Register::get_register();
  }

  //*-- GEq()
  Expr GEq(const Expr &a, const Expr &b) {
    return GEq(a, b, a->context());
  }

  Expr GEq(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply(">=", args, context);
  }

  //*-- GT()
  Expr GT(const Expr &a, const Expr &b) {
    return GT(a, b, a->context());
  }

  Expr GT(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply(">", args, context);
  }

  //*-- get_variables()
  std::set<Expr> get_variables(const Expr &f) {
    std::set<Expr> variables;
    std::set<std::string> added;
    std::stack<Expr> stack;
    stack.push(f);
    while(!stack.empty()) {
      auto e = stack.top();
      stack.pop();

      if(e->kind() == core::TermKind::Constant) {
        auto exprp = std::dynamic_pointer_cast<core::Constant>(e);
        if(added.count(exprp->name()) == 0) {
          variables.insert(e);
          added.insert(exprp->name());
        }
      } else if(e->kind() == core::TermKind::Application) {
        auto exprp = std::dynamic_pointer_cast<core::ApplicationTerm>(e);
        for(const auto &arg: exprp->arguments()) {
          stack.push(arg);
        }
      } else if(e->kind() == core::TermKind::Quantified) {
        auto exprp = std::dynamic_pointer_cast<core::QuantifiedFormula>(e);
        stack.push(exprp->formula());
      }
    }
    return variables;
  }

  //*-- Implies()
  Expr Implies(const Expr &a, const Expr &b) {
    return Implies(a, b, a->context());
  }

  Expr Implies(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply("=>", args, context);
  }

  //*-- Int()
  Expr Int(long num) {
    return Int(num, current_context());
  }

  Expr Int(const std::string &raw) {
    return Int(raw, current_context());
  }

  Expr Int(long num, Context &context) {
    return Int(std::to_string(num), context);
  }

  Expr Int(const std::string &raw, Context &context) {
    return Value(raw, INT(), context);
  }

  //*-- INT()
  Sort INT() {
    return get_register().get_sort_manager().Int();
  }

  //*-- ite()
  Expr ite(Expr cond, Expr cons, Expr altern) {
    return Apply("ite", {std::move(cond), std::move(cons), std::move(altern)});
  }

  //*-- LEq()
  Expr LEq(const Expr &a, const Expr &b) {
    return LEq(a, b, a->context());
  }

  Expr LEq(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply("<=", args, context);
  }

  //*-- LT()
  Expr LT(const Expr &a, const Expr &b) {
    return LT(a, b, a->context());
  }

  Expr LT(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply("<", args, context);
  }

  //*-- Mult()
  Expr Mult(const Expr &a, const Expr &b) {
    return Mult(a, b, a->context());
  }

  Expr Mult(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Apply("*", args, context);
  }

  //*-- Not()
  Expr Not(const Expr &f) {
    return Not(f, f->context());
  }

  Expr Not(const Expr &f, Context &context) {
    if(f->is_true()) {
      return False(context);
    } else if(f->is_false()) {
      return True(context);
    }
    std::vector<Expr> args;
    args.push_back(f);
    return Apply("not", args, context);
  }

  //*-- Null()
  Expr Null() {
    return Null(current_context());
  }

  Expr Null(Context &context) {
    return context.null();
  }

  //*-- Or()
  Expr Or(const Expr &a, const Expr &b) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Or(args, a->context());
  }

  Expr Or(const std::vector<Expr> &arguments) {
    return Or(arguments, arguments[0]->context());
  }

  Expr Or(const Expr &a, const Expr &b, Context &context) {
    std::vector<Expr> args;
    args.push_back(a);
    args.push_back(b);
    return Or(args, context);
  }

  Expr Or(const std::vector<Expr> &arguments, Context &context) {
    return Apply("or", arguments, context);
  }

  //*-- pop_context()
  Context *pop_context() {
    Context *context = nullptr;
    if(!CONTEXT_STACK.empty()) {
      context = CONTEXT_STACK.top();
      CONTEXT_STACK.pop();
    }
    return context;
  }

  //*-- push_context()
  Context &push_context(Context *context) {
    if(context == nullptr) {
      context = new Context();
      smtface::theories::initialize_core_theory(*context);
      smtface::theories::initialize_ints_theory(*context);
      smtface::theories::initialize_arrays_theory(*context);
    }
    CONTEXT_STACK.push(context);
    return *context;
  }

  //*-- Select()
  Expr Select(const Expr &array, const Expr &index) {
    return Select(array, index, array->context());
  }

  Expr Select(const Expr &array, const Expr &index, Context &context) {
    std::vector<Expr> args;
    args.push_back(array);
    args.push_back(index);
    return Apply("select", args, context);
  }

  //*-- Store()
  Expr Store(const Expr &array, const Expr &index, const Expr &element) {
    return Store(array, index, element, array->context());
  }

  Expr Store(const Expr &array, const Expr &index, const Expr &element, Context &context) {
    std::vector<Expr> args;
    args.push_back(array);
    args.push_back(index);
    args.push_back(element);
    return Apply("store", args, context);
  }

  //*-- Substitute()
  Expr Substitute(Expr expr, const std::map<Expr, Expr> &map, const std::map<const Function *, const Function *> &fmap) {
    core::Substituter s(map, fmap);
    return s.substitute(std::move(expr));
  }

  //*-- Symbol()
  Expr Symbol(const std::string &name) {
    return Symbol(name, current_context());
  }

  Expr Symbol(const std::string &name, Context &context) {
    return context.constant(name);
  }

  Expr Symbol(const std::string &name, Sort sort) {
    return Symbol(name, sort, current_context());
  }

  Expr Symbol(const std::string &name, Sort sort, Context &context) {
    return context.constant(name, sort);
  }

  //*-- ToString()
  std::string ToString(const Expr &expr) {
    core::Printer p;
    return p.to_string(expr);
  }

  //*-- True()
  Expr True() {
    return True(current_context());
  }

  Expr True(Context &context) {
    return Value("true", get_register().get_sort_manager().Bool(), context);
  }

  //*-- Value()
  Expr Value(const std::string &raw, Sort sort) {
    return Value(raw, sort, current_context());
  }

  Expr Value(const std::string &raw, Sort sort, Context &context) {
    return context.value(raw, sort);
  }

  //*-- Variable()
  Expr Variable(const std::string &name, Sort sort) {
    return Variable(name, sort, current_context());
  }

  Expr Variable(const std::string &name, Sort sort, Context &context) {
    return context.variable(name, sort);
  }

}
