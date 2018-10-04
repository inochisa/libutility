
#ifndef __UTILITY_ALGORITHM_IMPL_HEAP_MAKE_HEAP__
#define __UTILITY_ALGORITHM_IMPL_HEAP_MAKE_HEAP__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<typename _RandomAccessIterator, typename _Compare, typename _Difference>
      void __make_heap_aux(
        _RandomAccessIterator __first,
        _Difference __begin, _Difference __end,
        _Compare __compare
      )
      {
        using algorithm::swap;
        _Difference __hole = __begin;
        _Difference __child = 2*__begin+1;
        for(; __child < __end;)
        {
          if(
            __child+1 < __end &&
            __compare(*(__first+__child), *(__first+__child+1))
          )
          { ++__child;}
          if(__compare(*(__first+__child), *(__first+__hole)))
          { return;}
          else
          {
            swap(*(__first+__child), *(__first+__hole));
            __hole = __child;
            __child = 2*__child+1;
          }
        }
      }
    }
    template<typename _RandomAccessIterator, typename _Compare>
    void make_heap(
      _RandomAccessIterator __first, _RandomAccessIterator __last,
      _Compare __compare
    )
    {
      using algorithm::swap;
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::difference_type
        __difference_type;
      typedef typename
        trait::type::transform::add_lvalue_reference<_Compare>::type
        __comp_ref;

      __difference_type __len = __last - __first;
      if(__len == 1)
      { return;}

      for(__difference_type __hole = (__len-1) / 2; __hole >= 0; --__hole)
      {
        detail::__make_heap_aux<_RandomAccessIterator, __comp_ref, __difference_type>(
          __first, __hole, __len, __compare
        );
      }
    }
    template<typename _RandomAccessIterator>
    inline void make_heap(
      _RandomAccessIterator __first, _RandomAccessIterator __last
    )
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::value_type
        __value_type;
      algorithm::make_heap(__first, __last, algorithm::less<__value_type>());
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IMPL_HEAP_MAKE_HEAP__
