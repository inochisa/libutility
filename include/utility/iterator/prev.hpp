
#ifndef __UTILITY_ITERATOR_PREV__
#define __UTILITY_ITERATOR_PREV__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace iterator
  {
    namespace detail
    {
      template<typename _Iterator,
        bool = is_vaild_iterator_type<_Iterator,random_access_iterator_tag>::value>
      struct __prev
      {
        template<typename _Difference>
        __UTILITY_CPP17_CONSTEXPR__
        static inline _Iterator __aux(_Iterator __it, _Difference __len)
        {
          for(;__len;--__len)
          { --__it;}
          return __it;
        }
      };
      template<typename _Iterator>
      struct __prev<_Iterator, true>
      {
        template<typename _Difference>
        __UTILITY_CPP17_CONSTEXPR__
        static inline _Iterator __aux(_Iterator __it, _Difference __len)
        { return __it - __len;}
      };
    }
    template<typename _BidirectionalIterator>
    __UTILITY_CPP17_CONSTEXPR__
    inline
    _BidirectionalIterator prev(_BidirectionalIterator __it,
      typename iterator_traits<_BidirectionalIterator>::difference_type __len = 1
    )
    {
      return detail::__prev<_BidirectionalIterator>::__aux(__it, __len);
    }
  }
}

#endif // ! __UTILITY_ITERATOR_PREV__
