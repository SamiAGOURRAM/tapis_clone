//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/clause/hypergraph.hh"

#include <iostream>
#include <stack>
#include "hcvc/context.hh"
#include "hcvc/program/variable.hh"

namespace hcvc {

  //*-- HyperGraph
  void HyperGraph::dump() {
    for(auto clause: to_set()) {
      clause->dump();
    }
  }

  std::map<const Variable *, std::set<unsigned long>> get_used_var_indexes(const Expr &left) {
    std::map<const Variable *, std::set<unsigned long>> res;
    for(const auto &cnst_expr: get_constants(left)) {
      auto cnst = std::dynamic_pointer_cast<Constant>(cnst_expr);
      if(cnst->is_variable_constant()) {
        auto var_cnst = std::dynamic_pointer_cast<VariableConstant>(cnst);
        res[var_cnst->variable()].insert(var_cnst->index());
      }
    }
    return res;
  }

  const Clause *substitute_clause(const Clause *subclause, const Clause *clause, Context &context) {
    // subclause = R(a)... ^ phi_a => P(x)
    auto R_a = subclause->antecedent_preds();
    auto phi_a = subclause->phi();
    auto P_x = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*subclause->consequent());
    auto P = P_x->predicate();
    // clause = P(y) ^ Q(b)... ^ phi_b => ...b
    auto phi_b = clause->phi();
    // identifies P(y) and Q(b)... in clause
    std::vector<Expr> Q_b;
    std::shared_ptr<PredicateApplication> P_y;
    bool picked = false;
    for(const auto &expr: clause->antecedent_preds()) {
      auto pred_app = std::dynamic_pointer_cast<hcvc::PredicateApplication>(expr);
      if(pred_app->predicate() == P && !picked) {
        picked = true;
        P_y = pred_app;
      } else {
        Q_b.push_back(pred_app);
      }
    }

    // We will produce newclause = S(c)... ^ phi_d => ...c <==> R(a)... ^ Q(b)... ^ phi_b ^ phi_a => ...c

    std::vector<Expr> S_c = Q_b; // we will add R(a)... later
    std::vector<Expr> phi_c = phi_b; // we will add more things
    // before adding the other parts of subclause to the new clause, we have to ensure that the used
    // variable names are all different from those used on clause. We must rename them if necessary.
    auto used = get_used_var_indexes(clause->to_formula());
    auto sub_used = get_used_var_indexes(subclause->to_formula());
    std::map<Expr, Expr> sub_map;
    for(auto [var, indexes]: sub_used) {
      unsigned long i = 0;
      for(auto index: indexes) {
        while(used[var].count(i) > 0) {
          i++;
        }
        used[var].insert(i);
        sub_map[VariableConstant::create(var, index, context)] = VariableConstant::create(var, i, context);
      }
    }
    for(unsigned long i = 0, size = P_y->arguments().size(); i < size; i++) {
      auto a = P_y->arguments()[i];
      auto b = substitute(P_x->arguments()[i], sub_map);
      phi_c.push_back(a == b);
    }
    for(const auto &expr: R_a) {
      auto pred_app = std::dynamic_pointer_cast<PredicateApplication>(expr);
      std::vector<Expr> args;
      for(auto &arg: pred_app->arguments()) {
        args.push_back(substitute(arg, sub_map));
      }
      S_c.push_back(std::make_shared<PredicateApplication>(pred_app->predicate(), args, context));
    }
    for(auto &expr: phi_a) {
      phi_c.push_back(substitute(expr, sub_map));
    }

