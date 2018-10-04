
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_POINTER__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_pointer.hpp>
#include<utility/trait/type/transform/remove_all_pointer.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_const_pointer
        template<typename _T>
        struct remove_const_pointer
        {
          typedef typename
            remove_const<typename remove_pointer<_T>::type>::type type;
        };

        // remove_volatile_pointer
        template<typename _T>
        struct remove_volatile_pointer
        {
          typedef typename
            remove_volatile<typename remove_pointer<_T>::type>::type type;
        };

        // remove_cv_pointer
        template<typename _T>
        struct remove_cv_pointer
        {
          typedef typename
            remove_cv<typename remove_pointer<_T>::type>::type type;
        };

        // remove_const_all_pointer
        template<typename _T>
        struct remove_const_all_pointer
        {
          typedef typename
            remove_const<typename remove_all_pointer<_T>::type>::type type;
        };

        // remove_volatile_all_pointer
        template<typename _T>
        struct remove_volatile_all_pointer
        {
          typedef typename
            remove_volatile<typename remove_all_pointer<_T>::type>::type type;
        };

        // remove_cv_all_pointer
        template<typename _T>
        struct remove_cv_all_pointer
        {
          typedef typename
            remove_cv<typename remove_all_pointer<_T>::type>::type type;
        };

        template<typename _T>
        using remove_cv_all_pointer_t = typename remove_cv_all_pointer<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_POINTER__
