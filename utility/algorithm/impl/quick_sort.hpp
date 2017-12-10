
#ifndef __UTILITY_ALGORITHM_SORTIMPL_QUICK_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_QUICK_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/move_backward.hpp>
#include<utility/algorithm/iter_swap.hpp>

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
      constexpr ::utility::ptrdiff_t __qsort_min = 8;
    }

    namespace detail
    {
      namespace sort_impl
      {
        template<typename _RandomAccessIterator, typename _Compare>
        inline _RandomAccessIterator __qsort_median(
          _RandomAccessIterator __a, _RandomAccessIterator __b,
          _RandomAccessIterator __c, _Compare __compare
        )
        {
          if(__compare(*__a, *__b))
          {
            if(__compare(*__b, *__c))
            { return __b;}
            if(__compare(*__a, *__c))
            { return __c;}
            return __a;
          }
          if(__compare(*__a, *__c))
          { return __a;}
          if(__compare(*__b, *__c))
          { return __c;}
          return __b;
        }

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __qsort_igedge_linear_insert(
          _RandomAccessIterator __last, _Compare __compare
        )
        {
          typedef typename
            ::utility::iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          __value_type __val = ::utility::algorithm::move(*__last);
          _RandomAccessIterator __pos = __last;
          --__pos;
          for(;__compare(__val, *__pos);)
          {
            *__last = ::utility::algorithm::move(*__pos);
            __last = __pos;
            --__pos;
          }
          *__last = ::utility::algorithm::move(__val);
        }

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __qsort_idedge_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          for(_RandomAccessIterator __i = __first; __i != __last; ++__i)
          { __qsort_igedge_linear_insert(__i, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __qsort_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          typedef typename
            ::utility::iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          if(__last == __first)
          { return;}
          for(_RandomAccessIterator __i = __first+1; __i != __last; ++__i)
          {
            if(__compare(*__i, *__first))
            {
              __value_type __val = ::utility::algorithm::move(*__i);
              ::utility::algorithm::move_backward(__first, __i, __i+1);
              *__first = ::utility::algorithm::move(__val);
            }
            else
            { __qsort_igedge_linear_insert(__i, __compare);}
          }
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __qsort_final_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using ::utility::algorithm::sort_setting::__qsort_min;
          typedef typename
            ::utility::iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __qsort_len =
            static_cast<__difference_type>(__qsort_min);
          if(__last-__first > __qsort_len)
          {
            __qsort_insert_sort(__first, __first+__qsort_len, __compare);
            __qsort_idedge_insert_sort(__first+__qsort_len, __last, __compare);
          }
          else
          { __qsort_insert_sort(__first, __last, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        _RandomAccessIterator __qsort_partition(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _RandomAccessIterator __pivot, _Compare __compare
        )
        {
          for(;;)
          {
            for(;__compare(*__first, *__pivot);)
            { ++__first;}
            --__last;
            for(;__compare(*__pivot, *__last);)
            { --__last;}
            if(!(__first < __last))
            { return __first;}
            ::utility::algorithm::iter_swap(__first, __last);
            ++__first;
          }
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __qsort_loop(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using ::utility::algorithm::sort_setting::__qsort_min;
          typedef typename
            ::utility::iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __qsort_len =
            static_cast<__difference_type>(__qsort_min);
          if(__last - __first > __qsort_len)
          {
            _RandomAccessIterator __midpos = __first + (__last - __first) / 2;
            _RandomAccessIterator __part_pos =
              __qsort_partition(
                __first, __last,
                __qsort_median(__first, __midpos, __last, __compare), __compare
              );
            __qsort_loop(__first, __part_pos, __compare);
            __qsort_loop(__part_pos+1, __last, __compare);
          }
        }
      }
      using ::utility::algorithm::sort_tag::quick_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      inline void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, quick_sort_tag /*sort_tag*/
      )
      {
#ifdef UTILITY_DEBUG
        static_assert(
          ::utility::iterator::is_random_access_iterator<_RandomAccessIterator>::value,
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
