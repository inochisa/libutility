
#ifndef __UTILITY_ITERATOR_NEXT__
#define __UTILITY_ITERATOR_NEXT__

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
      struct __next
      {
        template<typename _Difference>
        __UTILITY_CPP17_CONSTEXPR__
        static inline _Iterator __aux(_Iterator __it, _Difference __len)
        {
          for(;__len;--__len)
          { ++__it;}
          return __it;
        }
      };
      template<typename _Iterator>
      struct __next<_Iterator, true>
      {
        template<typename _Difference>
        __UTILITY_CPP17_CONSTEXPR__
        static inline _Iterator __aux(_Iterator __it, _Difference __len)
        { return __it + __len;}
      };
    }
    template<typename _ForwardIterator>
    __UTILITY_CPP17_CONSTEXPR__
    inline
    _ForwardIterator next(_ForwardIterator __it,
      typename iterator_traits<_ForwardIterator>::difference_type __len = 1
    )
    {
      return detail::__next<_ForwardIterator>::__aux(__it, __len);
    }
  }
}

#endif // ! __UTILITY_ITERATOR_NEXT__
