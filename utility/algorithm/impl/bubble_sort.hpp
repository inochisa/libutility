
#ifndef __UTILITY_ALGORITHM_SORTIMPL_BUBBLE_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_BUBBLE_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/next.hpp>
#include<utility/iterator/prev.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct bubble_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::bubble_sort_tag;
      template<typename _BidirectionalIterator, typename _Compare>
      void __sort(
        _BidirectionalIterator __first, _BidirectionalIterator __last,
        _Compare __compare,
        bubble_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_bidirectional_iterator<_BidirectionalIterator>::value,
          "bubble sort sort need at least bidirectional iterator."
        );
#endif // ! UTILITY_DEBUG
        bool __unsorted = true;
        for(; __unsorted && __first != __last; --__last)
        {
          __unsorted = false;
          for(
            _BidirectionalIterator __i = iterator::next(__first);
            __i != __last; ++__i
          )
          {
            if(__compare(*__i, *iterator::prev(__i)))
            {
              swap(*__i, *iterator::prev(__i));
              __unsorted = true;
            }
          }
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_BUBBLE_SORT__
