
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_pointer
        template<typename _T>
        struct remove_pointer
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer<_T*>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer<_T* const>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer<_T* volatile>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer<_T* const volatile>
        { typedef _T type;};

        template<typename _T>
        using remove_pointer_t = typename remove_pointer<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER__
