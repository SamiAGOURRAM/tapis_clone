//
// Copyright (c) 2023 Wael-Amine Boutglay
//

#pragma once

#include <vector>

namespace rope {

  //*-- SeqRope
  template<class C1, class C2>
  class SeqRope {
  private:
    // retrieve containers' types (for usage) and assert they're the same.
    using T1 = typename C1::value_type;
    using T2 = typename C2::value_type;
    static_assert(std::is_same<T1, T2>::value, "Only containers with the same value's type are allowed in `rope.hh`!");

    //*- iterator
    class iterator {
    private:
      typedef typename C1::const_iterator c1_iterator_type;
      typedef typename C2::const_iterator c2_iterator_type;

    public:
      constexpr iterator(c1_iterator_type c1_it, c1_iterator_type c1_end,
                         c2_iterator_type c2_it, c2_iterator_type c2_end)
          : _c1_it(c1_it), _c1_end(c1_end),
            _c2_it(c2_it), _c2_end(c2_end) {}

      // copy constructor
      constexpr iterator(const iterator &other)
          : _c1_it(other._c1_it), _c1_end(other._c1_end), _c2_it(other._c2_it), _c2_end(other._c2_end) {}

      //*- operators

      constexpr T1 operator*() const {
        if(_c1_it != _c1_end) {
          return *_c1_it;
        }
        return *_c2_it;
      }

      constexpr iterator &operator++() { // prefix increment
        if(_c1_it != _c1_end) {
          _c1_it++;
        } else if(_c2_it != _c2_end) {
          _c2_it++;
        }
        return *this;
      }

      constexpr iterator operator++(int) { // postfix increment
        iterator retval = *this;
        ++(*this);
        return retval;
      }

      constexpr bool operator==(const iterator &other) const {
        return _c1_it == other._c1_it && _c2_it == other._c2_it;
      }

      constexpr bool operator!=(const iterator &other) const {
        return _c1_it != other._c1_it || _c2_it != other._c2_it;
      }

    private:
      c1_iterator_type _c1_it, _c1_end;
      c2_iterator_type _c2_it, _c2_end;
    };

  public:
    constexpr SeqRope(const C1 &container1, const C2 &container2)
        : _container1(container1), _container2(container2) {}

    constexpr iterator begin() const {
      return iterator(_container1.begin(), _container1.end(), _container2.begin(), _container2.end());
    }

    constexpr iterator end() const {
      return iterator(_container1.end(), _container1.end(), _container2.end(), _container2.end());
    }

    typedef typename C1::value_type value_type;
    typedef iterator const_iterator;

  private:
    const C1 &_container1;
    const C2 &_container2;
  };

  //*- add(container1, container2)
  template<typename C1, typename C2>
  constexpr SeqRope<C1, C2> add(const C1 &container1, const C2 &container2) {
    return SeqRope<C1, C2>(container1, container2);
  }

}
