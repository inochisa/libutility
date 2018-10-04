
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FLOATING_POINT__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FLOATING_POINT__

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
        // is_floating_point
        namespace __is_floating_impl
        {
          template<typename _T>
          struct __is_floating_test :
            public trait::false_type
          { };
          template<>
          struct __is_floating_test<float> :
            public trait::true_type
          { };
          template<>
          struct __is_floating_test<double> :
            public trait::true_type
          { };
          template<>
          struct __is_floating_test<long double> :
            public trait::true_type
          { };

        }
        template<typename _T>
        struct is_floating_point :
          public __is_floating_impl::__is_floating_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_floating_point_v = is_floating_point<_T>::value;
#endif

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FLOATING_POINT__
