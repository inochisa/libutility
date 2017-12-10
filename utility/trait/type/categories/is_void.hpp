
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_VOID__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_VOID__

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
        // is_void
        namespace __is_void_impl
        {
          template<typename _T>
          struct __is_void_test : public ::utility::trait::false_type
          { };
          template<>
          struct __is_void_test<void> : public ::utility::trait::true_type
          { };
        }
        template<typename _T>
        struct is_void :
          public __is_void_impl::__is_void_test<
            typename
              ::utility::trait::type::transform::remove_cv<_T>::type>
        { };
      }
    }
  }
}


#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_VOID__
