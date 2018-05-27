
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_SIGNED__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_SIGNED__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_signed
        namespace __is_signed_impl
        {
          template<typename _T, bool =
            trait::type::categories::is_integral<_T>::value>
          struct __is_signed_intger_test :
            public trait::bool_constant<(_T(-1) < _T(0))>
          { };
          template<typename _T>
          struct __is_signed_intger_test<_T, false> :
            public trait::true_type
          { };
          template<typename _T, bool =
            trait::type::categories::is_arithmetic<_T>::value>
          struct __is_signed_test : public __is_signed_intger_test<_T>
          { };
          template<typename _T>
          struct __is_signed_test<_T, false> :
            public trait::false_type
          { };
        }
        template<typename _T>
        struct is_signed :
          public __is_signed_impl::__is_signed_test<_T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_SIGNED__
