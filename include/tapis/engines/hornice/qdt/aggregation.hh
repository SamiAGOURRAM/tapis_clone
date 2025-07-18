#pragma once

#include <vector>
#include <map>
#include <set>
#include "hcvc/clause/predicate.hh"
#include "hcvc/context.hh"
#include "hcvc/logic/term.hh" // <-- Keep this for hcvc::Expr
#include "tapis/engines/hornice/qdt/quantifier.hh"

namespace tapis::HornICE::qdt {

  // Enum for the type of aggregation. Allows for future extension.
  enum class AggregationType {
    SUM
    // Potentially add AVG, MIN, MAX, etc. later
  };

  /**
   * @class AggregationInfo
   * @brief Holds all metadata for a single synthetic aggregation variable.
   *
   * This class describes the semantic meaning of a variable like '!s_array_i_N',
   * linking it to the aggregation type (SUM), the array it operates on,
   * and the variables that define its bounds.
   */
  class AggregationInfo {
  public:
    AggregationType type;          // The type of aggregation (e.g., SUM).
    const hcvc::Variable* variable; // The synthetic variable itself (e.g., s_a_i_j).
    const hcvc::Predicate* predicate;  // The predicate this variable belongs to.
    
    // The semantic meaning of the variable:
    const hcvc::Variable* array;       // The array being aggregated.
    const hcvc::Variable* lower_bound; // The variable for the lower bound. Can be nullptr for constant 0.
    const hcvc::Variable* upper_bound; // The variable for the upper bound.
  };

  /**
   * @class AggregationManager
   * @brief Manages the creation and lifecycle of synthetic aggregation variables.
   *
   * This class parallels the QuantifierManager. It inspects predicates,
   * identifies opportunities for aggregation (like sum), and synthesizes new
   * variables (e.g., s_a_i_v) that the Learner can use to discover invariants.
   */
  class AggregationManager {
  public:
    AggregationManager(QuantifierManager& quantifier_manager);
    ~AggregationManager();

    // Prevent copying
    AggregationManager(const AggregationManager&) = delete;
    AggregationManager& operator=(const AggregationManager&) = delete;

    // Configuration methods
    void set_context(hcvc::Context& context) { _context = &context; }
    hcvc::Context& context() const { return *_context; }
    void set_predicates(const std::set<const hcvc::Predicate*>& predicates);

    void setup();
    void resetup();

    // Accessor methods
    const std::vector<AggregationInfo*>& get_aggregations(const hcvc::Predicate* p) const;
    
    // Lifting method
    hcvc::Expr substitute(const hcvc::Predicate* predicate, hcvc::Expr body);

  private:
    void clear();

    hcvc::Context* _context;
    std::set<const hcvc::Predicate*> _predicates;
    QuantifierManager& _quantifier_manager;

    std::map<const hcvc::Predicate*, std::vector<AggregationInfo*>> _aggregations;
    
    // **THE FIX**: Use the full, correct type for the substitution map.
    std::map<const hcvc::Predicate*, std::map<hcvc::Expr, hcvc::Expr>> _sub_maps;

    static const std::vector<AggregationInfo*> s_empty_vector;
  };


}
