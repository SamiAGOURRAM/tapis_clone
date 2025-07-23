//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include <utility>
#include <variant>

#include "hcvc/logic/smtface.hh"

#include "hcvc/context.hh"

namespace hcvc {

  //*-- To_smtface
  To_smtface::To_smtface(hcvc::Context &hcvc_context, smtface::Context *smtface_context)
      : _hcvc_context(hcvc_context),
        _smtface_context(smtface_context == nullptr ? smtface::current_context() : *smtface_context) {}

  smtface::Expr To_smtface::to_smtface(const hcvc::Expr &expr) {
    expr->accept(*this);
    auto res = result();
    return res;
  }

  smtface::Sort To_smtface::to_smtface(const Type *type) {
    if(type->is_bool()) {
      return smtface::BOOL();
    } else if(type->is_int()) {
      return smtface::INT();
    } else if(type->is_array()) {
      return smtface::ArraySort(smtface::INT(), to_smtface(dynamic_cast<const ArrayType *>(type)->element_type()));
    }
    return nullptr;
  }

void To_smtface::visit(std::shared_ptr<OperatorApplication> term) {
    std::vector<smtface::Expr> args;
    const Operator *func = term->operat0r(); // Note: Original typo 'operat0r' is kept
    for (const auto &arg : term->arguments()) {
        arg->accept(*this);
        auto r = result();
        args.push_back(r);
    }

    std::string name = func->name();

    if (name == "[]") {
        if (args.size() == 2) {
            name = "select";
        } else if (args.size() == 3) {
            name = "store";
        }
    } else if (name == "/") {
        name = "div";
    } else if (name == "sum" || name == "sum_range") {
        // 1. Define the function's signature for the smtface context.
        smtface::Sort array_sort = smtface::ArraySort(smtface::INT(), smtface::INT());
        smtface::Sort int_sort = smtface::INT();
        std::vector<smtface::Sort> arg_sorts = {array_sort, int_sort, int_sort};
        smtface::Sort return_sort = int_sort;

        // 2. Ensure the function is declared in the context.
        //    This registers "sum_range" and its signature. We don't need the return value.
        _smtface_context.function("sum_range", arg_sorts, return_sort);

        // 3. Now, call the context's standard apply method using the registered name.
        //    This is consistent with how other operators are handled.
        _return(_smtface_context.apply("sum_range", args));
        return; // Important: exit after handling this special case.

    }
    
    // Original line for all other operators (like '!', '=>', 'and', etc.)
    _return(_smtface_context.apply(name, args));
}

  void To_smtface::visit(std::shared_ptr<Constant> term) {
    _return(_smtface_context.constant(term->name(), to_smtface(term->type())));
  }

  void To_smtface::visit(std::shared_ptr<BooleanLiteral> term) {
    _return(smtface::Value(term->value() ? "true" : "false", smtface::BOOL()));
  }

  void To_smtface::visit(std::shared_ptr<IntegerLiteral> term) {
    _return(smtface::Value(term->value(), smtface::INT()));
  }

  void To_smtface::visit(std::shared_ptr<QuantifiedFormula> term) {
    std::vector<smtface::Expr> vars;
    for(auto &var: term->quantifiers()) {
      var->accept(*this);
      vars.push_back(result());
    }
    term->formula()->accept(*this);
    auto formula = result();
    if(term->quantifier_kind() == Quantifier::ForAll) {
      _return(smtface::ForAll(vars, formula));
    } else if(term->quantifier_kind() == Quantifier::Exists) {
      _return(smtface::Exists(vars, formula));
    }
  }

  void To_smtface::visit(std::shared_ptr<ArrayLiteral> term) {
    std::cout << "IMPL-MISSING" << "\n";
    exit(10);
  }

  void To_smtface::visit(std::shared_ptr<PredicateApplication> term) {
  }

  //*-- From_smtface
  From_smtface::From_smtface(const hcvc::Expr &original)
      : _hcvc_context(original->context()) {
    auto constants = hcvc::get_constants(original);
    for(auto &exp: constants) {
      auto cnst = std::dynamic_pointer_cast<hcvc::Constant>(exp);
      _scope[cnst->name()] = exp;
    }
  }

  From_smtface::From_smtface(hcvc::Context &hcvc_context, std::map<std::string, hcvc::Expr> scope)
      : _hcvc_context(hcvc_context), _scope(std::move(scope)) {}

  hcvc::Expr From_smtface::from_smtface(smtface::Expr expr) {
    if(expr->kind() == smtface::core::TermKind::Constant) {
      auto cnst = std::dynamic_pointer_cast<smtface::core::Constant>(expr);
      return _scope.at(cnst->name());
    } else if(expr->kind() == smtface::core::TermKind::Value) {
      auto val = std::dynamic_pointer_cast<smtface::core::Value>(expr);
      if(val->is_true()) {
        return _hcvc_context.get_true();
      } else if(val->is_false()) {
        return _hcvc_context.get_false();
      } else {
        return hcvc::IntegerLiteral::get(val->raw(), _hcvc_context.type_manager().int_type(),
                                         _hcvc_context);
      }
    } else if(expr->kind() == smtface::core::TermKind::Application) {
      auto app = std::dynamic_pointer_cast<smtface::core::ApplicationTerm>(expr);
      std::vector<hcvc::Expr> args;
      for(auto &arg: app->arguments()) {
        args.push_back(from_smtface(arg));
      }
      auto name =app->function()->name();
      if(name == "div") {
        name = "/";
      }
      return _hcvc_context.apply(name, args);
    }
  }

}
