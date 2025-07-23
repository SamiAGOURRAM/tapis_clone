//
// Copyright (c) 2025 Wael-Amine Boutglay
//

#include <utility>

#include "tapis/engines/attributes/new_attr_synthesizer.hh"

#include "rope.hh"
#include "tapis/engines/bounds.hh"
#include "tapis/engines/outputs.hh"

namespace tapis::HornICE::qdt {

  unsigned long counterforpattern = 0;

  //*-- TermPattern
  class TermPattern {
  public:
    inline TermPattern(std::vector<hcvc::Expr> array_parameters,
      std::vector<hcvc::Expr> index_parameters,
      std::vector<hcvc::Expr> data_parameters,
      std::vector<hcvc::Expr> integer_parameters, 
      hcvc::Expr formula)

        : _array_parameters(std::move(array_parameters)),
        _index_parameters(std::move(index_parameters)),
          _data_parameters(std::move(data_parameters)),
          _integer_parameters(std::move(integer_parameters)),
          _formula(std::move(formula)) {}


    std::vector<hcvc::Expr> _array_parameters;
    std::vector<hcvc::Expr> _index_parameters;
    std::vector<hcvc::Expr> _data_parameters;
    std::vector<hcvc::Expr> _integer_parameters;
    hcvc::Expr _formula;
  };

  bool is_var_cnst(const hcvc::Expr &term) {
    return term->kind() == hcvc::TermKind::Constant &&
           std::dynamic_pointer_cast<hcvc::Constant>(term)->is_variable_constant();
  }

  bool is_integer_literal(const hcvc::Expr &term) {
    return term->kind() == hcvc::TermKind::IntegerLiteral;
  }

  bool is_var_plus_cnst(const hcvc::Expr &term) {
    if(term->kind() != hcvc::TermKind::OpApp) {
      return false;
    }
    auto op_app_term = std::dynamic_pointer_cast<hcvc::OperatorApplication>(term);
    if(op_app_term->arguments().size() != 2) {
      return false;
    }
    auto arg0 = op_app_term->arguments().at(0);
    auto arg1 = op_app_term->arguments().at(1);
    if(op_app_term->operat0r()->name() != "+") {
      return false;
    }
    if((is_integer_literal(arg0) && is_var_cnst(arg1)) || (is_integer_literal(arg1) && is_var_cnst(arg0))) {
      return true;
    }
    return false;
  }

  bool is_var_incrementation(const hcvc::Expr &term) {
    if(term->kind() != hcvc::TermKind::OpApp) {
      return false;
    }
    auto op_app_term = std::dynamic_pointer_cast<hcvc::OperatorApplication>(term);
    if(op_app_term->operat0r()->name() != "=") {
      return false;
    }
    if(op_app_term->arguments().size() != 2) {
      return false;
    }
    auto arg0 = op_app_term->arguments().at(0);
    auto arg1 = op_app_term->arguments().at(1);
    if((is_var_plus_cnst(arg0) && is_var_cnst(arg1)) || (is_var_plus_cnst(arg1) && is_var_cnst(arg0))) {
      auto arg0_vars = hcvc::get_variables(arg0);
      auto arg1_vars = hcvc::get_variables(arg1);
      if(arg0_vars.size() == arg1_vars.size() && arg0_vars.size() == 1) {
        if(*arg0_vars.begin() == *arg1_vars.begin()) {
          return true;
        }
      }
    }
    return false;
  }

  //*-- Term2Pattern
  class Term2Pattern: public hcvc::Visitor {
  public:
    inline explicit Term2Pattern(hcvc::Context &context)
        : _context(context) {}

    TermPattern analyze(const hcvc::Expr &term) {
      term->accept(*this);
      auto r = result();
#ifndef NDEBUG
      std::cout << "Extracted pattern: " << r.second << "\n";
#endif
      return {_array_parameters, _index_parameters, _data_parameters, _integer_parameters, r.second};
    }