    for(unsigned int i = 0; i < phi_c.size(); i++) {
      bool used_for_simplification = false;
      auto expr = phi_c[i];
      if(expr->kind() == TermKind::OpApp &&
         std::dynamic_pointer_cast<OperatorApplication>(expr)->operat0r()->name() == "=") {
        auto arg1 = std::dynamic_pointer_cast<OperatorApplication>(expr)->arguments().at(0);
        auto arg2 = std::dynamic_pointer_cast<OperatorApplication>(expr)->arguments().at(1);
        if(arg1->kind() == TermKind::Constant && arg2->kind() == TermKind::Constant &&
           std::dynamic_pointer_cast<Constant>(arg1)->is_variable_constant() &&
           std::dynamic_pointer_cast<Constant>(arg2)->is_variable_constant()) {
          auto vc1 = std::dynamic_pointer_cast<VariableConstant>(arg1);
          auto vc2 = std::dynamic_pointer_cast<VariableConstant>(arg2);
          if(vc1->variable() == vc2->variable()) {
            auto to_keep = vc1->index() < vc2->index() ? vc1 : vc2;
            auto to_eliminate = vc1->index() < vc2->index() ? vc2 : vc1;
            std::map<Expr, Expr> submap = {{to_eliminate, to_keep}};
            for(unsigned int j = 0; j < S_c.size(); j++) {
              S_c[j] = substitute(S_c[j], submap);
            }
            for(unsigned int j = 0; j < phi_c.size(); j++) {
              phi_c[j] = substitute(phi_c[j], submap);
            }
            used_for_simplification = true;
          }
        }
      }
      if(used_for_simplification) {
        phi_c.erase(phi_c.begin() + i);
        i--;
      }
    }
    return new Clause(S_c, phi_c, clause->consequent(), context);
  }

  void HyperGraph::simplify(hcvc::Context &context) {
    std::set<Weakness> weaknesses;
    for(auto [weakness, _]: _weakness_clause_map) {
      weaknesses.insert(weakness);
    }
    auto reachables = get_clauses(weaknesses).to_set();
    std::set<const Clause *> to_remove;
    for(auto clause: _clauses) {
      if(reachables.count(clause) == 0) {
        to_remove.insert(clause);
      }
    }
    for(auto clause: to_remove) {
      erase(clause);
    }

    // Eliminate if's postcondition
    while(true) {
      bool done = true;
      for(auto &predicate: _to_be_simplified) {
        if(!_antecedency[predicate].empty() && !_consequency[predicate].empty()) {
          done = false;
          auto clauses = _antecedency[predicate];
          auto subclauses = _consequency[predicate];
          for(auto &clause: clauses) {
            for(auto &subclause: subclauses) {
              auto newclause = substitute_clause(subclause, clause, context);
              Weakness clause_weakness;
              for(auto &[weakness, wclauses]: _weakness_clause_map) {
                if(wclauses.count(clause) > 0) {
                  wclauses.insert(newclause);
                  clause_weakness = weakness;
                }
              }
              add(newclause, clause_weakness);
            }
          }
          for(auto clause: clauses) {
            for(auto &[weakness, wclauses]: _weakness_clause_map) {
              if(wclauses.count(clause) > 0) {
                wclauses.erase(clause);
              }
            }
            erase(clause);
          }
          for(auto clause: subclauses) {
            erase(clause);
          }
        }
      }
      if(done) {
        break;
      }
    }
    while(true) {
      // pick P ^ ... => ...
      const Clause *clause = nullptr;
      const Predicate *P = nullptr;
      for(auto predicate: _to_be_simplified) {
        if(!_antecedency[predicate].empty()) {
          clause = *_antecedency[predicate].begin();
          P = predicate;
          break;
        }
      }
      if(clause == nullptr) {
        break;
      }
      while(true) {
        // pick ... => P such that P is to be eiminated
        const Clause *subclause = nullptr;
        if(!_consequency[P].empty()) {
          subclause = *_consequency[P].begin();
        }
        if(subclause == nullptr) {
          break;
        }
        // replace the left most P application in clause with subclause
        auto newclause = substitute_clause(subclause, clause, context);
        Weakness clause_weakness;
        for(auto &[weakness, clauses]: _weakness_clause_map) {
          if(clauses.count(clause) > 0) {
            clauses.erase(clause);
            clauses.insert(newclause);
            clause_weakness = weakness;
          }
        }
        add(newclause, clause_weakness);
        erase(subclause);
      }
      erase(clause);
    }
    // Eliminate precondition/summary for specified function and use instead their given specification
    std::set<const hcvc::Predicate *> predicate_to_eliminate;
    for(auto predicate: predicates()) {
      hcvc::Function *function = nullptr;
      if(predicate->kind() == PredicateKind::precondition) {
        function = ((FunctionPreconditionPredicate *) predicate)->function();
      } else if(predicate->kind() == PredicateKind::summary) {
        function = ((FunctionSummaryPredicate *) predicate)->function();
      }
      if(function != nullptr && function->is_specified()) {
        predicate_to_eliminate.emplace(predicate);
      }
    }
    while(true) {
      const hcvc::Clause *clause = nullptr;
      for(auto c: _clauses) {
        if(c->consequent()) {
          if(predicate_to_eliminate.count(
              std::dynamic_pointer_cast<hcvc::PredicateApplication>(*c->consequent())->predicate()) > 0) {
            clause = c;
            break;
          }
        }
        for(auto &pred_app: c->antecedent_preds()) {
          if(predicate_to_eliminate.count(
              std::dynamic_pointer_cast<hcvc::PredicateApplication>(pred_app)->predicate()) > 0) {
            clause = c;
            break;
          }
        }
      }
      if(clause == nullptr) {
        break;
      }
      clause->dump();

      auto new_phi = clause->phi();
      std::vector<hcvc::Expr> new_pred_apps;
      bool consequent_updated = false;
      bool consequent_is_pre = false;

      if(clause->consequent()) {
        auto predicate = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*clause->consequent())->predicate();
        hcvc::Function *function = nullptr;
        if(predicate->kind() == PredicateKind::precondition) {
          function = ((FunctionPreconditionPredicate *) predicate)->function();
        } else if(predicate->kind() == PredicateKind::summary) {
          function = ((FunctionSummaryPredicate *) predicate)->function();
        }
        consequent_is_pre = predicate->kind() == PredicateKind::precondition;
        if(predicate_to_eliminate.count(predicate) > 0) {
          auto consequent = std::dynamic_pointer_cast<hcvc::PredicateApplication>(*clause->consequent());
          std::map<Expr, Expr> sub_map = {};
          for(unsigned long i = 0; i < consequent->predicate()->parameters().size(); i++) {
            sub_map[VariableConstant::create(consequent->predicate()->parameters()[i], 0,
                                             context)] = consequent->arguments()[i];
          }
          if(consequent->predicate()->kind() == PredicateKind::precondition) {
            new_phi.push_back(!substitute(function->get_requirement(), sub_map));
          } else if(consequent->predicate()->kind() == PredicateKind::summary) {
            new_phi.push_back(!substitute(function->get_ensurement(), sub_map));
          }
          consequent_updated = true;
        }
      }

      for(auto &pred_app: clause->antecedent_preds()) {
        auto casted = std::dynamic_pointer_cast<hcvc::PredicateApplication>(pred_app);
        auto predicate = casted->predicate();
        hcvc::Function *function = nullptr;
        if(predicate->kind() == PredicateKind::precondition) {
          function = ((FunctionPreconditionPredicate *) predicate)->function();
        } else if(predicate->kind() == PredicateKind::summary) {
          function = ((FunctionSummaryPredicate *) predicate)->function();
        }
        if(predicate_to_eliminate.count(predicate) > 0) {
          std::map<Expr, Expr> sub_map = {};
          for(unsigned long i = 0; i < predicate->parameters().size(); i++) {
            sub_map[VariableConstant::create(predicate->parameters()[i], 0, context)] = casted->arguments()[i];
          }
          if(predicate->kind() == PredicateKind::precondition) {
            new_phi.push_back(substitute(function->get_requirement(), sub_map));
          } else if(predicate->kind() == PredicateKind::summary) {
            new_phi.push_back(substitute(function->get_ensurement(), sub_map));
          }
        } else {
          new_pred_apps.push_back(pred_app);
        }
      }

      auto new_clause = new Clause(new_pred_apps, new_phi, consequent_updated ? std::nullopt : clause->consequent(),
                                   context);
      std::set<Weakness> weaknesses;
      for(auto [weakness, clauses]: _weakness_clause_map) {
        if(clauses.count(clause) > 0) {
          weaknesses.insert(weakness);
        }
      }
      erase(clause);
      if(consequent_updated) {
        add(new_clause, consequent_is_pre ? Weakness::assertion_violation : Weakness::specification_violation);
      }
      if(!weaknesses.empty()) {
        for(auto weakness: weaknesses) {
          add(new_clause, weakness);
        }
      } else {
        add(new_clause);
      }
    }
    auto clauses = _clauses;
    _init_clauses = {};
    _ind_clauses = {};
    _goal_clauses = {};
    _antecedency = {};
    _consequency = {};
    for(auto clause: clauses) {
      add(clause);
    }
    for(auto [weakness, clss]: _weakness_clause_map) {
      std::set<const hcvc::Clause *> new_clss;
      for(auto cl: clss) {
        if(clauses.count(cl) > 0) {
          new_clss.insert(cl);
        }
      }
      _weakness_clause_map[weakness] = new_clss;
    }
    // remove clause where P(...) ^ false => ...
    std::set<const Clause *> to_rmv;
    for(auto clause: this->_clauses) {
      if(is_false(clause->phi_expr())) {
        to_rmv.insert(clause);
      }
    }
    for(auto clause: to_rmv) {
      this->erase(clause);
    }
  }

}
