
#ifndef __UTILITY_ALGORITHM_SORTIMPL_CYCLE_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_CYCLE_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/next.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct cycle_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::cycle_sort_tag;
      template<typename _ForwardIterartor, typename _Compare>
      void __sort(
        _ForwardIterartor __first, _ForwardIterartor __last,
        _Compare __compare, cycle_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_forward_iterator<_ForwardIterartor>::value,
          "cycle sort need at least forward iterator."
        );
#endif // ! UTILITY_DEBUG
        typedef typename
          iterator::iterator_traits<_ForwardIterartor>::value_type
          __value_type;
        for(
          _ForwardIterartor __i = __first;
          iterator::next(__i) != __last; ++__i
        )
        {
          __value_type __val = *__i;
          _ForwardIterartor __pos = __i;
          for(
            _ForwardIterartor __j = iterator::next(__i);
            __j != __last; ++__j
          )
          {
            if(__compare(*__j, __val))
            { ++__pos;}
          }
          if(__pos == __i)
          { continue;}
          for(;!(__compare(*__pos, __val) || __compare(__val, *__pos));)
          { ++__pos;}
          swap(*__pos, __val);
          for(;__pos != __i;)
          {
            __pos = __i;
            for(
              _ForwardIterartor __j = iterator::next(__i);
              __j != __last; ++__j
            )
            {
              if(__compare(*__j, __val))
              { ++__pos;}
            }
            for(;!(__compare(*__pos, __val) || __compare(__val, *__pos));)
            { ++__pos;}
            swap(*__pos, __val);
          }
        }
      }
    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_CYCLE_SORT__