    void visit(std::shared_ptr<hcvc::OperatorApplication> term) override {
      auto op_name = term->operat0r()->name();
      if(op_name == "[]" && term->arguments().size() == 3) { // a[i] = v
        auto new_ai = _new_data_parameter(((const hcvc::ArrayType *) term->type())->element_type());
        term->arguments()[2]->accept(*this);
        auto new_v_result = result();
        _return(true, new_ai == new_v_result.second);
      } else if(op_name == "[]" && term->arguments().size() == 2) { // a[i]
        auto new_ai = _new_data_parameter(term->type());
        _return(true, new_ai);
      } else {
        bool changed = false;
        std::vector<hcvc::Expr> args;
        const hcvc::Operator *func = term->operat0r();
        for(const auto &arg: term->arguments()) {
          arg->accept(*this);
          auto r = result();
          args.push_back(std::get<1>(r));
          if(std::get<0>(r)) {
            changed = true;
          }
        }
        if(changed) {
          return _return(true, term->context().apply(func->name(), args));
        } else {
          return _return(false, term);
        }
      }
    }

    void visit(std::shared_ptr<hcvc::Constant> term) override {
      if(term->is_variable_constant()) {
        auto variable = std::dynamic_pointer_cast<hcvc::VariableConstant>(term)->variable();
        if (variable->type()->is_array()) {
        return _return(true, _new_array_parameter(term->type()));
    } 
        if(variable->is_data()) {
          return _return(true, _new_data_parameter(term->type()));
        } else {
          return _return(true, _new_index_parameter());
        }
      }
      return _return(true, hcvc::IntegerLiteral::get("0", term->type(), term->context()));
    }

    void visit(std::shared_ptr<hcvc::BooleanLiteral> term) override {
      return _return(false, term);
    }

    void visit(std::shared_ptr<hcvc::IntegerLiteral> term) override {
      return _return(false, term);
    }

    void visit(std::shared_ptr<hcvc::ArrayLiteral> term) override {
      return _return(false, term);
    }

    void visit(std::shared_ptr<hcvc::QuantifiedFormula> term) override {}

    void visit(std::shared_ptr<hcvc::PredicateApplication> term) override {}

  private:
    std::vector<hcvc::Expr> _array_parameters; 

      hcvc::Expr _new_array_parameter(const hcvc::Type* type) {
      // a distinct prefix "!pa!" for "pattern array"
      auto c = hcvc::Constant::create("!pa!" + std::to_string(counterforpattern++), type, _context);
      _array_parameters.push_back(c);
      return c;
    }

    hcvc::Expr _new_data_parameter(const hcvc::Type *type) {
      auto c = hcvc::Constant::create("!pd!" + std::to_string(counterforpattern++), type, _context);
      _data_parameters.push_back(c);
      return c;
    }

    hcvc::Expr _new_index_parameter() {
      auto c = hcvc::Constant::create("!pi!" + std::to_string(counterforpattern++), _context.type_manager().int_type(),
                                      _context);
      _index_parameters.push_back(c);
      return c;
    }

    inline std::pair<bool, hcvc::Expr> result() {
      auto r = _stack.top();
      _stack.pop();
      return r;
    }

    inline void _return(bool modified, const hcvc::Expr &term) {
      _stack.emplace(modified, term);
    }

    std::stack<std::pair<bool, hcvc::Expr>> _stack;

    std::vector<hcvc::Expr> _index_parameters;
    std::vector<hcvc::Expr> _data_parameters;
    std::vector<hcvc::Expr> _integer_parameters;
    hcvc::Context &_context;
  };

