
#ifndef __UTILITY_ALGORITHM_SORTIMPL_INTROSPECTIVE_SORT__
#define __UTILITY_ALGORITHM_SORTIMPL_INTROSPECTIVE_SORT__

#include<utility/algorithm/partial_sort.hpp>

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
      struct introspective_sort_tag { };
    }

    namespace sort_setting
    {
      constexpr ptrdiff_t __introspective_sort_min = 16;
    }

    namespace detail
    {
      namespace sort_impl
      {
        template<typename _Size>
        inline _Size __intro_depth(_Size __len)
        {
          _Size __dep;
          for(__dep = 0; __len > 1; __len = __len / 2)
          { ++__dep;}
          return __dep;
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __intro_final_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          using algorithm::sort_setting::__introspective_sort_min;
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __intro_len =
            static_cast<__difference_type>(__introspective_sort_min);
          if(__last-__first > __intro_len)
          {
            __insert_sort(__first, __first+__intro_len, __compare);
            __idedge_insert_sort(__first+__intro_len, __last, __compare);
          }
          else
          { __insert_sort(__first, __last, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare, typename _Size>
        void __intro_sort_loop(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Size __dep_lim, _Compare __compare
        )
        {
          using algorithm::sort_setting::__introspective_sort_min;
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::difference_type
            __difference_type;
          const __difference_type __intro_len =
            static_cast<__difference_type>(__introspective_sort_min);

          for(; __last - __first > __intro_len;)
          {
            if(__dep_lim == 0)
            {
              algorithm::partial_sort(__first, __last, __last, __compare);
              return;
            }
            _RandomAccessIterator __midpos = __first + (__last - __first) / 2;
            _RandomAccessIterator __part_pos =
              __partition(
                __first, __last,
                __median(__first, __midpos, __last-1, __compare), __compare
              );
            __intro_sort_loop(__part_pos, __last, --__dep_lim, __compare);
            __last = __part_pos;
          }
        }
      }

      using algorithm::sort_tag::introspective_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      inline void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, introspective_sort_tag /*sort_tag*/
      )
      {
#ifdef UTILITY_DEBUG
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
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
