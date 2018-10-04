
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL_POINTER__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL_POINTER__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_all_pointer
        template<typename _T>
        struct remove_all_pointer
        { typedef _T type;};
        template<typename _T>
        struct remove_all_pointer<_T*>
        { typedef typename remove_all_pointer<_T>::type type;};
        template<typename _T>
        struct remove_all_pointer<_T* const>
        { typedef typename remove_all_pointer<_T>::type type;};
        template<typename _T>
        struct remove_all_pointer<_T* volatile>
        { typedef typename remove_all_pointer<_T>::type type;};
        template<typename _T>
        struct remove_all_pointer<_T* const volatile>
        { typedef typename remove_all_pointer<_T>::type type;};

        template<typename _T>
        using remove_all_pointer_t = typename remove_all_pointer<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER__
