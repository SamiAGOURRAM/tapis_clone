//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include "hcvc/context.hh"
#include "hcvc/logic/term.hh"
#include "hcvc/program/state.hh"
#include "tapis/engines/hornice/qdt/diagram.hh"

namespace tapis::HornICE::qdt {

  class Attribute {
  public:
    Attribute(const hcvc::Predicate *predicate, hcvc::Expr constraint);

    //*- properties

    inline hcvc::Expr constraint() const {
      return _constraint;
    }

    inline const hcvc::Predicate *predicate() const {
      return _predicate;
    }

    //*- methods

    bool satisfied_by(const Diagram *diagram) const;

    mutable unsigned long _level = 0;
  private:
    const hcvc::Predicate *_predicate;
    hcvc::Expr _constraint;

    mutable std::unordered_map<const Diagram *, bool> _sat_cache;
  };

  //*-- AttributeManager
  class AttributeManager {
  public:
    //*- methods

    const Attribute *get_attribute(const hcvc::Predicate *predicate, const hcvc::Expr &constraint);

  private:
    std::map<const hcvc::Predicate *, std::map<std::string, Attribute *>> _cache;
  };

  //*-- AttributeSynthesizer
  class AttributeSynthesizer {
  public:
    inline AttributeSynthesizer()
        : _attr_manager(nullptr), _context(nullptr) {}

    virtual ~AttributeSynthesizer();

    //*- properties

    inline AttributeManager &attribute_manager() const {
      return *_attr_manager;
    }

    inline hcvc::Context &context() const {
      return *_context;
    }

    //*- methods

    inline void set_manager(AttributeManager *attr_manager) {
      _attr_manager = attr_manager;
    }

    inline void set_context(hcvc::Context *context) {
      _context = context;
    }

    virtual void set_predicate(const std::set<const hcvc::Predicate *> &predicates) = 0;

    virtual void setup() = 0;

    virtual std::pair<std::set<const Attribute *>, std::set<const Attribute *>>
    attributes(const hcvc::Predicate *predicate) const = 0;

    virtual bool generate_attributes(DiagramPartialReachabilityGraph *sample) = 0;

  private:
    AttributeManager *_attr_manager;
    hcvc::Context *_context;
  };

}
