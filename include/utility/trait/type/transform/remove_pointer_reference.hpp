
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER_REFERENCE__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER_REFERENCE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_pointer_reference
        template<typename _T>
        struct remove_pointer_reference
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T&>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T&&>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T*>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T* const>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T* volatile>
        { typedef _T type;};
        template<typename _T>
        struct remove_pointer_reference<_T* const volatile>
        { typedef _T type;};

        template<typename _T>
        using remove_ptr_ref = remove_pointer_reference<_T>;
        template<typename _T>
        using remove_pointer_reference_t =
          typename remove_pointer_reference<_T>::type;
        template<typename _T>
        using remove_ptr_ref_t = typename remove_pointer_reference<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_POINTER_REFERENCE__