  //*-- ProgramTermAnalyzer
  class ProgramTermAnalyzer: public hcvc::Visitor {
  public:
    void analyze(const hcvc::ClauseSet &clauses) {
      for(auto &clause: clauses.to_set()) {
        clause->phi_expr()->accept(*this);
      }
    }

void visit(std::shared_ptr<hcvc::OperatorApplication> term) override {
    // ignore any term coming from "i = i + c" where c is a literal integer
    if(is_var_incrementation(term)) {
      return;
    }
    
    // Check if this term contains sum operations - if so, skip it
    auto ops = hcvc::get_operations(term);
    bool has_sum = false;
    for(auto op : ops) {
      if(op->name() == "sum" || op->name() == "sum_range") {
        has_sum = true;
        break;
      }
    }
    
    if(has_sum) {
      // Skip this term entirely - don't extract patterns from sum expressions
      // The sum variables will be handled by the AggregationManager
      return;
    }
    
    for(auto &argument: term->arguments()) {
      argument->accept(*this);
    }
    
    auto op_name = term->operat0r()->name();
    if(op_name == "[]") { // a[i] or a[i] = v
      auto i = term->arguments()[1];
      if(i->kind() != hcvc::TermKind::Constant) {
        _potential_index_terms.push_back(i);
      }
    }
    if(op_name == "[]" && term->arguments().size() == 3) { // a[i] = v
      if(!term->arguments()[2]->type()->is_bool()) {
        _attribute_pattern.push_back(Term2Pattern(term->context()).analyze(term));
      }
    }
    if(op_name == "<=" || op_name == "<" || op_name == ">" || op_name == ">=" || op_name == "=") {
      auto left_ops = hcvc::get_operations(term->arguments()[0]);
      auto right_ops = hcvc::get_operations(term->arguments()[1]);
      
      // Check if either argument contains sum operations
      bool left_has_sum = false;
      bool right_has_sum = false;
      
      for(auto op : left_ops) {
        if(op->name() == "sum" || op->name() == "sum_range") {
          left_has_sum = true;
          break;
        }
      }
      
      for(auto op : right_ops) {
        if(op->name() == "sum" || op->name() == "sum_range") {
          right_has_sum = true;
          break;
        }
      }
      
      // Skip patterns containing sum operations
      if(left_has_sum || right_has_sum) {
        return;
      }
      
      auto left_contains_const = std::count_if(left_ops.begin(), left_ops.end(), [](const hcvc::Operator *op) {
        return op->name() == "<=" || op->name() == "<" || op->name() == ">" || op->name() == ">=" ||
               op->name() == "=";
      });
      auto right_contains_const = std::count_if(right_ops.begin(), right_ops.end(), [](const hcvc::Operator *op) {
        return op->name() == "<=" || op->name() == "<" || op->name() == ">" || op->name() == ">=" ||
               op->name() == "=";
      });
      auto args_are_bool_or_array = std::all_of(term->arguments().begin(), term->arguments().end(),
                                                [](const hcvc::Expr &t) {
                                                  return !t->type()->is_bool() && !t->type()->is_array();
                                                });
      if(!left_contains_const && !right_contains_const && args_are_bool_or_array) {
        _attribute_pattern.push_back(Term2Pattern(term->context()).analyze(term));
      }
    }
}

    void visit(std::shared_ptr<hcvc::Constant> term) override {}

    void visit(std::shared_ptr<hcvc::BooleanLiteral> term) override {}

    void visit(std::shared_ptr<hcvc::IntegerLiteral> term) override {
      _integer_values.insert(std::stol(term->value()));
    }

    void visit(std::shared_ptr<hcvc::ArrayLiteral> term) override {}

    void visit(std::shared_ptr<hcvc::QuantifiedFormula> term) override {
      term->formula()->accept(*this);
    }

    void visit(std::shared_ptr<hcvc::PredicateApplication> term) override {}

    std::vector<TermPattern> _attribute_pattern;
    std::set<long> _integer_values;
    std::vector<hcvc::Expr> _potential_index_terms;
    std::vector<hcvc::Expr> _potential_data_terms;
  private:
  };

  //*-- PatternEnumerator
  class PatternEnumerator: public Enumerator {
  public:
    PatternEnumerator(TermPattern pattern, const hcvc::Predicate *predicate,std::vector<hcvc::Expr> array_terms,
 std::vector<hcvc::Expr> index_terms,
                      std::vector<hcvc::Expr> data_terms,
                      std::set<long> values, AttributeManager &attribute_manager, hcvc::Context &context)
        : Enumerator(predicate, {}, attribute_manager, context),
          _pattern(std::move(pattern)),
          _array_terms(std::move(array_terms)),
          _index_terms(std::move(index_terms)),
          _data_terms(std::move(data_terms)),
          _values(std::move(values)),
          _bound(0),
          _has_started(true) {}

    ~PatternEnumerator() override = default;

    bool has_terminated() const override {
      return false;
    }

    bool is_finite() const override {
      return _pattern._integer_parameters.empty();
    }

