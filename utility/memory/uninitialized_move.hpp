
#ifndef __UTILITY_MEMORY_UNINITIALIZED_MOVE__
#define __UTILITY_MEMORY_UNINITIALIZED_MOVE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/sstd/new.hpp>

namespace utility
{
  namespace memory
  {
    /*!
    * \brief Move block of memory
    *
    * Constructs moves of the elements in the range
    * [\a __first,\a __last) into a range beginning at result and
    * returns an iterator to the last element in the destination range.<br/>
    * \b uninitialized_move constructs the objects in-place,
    * instead of just moving them. This allows to obtain fully constructed
    * moves of the elements into a range of uninitialized memory
    *
    * \param __first,__last Input iterators to the initial and final positions
    *         in a sequence to be moved. The range used is [\a __first, \a last),
    *         which contains all the elements between \a __first and \a __last,
    *         including the element pointed by \a __first
    *         but not the element pointed by \a __last.
    * \param __result Output iterator to the initial position
    *         in the uninitialized destination sequence. This shall not
    *         point to any element in the range [\a__first, \a __last).
    * \return An iterator to the last element of the destination sequence
    *         where elements have been moved.
    * \attention If an exception is thrown during the initialization,
    *         the function has no effects. And the original source will be
    *         right but uncertain.
    * \see utility::memory::uninitialized_move_n
    */
    template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator
    uninitialized_move(
      _InputIterator __first, _InputIterator __last, _ForwardIterator __result
    )
    {
      typedef typename
        utility::iterator::iterator_traits<_ForwardIterator>::value_type
        __value_type;
#ifdef __UTILITY_USE_EXCEPTION
      _ForwardIterator __epos = __result;
#endif // ! __UTILITY_USE_EXCEPTION
      __UTILITY_TRY_BEGIN
        for(; __first != __last; (void)++__first, ++__result)
        {
          ::new (static_cast<void*>(utility::memory::addressof(*__result)))
          __value_type(utility::algorithm::move(*__first));
        }
      __UTILITY_TRY_END
      __UTILITY_CATCH(...)
      __UTILITY_CATCH_UNWIND(
        for(; __epos != __result; ++__epos)
        { __epos->~__value_type();}
      )
      return __first;
    }

    template<typename _BidirIterator1, typename _BidirIterator2>
    _BidirIterator2
    uninitialized_move_backward(
      _BidirIterator1 __first, _BidirIterator1 __last, _BidirIterator2 __result
    )
    {
      typedef typename
        utility::iterator::iterator_traits<_BidirIterator2>::value_type
        __value_type;
#ifdef __UTILITY_USE_EXCEPTION
      _BidirIterator2 __epos = __result;
#endif // ! __UTILITY_USE_EXCEPTION
      __UTILITY_TRY_BEGIN
        for(; __first != __last;)
        {
          ::new (static_cast<void*>(utility::memory::addressof(*--__result)))
          __value_type(utility::algorithm::move(*--__last));
        }
      __UTILITY_TRY_END
      __UTILITY_CATCH(...)
      __UTILITY_CATCH_UNWIND(
        for(; __epos != __result; )
        { (--__epos)->~__value_type();}
      )
      return __result;
    }
  }
}

#endif // ! __UTILITY_MEMORY_UNINITIALIZED_MOVE__
