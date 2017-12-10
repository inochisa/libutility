
#ifndef __UTILITY_MEMORY_UNINITIALIZED_FILL__
#define __UTILITY_MEMORY_UNINITIALIZED_FILL__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/sstd/new.hpp>

namespace utility
{
  namespace memory
  {
    /*!
    * \brief Fill block of memory
    *
    * Constructs all the elements in the range [\a __first,\a __last)
    * initializing them to a value of \a __val.<br/>
    * \b uninitialized_fill constructs the objects in-place,
    * instead of just copying the value to them. This allows to obtain
    * fully constructed copies into a range of uninitialized memory
    *
    * \param __first,__last Forward iterators to the initial and final positions
    *         in an uninitialized sequence. The range affected is
    *         [\a __first,\a __last), which contains all the elements
    *         between \a __first and \a __last, including the element
    *         pointed by \a __first but not the element pointed by \a __last.
    * \param __val Value to be used to fill the range.
    * \return none
    * \attention If an exception is thrown during the initialization,
    *         the function has no effects.
    * \see utility::memory::uninitialized_fill_n
    */
    template<typename _ForwardIterator, typename _T>
    void
    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _T& __val)
    {
      typedef typename
        ::utility::iterator::iterator_traits<_ForwardIterator>::value_type
        __value_type;
#ifdef __UTILITY_USE_EXCEPTION
      _ForwardIterator __epos = __first;
#endif // ! __UTILITY_USE_EXCEPTION
      __UTILITY_TRY_BEGIN
        for(; __first != __last; ++__first)
        {
          ::new (static_cast<void*>(::utility::memory::addressof(*__first)))
          __value_type(__val);
        }
      __UTILITY_TRY_END
      __UTILITY_CATCH(...)
      __UTILITY_CATCH_UNWIND(
        for(; __epos != __first; ++__epos)
        { __epos->~__value_type();}
      )
    }
  }
}

#endif // ! __UTILITY_MEMORY_UNINITIALIZED_FILL__
