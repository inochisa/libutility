
#ifndef __UTILITY_ALGORITHM_SORTIMPL_ODD_EVEN_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_ODD_EVEN_SORT__

#include<utility/algorithm/swap.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct odd_even_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::odd_even_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, odd_even_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "odd even sort  need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG
        bool __unsorted = true;
        for(;__unsorted;)
        {
          __unsorted = false;
          for(_RandomAccessIterator __pos = __first; __pos < __last-1; __pos = __pos + 2)
          {
            if(__compare(*(__pos+1), *__pos))
            {
              swap(*(__pos+1), *__pos);
              __unsorted = true;
            }
          }
          for(_RandomAccessIterator __pos = __first+1; __pos < __last-1; __pos = __pos + 2)
          {
            if(__compare(*(__pos+1), *__pos))
            {
              swap(*(__pos+1), *__pos);
              __unsorted = true;
            }
          }
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_ODD_EVEN_SORT__
