
#ifndef __UTILITY_ALGORITHM_IS_PERMUTATION__
#define __UTILITY_ALGORITHM_IS_PERMUTATION__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/distance.hpp>
#include<utility/iterator/next.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2,
        typename _BinaryPredicate
      >
      bool __is_permutation(
        _ForwardIterator1 __first1, _ForwardIterator1 __last1,
        _ForwardIterator2 __first2, _ForwardIterator2 __last2,
        _BinaryPredicate __pred
      )
      {
        typedef typename
          iterator::iterator_traits<_ForwardIterator1>::difference_type
          __difference_type;

        __difference_type __count1, __count2;
        for(_ForwardIterator1 __i = __first1; __i != __last1; ++__i)
        {
          // determine whether the *__i is operated.
          for(_ForwardIterator1 __j = __first1; __i != __j; ++__j)
          {
            if(__pred(*__j, *__i))
            { goto __next_operation;}
          }

          // Count the number of *__i in the second range
          __count2 = 0;
          for(_ForwardIterator2 __j = __first2; __j != __last2; ++__j)
          {
            if(__pred(*__j, *__i))
            { ++__count2;}
          }
          if(__count2 == 0)
          { return false;}

          // Count the number of *__i in the first range
          __count1 = 1;
          for(_ForwardIterator1 __j = iterator::next(__i);
            __j != __last1; ++__j
          )
          {
            if(__pred(*__j, *__i))
            { ++__count1;}
          }
          if(__count1 != __count2)
          { return false;}
          __next_operation:;
        }
        return true;
      }

      template<typename _Iterator1, typename _Iterator2,
        bool = iterator::is_random_access_iterator<_Iterator1>::value &&
        iterator::is_random_access_iterator<_Iterator2>::value
      >
      struct __is_permutation_helper
      {

        template<typename _BinaryPredicate>
        static inline bool __aux(
          _Iterator1 __first1, _Iterator1 __last1,
          _Iterator2 __first2, _Iterator2 __last2,
          _BinaryPredicate __pred
        )
        {
          for(; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
          {
            if(!__pred(*__first1, *__first2))
            { break;}
          }
          if(__first1 == __last1 && __first2 == __last2)
          { return true;}

          if(
            iterator::distance(__first1, __last1) !=
            iterator::distance(__first2, __last2)
          )
          { return false;}

          return __is_permutation(
            __first1, __last1, __first2, __last2,
            __pred
          );
        }
      };

      template<typename _Iterator1, typename _Iterator2>
      struct __is_permutation_helper<_Iterator1, _Iterator2, true>
      {
        template<typename _BinaryPredicate>
        static inline bool __aux(
          _Iterator2 __first1, _Iterator2 __last1,
          _Iterator2 __first2, _Iterator2 __last2,
          _BinaryPredicate __pred
        )
        {
          if(
            iterator::distance(__first1, __last1) !=
            iterator::distance(__first2, __last2)
          )
          { return false;}

          for(; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
          {
            if(!__pred(*__first1, *__first2))
            { break;}
          }
          if(__first1 == __last1 && __first2 == __last2)
          { return true;}

          return __is_permutation(
            __first1, __last1, __first2, __last2,
            __pred
          );
        }
      };
    }

    /**
     * \brief Determine if a sequence is a permutation of another sequence
     *
     * Returns \b true if there exists a permutation of the elements
     * in the range [\a __first1, \a __last1) that makes that
     * range equal to the range [\a __first2, \a __last2)<br/>
     * Elements are compared using the given binary predicate \a __pred.
     *
     * \param __first1,__last1 the range of elements to compare
     * \param __first2,__last2 	the second range to compare
     * \param __pred           binary predicate which returns ​\b true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return \b true if the range [\a __first1, \a __last1) is
     *         a permutation of the range [\a __first2, \a __last2).
     * \warning The behavior is undefined if \a __pred
     *          is not an equivalence relation.
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2,
      typename _BinaryPredicate
    >
    inline bool is_permutation(
      _ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2,
      _BinaryPredicate __pred
    )
    {
      typedef typename
        trait::type::transform::add_lvalue_reference<_BinaryPredicate>::type
        __pred_ref;

      return detail::__is_permutation_helper<_ForwardIterator1,
        _ForwardIterator2>::template __aux<__pred_ref>(
          __first1, __last1, __first2, __last2, __pred
      );
    }
    /**
     * \overload inline bool is_permutation(
     *   _ForwardIterator1 __first1, _ForwardIterator1 __last1,
     *   _ForwardIterator2 __first2, _ForwardIterator2 __last2
     * )
     *
     * This function use operator== as binary predicate.
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline bool is_permutation(
      _ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2
    )
    {
      return is_permutation(
        __first1, __last1, __first2, __last2,
        algorithm::equal_to<void>()
      );
    }
    /**
     * \brief Determine if a sequence is a permutation of another sequence
     *
     * Returns \b true if there exists a permutation of the elements
     * in the range [\a __first1, \a __last1) that makes that
     * range equal to the range
     * [\a __first2, \a __first2 +(\a __last1-\a __first1))<br/>
     * Elements are compared using the given binary predicate \a __pred.
     *
     * \param __first1,__last1 the range of elements to compare
     * \param __first2         the first iterator of the second range
     * \param __pred           binary predicate which returns ​\b true if
     *                         the elements should be treated as equal.<br/>
     *                         The signature of the predicate function
     *                         should be logically equivalent to the following:
     *                         \code{.cpp}
     *                           bool pred(const Type1&, const Type2&);
     *                         \endcode
     * \return \b true if the range [\a __first1, \a __last1) is
     *         a permutation of the range [\a __first2, \a __last2).
     * \warning The behavior is undefined if \a __pred
     *          is not an equivalence relation.
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2,
      typename _BinaryPredicate
    >
    inline bool is_permutation(
      _ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _BinaryPredicate __pred
    )
    {
      typedef typename
        iterator::iterator_traits<_ForwardIterator1>::difference_type
        __difference_type;
      typedef typename
        trait::type::transform::add_lvalue_reference<_BinaryPredicate>::type
        __pred_ref;

      for(; __first1 != __last1; ++__first1, ++__first2)
      {
        if(!__pred(*__first1, *__first2))
        { break;}
      }
      if(__first1 == __last1)
      { return true;}
      __difference_type __len =
        iterator::distance(__first1, __last1);
      if(__len == 1)
      { return false;}

      return detail::__is_permutation<_ForwardIterator1, _ForwardIterator2, __pred_ref>(
        __first1, __last1, __first2,
        iterator::next(__first2, __len), __pred
      );
    }
    /**
     * \overload inline bool is_permutation(
     *   _ForwardIterator1 __first1, _ForwardIterator1 __last1,
     *   _ForwardIterator2 __first2
     * )
     *
     * This function use operator== as binary predicate.
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline bool is_permutation(
      _ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2
    )
    {
      return is_permutation(
        __first1, __last1, __first2,
        algorithm::equal_to<void>()
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IS_PERMUTATION__
