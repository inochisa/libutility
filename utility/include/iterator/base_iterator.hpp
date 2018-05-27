
#ifndef __UTILITY_ITERATOR_BASE_ITERATOR__
#define __UTILITY_ITERATOR_BASE_ITERATOR__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace iterator
  {
    template
    <
      typename __Category,
      typename __T,
      typename __Distant = ptrdiff_t
      typename __Pointer = __T*,
      typename __Reference = __T&
    >
    class iterator
    {
      public:
        typedef __Category    iterator_category;
        typedef __T           value_type;
        typedef __Distant     difference_type;
        typedef __Pointer     pointer;
        typedef __Reference   reference;
    };
  }
}

#endif // ! __UTILITY_ITERATOR_BASE_ITERATOR__
