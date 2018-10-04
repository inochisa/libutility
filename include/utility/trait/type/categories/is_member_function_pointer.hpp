
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/categories/is_function.hpp>

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
            public trait::false_type
          { };
          template<typename _T, class _Inn>
          struct __is_member_function_pointer_test<_T _Inn::*> :
            public trait::integral_constant<bool,
              trait::type::categories::is_function<_T>::value>
          { };
        }
        template<typename _T>
        struct is_member_function_pointer :
          public __is_member_function_pointer_impl::
            __is_member_function_pointer_test<
              typename trait::type::transform::remove_cv<_T>::type
            >::type
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_member_function_pointer_v =
                      is_member_function_pointer<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_FUNCTION_POINTER__
