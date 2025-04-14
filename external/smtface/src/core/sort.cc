//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "smtface/core/sort.hh"

#include <utility>

namespace smtface::core {

  //*-- Sort
  Sort::Sort(SortKind kind)
      : _kind(kind) {}

  Sort::~Sort() = default;

  SortKind Sort::kind() const {
    return _kind;
  }

  bool Sort::is_array() const {
    return false;
  }

  //*-- NativeSort
  NativeSort::NativeSort(std::string name)
      : Sort(SortKind::native), _name(std::move(name)) {}

  NativeSort::~NativeSort() = default;

  const std::string &NativeSort::name() const {
    return _name;
  }

  bool NativeSort::operator==(const Sort &other) const {
    return this == &other;
  }

  //*-- ArraySort
  ArraySort::ArraySort(const Sort *index_sort, const Sort *element_sort)
      : Sort(SortKind::array), _index_sort(index_sort), _element_sort(element_sort) {}

  ArraySort::~ArraySort() = default;

  const Sort *ArraySort::index_sort() const {
    return _index_sort;
  }

  const Sort *ArraySort::element_sort() const {
    return _element_sort;
  }

  bool ArraySort::is_array() const {
    return true;
  }

  bool ArraySort::operator==(const Sort &other) const {
    if(this == &other) {
      return true;
    }
    if(this->kind() != other.kind()) {
      return false;
    }
    const auto &casted = (const ArraySort &) other;
    if(!(*_index_sort == *casted.index_sort())) {
      return false;
    }
    if(!(*_element_sort == *casted.element_sort())) {
      return false;
    }
    return true;
  }

  //*-- FunctionSort
  FunctionSort::FunctionSort(std::vector<const Sort *> domain, const Sort *range)
      : Sort(SortKind::function), _domain(std::move(domain)), _range(range) {}

  FunctionSort::~FunctionSort() = default;

  const std::vector<const Sort *> &FunctionSort::domain() const {
    return _domain;
  }

  const Sort *FunctionSort::range() const {
    return _range;
  }

  bool FunctionSort::operator==(const Sort &other) const {
    if(this == &other) {
      return true;
    }
    if(this->kind() != other.kind()) {
      return false;
    }
    const auto &casted = (const FunctionSort &) other;
    if(!(*_range == *casted.range())) {
      return false;
    }
    if(_domain.size() != casted.domain().size()) {
      return false;
    }
    for(unsigned long i = 0; i < _domain.size(); i++) {
      if(!(*_domain.at(i) == *casted.domain().at(i))) {
        return false;
      }
    }
    return true;
  }

  //*-- SortManager
  SortManager::SortManager()
      : _null_sort("Null"), _bool_sort("Bool"), _int_sort("Int"), _real_sort("Real") {}

  const Sort *SortManager::Null() const {
    return &_null_sort;
  }

  const Sort *SortManager::Bool() const {
    return &_bool_sort;
  }

  const Sort *SortManager::Int() const {
    return &_int_sort;
  }

  const Sort *SortManager::Real() const {
    return &_real_sort;
  }

  const ArraySort *SortManager::array_sort(const Sort *index_sort, const Sort *element_sort) {
    if(_array_sorts.count(index_sort) == 0 || _array_sorts.at(index_sort).count(element_sort) == 0) {
      _array_sorts[index_sort][element_sort] = new ArraySort(index_sort, element_sort);
    }
    return _array_sorts[index_sort][element_sort];
  }

  const FunctionSort *SortManager::function_sort(const std::vector<const Sort *> &domain, const Sort *range) {
    if(_func_sorts.count(domain.size()) > 0) {
      for(const auto &[signature, sort]: _func_sorts.at(domain.size())) {
        bool is_equal = true;
        if(*range == *signature.at(signature.size() - 1)) {
          for(unsigned long i = 0; i < domain.size(); i++) {
            if(!(*domain.at(i) == *signature.at(i))) {
              is_equal = false;
              break;
            }
          }
        } else {
          is_equal = false;
        }
        if(is_equal) {
          return sort;
        }
      }
    }
    std::vector<const Sort *> signature(domain);
    signature.push_back(range);
    _func_sorts[domain.size()][signature] = new FunctionSort(domain, range);
    return _func_sorts[domain.size()][signature];
  }

}
