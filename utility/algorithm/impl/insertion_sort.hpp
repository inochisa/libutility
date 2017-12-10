
#ifndef __UTILITY_ALGORITHM_SORTIMPL_INSERTION_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_INSERTION_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/next.hpp>
#include<utility/iterator/prev.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct insertion_sort_tag { };
    }

    namespace detail
    {
      using ::utility::algorithm::sort_tag::insertion_sort_tag;
      template<typename _BidirectionalIterator, typename _Compare>
      void __sort(
        _BidirectionalIterator __first, _BidirectionalIterator __last,
        _Compare __compare, insertion_sort_tag /*sort_tag*/
      )
      {
        using utility::algorithm::swap;
        typedef typename
          ::utility::iterator::iterator_traits<_BidirectionalIterator>::value_type
          __value_type;
        for(
          _BidirectionalIterator __i = ::utility::iterator::next(__first);
          __i != __last; ++__i
        )
        {
#ifdef UTILITY_DEBUG
          static_assert(
            ::utility::iterator::is_bidirectional_iterator<_BidirectionalIterator>::value,
            "insertion sort tag need at least bidirectional iterator."
          );
#endif // ! UTILITY_DEBUG
          __value_type __tmp = *__i;
          _BidirectionalIterator __fpos;
          for(
            __fpos = ::utility::iterator::prev(__i);
            ::utility::iterator::next(__fpos) != __first && __compare(__tmp, *__fpos);
            --__fpos
          )
          { swap(*__fpos, *::utility::iterator::next(__fpos));}
          *::utility::iterator::next(__fpos) = __tmp;
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_INSERTION_SORT__