    bool is_incremental() const override {
      return this->is_finite();
    }

void enumerate() override {
  using AssignmentTuple = std::tuple<
      std::vector<hcvc::Expr>, // 0: Array assignments
      std::vector<hcvc::Expr>, // 1: Index assignments
      std::vector<hcvc::Expr>, // 2: Data assignments
      std::vector<hcvc::Expr>  // 3: Integer assignments
  >;

  std::list<AssignmentTuple> assignments = {{}};

  // Calculate the total number of parameters to assign.
  unsigned long array_param_count = _pattern._array_parameters.size();
  unsigned long index_param_count = _pattern._index_parameters.size();
  unsigned long data_param_count = _pattern._data_parameters.size();
  unsigned long int_param_count = _pattern._integer_parameters.size();

  unsigned long total_params = array_param_count + index_param_count + data_param_count + int_param_count;

  // This loop iterates through each placeholder (`!pa!`, `!pi!`, etc.) one by one
  // and expands the list of assignments for it.
  for (unsigned long i = 0; i < total_params; i++) {
    std::list<AssignmentTuple> new_assignments;

    // Case 1: Assigning an Array Parameter (`!pa!`)
    if (i < array_param_count) {
      for (auto &term : _array_terms) {
        for (const auto& assignment : assignments) {
          auto new_assignment = assignment; // Make a copy
          std::get<0>(new_assignment).push_back(term);
          new_assignments.push_back(new_assignment);
        }
      }
    }
    // Case 2: Assigning an Index Parameter (`!pi!`)
    else if (i < array_param_count + index_param_count) {
      for (auto &term : _index_terms) {
        for (const auto& assignment : assignments) {
          auto new_assignment = assignment; // Make a copy
          std::get<1>(new_assignment).push_back(term);
          new_assignments.push_back(new_assignment);
        }
      }
    }
    // Case 3: Assigning a Data Parameter (`!pd!`)
    else if (i < array_param_count + index_param_count + data_param_count) {
      for (auto &term : _data_terms) {
        for (const auto& assignment : assignments) {
          auto new_assignment = assignment; // Make a copy
          std::get<2>(new_assignment).push_back(term);
          new_assignments.push_back(new_assignment);
        }
      }
    }
    // Case 4: Assigning an Integer Literal Parameter
    else {
      // Add integer constants found in the program
      for (auto value : _values) {
        auto term = hcvc::IntegerLiteral::get(std::to_string(value), context().type_manager().int_type(), context());
        for (const auto& assignment : assignments) {
          auto new_assignment = assignment; // Make a copy
          std::get<3>(new_assignment).push_back(term);
          new_assignments.push_back(new_assignment);
        }
      }
      // Add small integer constants (0, +/-1, +/-2, ...) up to the current bound
      for (unsigned long j = 0; j < _bound; j++) {
        // Positive value
        auto term_pos = hcvc::IntegerLiteral::get(std::to_string((long)j), context().type_manager().int_type(), context());
        for (const auto& assignment : assignments) {
          auto new_assignment = assignment; // Make a copy
          std::get<3>(new_assignment).push_back(term_pos);
          new_assignments.push_back(new_assignment);
        }
        // Negative value (if not zero)
        if (j > 0) {
            auto term_neg = hcvc::IntegerLiteral::get(std::to_string(-((long)j)), context().type_manager().int_type(), context());
            for (const auto& assignment : assignments) {
              auto new_assignment = assignment; // Make a copy
              std::get<3>(new_assignment).push_back(term_neg);
              new_assignments.push_back(new_assignment);
            }
        }
      }
    }
    // Replace the old list of assignments with the newly expanded one.
    assignments = new_assignments;
  }

  // Now that all combinations have been generated, create the attributes.
  for (const auto &assignment : assignments) {
    std::map<hcvc::Expr, hcvc::Expr> substitute_map;

    // Substitute array parameters
    for (unsigned long i = 0; i < array_param_count; i++) {
      substitute_map[_pattern._array_parameters[i]] = std::get<0>(assignment)[i];
    }
    // Substitute index parameters
    for (unsigned long i = 0; i < index_param_count; i++) {
      substitute_map[_pattern._index_parameters[i]] = std::get<1>(assignment)[i];
    }
    // Substitute data parameters
    for (unsigned long i = 0; i < data_param_count; i++) {
      substitute_map[_pattern._data_parameters[i]] = std::get<2>(assignment)[i];
    }
    // Substitute integer parameters
    for (unsigned long i = 0; i < int_param_count; i++) {
      substitute_map[_pattern._integer_parameters[i]] = std::get<3>(assignment)[i];
    }

    // Perform the substitution on the formula template
    auto f = hcvc::substitute(_pattern._formula, substitute_map);
    // Get or create the attribute and add it to the set of generated attributes
    auto attribute = attribute_manager().get_attribute(predicate(), f);
    _attributes.insert(attribute);
  }

  // Increment the bound for the next enumeration round (for integer constants).
  _bound++;
}

  private:
    TermPattern _pattern;
    std::vector<hcvc::Expr> _array_terms;
    std::vector<hcvc::Expr> _index_terms;
    std::vector<hcvc::Expr> _data_terms;
    std::set<long> _values;

    long _bound;
    bool _has_started;
  };

