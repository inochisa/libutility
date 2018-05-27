
#ifndef __UTILITY_ALGORITHM_COPY_BACKWARD__
#define __UTILITY_ALGORITHM_COPY_BACKWARD__

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
      struct __copy_backward
      {
        template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
        static _BidirectionalIterator2 __aux(
          _BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
          _BidirectionalIterator2 __flast
        )
        {
          for(;__first != __last;)
          { *(--__flast) = *(--__last);}
          return __flast;
        }
      };
      template<typename _Iterator>
      struct __copy_backward<_Iterator, true>
      {
        template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
        static _BidirectionalIterator2 __aux(
          _BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
          _BidirectionalIterator2 __flast
        )
        {
          typedef typename
            iterator::iterator_traits<_BidirectionalIterator2>::value_type
            __value_type;
          sstd::memmove(
            __flast - (__last - __first), __first,
            __size*sizeof(__value_type)
          );
          return __flast - (__last - __first);
        }
      };
    }
    /**
     * \brief Copy range of elements backward
     *
     * Copies the elements from the range, defined by [ \a __first, \a __last),
     * to another range ending at \a __flast.
     * The elements are copied in reverse order (the last element is copied first),
     * but their relative order is preserved.<br/>
     *
     * \tparam _BidirectionalIterator1 the input iterator type
     * \tparam _BidirectionalIterator2 the output iterator type
     * \param __first,__last 	the range of the elements to copy
     * \param __flast         end of the destination range
     * \return iterator to the last element copied
     * \warning The behavior is undefined if \a __flast is within ( \a __first, \a __last].
     * copy must be used instead;
     */
    template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
    _BidirectionalIterator2 copy_backward(
      _BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
      _BidirectionalIterator2 __flast
    )
    {
      return detail::__copy_backward<_BidirectionalIterator2>::__aux(
        __first, __last, __flast
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_COPY_BACKWARD__
