
#ifndef __UTILITY_MEMORY_UNINITIALIZED_COPY__
#define __UTILITY_MEMORY_UNINITIALIZED_COPY__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/trait/type/categories/is_arithmetic.hpp>
#include<utility/trait/type/categories/is_pointer.hpp>
#include<utility/trait/type/property/is_pod.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/sstd/new.hpp>
#include<utility/sstd/cstring.hpp>

namespace utility
{
  namespace memory
  {
    namespace detail
    {
      template<typename _InputIterator, typename _ForwardIterator>
      _ForwardIterator
      __uninitialized_copy(_InputIterator __first,
        _InputIterator __last, _ForwardIterator __result,
        utility::trait::false_type
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
            __value_type(*__first);
          }
        __UTILITY_TRY_END
        __UTILITY_CATCH(...)
        __UTILITY_CATCH_UNWIND(
          for(; __epos != __result; ++__epos)
          { __epos->~__value_type();}
        )
        return __result;
      }

      template<typename _InputIterator, typename _ForwardIterator>
      inline
      _ForwardIterator
      __uninitialized_copy(_InputIterator __first,
        _InputIterator __last, _ForwardIterator __result,
        utility::trait::true_type
      )
      {
        typedef typename
          utility::iterator::iterator_traits<_ForwardIterator>::value_type
          __value_type;
        utility::sstd::memmove(
          __result, __first, (__last-__first)*sizeof(__value_type));
        return __result + (__last-__first);
      }
    }

    /*!
    * \brief Copy block of memory
    *
    * Constructs copies of the elements in the range
    * [\a __first,\a __last) into a range beginning at result and
    * returns an iterator to the last element in the destination range.<br/>
    * \b uninitialized_copy constructs the objects in-place,
    * instead of just copying them. This allows to obtain fully constructed
    * copies of the elements into a range of uninitialized memory
    *
    * \param __first,__last Input iterators to the initial and final positions
    *         in a sequence to be copied. The range used is [\a __first, \a last),
    *         which contains all the elements between \a __first and \a __last,
    *         including the element pointed by \a __first
    *         but not the element pointed by \a __last.
    * \param __result Output iterator to the initial position
    *         in the uninitialized destination sequence. This shall not
    *         point to any element in the range [\a__first, \a __last).
    * \return An iterator to the last element of the destination sequence
    *         where elements have been copied.
    * \attention If an exception is thrown during the initialization,
    *         the function has no effects.
    * \note   If the \a _ForwardIterator and \a _InputIterator are both pointer
    *         the memmove is used to speed up copying.
    * \see utility::memory::uninitialized_copy_n
    */
    template<typename _InputIterator, typename _ForwardIterator>
    inline
    _ForwardIterator
    uninitialized_copy(_InputIterator __first,
      _InputIterator __last, _ForwardIterator __result)
    {
      typedef typename
      utility::iterator::iterator_traits<_ForwardIterator>::value_type
      __value_type;
      typedef
        utility::trait::integral_constant<bool,
          utility::trait::type::categories::is_pointer<_InputIterator>::value &&
          utility::trait::type::categories::is_pointer<_ForwardIterator>::value &&
          (utility::trait::type::categories::is_arithmetic<__value_type>::value ||
           utility::trait::type::categories::is_pointer<__value_type>::value ||
           utility::trait::type::property::is_pod<__value_type>::value)>
        __identify;
      return detail::__uninitialized_copy(__first, __last, __result, __identify());
    }
  }
}

#endif // ! __UTILITY_MEMORY_UNINITIALIZED_COPY__
