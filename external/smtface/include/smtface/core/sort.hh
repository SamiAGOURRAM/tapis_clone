//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace smtface::core {

  enum class SortKind {
    native,
    array,
    function
  };

  class Sort {
  public:
    explicit Sort(SortKind kind);

    virtual ~Sort();

    //*- properties

    SortKind kind() const;

    virtual bool is_array() const;

    //*- operators

    virtual bool operator==(const Sort &other) const = 0;

  private:
    SortKind _kind;
  };

  class NativeSort: public Sort {
  public:
    explicit NativeSort(std::string name);

    ~NativeSort() override;

    //*- properties

    const std::string &name() const;

    //*- operators

    bool operator==(const Sort &other) const override;

  private:
    std::string _name;
  };

  //*-- ArraySort
  class ArraySort: public Sort {
  public:
    ArraySort(const Sort *index_sort, const Sort *element_sort);

    ~ArraySort() override;

    //*- properties

    const Sort *index_sort() const;

    const Sort *element_sort() const;

    bool is_array() const override;

    //*- operators

    bool operator==(const Sort &other) const override;

  private:
    const Sort *_index_sort;
    const Sort *_element_sort;
  };

  //*-- FunctionSort
  class FunctionSort: public Sort {
  public:
    FunctionSort(std::vector<const Sort *> domain, const Sort *range);

    ~FunctionSort() override;

    //*- properties

    const std::vector<const Sort *> &domain() const;

    const Sort *range() const;

    //*- operators

    bool operator==(const Sort &other) const override;

  private:
    std::vector<const Sort *> _domain;
    const Sort *_range;
  };

  //*-- SortManager
  class SortManager {
  public:
    SortManager();

    //*- properties

    const Sort *Null() const;

    const Sort *Bool() const;

    const Sort *Int() const;

    const Sort *Real() const;

    //*- methods

    const ArraySort *array_sort(const Sort *index_sort, const Sort *element_sort);

    const FunctionSort *function_sort(const std::vector<const Sort *> &domain, const Sort *range);

  private:
    NativeSort _null_sort;
    NativeSort _bool_sort;
    NativeSort _int_sort;
    NativeSort _real_sort;
    std::unordered_map<const Sort *, std::unordered_map<const Sort *, const ArraySort *>> _array_sorts;
    std::unordered_map<unsigned long, std::map<std::vector<const Sort *>, const FunctionSort *>> _func_sorts;
  };

}
