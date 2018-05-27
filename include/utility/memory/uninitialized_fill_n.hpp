
#ifndef __UTILITY_MEMORY_UNINITIALIZED_FILL_N__
#define __UTILITY_MEMORY_UNINITIALIZED_FILL_N__

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
    * Constructs n elements in the array pointed by \a __first,
    * initializing them to a value of \a __val.<br/>
    * \b uninitialized_fill_n constructs the objects in-place,
    * instead of just copying the value to them.
    * This allows to obtain fully constructed copies into
    * a range of uninitialized memory.
    *
    * \param __first Forward iterator to the initial position
    *         in an uninitialized sequence of at least n elements.
    * \param __size Number of elements to initialize
    * \param __val Value to be used to fill the range
    * \return An iterator to the last element of the destination sequence
    *         where elements have been initialized.
    * \attention If an exception is thrown during the initialization,
    *         the function has no effects.
    * \see memory::uninitialized_fill
    */
    template<typename _ForwardIterator, typename _Size, typename _T>
    _ForwardIterator
    uninitialized_fill_n(_ForwardIterator __first, _Size __size, const _T& __val)
    {
      typedef typename
        iterator::iterator_traits<_ForwardIterator>::value_type
        __value_type;
#ifdef __UTILITY_USE_EXCEPTION
      _ForwardIterator __epos = __first;
#endif // ! __UTILITY_USE_EXCEPTION
      __UTILITY_TRY_BEGIN
        for(; __size > 0; ++__first, --__size)
        {
          ::new (static_cast<void*>(memory::addressof(*__first)))
          __value_type(__val);
        }
      __UTILITY_TRY_END
      __UTILITY_CATCH(...)
      __UTILITY_CATCH_UNWIND(
        for(; __epos != __first; ++__epos)
        { __epos->~__value_type();}
      )
      return __first;
    }
  }
}

#endif // ! __UTILITY_MEMORY_UNINITIALIZED_FILL__
