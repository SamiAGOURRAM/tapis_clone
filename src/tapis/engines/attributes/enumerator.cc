//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "tapis/engines/attributes/enumerator.hh"

#include <stack>
#include <utility>
#include "rope.hh"

#include "tapis/engines/outputs.hh"
#include "smtface/solvers/z3/solver.hh"
#include "smtface/utils/array_to_epr.hh"
#include "hcvc/logic/smtface.hh"

namespace tapis::HornICE::qdt {

  //*-- Enumerator
  Enumerator::Enumerator(const hcvc::Predicate *predicate, const std::vector<hcvc::Expr> &terms,
                         AttributeManager &attribute_manager, hcvc::Context &context)
      : _predicate(predicate),
        _terms(terms),
        _attribute_manager(attribute_manager),
        _context(context) {}

  Enumerator::~Enumerator() = default;

  //*-- EmptyEnumerator
  EmptyEnumerator::EmptyEnumerator(const hcvc::Predicate *predicate,
                                   const std::vector<hcvc::Expr> &terms,
                                   AttributeManager &attribute_manager, hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context) {}

  EmptyEnumerator::~EmptyEnumerator() = default;

  bool EmptyEnumerator::has_terminated() const {
    return true;
  }

  bool EmptyEnumerator::is_finite() const {
    return true;
  }

  bool EmptyEnumerator::is_incremental() const {
    return false;
  }

  void EmptyEnumerator::enumerate() {}

