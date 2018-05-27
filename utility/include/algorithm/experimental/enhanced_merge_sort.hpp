
#ifndef __UTILITY_ALGORITHM_EXPL_ENHANCED_MERGE_SORT__
#define __UTILITY_ALGORITHM_EXPL_ENHANCED_MERGE_SORT__

#include<utility/algorithm/swap.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/prev.hpp>
#include<utility/iterator/next.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace sort_tag
    {
      struct enhanced_merge_sort_tag { };
    }
    namespace detail
    {

      namespace sort_impl
      {
        template<typename _RandomAccessIterator, typename _Compare>
        void __en_msort_sort(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          _RandomAccessIterator __x = __first;
          _RandomAccessIterator __a = __x;
          _RandomAccessIterator __b =
            __first + iterator::distance(__first, __last) / 2+1;
          _RandomAccessIterator __y = __b;
          while(__x < __b)
          {
            if(__b > __last)
            {
              if(__a > __x)
              {
                if(__b == __a+1 && __a > __y)
                { __b = __a; __a = __y;}
                else
                { __b = __y; __a = __x;}
              }
              else
              { break;}
            }
            if(__x == __y)
            {
              if(__a == __x)
              { __y = __b;}
              else
              { __y = __a;}
            }

            if(__compare(*__b, *__a))
            {
              if(__a > __y && __b > __a+1)
              {
                algorithm::swap(*__a, *__b);
                algorithm::swap(*__a, *__x);
                ++__x; ++__a;
              }
              else if(__a == __x && __b == __y)
              {
                algorithm::swap(*__x, *__b);
                __a = __b; ++__b; ++__x;
              }
              else if(__a+1 == __b)
              {
                algorithm::swap(*__b, *__x);
                algorithm::swap(*__b, *__a);
                ++__b; ++__x; ++__a;
              }
              else if(__a ==__y && __x < __y)
              {
                algorithm::swap(*__x, *__b);
                ++__b; ++__x;
              }
            }
            else
            {
              if(__a == __x && __b == __y)
              { ++__x; ++__a;}
              else if(__a+1 == __b)
              {
                algorithm::swap(*__x, *__a);
                __a = __y; ++__x;
              }
              else if(__b > __a+1)
              {
                algorithm::swap(*__x, *__a);
                ++__x; ++__a;
              }
            }
          }
        }

        template<typename _RandomAccessIterator, typename _Compare>
        void __en_msort_split(
          _RandomAccessIterator __first, _RandomAccessIterator __last,
          _Compare __compare
        )
        {
          if(__first == __last)
          { return;}
          if(__first+1 == __last)
          {
            if(__compare(*(__first+1), *__first))
            { algorithm::swap(*__first, *(__first+1));}
            return;
          }

          _RandomAccessIterator __mid =
            __first + iterator::distance(__first, __last) / 2;
          __en_msort_split(__first, __mid,  __compare);
          __en_msort_split(__mid+1, __last, __compare);

          if(__compare(*(__mid+1), *__mid))
          { __en_msort_sort(__first, __last, __compare);}
        }
      }

      using algorithm::sort_tag::enhanced_merge_sort_tag;
      template<typename _RandomAccessIterator, typename _Compare>
      void __sort(
        _RandomAccessIterator __first, _RandomAccessIterator __last,
        _Compare __compare, enhanced_merge_sort_tag /*sort_tag*/
      )
      {
        static_assert(
          iterator::is_random_access_iterator<_RandomAccessIterator>::value,
          "enhanced merge sort need at least random access iterator."
        );
        if(__first != __last)
        { sort_impl::__en_msort_split(__first, --__last, __compare);}
      }
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_EXPL_ENHANCED_MERGE_SORT__
