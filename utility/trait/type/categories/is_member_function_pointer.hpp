
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__

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
        // is_member_function_pointer
        namespace __is_member_function_pointer_impl
        {
          template<typename _T>
          struct __is_member_function_pointer_test :
            public ::utility::trait::false_type
          { };
          template<typename _T, class _Inn>
          struct __is_member_function_pointer_test<_T _Inn::*> :
            public is_function<_T>
          { };
        }
        template<typename _T>
        struct is_member_function_pointer :
          public __is_member_function_pointer_impl::
            __is_member_function_pointer_test<
              typename
                ::utility::trait::type::transform::remove_cv<_T>::type>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__
