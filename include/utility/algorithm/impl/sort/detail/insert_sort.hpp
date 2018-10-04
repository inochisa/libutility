
#ifndef __UTILITY_ALGORITHM_IMPL_SORT_INSERT_SORT__
#define __UTILITY_ALGORITHM_IMPL_SORT_INSERT_SORT__

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/move_backward.hpp>

#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      namespace sort_impl
      {

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __igedge_linear_insert(
          _RandomAccessIterator __last, _Compare __compare
        )
        {
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          __value_type __val = algorithm::move(*__last);
          _RandomAccessIterator __pos = __last;
          --__pos;
          for(; __compare(__val, *__pos);)
          {
            *__last = algorithm::move(*__pos);
            __last = __pos;
            --__pos;
          }
          *__last = algorithm::move(__val);
        }

        template<typename _RandomAccessIterator, typename _Compare>
        inline void __idedge_insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          for(_RandomAccessIterator __i = __first; __i != __last; ++__i)
          { __igedge_linear_insert(__i, __compare);}
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __insert_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          typedef typename
            iterator::iterator_traits<_RandomAccessIterator>::value_type
            __value_type;
          if(__last == __first)
          { return;}
          for(_RandomAccessIterator __i = __first+1; __i != __last; ++__i)
          {
            if(__compare(*__i, *__first))
            {
              __value_type __val = algorithm::move(*__i);
              algorithm::move_backward(__first, __i, __i+1);
              *__first = algorithm::move(__val);
            }
            else
            { __igedge_linear_insert(__i, __compare);}
          }
        }

      }
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IMPL_SORT_INSERT_SORT__
