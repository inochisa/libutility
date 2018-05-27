
#ifndef __UTILITY_ALGORITHM_SORTIMPL_SHELL_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_SHELL_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct shell_sort_tag { };
    }

    namespace detail
    {
      using algorithm::sort_tag::shell_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, shell_sort_tag /*sort_tag*/
      )
      {
        using algorithm::swap;
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "shell sort need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG
        typedef typename
          iterator::iterator_traits<_RandomAccessIterator>::difference_type
          __difference_type;

        __difference_type __size = iterator::distance(__first,__last);

        for(__difference_type __step = __size / 2; __step > 0; __step = __step / 2)
        {
          for(__difference_type __i = __step; __i < __size; ++__i)
          {
            for(
              _RandomAccessIterator __it = __first + __i;
              __it > __first && __compare(*__it, *(__it - __step));
              __it -= __step
            )
            { swap(*__it, *(__it - __step));}
          }
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_SHELL_SORT__