  //*-- NewAttributeSynthesizer
  NewAttributeSynthesizer::~NewAttributeSynthesizer() = default;

  void NewAttributeSynthesizer::set_predicate(const std::set<const hcvc::Predicate *> &predicates) {
    _predicates = predicates;
  }


void NewAttributeSynthesizer::setup() {
    ProgramTermAnalyzer pta;
    // This has to be performed anyway to obtain constants in the program
    pta.analyze(get_outputs().clauses);

    // set the array size bound to the max integer constant in the program + 1
    if(!pta._integer_values.empty()) {
      auto max = *pta._integer_values.rbegin();
      if(max > get_bounds()._max_array_value) {
        get_bounds()._max_array_value = max + 1;
      }
    }

    for(auto predicate: _predicates) {
      if(get_options().ice.learner.attr_from_spec) {
        auto attrs = PropertyAttributeAnalyzer(_quantifier_manager, attribute_manager()).analyze(get_outputs().clauses,
                                                                                                 predicate);
        for(auto attr: attrs) {
          // Skip attributes that contain sum operations over arrays
          // These cannot be evaluated on diagrams and should use synthetic sum variables instead
          auto ops = hcvc::get_operations(attr->constraint());
          bool has_sum = false;
          for(auto op : ops) {
            if(op->name() == "sum" || op->name() == "sum_range") {
              has_sum = true;
              break;
            }
          }
          
          // Also check if the attribute references array variables
          auto constants = hcvc::get_constants(attr->constraint());
          bool has_array = false;
          for(const auto& c : constants) {
            if(c->type()->is_array()) {
              has_array = true;
              break;
            }
          }
          
          // Skip attributes with sum operations or array references
          if(has_sum || has_array) {
            std::cerr << "Skipping PropertyAttributeAnalyzer attribute that cannot be evaluated on diagrams: " 
                      << attr->constraint() << std::endl;
            continue;
          }
          
          _init_index_attributes[predicate].insert(attr);
        }
      }

      // Each vector now holds terms of a specific, distinct type.
      std::vector<hcvc::Expr> arrays;   // For Array-typed variables
      std::vector<hcvc::Expr> booleans; // For Boolean-typed variables
      std::vector<hcvc::Expr> datas;    // For non-array, non-bool data variables (e.g., int data)
      std::vector<hcvc::Expr> indexes;  // For index-like integer variables
      std::vector<hcvc::Expr> sums;     // For synthetic sum variables
      std::vector<hcvc::Expr> int_quantifier_variables; // For quantifier variables like !k0

      // Process potential index terms from program analysis (e.g., i+1)
      for(auto &term: pta._potential_index_terms) {
        auto cnsts = hcvc::get_constants(term);
        bool can = true;
        for(auto &cnst: cnsts) {
          auto constant = std::dynamic_pointer_cast<hcvc::Constant>(cnst);
          if(constant->is_variable_constant()) {
            auto variable = std::dynamic_pointer_cast<hcvc::VariableConstant>(cnst)->variable();
            if(std::count(predicate->parameters().begin(), predicate->parameters().end(), variable) == 0) {
              can = false;
              break;
            }
          } else {
            can = false;
            break;
          }
        }
        if(can) {
          indexes.push_back(term);
        }
      }

      // Process predicate parameters, sorting them by type
      auto &variables = predicate->parameters();
      for(auto variable: variables) {
        if (variable->type()->is_array()) {
          auto term = hcvc::VariableConstant::create(variable, 0, this->context());
          arrays.push_back(term);
        } else if(variable->type()->is_bool()) {
          auto term = hcvc::VariableConstant::create(variable, 0, this->context());
          booleans.push_back(term);
        } else if(variable->type()->is_int()) {
          if(variable->is_data()) {
            auto term = hcvc::VariableConstant::create(variable, 0, this->context());
            datas.push_back(term);
          } else {
            auto term = hcvc::VariableConstant::create(variable, 0, this->context());
            indexes.push_back(term);
          }
        }
      }
      
      // Process quantifier variables
      for(auto qi: _quantifier_manager.quantifiers(predicate)) {
        auto qac = hcvc::VariableConstant::create(qi->quantifier, 0, this->context());
        indexes.push_back(qac);
        int_quantifier_variables.push_back(qac);
        // The accessor (!array!k0) can be bool or data
        if(qi->accessor->type()->is_bool()) {
          booleans.push_back(hcvc::VariableConstant::create(qi->accessor, 0, this->context()));
        } else {
          datas.push_back(hcvc::VariableConstant::create(qi->accessor, 0, this->context()));
        }
      }
      
      // Process aggregation variables
      for(auto ai: _aggregation_manager.get_aggregations(predicate)) {
        auto sum_var = hcvc::VariableConstant::create(ai->variable, 0, this->context());
        sums.push_back(sum_var);
      }
      
      // Handle mix_data_indexes option
      if(get_options().ice.learner.mix_data_indexes) {
        indexes.insert(indexes.end(), datas.begin(), datas.end());
        indexes.insert(indexes.end(), sums.begin(), sums.end());
        datas.clear();
        sums.clear();
      }

      // Create enumerators for booleans
      _data_enumerators[predicate].push_back(
          new BooleanEnumerator(predicate, booleans, attribute_manager(), context()));
      
      // Create enumerators for index domains
      for(auto domain: get_options().ice.learner.index_domains) {
        if(domain != AttributeDomain::Kmod0) {
          _index_enumerators[predicate].push_back(
              create_enumerator(domain, predicate, indexes, attribute_manager(), context()));
        }
      }
      
      // Create enumerators for sum variables (if not mixed with indexes)
      // These discover relationships like `s == !s_array_0_i`
      if(!get_options().ice.learner.mix_data_indexes && !sums.empty()) {
        for(auto domain: get_options().ice.learner.index_domains) {
          if(domain == AttributeDomain::Interval || 
             domain == AttributeDomain::DifferenceBound ||
             domain == AttributeDomain::Octagon ||
             domain == AttributeDomain::Polyhedra) {
            _index_enumerators[predicate].push_back(
                create_enumerator(domain, predicate, sums, attribute_manager(), context()));
          }
        }
      }
      
      // Handle Kmod0 specially (only for primitive quantifier variables)
      if(get_options().ice.learner.index_domains.count(AttributeDomain::Kmod0)) {
        _index_enumerators[predicate].push_back(
            create_enumerator(AttributeDomain::Kmod0, predicate, int_quantifier_variables, attribute_manager(),
                              context()));
      }
      
      // Create enumerators for data domains
      for(auto domain: get_options().ice.learner.data_domains) {
        _data_enumerators[predicate].push_back(
            create_enumerator(domain, predicate, datas, attribute_manager(), context()));
      }
      
      // Handle pattern-based attributes using the new type-aware enumerator
      if(get_options().ice.learner.attr_from_program) {
        // Debug: Print extracted patterns
        std::cerr << "Number of attribute patterns extracted: " << pta._attribute_pattern.size() << std::endl;
        
        for(auto &pattern: pta._attribute_pattern) {
          _index_enumerators[predicate].push_back(
              new PatternEnumerator(pattern, 
                                    predicate, 
                                    arrays,  // Pass the dedicated list of array variables
                                    indexes, // Pass index-like variables
                                    datas,   // Pass data-like variables
                                    pta._integer_values, 
                                    attribute_manager(),
                                    context()));
        }
      }
    }
    generate_attributes(nullptr);
  }
  std::pair<std::set<const Attribute *>, std::set<const Attribute *>>
  NewAttributeSynthesizer::attributes(const hcvc::Predicate *predicate) const {
    std::pair<std::set<const Attribute *>, std::set<const Attribute *>> res;
    if(_init_index_attributes.count(predicate) > 0) {
      res.first.insert(_init_index_attributes.at(predicate).begin(), _init_index_attributes.at(predicate).end());
    }
    if(_init_data_attributes.count(predicate) > 0) {
      res.second.insert(_init_data_attributes.at(predicate).begin(), _init_data_attributes.at(predicate).end());
    }
    for(auto enumerator: _index_enumerators.at(predicate)) {
      res.first.insert(enumerator->attributes().begin(), enumerator->attributes().end());
    }
    for(auto enumerator: _data_enumerators.at(predicate)) {
      res.second.insert(enumerator->attributes().begin(), enumerator->attributes().end());
    }
    return res;
  }

  bool NewAttributeSynthesizer::generate_attributes(tapis::HornICE::qdt::DiagramPartialReachabilityGraph *sample) {
    for(auto predicate: _predicates) {
      for(auto enumerator: rope::add(_index_enumerators[predicate], _data_enumerators[predicate])) {
        if(!enumerator->has_terminated()) {
          enumerator->enumerate();
        }
      }
    }
    return true;
  }

}
