
#ifndef __UTILITY_ALGORITHM_ROTATE_COPY__
#define __UTILITY_ALGORITHM_ROTATE_COPY__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/copy.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Copy range rotated left
     *
     * Copies the elements from the range [\a __first, \a __last),
     * to another range beginning at \a __ofirst in such a way,
     * that the element \a __mid becomes the first element of
     * the new range and \a __mid - 1 becomes the last element.
     *
     * \param __first,__last  the original range
     * \param __mid           the element that should appear
     *                        at the beginning of the rotated range
     * \param __ofirst        beginning of the destination range
     * \return Output iterator to the element past the last element copied.
     * \note A precondition of this function is
     *       that [\a __first, \a __last) are valid ranges.
     * \warning the behavior is undefined if the \
     *          a __mid is not in the range [\a __first, \a __last).
     */
    template<typename _ForwardIterator, typename _OutputIterator>
    _OutputIterator rotate_copy(
      _ForwardIterator __first, _ForwardIterator __mid,
      _ForwardIterator __last,  _OutputIterator __ofirst
    )
    {
      __ofirst = algorithm::copy(__mid, __last, __ofirst);
      return algorithm::copy(__first, __mid, __ofirst);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_ROTATE_COPY__
