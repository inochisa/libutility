
#ifndef __UTILITY_ALGORITHM_COPY_N__
#define __UTILITY_ALGORITHM_COPY_N__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/categories/is_pointer.hpp>
#include<utility/trait/type/property/is_pod.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/sstd/cstring.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<
        typename _Iterator,
        bool =
          trait::type::property::is_pod
          <
            typename iterator::iterator_traits<_Iterator>::value_type
          >::value &&
          trait::type::categories::is_pointer<_Iterator>::value
      >
      struct __copy_if
      {
        template<typename _InputIterator,
          typename _Size, typename _OutputIterator>
        static _OutputIterator __aux(
          _InputIterator __first, _Size __size,
          _OutputIterator __ffirst
        )
        {
          for(_Size __i = 0; __i < __size; ++__i)
          { *__ffirst++ = *__first++;}
          return __ffirst;
        }
      };
      template<typename _Iterator>
      struct __copy_if<_Iterator, true>
      {
        template<typename _InputIterator,
          typename _Size, typename _OutputIterator>
        static _OutputIterator __aux(
          _InputIterator __first, _Size __size,
          _OutputIterator __ffirst
        )
        {
          typedef typename
            iterator::iterator_traits<_OutputIterator>::value_type
            __value_type;
          if(__size > 0)
          {
            sstd::memmove(
              __ffirst, __first, __size*sizeof(__value_type)
            );
            return __ffirst + __size;
          }
          return __ffirst;
        }
      };
    }
    /**
     * \brief Copy elements
     *
     * Copies exactly \a __size values from the range
     * beginning at \a __first to the range beginning at \a __ffirst,
     * if \a __size > 0. Does nothing otherwise.
     *
     * \tparam _InputIterator   the input iterator type
     * \tparam _Size            the length type, usually size_t or ptrdiff_t
     * \tparam _OutputIterator  the output iterator type
     * \param __first   the beginning of the range of elements to copy from
     * \param __size    number of the elements to copy
     * \param __ffirst  the beginning of the destination range
     * \return Iterator in the destination range,
     *         pointing past the last element copied if \a __size > 0
     *         or \a __ffirst otherwise.
     */
    template<typename _InputIterator, typename _Size, typename _OutputIterator>
    _OutputIterator copy_n(
      _InputIterator __first, _Size __size,
      _OutputIterator __ffirst
    )
    {
      return detail::__copy_if<_OutputIterator>::__aux(
        __first, __size, __ffirst
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_COPY_N__
