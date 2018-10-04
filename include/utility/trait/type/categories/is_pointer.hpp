
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_POINTER__

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
        // is_pointer
        namespace __is_pointer_impl
        {
          template<typename _T>
          struct __is_pointer_test :
            public trait::false_type
          { };
          template<typename _T>
          struct __is_pointer_test<_T*> :
            public trait::true_type
          { };
        }
        template<typename _T>
        struct is_pointer :
          public __is_pointer_impl::__is_pointer_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_pointer_v = is_pointer<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_POINTER__
