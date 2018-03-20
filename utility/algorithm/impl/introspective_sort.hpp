
#ifndef __UTILITY_ALGORITHM_SORTIMPL_INTROSPECTIVE_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_INTROSPECTIVE_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/iter_swap.hpp>
#include<utility/algorithm/partial_sort.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/move_backward.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct introspective_sort_tag { };
    }

    namespace sort_setting
    {
      constexpr utility::ptrdiff_t __introspective_sort_min = 16;
    }

    namespace detail
    {
      namespace sort_impl
      {
        template<typename _RandomAccessIterator, typename _Compare>
        inline _RandomAccessIterator __intro_median(
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

        template<typename _Size>
        inline _Size __intro_depth(_Size __len)
        {
          _Size __dep;
          for(__dep = 0; __len > 1; __len = __len / 2)
          { ++__dep;}
          return __dep;
        }

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __intro_igedge_linear_insert(
          _RandomAccessIterator __last, _Compare __compare
        )
        {
          typedef typename
            utility::iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          __value_type __val = utility::algorithm::move(*__last);
          _RandomAccessIterator __pos = __last;
          --__pos;
          for(;__compare(__val, *__pos);)
          {
            *__last = utility::algorithm::move(*__pos);
            __last = __pos;
            --__pos;
          }
          *__last = utility::algorithm::move(__val);
        }

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __intro_idedge_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          for(_RandomAccessIterator __i = __first; __i != __last; ++__i)
          { __intro_igedge_linear_insert(__i, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __intro_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          typedef typename
            utility::iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          if(__last == __first)
          { return;}
          for(_RandomAccessIterator __i = __first+1; __i != __last; ++__i)
          {
            if(__compare(*__i, *__first))
            {
              __value_type __val = utility::algorithm::move(*__i);
              utility::algorithm::move_backward(__first, __i, __i+1);
              *__first = utility::algorithm::move(__val);
            }
            else
            { __intro_igedge_linear_insert(__i, __compare);}
          }
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __intro_final_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using utility::algorithm::sort_setting::__introspective_sort_min;
          typedef typename
            utility::iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __intro_len =
            static_cast<__difference_type>(__introspective_sort_min);
          if(__last-__first > __intro_len)
          {
            __intro_insert_sort(__first, __first+__intro_len, __compare);
            __intro_idedge_insert_sort(__first+__intro_len, __last, __compare);
          }
          else
          { __intro_insert_sort(__first, __last, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        _RandomAccessIterator __intro_igedge_partition(
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
            utility::algorithm::iter_swap(__first, __last);
            ++__first;
          }
        }

        template<typename _RandomAccessIterator, typename _Compare, typename _Size>
        void __intro_sort_loop(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Size __dep_lim, _Compare __compare
        )
        {
          using utility::algorithm::sort_setting::__introspective_sort_min;
          typedef typename
            utility::iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __intro_len =
            static_cast<__difference_type>(__introspective_sort_min);

          for(;__last - __first > __intro_len;)
          {
            if(__dep_lim == 0)
            {
              utility::algorithm::partial_sort(__first, __last, __last, __compare);
              return;
            }
            _RandomAccessIterator __midpos = __first + (__last - __first) / 2;
            _RandomAccessIterator __part_pos =
              __intro_igedge_partition(
                __first, __last,
                __intro_median(__first, __midpos, __last-1, __compare), __compare
              );
            __intro_sort_loop(__part_pos, __last, --__dep_lim, __compare);
            __last = __part_pos;
          }
        }
      }

      using utility::algorithm::sort_tag::introspective_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      inline void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, introspective_sort_tag /*sort_tag*/
      )
      {
#ifdef UTILITY_DEBUG
        static_assert(
          utility::iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "introspective sort need at least random access iterator."
        );
#endif // ! UTILITY_DEBUG

        if(__first != __last)
        {
          sort_impl::__intro_sort_loop(
            __first, __last, sort_impl::__intro_depth(__last-__first)*2, __compare
          );
          sort_impl::__intro_final_insert_sort(__first, __last, __compare);
        }
      }

    }

  }
}

#endif // ! __UTILITY_ALGORITHM_SORTIMPL_INTROSPECTIVE_SORT__
