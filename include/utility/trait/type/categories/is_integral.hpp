
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_INTEGRAL__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_INTEGRAL__

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
        // the libinteger has some lager integer specifiic
        // is_integral
        // for some reason the __int128_t ans __uint128_t
        // will not support
        namespace __is_integral_impl
        {
          template<typename _T>
          struct __is_integral_test :
            public trait::false_type
          { };
          template<>
          struct __is_integral_test<bool> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<char> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<signed char> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<unsigned char> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<wchar_t> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<signed short> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<unsigned short> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<signed int> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<unsigned int> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<signed long int> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<unsigned long int> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<signed long long int> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<unsigned long long int> :
            public trait::true_type
          { };
#ifndef UTILITY_NO_UNICODE
          template<>
          struct __is_integral_test<char16_t> :
            public trait::true_type
          { };
          template<>
          struct __is_integral_test<char32_t> :
            public trait::true_type
          { };

#endif // ! UTILITY_NO_UNICODE
        }
        template<typename _T>
        struct is_integral :
          public __is_integral_impl::__is_integral_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_integral_v = is_integral<_T>::value;
#endif

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_INTEGRAL__
