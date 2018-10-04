
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
          struct __is_void_test : public trait::false_type
          { };
          template<>
          struct __is_void_test<void> : public trait::true_type
          { };
        }
        template<typename _T>
        struct is_void :
          public __is_void_impl::__is_void_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_void_v = is_void<_T>::value;
#endif

      }
    }
  }
}


#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_VOID__