  //*-- BooleanEnumerator
  BooleanEnumerator::BooleanEnumerator(const hcvc::Predicate *predicate,
                                       const std::vector<hcvc::Expr> &terms,
                                       AttributeManager &attribute_manager, hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_terminated(false) {
    // assumes that all variables are of boolean sort.
  }

  BooleanEnumerator::~BooleanEnumerator() = default;

  bool BooleanEnumerator::has_terminated() const {
    return _has_terminated;
  }

  bool BooleanEnumerator::is_finite() const {
    return true;
  }

  bool BooleanEnumerator::is_incremental() const {
    return false;
  }

  void BooleanEnumerator::enumerate() {
    _has_terminated = true;
    for(const auto &symbol: this->terms()) {
      auto attribute = this->attribute_manager().get_attribute(this->predicate(), symbol);
      _attributes.insert(attribute);
    }
  }

  //*-- EqualityEnumerator
  EqualityEnumerator::EqualityEnumerator(const hcvc::Predicate *predicate,
                                         const std::vector<hcvc::Expr> &terms,
                                         tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                         hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_terminated(false) {}

  EqualityEnumerator::~EqualityEnumerator() = default;

  bool EqualityEnumerator::has_terminated() const {
    return _has_terminated;
  }

  bool EqualityEnumerator::is_finite() const {
    return true;
  }

  bool EqualityEnumerator::is_incremental() const {
    return false;
  }

  void EqualityEnumerator::enumerate() {
    _has_terminated = true;
    for(unsigned long i = 0, lengthi = this->terms().size() - 1; i < lengthi; i++) {
      auto symboli = this->terms()[i];
      for(unsigned long j = i + 1, lengthj = this->terms().size(); j < lengthj; j++) {
        auto symbolj = this->terms()[j];
        auto attribute = this->attribute_manager().get_attribute(this->predicate(), symboli == symbolj);
        _attributes.insert(attribute);
      }
    }
  }

  //*-- UpperBoundEnumerator
  UpperBoundEnumerator::UpperBoundEnumerator(const hcvc::Predicate *predicate,
                                             const std::vector<hcvc::Expr> &terms,
                                             tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                             hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_terminated(false) {}

  UpperBoundEnumerator::~UpperBoundEnumerator() = default;

  bool UpperBoundEnumerator::has_terminated() const {
    return _has_terminated;
  }

  bool UpperBoundEnumerator::is_finite() const {
    return true;
  }

  bool UpperBoundEnumerator::is_incremental() const {
    return false;
  }

  void UpperBoundEnumerator::enumerate() {
    _has_terminated = true;
    if(this->terms().size() > 0) {
      for(unsigned long i = 0, lengthi = this->terms().size() - 1; i < lengthi; i++) {
        auto symboli = this->terms()[i];
        for(unsigned long j = i + 1, lengthj = this->terms().size(); j < lengthj; j++) {
          auto symbolj = this->terms()[j];
          auto attribute1 = this->attribute_manager().get_attribute(this->predicate(), symboli <= symbolj);
          auto attribute2 = this->attribute_manager().get_attribute(this->predicate(), symbolj <= symboli);
          _attributes.insert(attribute1);
          _attributes.insert(attribute2);
        }
      }
    }
  }

  //*-- StrictUpperBoundEnumerator
  StrictUpperBoundEnumerator::StrictUpperBoundEnumerator(const hcvc::Predicate *predicate,
                                                         const std::vector<hcvc::Expr> &terms,
                                                         tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                                         hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_terminated(false) {}

  StrictUpperBoundEnumerator::~StrictUpperBoundEnumerator() = default;

  bool StrictUpperBoundEnumerator::has_terminated() const {
    return _has_terminated;
  }

  bool StrictUpperBoundEnumerator::is_finite() const {
    return true;
  }

  bool StrictUpperBoundEnumerator::is_incremental() const {
    return false;
  }

  void StrictUpperBoundEnumerator::enumerate() {
    _has_terminated = true;
    for(unsigned long i = 0, lengthi = this->terms().size() - 1; i < lengthi; i++) {
      auto symboli = this->terms()[i];
      for(unsigned long j = i + 1, lengthj = this->terms().size(); j < lengthj; j++) {
        auto symbolj = this->terms()[j];
        auto attribute1 = this->attribute_manager().get_attribute(this->predicate(),
                                                                  this->context().apply("<", {symboli, symbolj}));
        auto attribute2 = this->attribute_manager().get_attribute(this->predicate(),
                                                                  this->context().apply("<", {symbolj, symboli}));
        _attributes.insert(attribute1);
        _attributes.insert(attribute2);
      }
    }
  }

  //*-- IntervalEnumerator
  IntervalEnumerator::IntervalEnumerator(const hcvc::Predicate *predicate,
                                         const std::vector<hcvc::Expr> &terms,
                                         tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                         hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_started(false),
        _bound(0) {}

  IntervalEnumerator::~IntervalEnumerator() = default;

  bool IntervalEnumerator::has_terminated() const {
    return false;
  }

  bool IntervalEnumerator::is_finite() const {
    return false;
  }

  bool IntervalEnumerator::is_incremental() const {
    return true;
  }

  void IntervalEnumerator::enumerate() {
    if(!_has_started) {
      _has_started = true;
      for(const auto &symbol: this->terms()) {
        _bases.push_back(symbol);
        _bases.push_back(-symbol);
      }
    }
    auto k = _bound++;
    for(auto &base: _bases) {
      if(k != 0) {
        auto attribute = attribute_manager().get_attribute(this->predicate(), base <= hcvc::IntegerLiteral::get(
            std::to_string(-k), base->type(), this->context()));
        _attributes.insert(attribute);
      }
      auto attribute = attribute_manager().get_attribute(this->predicate(), base <=
                                                                            hcvc::IntegerLiteral::get(std::to_string(k),
                                                                                                      base->type(),
                                                                                                      this->context()));
      _attributes.insert(attribute);
    }
  }

  //*-- DifferenceBoundEnumerator
  DifferenceBoundEnumerator::DifferenceBoundEnumerator(const hcvc::Predicate *predicate,
                                                       const std::vector<hcvc::Expr> &terms,
                                                       tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                                       hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_started(false),
        _bound(0) {}

  DifferenceBoundEnumerator::~DifferenceBoundEnumerator() = default;

  bool DifferenceBoundEnumerator::has_terminated() const {
    return false;
  }

  bool DifferenceBoundEnumerator::is_finite() const {
    return false;
  }

  bool DifferenceBoundEnumerator::is_incremental() const {
    return true;
  }

  void DifferenceBoundEnumerator::enumerate() {
    if(!_has_started) {
      _has_started = true;
      for(unsigned long i = 0, lengthi = this->terms().size() - 1; i < lengthi; i++) {
        auto symboli = this->terms()[i];
        for(unsigned long j = i + 1, lengthj = this->terms().size(); j < lengthj; j++) {
          auto symbolj = this->terms()[j];
          _bases.push_back(symboli - symbolj);
          _bases.push_back(symbolj - symboli);
        }
      }
    }
    auto k = _bound++;
    for(auto &base: _bases) {
      if(k != 0) {
        auto attribute = attribute_manager().get_attribute(this->predicate(), base <= hcvc::IntegerLiteral::get(
            std::to_string(-k), base->type(), this->context()));
        _attributes.insert(attribute);
      }
      auto attribute = attribute_manager().get_attribute(this->predicate(), base <=
                                                                            hcvc::IntegerLiteral::get(std::to_string(k),
                                                                                                      base->type(),
                                                                                                      this->context()));
      _attributes.insert(attribute);
    }
  }

  //*-- OctagonEnumerator
  OctagonEnumerator::OctagonEnumerator(const hcvc::Predicate *predicate,
                                       const std::vector<hcvc::Expr> &terms,
                                       tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                       hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_started(false),
        _bound(0) {}

  OctagonEnumerator::~OctagonEnumerator() = default;

  bool OctagonEnumerator::has_terminated() const {
    return false;
  }

  bool OctagonEnumerator::is_finite() const {
    return false;
  }

  bool OctagonEnumerator::is_incremental() const {
    return true;
  }

  void OctagonEnumerator::enumerate() {
    if(!_has_started) {
      _has_started = true;
      if(this->terms().size() >= 1) {
        for(unsigned long i = 0, lengthi = this->terms().size() - 1; i < lengthi; i++) {
          auto symboli = this->terms()[i];
          for(unsigned long j = i + 1, lengthj = this->terms().size(); j < lengthj; j++) {
            auto symbolj = this->terms()[j];
            _bases.push_back(symboli + symbolj);
            _bases.push_back(symboli + (-symbolj));
            _bases.push_back((-symboli) + symbolj);
            _bases.push_back((-symboli) + (-symbolj));
          }
        }
      }
    }
    auto k = _bound++;
    for(auto &base: _bases) {
      if(k != 0) {
        auto attribute = attribute_manager().get_attribute(this->predicate(), base <= hcvc::IntegerLiteral::get(
            std::to_string(-k), base->type(), this->context()));
        _attributes.insert(attribute);
      }
      auto attribute = attribute_manager().get_attribute(this->predicate(), base <=
                                                                            hcvc::IntegerLiteral::get(std::to_string(k),
                                                                                                      base->type(),
                                                                                                      this->context()));
      _attributes.insert(attribute);
    }
  }

  //*-- OctahedronEnumerator
  OctahedronEnumerator::OctahedronEnumerator(const hcvc::Predicate *predicate,
                                             const std::vector<hcvc::Expr> &terms,
                                             unsigned long n,
                                             tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                             hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_started(false),
        _bound(0), _n(n) {}

  OctahedronEnumerator::~OctahedronEnumerator() = default;

  bool OctahedronEnumerator::has_terminated() const {
    return false;
  }

  bool OctahedronEnumerator::is_finite() const {
    return false;
  }

  bool OctahedronEnumerator::is_incremental() const {
    return true;
  }

  void OctahedronEnumerator::enumerate() {
    if(!_has_started) {
      _has_started = true;
      for(unsigned long i = 0, lengthi = this->terms().size() - 2; i < lengthi; i++) {
        auto symboli = this->terms()[i];
        for(unsigned long j = i + 1, lengthj = this->terms().size() - 1; j < lengthj; j++) {
          auto symbolj = this->terms()[j];
          for(unsigned long k = j + 1, lengthk = this->terms().size(); k < lengthk; k++) {
            auto symbolk = this->terms()[k];
            _bases.push_back(symboli + symbolj);
            _bases.push_back(symboli + (-symbolj));
            _bases.push_back((-symboli) + symbolj);
            _bases.push_back((-symboli) + (-symbolj));

            _bases.push_back(symboli + symbolk);
            _bases.push_back(symboli + (-symbolk));
            _bases.push_back((-symboli) + symbolk);
            _bases.push_back((-symboli) + (-symbolk));

            _bases.push_back(symbolj + symbolk);
            _bases.push_back(symbolj + (-symbolk));
            _bases.push_back((-symbolj) + symbolk);
            _bases.push_back((-symbolj) + (-symbolk));

            _bases.push_back(symboli + symbolj + symbolk);
            _bases.push_back(symboli + symbolj + (-symbolk));
            _bases.push_back(symboli + (-symbolj) + symbolk);
            _bases.push_back(symboli + (-symbolj) + (-symbolk));
            _bases.push_back((-symboli) + symbolj + symbolk);
            _bases.push_back((-symboli) + symbolj + (-symbolk));
            _bases.push_back((-symboli) + (-symbolj) + symbolk);
            _bases.push_back((-symboli) + (-symbolj) + (-symbolk));
          }
        }
      }
    }
    auto k = _bound++;
    for(auto &base: _bases) {
      if(k != 0) {
        auto attribute = attribute_manager().get_attribute(this->predicate(), base <= hcvc::IntegerLiteral::get(
            std::to_string(-k), base->type(), this->context()));
        _attributes.insert(attribute);
      }
      auto attribute = attribute_manager().get_attribute(this->predicate(), base <=
                                                                            hcvc::IntegerLiteral::get(std::to_string(k),
                                                                                                      base->type(),
                                                                                                      this->context()));
      _attributes.insert(attribute);
    }
  }

  //*-- PolyhedraEnumerator
  PolyhedraEnumerator::PolyhedraEnumerator(const hcvc::Predicate *predicate,
                                           const std::vector<hcvc::Expr> &terms,
                                           tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                           hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _has_started(false),
        _bound(0) {}

  PolyhedraEnumerator::~PolyhedraEnumerator() = default;

  bool PolyhedraEnumerator::has_terminated() const {
    return false;
  }

  bool PolyhedraEnumerator::is_finite() const {
    return false;
  }

  bool PolyhedraEnumerator::is_incremental() const {
    return false;
  }

  void PolyhedraEnumerator::enumerate() {
    if(!_has_started) {
      _has_started = true;
    }
    auto _k = _bound++;
    _attributes.clear();
    // make all possible combinations
    std::list<std::vector<long>> combinations;
    for(unsigned int i = 0; i <= this->terms().size(); i++) {
      if(i == 0) {
        for(long k = -_k; k <= _k; k++) {
          combinations.emplace_back(std::vector<long>({(long) k}));
          combinations.emplace_back(std::vector<long>({-((long) k)}));
        }
      } else {
        std::list<std::vector<long>> new_combinations;
        for(auto &combination: combinations) {
          for(long k = -_k; k <= _k; k++) {
            auto new_comb1 = combination;
            new_comb1.push_back((long) k);
            auto new_comb2 = combination;
            new_comb2.push_back(-((long) k));
            new_combinations.push_back(new_comb1);
            new_combinations.push_back(new_comb2);
          }
        }
        combinations = new_combinations;
      }
    }

    for(auto &combination: combinations) {
      auto sum = combination[0];
      auto term =
          hcvc::IntegerLiteral::get(std::to_string(combination[0]), this->terms()[0]->type(), this->context()) *
          this->terms()[0];
      for(unsigned long i = 1; i < this->terms().size(); i++) {
        sum += combination[i];
        term = term +
               hcvc::IntegerLiteral::get(std::to_string(combination[i]), this->terms()[i]->type(), this->context()) *
               this->terms()[i];
      }
      if(sum == 0) {
        continue;
      }
      auto attribute = attribute_manager().get_attribute(this->predicate(), term <= hcvc::IntegerLiteral::get(
          std::to_string(combination[combination.size() - 1]), term->type(), this->context()));
      _attributes.insert(attribute);
    }
  }

  //*-- Kmod0Enumerator
  Kmod0Enumerator::Kmod0Enumerator(const hcvc::Predicate *predicate,
                                   const std::vector<hcvc::Expr> &terms,
                                   tapis::HornICE::qdt::AttributeManager &attribute_manager,
                                   hcvc::Context &context)
      : Enumerator(predicate, terms, attribute_manager, context),
        _bound(1) {}

  Kmod0Enumerator::~Kmod0Enumerator() = default;

  bool Kmod0Enumerator::has_terminated() const {
    return false;
  }

  bool Kmod0Enumerator::is_finite() const {
    return false;
  }

  bool Kmod0Enumerator::is_incremental() const {
    return true;
  }

  void Kmod0Enumerator::enumerate() {
    auto k = ++_bound;
    auto zero = hcvc::IntegerLiteral::get("0", context().type_manager().int_type(), this->context());
    for(auto &term: this->terms()) {
      auto kv = hcvc::IntegerLiteral::get(std::to_string(k), term->type(), this->context());
      auto f = context().apply("mod", {term, kv}) == zero;
      auto attribute = attribute_manager().get_attribute(this->predicate(), f);
      _attributes.insert(attribute);
      /*
      for(unsigned long c = 0; c < k; c++) {
        auto cc = hcvc::IntegerLiteral::get(std::to_string(c), context().type_manager().int_type(), this->context());
        auto f = context().apply("mod", {term, kv}) == cc;
        auto attribute = attribute_manager().get_attribute(this->predicate(), f);
        _attributes.insert(attribute);
      }
       */
    }
  }

  //*-- PropertyAccessAnalyzer
  PropertyAccessAnalyzer::PropertyAccessAnalyzer() : _look_accesses(false) {
    _stack.emplace(std::vector<hcvc::Expr>());
  }

  std::vector<std::pair<std::vector<hcvc::Expr>, std::vector<std::pair<hcvc::Expr, hcvc::Expr>>>>
  PropertyAccessAnalyzer::analyze(const hcvc::Expr &f) {
    f->accept(*this);
    return _results;
  }

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::OperatorApplication> term) {
    auto op_name = term->operat0r()->name();
    if(_look_accesses && op_name == "[]" && term->arguments().size() == 2) {
      _accesses.push_back(std::make_pair(term->arguments()[0], term->arguments()[1]));
      return;
    }
    if(_stack.size() > 1) {
      std::vector<std::string> ops = {"<=", "<", ">", ">=", "="};
      _look_accesses = true;
      for(auto &arg: term->arguments()) {
        arg->accept(*this);
      }
      _results.emplace_back(_stack.top(), _accesses);
      _accesses.clear();
      _look_accesses = false;
    }
    for(auto &arg: term->arguments()) {
      arg->accept(*this);
    }
  }

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::BooleanLiteral> term) {}

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::Constant> term) {}

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::ArrayLiteral> term) {}

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::IntegerLiteral> term) {}

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::QuantifiedFormula> term) {
    auto qvars = _stack.top();
    qvars.insert(qvars.end(), term->quantifiers().begin(), term->quantifiers().end());
    _stack.push(qvars);
    term->formula()->accept(*this);
    _stack.pop();
  }

  void PropertyAccessAnalyzer::visit(std::shared_ptr<hcvc::PredicateApplication> term) {}

  //*-- PropertyAttributeAnalyzer
  PropertyAttributeAnalyzer::PropertyAttributeAnalyzer(QuantifierManager &quantifier_manager,
                                                       AttributeManager &attribute_manager)
      : _quantifier_manager(quantifier_manager),
        _attribute_manager(attribute_manager) {}

  bool appears(hcvc::Expr &ex, std::vector<hcvc::Expr> &q) {
    if(ex->kind() != hcvc::TermKind::Constant) {
      return false;
    }
    auto exc = std::dynamic_pointer_cast<hcvc::Constant>(ex);
    for(auto &k: q) {
      auto c = std::dynamic_pointer_cast<hcvc::Constant>(k);
      if(exc->name() == c->name()) {
        return true;
      }
    }
    return false;
  }

  std::vector<const Attribute *>
  PropertyAttributeAnalyzer::analyze(const hcvc::ClauseSet &clauses, const hcvc::Predicate *predicate) {
    std::vector<const Attribute *> attributes;
    for(auto clause: clauses.to_set()) {
      auto results = PropertyAccessAnalyzer().analyze(clause->phi_expr());
      for(auto r: results) {
        auto q = r.first;
        if(!r.second.empty()) {
          auto array1 = std::dynamic_pointer_cast<hcvc::VariableConstant>(r.second[0].first)->variable();
          auto access1 = r.second[0].second;
          if(r.second.size() > 1) {
            auto array2 = std::dynamic_pointer_cast<hcvc::VariableConstant>(r.second[1].first)->variable();
            auto access2 = r.second[1].second;
            if(!appears(access1, q) || !appears(access2, q)) {
              for(auto &qi1: _quantifier_manager.quantifiers(predicate)) {
                if(qi1->array != array1) continue;
                auto k1 = hcvc::VariableConstant::create(qi1->quantifier, 0, _quantifier_manager.context());
                for(auto &qi2: _quantifier_manager.quantifiers(predicate)) {
                  if(qi2->array != array2) continue;
                  auto k2 = hcvc::VariableConstant::create(qi2->quantifier, 0, _quantifier_manager.context());
                  auto qf = _quantifier_manager.context().apply("=", {k1, access1}) &&
                            _quantifier_manager.context().apply("=", {k2, access2});
                  auto qff = hcvc::QuantifiedFormula::create(hcvc::Quantifier::Exists, q, qf,
                                                             _quantifier_manager.context());

                  smtface::push_context();
                  smtface::solvers::Z3Solver solver(smtface::current_context());
                  auto r = solver.qe(hcvc::to_smtface(qff));
                  auto cnstraint = hcvc::from_smtface(r, qf);
                  auto attr = _attribute_manager.get_attribute(predicate, cnstraint);
                  attr->_level = 5;
                  attributes.push_back(attr);

                  smtface::pop_context();
                }
              }
            }
          } else {

          }
        }
      }
    }
    return attributes;
  }

  //*-- PatternExtractor
  std::pair<std::vector<hcvc::Expr>, std::vector<hcvc::Expr>>
  PatternExtractor::extract(const hcvc::ClauseSet &clauses) {
    for(auto &clause: clauses.to_set()) {
      clause->phi_expr()->accept(*this);
    }
    return _results;
  }

  void PatternExtractor::visit(std::shared_ptr<hcvc::OperatorApplication> term) {
    auto op_name = term->operat0r()->name();
    if(op_name == "[]") { // a[i] or a[i] = v
      auto i = term->arguments()[1];
      if(i->kind() != hcvc::TermKind::Constant) {
        _results.first.push_back(i);
      }
      return;
    }
    for(auto &arg: term->arguments()) {
      arg->accept(*this);
    }
  }

  void PatternExtractor::visit(std::shared_ptr<hcvc::BooleanLiteral> term) {}

  void PatternExtractor::visit(std::shared_ptr<hcvc::Constant> term) {}

  void PatternExtractor::visit(std::shared_ptr<hcvc::ArrayLiteral> term) {}

  void PatternExtractor::visit(std::shared_ptr<hcvc::IntegerLiteral> term) {}

  void PatternExtractor::visit(std::shared_ptr<hcvc::QuantifiedFormula> term) {
  }

  void PatternExtractor::visit(std::shared_ptr<hcvc::PredicateApplication> term) {}

  //*-- EnumerationAttributeSynthesizer
  EnumerationAttributeSynthesizer::EnumerationAttributeSynthesizer(QuantifierManager &quantifier_manager)
      : _quantifier_manager(quantifier_manager) {}

  EnumerationAttributeSynthesizer::~EnumerationAttributeSynthesizer() {
  }

  void EnumerationAttributeSynthesizer::set_predicate(const std::set<const hcvc::Predicate *> &predicates) {
    _predicates = predicates;
  }

  Enumerator *create_enumerator(AttributeDomain domain, const hcvc::Predicate *predicate,
                                const std::vector<hcvc::Expr> &terms,
                                AttributeManager &attribute_manager, hcvc::Context &context) {
    if(domain == AttributeDomain::Empty) {
      return new EmptyEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::Equality) {
      return new EqualityEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::UpperBound) {
      return new UpperBoundEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::StrictUpperBound) {
      return new StrictUpperBoundEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::Interval) {
      return new IntervalEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::DifferenceBound) {
      return new DifferenceBoundEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::Octagon) {
      return new OctagonEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::Octahedron) {
      return new OctahedronEnumerator(predicate, terms, 3, attribute_manager, context);
    } else if(domain == AttributeDomain::Polyhedra) {
      return new PolyhedraEnumerator(predicate, terms, attribute_manager, context);
    } else if(domain == AttributeDomain::Kmod0) {
      return new Kmod0Enumerator(predicate, terms, attribute_manager, context);
    }
    return nullptr;
  }

  void EnumerationAttributeSynthesizer::setup() {
    std::map<const hcvc::Predicate *, std::vector<const hcvc::Variable *>> eq_classes_idx_vars;
    if(get_options().ice.qdt.eq_classes_attr_vars) {
      for(auto predicate: _predicates) {
        smtface::push_context();
        smtface::solvers::Z3Solver solver(smtface::current_context());
        std::vector<std::vector<const hcvc::Variable *>> eq_classes;
        for(auto parameter: predicate->parameters()) {
          if(parameter->type()->is_int()) {
            eq_classes_idx_vars[predicate].push_back(parameter);
          }
        }
        auto pref = hcvc::to_smtface(get_outputs().preanalysis_invariants[predicate]);
        for(unsigned long i = 0; i < eq_classes_idx_vars[predicate].size() - 1; i++) {
          auto symboli = hcvc::VariableConstant::create(eq_classes_idx_vars[predicate][i], 0, this->context());
          auto constr = this->context().get_true();
          bool eq = false;
          for(unsigned long j = i + 1; j < eq_classes_idx_vars[predicate].size(); j++) {
            auto symbolj = hcvc::VariableConstant::create(eq_classes_idx_vars[predicate][j], 0, this->context());
            auto f = smtface::Not(smtface::Implies(pref, hcvc::to_smtface(symbolj == symboli)));
            if(!solver.is_sat(smtface::utils::array_to_epr(f))) {
              constr = constr && (symboli == symbolj);
              eq = true;
              //get_outputs().preanalysis_invariants[predicate] =get_outputs().preanalysis_invariants[predicate] && (symbolj == symboli);
              eq_classes_idx_vars[predicate].erase(eq_classes_idx_vars[predicate].begin() + j);
              j--;
            }
          }
          if(eq) {
            auto attribute = attribute_manager().get_attribute(predicate, constr);
            _init_idx_attributes.insert(attribute);
          }
        }
        smtface::pop_context();
      }
    }

    for(auto predicate: _predicates) {
      if(get_options().ice.learner.attr_from_spec) {
        auto attrs = PropertyAttributeAnalyzer(_quantifier_manager, attribute_manager()).analyze(get_outputs().clauses,
                                                                                                 predicate);
        for(auto attr: attrs) {
          _init_idx_attributes.insert(attr);
        }
      }

      std::vector<hcvc::Expr> booleans;
      std::vector<hcvc::Expr> datas;
      std::vector<hcvc::Expr> indexes;
      if(get_options().ice.qdt.eq_classes_attr_vars) {
        //indexes = eq_classes_idx_vars[predicate];
      }

      /*PatternExtractor pe;
      auto r = pe.extract(get_outputs().clauses);
      indexes.insert(indexes.end(), r.first.begin(), r.first.end());
      indexes.insert(datas.end(), r.second.begin(), r.second.end());*/

      auto &variables = predicate->parameters();
      for(auto variable: variables) {
        if(variable->type()->is_bool()) {
          auto term = hcvc::VariableConstant::create(variable, 0, this->context());
          booleans.push_back(term);
        } else if(variable->type()->is_int()) {
          if(variable->is_data()) {
            auto term = hcvc::VariableConstant::create(variable, 0, this->context());
            datas.push_back(term);
          } else {
            if(!get_options().ice.qdt.eq_classes_attr_vars) {
              auto term = hcvc::VariableConstant::create(variable, 0, this->context());
              indexes.push_back(term);
            }
          }
        }
      }
      for(auto qi: _quantifier_manager.quantifiers(predicate)) {
        indexes.push_back(hcvc::VariableConstant::create(qi->quantifier, 0, this->context()));
        if(qi->accessor->type()->is_bool()) {
          booleans.push_back(hcvc::VariableConstant::create(qi->accessor, 0, this->context()));
        } else {
          datas.push_back(hcvc::VariableConstant::create(qi->accessor, 0, this->context()));
        }
      }
      if(get_options().ice.learner.mix_data_indexes) {
        indexes.insert(indexes.end(), datas.begin(), datas.end());
        datas.clear();
      }
      _data_enumerators[predicate].push_back(
          new BooleanEnumerator(predicate, booleans, attribute_manager(), context()));
      for(auto domain: get_options().ice.learner.index_domains) {
        _index_enumerators[predicate].push_back(
            create_enumerator(domain, predicate, indexes, attribute_manager(), context()));
      }
      for(auto domain: get_options().ice.learner.data_domains) {
        _data_enumerators[predicate].push_back(
            create_enumerator(domain, predicate, datas, attribute_manager(), context()));
      }
    }
    generate_attributes(nullptr);
  }

  bool EnumerationAttributeSynthesizer::generate_attributes(DiagramPartialReachabilityGraph *sample) {
    for(auto predicate: _predicates) {
      for(auto enumerator: rope::add(_index_enumerators[predicate], _data_enumerators[predicate])) {
        if(!enumerator->has_terminated()) {
          enumerator->enumerate();
        }
      }
    }
    return true;
  }

  std::pair<std::set<const Attribute *>, std::set<const Attribute *>>
  EnumerationAttributeSynthesizer::attributes(const hcvc::Predicate *predicate) const {
    std::pair<std::set<const Attribute *>, std::set<const Attribute *>> res;
    res.first.insert(_init_idx_attributes.begin(), _init_idx_attributes.end());
    for(auto enumerator: _index_enumerators.at(predicate)) {
      res.first.insert(enumerator->attributes().begin(), enumerator->attributes().end());
    }
    for(auto enumerator: _data_enumerators.at(predicate)) {
      res.second.insert(enumerator->attributes().begin(), enumerator->attributes().end());
    }
    return res;
  }

}
