
#ifndef __UTILITY_ALGORITHM_MERGE_SORT__
#define __UTILITY_ALGORITHM_MERGE_SORT__

#include<utility/algorithm/merge.hpp>
#include<utility/algorithm/copy.hpp>
#include<utility/iterator/advance.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<typename _RandomAccessIterator, typename _Compare>
      void __merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _RandomAccessIterator __tfirst, _RandomAccessIterator __tlast, _Compare __compare)
      {
        typedef typename
          utility::iterator::iterator_traits<_RandomAccessIterator>::difference_type
          __difference_type;
        __difference_type __len = __last - __first;
        if(__len < 2)
        { return;}
        _RandomAccessIterator __mid = __first + __len / 2;
        _RandomAccessIterator __tmid = __tfirst + __len / 2;
        __merge_sort(__first, __mid, __tfirst, __tmid, __compare);
        __merge_sort(__mid, __last, __tmid, __tlast, __compare);
        utility::algorithm::merge(__first, __mid, __mid, __last, __tfirst, __compare);
        utility::algorithm::copy(__tfirst, __tlast, __first);
      }
    }
    template<typename _RandomAccessIterator, typename _Compare>
    inline void merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _RandomAccessIterator __tfirst, _RandomAccessIterator __tlast,_Compare __compare)
    {
      detail::__merge_sort(__first, __last, __tfirst, __tlast, __compare);
    }
    template<typename _RandomAccessIterator>
    inline void merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _RandomAccessIterator __tfirst, _RandomAccessIterator __tlast)
    {
      typedef typename
        utility::iterator::iterator_traits<_RandomAccessIterator>::value_type
        __value_type;
      merge_sort(__first, __last, __tfirst, __tlast, utility::algorithm::less<__value_type>());
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MERGE_SORT__
