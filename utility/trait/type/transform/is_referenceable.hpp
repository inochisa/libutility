
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_IS_REFERENECABLE__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_IS_REFERENECABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/releations/is_same.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        namespace __is_referenceable_impl
        {
          template<typename _T>
          _T& __is_referenceable_test(int);
          template<typename _T>
          ::utility::trait::__impl_helper::__twochar
            __is_referenceable_test(...);

        }
        template<typename _T>
        struct is_referenceable :
          public ::utility::trait::integral_constant<bool,
          !::utility::trait::type::releations::is_same<
            decltype(__is_referenceable_impl::__is_referenceable_test<_T>(0)),
            ::utility::trait::__impl_helper::__twochar>::value>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_IS_REFERENECABLE__
