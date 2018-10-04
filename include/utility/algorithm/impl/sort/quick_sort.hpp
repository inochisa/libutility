
#ifndef __UTILITY_ALGORITHM_SORTIMPL_QUICK_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_QUICK_SORT__

#include<utility/algorithm/impl/sort/detail/median.hpp>
#include<utility/algorithm/impl/sort/detail/partition.hpp>
#include<utility/algorithm/impl/sort/detail/insert_sort.hpp>

#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct quick_sort_tag { };
    }

    namespace sort_setting
    {
      constexpr ptrdiff_t __qsort_min = 8;
    }

    namespace detail
    {
      namespace sort_impl
      {
        template<typename _RandomAccessIterator, typename _Compare>
        void __qsort_final_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using algorithm::sort_setting::__qsort_min;
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __qsort_len =
            static_cast<__difference_type>(__qsort_min);
          if(__last-__first > __qsort_len)
          {
            __insert_sort(__first, __first+__qsort_len, __compare);
            __igedge_insert_sort(__first+__qsort_len, __last, __compare);
          }
          else
          { __insert_sort(__first, __last, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __qsort_loop(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using algorithm::sort_setting::__qsort_min;
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __qsort_len =
            static_cast<__difference_type>(__qsort_min);
          if(__last - __first > __qsort_len)
          {
            _RandomAccessIterator __midpos = __first + (__last - __first) / 2;
            _RandomAccessIterator __part_pos =
              __partition(
                __first, __last,
                __median(__first, __midpos, __last-1, __compare), __compare
              );
            __qsort_loop(__first, __part_pos, __compare);
            __qsort_loop(__part_pos, __last, __compare);
          }
        }
      }
      using algorithm::sort_tag::quick_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      inline void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, quick_sort_tag /*sort_tag*/
      )
      {
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "quick sort need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG
        if(__first != __last)
        {
          sort_impl::__qsort_loop(__first, __last, __compare);
          sort_impl::__qsort_final_insert_sort(__first, __last, __compare);
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_QUICK_SORT__
