
#ifndef __UTILITY_ALGORITHM_SORTIMPL_SELECT_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_SELECT_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/prev.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct select_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::select_sort_tag;
      template<typename _BidirectionalIterator, typename _Compare>
      void __sort(
        _BidirectionalIterator __first, _BidirectionalIterator __last,
        _Compare __compare, select_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_bidirectional_iterator<_BidirectionalIterator>::value,
          "select sort need at least bidirectional iterator."
        );
#endif // ! UTILITY_DEBUG
        bool __sorted = false;
        for(; !__sorted && (__last != __first); --__last)
        {
          __sorted = true;
          _BidirectionalIterator __tpos = iterator::prev(__last);
          for(_BidirectionalIterator __tfind = __first; __tfind < __last ; ++__tfind)
          {
            if(!(__compare(*__tfind, *__tpos)))
            { __tpos = __tfind;}
            else
            { __sorted = false;}
          }
          swap(*__tpos, *iterator::prev(__last));
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_SELECT_SORT__
