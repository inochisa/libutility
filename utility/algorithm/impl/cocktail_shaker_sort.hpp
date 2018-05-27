
#ifndef __UTILITY_ALGORITHM_SORTIMPL_COCKTAIL_SHAKER_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_COCKTAIL_SHAKER_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/next.hpp>
#include<utility/iterator/prev.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct cocktail_shaker_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::cocktail_shaker_sort_tag;
      template<typename _BidirectionalIterator, typename _Compare>
      void __sort(
        _BidirectionalIterator __first, _BidirectionalIterator __last,
        _Compare __compare, cocktail_shaker_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_bidirectional_iterator<_BidirectionalIterator>::value,
          "cocktail shaker sort need at least bidirectional iterator."
        );
#endif // ! UTILITY_DEBUG
        --__last;
        for(;__first < __last;)
        {
          for(_BidirectionalIterator __pos = __first; __pos != __last; ++__pos)
          {
            if(__compare(*iterator::next(__pos), *__pos))
            { swap(*iterator::next(__pos), *__pos);}
          }
          --__last;
          for(_BidirectionalIterator __pos = __last; __pos != __first; --__pos)
          {
            if(__compare(*__pos, *iterator::prev(__pos)))
            { swap(*__pos, *iterator::prev(__pos));}
          }
          ++__first;
        }
      }
    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_COCKTAIL_SHAKER_SORT__
