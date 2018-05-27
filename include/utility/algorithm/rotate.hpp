
#ifndef __UTILITY_ALGORITHM_ROTATE__
#define __UTILITY_ALGORITHM_ROTATE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/iter_swap.hpp>
#include<utility/algorithm/reverse.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/distance.hpp>
#include<utility/iterator/next.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template
      <
        typename _Iterator,
        bool = iterator::is_vaild_iterator_type<
          _Iterator, iterator::bidirectional_iterator_tag
        >::value
      >
      struct __rotate
      {
        template<typename _ForwardIterator>
        _ForwardIterator __aux(
          _ForwardIterator __first, _ForwardIterator __mid,
          _ForwardIterator __last
        )
        {
          if(__first == __mid)
          { return __last;}
          _ForwardIterator __tit = __mid;
          for(;__tit != __last;)
          {
            algorithm::iter_swap(__first++, __tit++);
            if(__first == __mid)
            { __mid = __tit;}
          }
          _ForwardIterator __res = __first;
          for(__tit = __mid; __tit != __last;)
          {
            algorithm::iter_swap(__first++, __tit++);
            if(__first == __mid)
            { __mid = __tit;}
            else if(__tit == __last)
            { __tit = __mid;}
          }
          return __res;
        }
      };
      template<typename _Iterator>
      struct __rotate<_Iterator, true>
      {
        template<typename _BidirectionalIterator>
        static inline _BidirectionalIterator __aux(
          _BidirectionalIterator __first, _BidirectionalIterator __mid,
          _BidirectionalIterator __last
        )
        {
          if(__first == __mid)
          { return __last;}
          algorithm::reverse(__first, __mid);
          algorithm::reverse(__mid, __last);
          algorithm::reverse(__first, __last);
          return iterator::next(
            __first, iterator::distance(__mid, __last)
          );
        }
      };
    }
    /**
     * \brief Rotate left the elements in range
     *
     * Performs a left rotation on a range of elements.<br/>
     * Specifically, \c rotate swaps the elements in the range [\a __first, \a __last)
     * in such a way that the element \a __mid becomes the first element
     * of the new range and \a __mid becomes the last element.
     *
     * \param __first,__last  the original range
     * \param __mid           the element that should appear
     *                        at the beginning of the rotated range
     * \return The iterator equal to \a __first + (\a __last - \a __mid)
     * \note A precondition of this function is
     *       that [\a __first, \a __last) are valid ranges.
     * \warning the behavior is undefined if the \
     *          a __mid is not in the range [\a __first, \a __last).
     */
    template<typename _ForwardIterator>
    inline _ForwardIterator rotate(
      _ForwardIterator __first, _ForwardIterator __mid,
      _ForwardIterator __last
    )
    {
      return
        algorithm::detail::__rotate<_ForwardIterator>::__aux(
          __first, __mid, __last
        );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_ROTATE__
