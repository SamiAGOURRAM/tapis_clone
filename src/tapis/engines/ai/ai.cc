//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#include "tapis/engines/ai/ai.hh"

#include "hcvc/logic/not_eliminator.hh"

namespace tapis::ai {

  AbstractInterpreter::AbstractInterpreter(hcvc::Module *module, const std::set<hcvc::Weakness> &weaknesses)
      : _module(module) {
    _clauses = module->hypergraph().get_clauses(weaknesses);
    auto clauses = _clauses.to_set();
    for(auto clause: clauses) {
      for(const auto &app: clause->antecedent_preds()) {
        auto casted = std::dynamic_pointer_cast<hcvc::PredicateApplication>(app);
        _predicates.insert(casted->predicate());
      }
      if(clause->consequent()) {
        auto casted = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*clause->consequent());
        _predicates.insert(casted->predicate());
      }
    }
  }

  unsigned long index_of(const std::string &name, const std::vector<std::string> &elements) {
    auto it = std::find(elements.begin(), elements.end(), name);
    if(it != elements.end()) {
      return it - elements.begin();
    }
    return -1;
  }

  bool is_scalar(const std::vector<long> &vec) {
    for(unsigned long i = 0; i < vec.size() - 1; i++) {
      if(vec[i] != 0) {
        return false;
      }
    }
    return true;
  }

  std::vector<long> term_to_vector(const hcvc::Expr &term, const std::vector<std::string> &int_dims) {
    if(term->kind() == hcvc::TermKind::Constant) {
      auto cnst = std::dynamic_pointer_cast<hcvc::Constant>(term);
      std::vector<long> vec(int_dims.size() + 1, 0);
      vec[index_of(cnst->name(), int_dims)] = 1;
      return vec;
    } else if(term->kind() == hcvc::TermKind::IntegerLiteral) {
      auto val = std::dynamic_pointer_cast<hcvc::IntegerLiteral>(term);
      std::vector<long> vec(int_dims.size() + 1, 0);
      vec[vec.size() - 1] = std::stol(val->value());
      return vec;
    } else if(term->kind() == hcvc::TermKind::OpApp) {
      auto app = std::dynamic_pointer_cast<hcvc::OperatorApplication>(term);
      std::vector<std::vector<long>> args;
      for(const auto &arg: app->arguments()) {
        args.push_back(term_to_vector(arg, int_dims));
      }
      std::vector<long> res(args[0]);
      auto func = app->operat0r()->name();
      if(func == "+") {
        for(unsigned long i = 1; i < args.size(); i++) {
          for(unsigned long j = 0; j < res.size(); j++) {
            res[j] += args[i][j];
          }
        }
      } else if(func == "-") {
        if(args.size() == 1) {
          for(long &re: res) {
            re = -re;
          }
        } else {
          for(unsigned long i = 1; i < args.size(); i++) {
            for(unsigned long j = 0; j < res.size(); j++) {
              res[j] -= args[i][j];
            }
          }
        }
      } else if(func == "*") {
        if(is_scalar(res)) {
          for(unsigned long j = 0; j < res.size(); j++) {
            res[j] = res.back();
          }
        }
        for(unsigned long i = 1; i < args.size(); i++) {
          for(unsigned long j = 0; j < res.size(); j++) {
            if(is_scalar(args[i])) {
              res[j] *= args[i].back();
            } else {
              res[j] *= args[i][j];
            }
          }
        }
      }
      return res;
    }
    return {};
  }

  apron::lincons1 abstract_formula(hcvc::Expr atom, apron::environment &environment) {
    std::vector<std::string> vars;
    for(const auto &var: environment.get_vars()) {
      vars.push_back(var);
    }
    // create the abstract of the atom
    auto app = std::dynamic_pointer_cast<hcvc::OperatorApplication>(atom);
    auto res = term_to_vector(app->arguments()[0], vars);
    auto res_r = term_to_vector(app->arguments()[1], vars);
    for(unsigned long j = 0; j < res.size(); j++) {
      res[j] -= res_r[j];
    }
    // create apron_expr
    ap_constyp_t cty = AP_CONS_EQ;
    if(app->operat0r()->name() == "<") {
      cty = AP_CONS_SUP;
      for(long &re: res) {
        re = -re;
      }
    } else if(app->operat0r()->name() == "<=") {
      cty = AP_CONS_SUPEQ;
      for(long &re: res) {
        re = -re;
      }
    } else if(app->operat0r()->name() == ">") {
      cty = AP_CONS_SUP;
    } else if(app->operat0r()->name() == ">=") {
      cty = AP_CONS_SUPEQ;
    }
    std::vector<apron::coeff> vec(environment.intdim(), 0);
    for(unsigned long j = 0; j < environment.intdim(); j++) {
      vec[j] = res[j];
    }
    apron::linexpr1 expr1(environment, apron::linexpr0(environment.intdim(), &vec[0], res.back(), AP_LINEXPR_SPARSE));
    //std::cout << atom << "= " << apron::lincons1(cty, expr1) << "\n";
    return {cty, expr1};
  }

  std::shared_ptr<hcvc::IntegerLiteral>
  ap_scalar_to_hcvc_int(const apron::scalar &scalar, const hcvc::Variable *variable, hcvc::Context &context) {
    std::string raw;
    if(scalar.get_discr() == AP_SCALAR_DOUBLE) {
      raw = std::to_string((int) scalar.get_double());
    } else if(scalar.get_discr() == AP_SCALAR_MPQ) {
      raw = scalar.get_mpq().get_str();
    } else if(scalar.get_discr() == AP_SCALAR_MPFR) {
      std::cout << "IMPL-MISSING" << "\n";
      exit(10);
    }
    return std::make_shared<hcvc::IntegerLiteral>(raw, variable->type(), context);
  }

  hcvc::Expr
  ap_lincons_to_hcvc_term(const apron::lincons1 &lincons, const std::vector<hcvc::Variable *> &variables,
                          hcvc::Context &context) {
    auto linexpr = lincons.get_linexpr();
    auto ap_variables = lincons.get_environment().get_vars();
    std::vector<hcvc::Expr> args;
    const hcvc::Variable *typing_var = nullptr;
    for(auto &ap_variable: ap_variables) {
      const hcvc::Variable *variable = nullptr;
      for(auto var: variables) {
        if(var->name() == ap_variable) {
          variable = var;
          if(typing_var == nullptr) {
            typing_var = var;
          }
          break;
        }
      }
      auto coeff = ap_scalar_to_hcvc_int(linexpr[variable->name()].get_scalar(), variable, context);
      auto symbol = hcvc::VariableConstant::create(variable, 0, context);
      if(!(coeff->value() == "0")) {
        args.push_back(coeff * symbol);
      }
    }
    args.push_back(ap_scalar_to_hcvc_int(lincons.get_cst().get_scalar(), typing_var, context));
    auto expr = context.apply("+", args);
    if(lincons.get_constyp() == AP_CONS_EQ) {
      expr = (expr == hcvc::IntegerLiteral::get("0", typing_var->type(), context));
    } else if(lincons.get_constyp() == AP_CONS_SUPEQ) {
      expr = context.apply("<=", {hcvc::IntegerLiteral::get("0", typing_var->type(), context), expr});
    } else {
      std::cout << "IMPL-MISSING" << "\n";
      exit(10);
    }
    return expr;
  }

  apron::environment get_environment(const hcvc::Expr &formula) {
    auto variables = hcvc::get_constants(formula);
    // create an environment
    std::vector<apron::var> int_dims(0, "d");
    std::vector<apron::var> real_dims(0, "d");
    for(const auto &variable: variables) {
      if(variable->type()->is_int()) {
        if(variable->kind() == hcvc::TermKind::Constant) {
          auto cnst = std::dynamic_pointer_cast<hcvc::Constant>(variable);
          if(cnst->is_variable_constant()) {
            auto vcnst = std::dynamic_pointer_cast<hcvc::VariableConstant>(variable);
            if(vcnst->variable()->is_data()) {
              continue;
            }
          }
        }
        auto name = std::dynamic_pointer_cast<hcvc::Constant>(variable)->name();
        if(std::find(int_dims.begin(), int_dims.end(),
                     apron::var(std::dynamic_pointer_cast<hcvc::Constant>(variable)->name())) == int_dims.end()) {
          int_dims.emplace_back(name);
        }
      }
    }
    return {int_dims, real_dims};
  }

  const hcvc::Clause *transform_clause(const hcvc::Clause *clause) {
    std::vector<hcvc::Expr> antecedent_preds;
    std::vector<hcvc::Expr> phi = clause->phi();
    std::optional<hcvc::Expr> consequent = std::nullopt;
    int i = 0;
    for(auto &ant_pred: clause->antecedent_preds()) {
      auto ant_pred_app = std::dynamic_pointer_cast<hcvc::PredicateApplication>(ant_pred);
      std::vector<hcvc::Expr> new_args;
      for(auto &arg: ant_pred_app->arguments()) {
        auto cnst = hcvc::Constant::create("..p" + std::to_string(i++), arg->type(), clause->context());
        phi.push_back(cnst == arg);
        new_args.push_back(cnst);
      }
      antecedent_preds.push_back(
          std::make_shared<hcvc::PredicateApplication>(ant_pred_app->predicate(), new_args, clause->context()));
    }
    if(clause->consequent()) {
      auto ant_pred_app = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*clause->consequent());
      std::vector<hcvc::Expr> new_args;
      for(auto &arg: ant_pred_app->arguments()) {
        auto cnst = hcvc::Constant::create("..p" + std::to_string(i++), arg->type(), clause->context());
        phi.push_back(cnst == arg);
        new_args.push_back(cnst);
      }
      consequent = std::make_optional(
          std::make_shared<hcvc::PredicateApplication>(ant_pred_app->predicate(), new_args, clause->context()));
    }
    return new hcvc::Clause(antecedent_preds, phi, consequent, clause->context());
  }

  bool itere(unsigned long k,
             std::map<const hcvc::Predicate *, apron::abstract1> **invariants,
             const std::set<const hcvc::Clause *> &clauses,
             std::map<const hcvc::Predicate *, apron::environment> &environments,
             bool widen,
             bool fixpoint,
             apron::manager &manager) {
    auto updated_invariants = new std::map<const hcvc::Predicate *, apron::abstract1>((*invariants)->begin(),
                                                                                      (*invariants)->end());

    //std::cout << "---" << "\n";
    for(auto clause: clauses) {
      clause = transform_clause(clause);
      auto consequent = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*clause->consequent());
      auto predicate = consequent->predicate();
      auto environment = get_environment(clause->to_formula());
      // deal with the phi part
      std::vector<apron::lincons1> ap_constraints_vect;
      std::vector<hcvc::Expr> phi;
      for(const auto &el: clause->phi()) {
        if(el->kind() == hcvc::TermKind::OpApp &&
           std::dynamic_pointer_cast<hcvc::OperatorApplication>(el)->operat0r()->name() == "and") {
          auto a = std::dynamic_pointer_cast<hcvc::OperatorApplication>(el);
          for(auto suba: a->arguments()) {
            phi.push_back(suba);
          }
        } else {
          phi.push_back(el);
        }
      }
      for(const auto &atom: phi) {
        if(atom->kind() == hcvc::TermKind::QuantifiedFormula || atom->kind() == hcvc::TermKind::BooleanLiteral) {
          continue;
        }
        bool slice = false;
        for(const auto &cnst: hcvc::get_constants(
            atom)) {
          if(std::dynamic_pointer_cast<hcvc::Constant>(cnst)->is_variable_constant()) {
            if(std::dynamic_pointer_cast<hcvc::VariableConstant>(cnst)->variable()->is_data()) {
              slice = true;
              break;
            }
          }
          if(cnst->type()->is_array() || cnst->type()->is_bool()) {
            slice = true;
            break;
          }
        }
        if(slice) {
          continue;
        }
        for(auto operat0r: hcvc::get_operations(atom)) {
          if(operat0r->name() == "[]") {
            slice = true;
            break;
          }
        }
        if(slice) {
          continue;
        }
        hcvc::NotEliminator ne;
        auto atm = ne.eliminate(atom);
        ap_constraints_vect.emplace_back(abstract_formula(atm, environment));
      }
      apron::lincons1_array ap_constraints(environment, ap_constraints_vect.size());
      for(unsigned long i = 0, lengthi = ap_constraints_vect.size(); i < lengthi; i++) {
        ap_constraints.set(i, ap_constraints_vect[i]);
      }
      apron::abstract1 result(manager, ap_constraints);
      // deal with the antecedent predicates part
      for(const auto &app: clause->antecedent_preds()) {
        auto pred_app = std::dynamic_pointer_cast<hcvc::PredicateApplication>(app);
        std::vector<apron::var> old_names;
        std::vector<apron::var> new_names;
        unsigned long i = 0;
        for(const auto &arg: pred_app->arguments()) {
          if(arg->type()->is_array() || arg->type()->is_bool() ||
             pred_app->predicate()->parameters()[i]->is_data()) {
            i++;
            continue;
          }
          old_names.emplace_back(pred_app->predicate()->parameters()[i]->name());
          new_names.emplace_back(std::dynamic_pointer_cast<hcvc::Constant>(arg)->name());
          //std::cout << pred_app->predicate()->parameters()[i]->name() << " - " << arg << "\n";
          i++;
        }
        auto known = updated_invariants->at(pred_app->predicate());
        known = known.rename(manager, old_names, new_names);
        known = known.change_environment(manager, environment, false);
        apron::meet(manager, result, result, known);
      }
      std::vector<apron::var> old_names;
      std::vector<apron::var> new_names;
      unsigned long i = 0;
      //std::cout << result << "\n";
      for(const auto &arg: consequent->arguments()) {
        if(arg->type()->is_array() || arg->type()->is_bool() || predicate->parameters()[i]->is_data()) {
          i++;
          continue;
        }
        //std::cout << "map: " << arg << " to " << predicate->parameters()[i]->name() << "\n";
        old_names.emplace_back(std::dynamic_pointer_cast<hcvc::Constant>(arg)->name());
        new_names.emplace_back(predicate->parameters()[i]->name());
        i++;
      }
      apron::abstract1 joined(manager, environments[predicate], apron::top());
      result = result.rename(manager, old_names, new_names);
      result = result.change_environment(manager, environments[predicate], false);
      apron::join(manager, joined, updated_invariants->at(predicate), result);
      updated_invariants->insert_or_assign(predicate, joined);
      delete clause;
    }
    if(widen) {
      for(const auto &[predicate, abs]: *updated_invariants) {
        apron::abstract1 widened(manager, environments[predicate], apron::top());
        apron::widening(manager, widened, (*invariants)->at(predicate), abs);
        updated_invariants->insert_or_assign(predicate, widened);
      }
    }
    bool is_fixpoint = true;
    if(fixpoint) {
      for(const auto &[predicate, abs]: *updated_invariants) {
        if(!abs.is_leq(manager, (*invariants)->at(predicate))) {
          is_fixpoint = false;
          break;
        }
      }
    } else {
      is_fixpoint = false;
    }

    delete *invariants;
    *invariants = updated_invariants;
    return is_fixpoint;
  }

  std::map<const hcvc::Predicate *, hcvc::Expr> AbstractInterpreter::analyze(apron::manager &manager) {
    std::map<const hcvc::Predicate *, apron::environment> environments;
    for(const auto &predicate: _predicates) {
      std::vector<apron::var> int_dims(0, "d");
      std::vector<apron::var> real_dims(0, "d");
      for(const auto &variable: predicate->parameters()) {
        if(variable->type()->is_int() && !variable->type()->is_bool()) {
          int_dims.emplace_back(variable->name());
        }
      }
      auto environment = apron::environment(int_dims, real_dims);
      environments.emplace(predicate, environment);
    }
    auto invariants = new std::map<const hcvc::Predicate *, apron::abstract1>();
    for(const auto &predicate: _predicates) {
      apron::abstract1 abstract(manager, environments[predicate], apron::bottom());
      invariants->emplace(predicate, abstract);
    }
    itere(0, &invariants, _clauses.init_clauses(), environments, false, false, manager);
    unsigned long k = 1, max_k = _clauses.to_set().size() * 2;
    while(k < max_k) {
      if(itere(k, &invariants, _clauses.induction_clauses(), environments, k >= std::min(2 * max_k / 3, 2 * max_k / 3),
               k >= std::min(2 * max_k / 3, 2 * max_k / 3), manager)) {
#ifndef NDEBUG
        //std::cout << "ai " << max_k << " - " << k << " - " << 2 * max_k / 3 << "\n";
#endif
        break;
      }
      k++;
    }
    std::map<const hcvc::Predicate *, hcvc::Expr> results;
    for(auto &[predicate, abs]: *invariants) {
      hcvc::Expr f = _module->context().get_true();
      if(!abs.is_bottom(manager)) {
        auto lincons_array = abs.to_lincons_array(manager);
        for(unsigned long i = 0, length = lincons_array.size(); i < length; i++) {
          f = f && ap_lincons_to_hcvc_term(lincons_array.get(i), predicate->parameters(), _module->context());
        }
      } else {
        f = _module->context().get_false();
      }
      results.emplace(predicate, f);
#ifndef NDEBUG
      std::cout << "ai " << predicate->name() << ": " << abs << "\n";
#endif
    }
    delete invariants;
    return results;
  }

}
