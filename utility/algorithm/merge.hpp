
#ifndef __UTILITY_ALGORITHM_MERGE__
#define __UTILITY_ALGORITHM_MERGE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/copy.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Merge sorted ranges
     *
     * Merges two sorted ranges [\a __first1, \a __last1)
     * and [\a __first2, \a __last2) into one sorted range
     * beginning at \a __result using the given
     * binary comparison function \a __compare.
     *
     * \param __first1,__last1  the first range of elements to merge
     * \param __first2,__last2  the second range of elements to merge
     * \param __result          the beginning of the destination range
     * \param __compare         comparison function object which returns \b ​true
     *                          if the first argument is less than the second.
     *                          The signature of the comparison function
     *                          should be logically equivalent to the following:
     *                          \code{.cpp}
     *                            bool cmp(const Type1&, const Type2&);
     *                          \endcode
     * \return An output iterator to element past the last element copied.
     */
    template
    <
      typename _InputIterator1, typename _InputIterator2,
      typename _OutputIterator, typename _Compare
    >
    _OutputIterator merge(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _OutputIterator __result, _Compare __compare
    )
    {
      for(; __first1 != __last1;)
      {
        if(__first2 == __last2)
        { return algorithm::copy(__first1, __last1, __result);}
        if(__compare(*__first1, *__first2))
        { *__result++ = *__first1++; }
        else
        { *__result++ = *__first2++;}
      }
      return algorithm::copy(__first2, __last2, __result);
    }
    template
    <
      typename _InputIterator1, typename _InputIterator2,
      typename _OutputIterator
    >
    inline _OutputIterator merge(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _OutputIterator __result
    )
    {
      return merge(
        __first1, __last1, __first2, __last2,
        __result, algorithm::less<void>()
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MERGE__
