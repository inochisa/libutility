
#ifndef __UTILITY_ALGORITHM_EQUAL__
#define __UTILITY_ALGORITHM_EQUAL__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Test whether the elements in two ranges are equal
     *
     * Compares the elements in the range [\a __first1, \a __last1)
     * with those in the range beginning at \a __first2,
     * and returns true if all of the elements in both ranges match.
     *
     * \tparam _InputIterator1,_InputIterator2 the iterator type
     * \tparam _BinaryPredicate binary predicate function type
     * \param __first1,__last1 the first range of the elements to compare
     * \param __first2         the second range of the elements to compare
     * \param __binarypred     binary predicate which returns ​\b true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return If the elements in the two ranges are equal,
     *         returns true, Otherwise returns false.
     *
     * \note this function should not be used for the iterator from hasing container.
     *       the wrong value may be returned.
     */
    template<typename _InputIterator1, typename _InputIterator2,
      typename _BinaryPredicate>
    inline bool equal(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __binarypred
    )
    {
      for(;__first1 != __last1;)
      {
        if(!__binarypred(*__first1++, *__first2++))
        { return false;}
      }
      return true;
    }
    /**
     * \overload equal(
     *  _InputIterator1 __first1, _InputIterator1 __last1,
     *  _InputIterator2 __first2
     * )
     *
     * this version use operator== as binary predicate.
     *
     */
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool equal(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2)
    {
      return equal(
        __first1, __last1, __first2,
        algorithm::equal_to<void>()
      );
    }
    /**
     * \brief Test whether the elements in two ranges are equal
     *
     * Compares the elements in the range [\a __first1, \a __last1)
     * with those in the range beginning at \a __first2,
     * and returns true if all of the elements in both ranges match.
     *
     * \tparam _InputIterator1,_InputIterator2 the iterator type
     * \tparam _BinaryPredicate binary predicate function type
     * \param __first1,__last1 the first range of the elements to compare
     * \param __first2,__last2 the second range of the elements to compare
     * \param __binarypred     binary predicate which returns ​true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return If the elements in the two ranges are equal,
     *         returns true, Otherwise returns false.
     *
     * \note this function should not be used for the iterator from hasing container.
     *       the wrong value may be returned.
     */
    template<typename _InputIterator1, typename _InputIterator2,
      typename _BinaryPredicate>
    inline bool equal(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _BinaryPredicate __binarypred
    )
    {
      for(;__first1 != __last1 && __first2 != __last2;)
      {
        if(!__binarypred(*__first1++, *__first2++))
        { return false;}
      }
      return true;
    }
    /**
     * \overload equal(
     *  _InputIterator1 __first1, _InputIterator1 __last1,
     *  _InputIterator2 __first2, _InputIterator2 __last2
     * )
     *
     * this version use operator== as binary predicate.
     *
     */
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool equal(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2
    )
    {
      return equal(
        __first1, __last1, __first2, __last2,
        algorithm::equal_to<void>()
      );
    }

  }
}

#endif // ! __UTILITY_ALGORITHM_EQUAL__
