
#ifndef __UTILITY_ITERATOR_DISTANCE__
#define __UTILITY_ITERATOR_DISTANCE__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace iterator
  {
    namespace detail
    {
      template<typename _Difference, bool = false>
      struct __distance
      {
        template<typename _Iterator>
        static _Difference __aux(_Iterator __first, _Iterator __last)
        {
          _Difference __dis = 0;
          for(; __first != __last; ++__first, ++__dis);
          return __dis;
        }
      };
      template<typename _Difference>
      struct __distance<_Difference, true>
      {
        template<typename _Iterator>
        static _Difference __aux(_Iterator __first, _Iterator __last)
        {
          return __last - __first;
        }
      };

    }
    template<typename _Iterator>
    inline
    typename
    trait::type::miscellaneous::enable_if<
      iterator::is_iterator<_Iterator>::value,
      typename
      iterator::iterator_traits<_Iterator>::difference_type
    >::type
    distance(_Iterator __first, _Iterator __last)
    {
      typedef trait::type::releations::is_convertible<
        typename
        iterator::iterator_traits<_Iterator>::iterator_category,
        iterator::random_access_iterator_tag>
        __identify;
      typedef typename
        iterator::iterator_traits<_Iterator>::difference_type
        __difference_type;
      return detail::__distance<__difference_type, __identify::value
        >::__aux(__first, __last);
    }
  }
}

#endif // ! __UTILITY_ITERATOR_DISTANCE__
