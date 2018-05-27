
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_NULL_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_NULL_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_null_pointer && is_nullptr_t
        namespace __is_null_pointer_impl
        {
          template<typename _T>
          struct __is_null_pointer_test :
            public trait::false_type
          { };
          template<>
          struct __is_null_pointer_test<trait::nullptr_t> :
            public trait::true_type
          { };
        }
        template<typename _T>
        struct is_nullptr_t :
          public __is_null_pointer_impl::__is_null_pointer_test<
            typename
            trait::type::transform::remove_cv<_T>::type>
        { };
        template<typename _T>
        struct is_null_pointer :
          public __is_null_pointer_impl::__is_null_pointer_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_NULL_POINTER__
