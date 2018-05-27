
#ifndef __UTILITY_ALGORITHM_MISMATCH__
#define __UTILITY_ALGORITHM_MISMATCH__

#include<utility/config/utility_config.hpp>
#include<utility/container/pair.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Find the first position where two ranges differ
     *
     * Returns the first mismatching pair of elements from two ranges:
     * one defined by [\a __first1, \a __last1)
     * and another defined by [\a __first2,\a __last2).<br/>
     * Elements are compared using the given binary predicate p.
     *
     * \param __first1,__last1 the first range of the elements
     * \param __first2,__last2 the second range of the elements
     * \param __pred           binary predicate which returns ​\b true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return pair with iterators to the first
     *         two non-equivalent elements.
     */
    template<typename _InputIterator1, typename _InputIterator2,
      typename _BinaryPredicate
    >
    container::pair<_InputIterator1, _InputIterator2>
    mismatch(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _BinaryPredicate __pred
    )
    {
      for(; __first1 != __last1 && __first1 != __last2
         && __pred(*__first1, *__first2); ++__first1, ++__first2
      )
      { }
      return container::make_pair(__first1, __first2);
    }
    /**
     * \overload container::pair<_InputIterator1, _InputIterator2>
     *  mismatch(
     *    _InputIterator1 __first1, _InputIterator1 __last1,
     *    _InputIterator2 __first2, _InputIterator2 __last2
     *  )
     *
     * This function use operator== as binary predicate.
     *
     */
    template<typename _InputIterator1, typename _InputIterator2>
    container::pair<_InputIterator1, _InputIterator2>
    mismatch(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2
    )
    {
      for(; __first1 != __last1 && __first1 != __last2
         && *__first1 == *__first2; ++__first1, ++__first2
      )
      { }
      return container::make_pair(__first1, __first2);
    }

    /**
     * \brief Find the first position where two ranges differ
     *
     * Returns the first mismatching pair of elements from two ranges:
     * one defined by [\a __first1, \a __last1) and another defined by
     * [\a __first2,\a \a __first2 + (\a __last1 - \a __first1)).<br/>
     * Elements are compared using the given binary predicate p.
     *
     * \param __first1,__last1 the first range of the elements
     * \param __first2         the first iterator of the second range
     * \param __pred           binary predicate which returns ​\b true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return pair with iterators to the first
     *         two non-equivalent elements.
     */
    template<typename _InputIterator1, typename _InputIterator2,
      typename _BinaryPredicate
    >
    container::pair<_InputIterator1, _InputIterator2>
    mismatch(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __pred
    )
    {
      for(; __first1 != __last1 &&  __pred(*__first1, *__first2);
        ++__first1, ++__first2
      )
      { }
      return container::make_pair(__first1, __first2);
    }
    /**
     * \overload container::pair<_InputIterator1, _InputIterator2>
     *  mismatch(
     *    _InputIterator1 __first1, _InputIterator1 __last1,
     *    _InputIterator2 __first2
     *  )
     *
     * This function use operator== as binary predicate.
     *
     */
    template<typename _InputIterator1, typename _InputIterator2>
    container::pair<_InputIterator1, _InputIterator2>
    mismatch(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2
    )
    {
      for(; __first1 != __last1 && *__first1 == *__first2;
        ++__first1, ++__first2
      )
      { }
      return container::make_pair(__first1, __first2);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MISMATCH__
