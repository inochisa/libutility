
#ifndef __UTILITY_MEMORY_DESTROY_AT__
#define __UTILITY_MEMORY_DESTROY_AT__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/features/is_trivially_destructible.hpp>

namespace utility
{
  namespace memory
  {
    namespace detail
    {
      template<typename _T,
        bool = trait::type::features::is_trivially_destructible<_T>::value
      >
      struct __destroy_at
      {
        static inline void __aux(_T* __ptr)
        { __ptr->~_T();}
      };
      template<typename _T>
      struct __destroy_at<_T, true>
      {
        static inline void __aux(_T*)
        { }
      };
    }
    template<typename _T>
    inline void destroy_at(_T* __ptr)
    { detail::__destroy_at<_T>::__aux(__ptr);}
  }
}

#endif // ! __UTILITY_MEMORY_DESTROY_AT__
