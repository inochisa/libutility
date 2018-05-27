
#ifndef __UTILITY_ALGORITHM_SORTIMPL_COMB_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_COMB_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct comb_sort_tag { };
    }

    namespace sort_setting
    {
      constexpr double __comb_shrink_factor = 0.8;
      static_assert(__comb_shrink_factor < 1.0, "Shrink Factor must be smaller than 1.");
    }

    namespace detail
    {
      using algorithm::sort_tag::comb_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, comb_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "comb sort need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG
        using algorithm::sort_setting::__comb_shrink_factor;
        typedef typename
          iterator::iterator_traits<_RandomAccessIterator>::difference_type
          __difference_type;
        __difference_type __len = __last - __first;
        bool __unsorted = true;
        for(;(__len > 1) || __unsorted;)
        {
          if(__len > 1)
          { __len = static_cast<__difference_type>(__len*__comb_shrink_factor);}
          __unsorted = false;
          for(
            _RandomAccessIterator __pos = __first;
            __pos+__len < __last; ++__pos)
          {
            if(__compare(*(__pos+__len), *__pos))
            {
              swap(*__pos, *(__pos+__len));
              __unsorted = true;
            }
          }
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_COMB_SORT__
