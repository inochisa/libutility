
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
            public utility::trait::false_type
          { };
          template<>
          struct __is_floating_test<float> :
            public utility::trait::true_type
          { };
          template<>
          struct __is_floating_test<double> :
            public utility::trait::true_type
          { };
          template<>
          struct __is_floating_test<long double> :
            public utility::trait::true_type
          { };

        }
        template<typename _T>
        struct is_floating_point :
          public __is_floating_impl::__is_floating_test<
            typename
              utility::trait::type::transform::remove_cv<_T>::type>
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FLOATING_POINT__
