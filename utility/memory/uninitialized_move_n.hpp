
#ifndef __UTILITY_MEMORY_UNINITIALIZED_MOVE_N__
#define __UTILITY_MEMORY_UNINITIALIZED_MOVE_N__

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
    * Constructs moves of the \a __size first elements of the array
    * pointed by \a __first into a range beginning at \a __result
    * and returns an iterator to the last element in the destination range.<br/>
    * \b uninitialized_copy constructs the objects in-place,
    * instead of just moving them. This allows to obtain fully constructed
    * moves of the elements into a range of uninitialized memory.
    *
    * \tparam _InputIterator,_ForwardIterator
    * \param __first  Forward iterator to the initial position in
    *         an uninitialized sequence of at least \a __size elements.
    * \param __size   Number of elements to move.
    * \param __result Output iterator to the initial position
    *         in the uninitialized destination sequence.
    *         This shall not point to any element in
    *         the range [\a __first, \a __first+\a __size).
    * \return
    * \attention If an exception is thrown during the initialization,
    *         the function has no effects. And the original source will be
    *         right but uncertain.
    * \see utility::memory::uninitialized_move
    */
    template<typename _InputIterator, typename _Size, typename _ForwardIterator>
    _ForwardIterator
    uninitialized_move_n(_InputIterator __first, _Size __size, _ForwardIterator __result)
    {
      typedef typename
        utility::iterator::iterator_traits<_ForwardIterator>::value_type
        __value_type;
#ifdef __UTILITY_USE_EXCEPTION
      _ForwardIterator __epos = __result;
#endif // ! __UTILITY_USE_EXCEPTION
      __UTILITY_TRY_BEGIN
        for(; __size > 0; (void)++__first, ++__result, --__size)
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
  }
}

#endif // ! __UTILITY_MEMORY_UNINITIALIZED_MOVE__
