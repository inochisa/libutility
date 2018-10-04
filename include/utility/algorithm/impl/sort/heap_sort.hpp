
#ifndef __UTILITY_ALGORITHM_SORTIMPL_HEAP_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_HEAP_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/impl/heap/make_heap.hpp>
#include<utility/algorithm/impl/heap/pop_heap.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/algorithm/partial_sort.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct heap_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::heap_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, heap_sort_tag /*sort_tag*/
      )
      {
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "heap sort need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG
        algorithm::make_heap(__first, __last, __compare);
        for(;__last - __first > 1;)
        { algorithm::pop_heap(__first, __last--, __compare);}
      }
    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_HEAP_SORT__
