
#ifndef __UTILITY_ALGORITHM_IMPL_HEAP_SORT_HEAP__
#define __UTILITY_ALGORITHM_IMPL_HEAP_SORT_HEAP__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/impl/heap/pop_heap.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _RandomAccessIterator, typename _Compare>
    void sort_heap(
      _RandomAccessIterator __first, _RandomAccessIterator __last,
      _Compare __compare
    )
    {
      for(;__last-__first > 1;)
      { pop_heap(__first, __last--, __compare);}
    }
    template<typename _RandomAccessIterator>
    inline void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::value_type
        __value_type;
      sort_heap(__first, __last, algorithm::less<__value_type>());
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IMPL_HEAP_SORT_HEAP__
