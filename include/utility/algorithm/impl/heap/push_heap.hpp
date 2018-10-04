
#ifndef __UTILITY_ALGORITHM_IMPL_HEAP_PUSH_HEAP__
#define __UTILITY_ALGORITHM_IMPL_HEAP_PUSH_HEAP__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<
        typename _RandomAccessIterator, typename _Compare,
        typename _Difference
      >
      void __push_heap_aux(
        _RandomAccessIterator __first,
        _Difference __hole, _Difference __top,
        _Compare __compare
      )
      {
        using algorithm::swap;
        _Difference __parent = (__hole-1)/2;
        for(;__hole > __top && __compare(*(__first+__parent), *(__first+__hole));)
        {
          swap(*(__first+__hole), *(__first+__parent));
          __hole = __parent;
          __parent = (__parent-1) / 2;
        }
      }
    }

    template<typename _RandomAccessIterator, typename _Compare>
    inline void push_heap(
      _RandomAccessIterator __first, _RandomAccessIterator __last,
      _Compare __compare
    )
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::difference_type
        __difference_type;
      typedef typename
        trait::type::transform::add_lvalue_reference<_Compare>::type
        __comp_ref;

      detail::__push_heap_aux<_RandomAccessIterator, __comp_ref, __difference_type>(
        __first, __difference_type((__last-__first)-1),
        __difference_type(0), __compare
      );
    }
    template<typename _RandomAccessIterator>
    inline void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::value_type
        __value_type;
      push_heap(
        __first, __last,
        algorithm::less<__value_type>()
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IMPL_HEAP_PUSH_HEAP__
