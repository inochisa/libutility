
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_REF__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_REF__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_const_reference
        template<typename _T>
        struct remove_const_reference
        {
          typedef typename
            remove_const<typename remove_reference<_T>::type>::type type;
        };
        // remove_volatile_reference
        template<typename _T>
        struct remove_volatile_reference
        {
          typedef typename
            remove_volatile<typename remove_reference<_T>::type>::type type;
        };
        // remove_cv_reference
        template<typename _T>
        struct remove_cv_reference
        {
          typedef typename
            remove_cv<typename remove_reference<_T>::type>::type type;
        };

        template<typename _T>
        using remove_cv_ref = remove_cv_reference<_T>;
        template<typename _T>
        using remove_cv_ref_t = typename remove_cv_reference<_T>::type;
        template<typename _T>
        using remove_cv_reference_t = typename remove_cv_reference<_T>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_CV_REF__
