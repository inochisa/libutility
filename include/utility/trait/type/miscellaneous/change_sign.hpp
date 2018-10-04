
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_CHANGE_SIGN__
#define __UTILITY_TRAIT_TYPE_PROPERTY_CHANGE_SIGN__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_integral.hpp>
#include<utility/trait/type/releations/is_same.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // make_signed & make_unsigned
        namespace __change_sign_impl
        {
          using trait::type::releations::is_same;
          template<typename _T>
          struct __make_signed_impl
          { };

          template<>
          struct __make_signed_impl<signed char>
          { typedef signed char type;};
          template<>
          struct __make_signed_impl<unsigned char>
          { typedef signed char type;};
          template<>
          struct __make_signed_impl<signed short>
          { typedef signed short type;};
          template<>
          struct __make_signed_impl<unsigned short>
          { typedef signed short type;};
          template<>
          struct __make_signed_impl<signed int>
          { typedef signed int type;};
          template<>
          struct __make_signed_impl<unsigned int>
          { typedef signed int type;};
          template<>
          struct __make_signed_impl<signed long>
          { typedef signed long type;};
          template<>
          struct __make_signed_impl<unsigned long>
          { typedef signed long type;};
          template<>
          struct __make_signed_impl<signed long long>
          { typedef signed long long type;};
          template<>
          struct __make_signed_impl<unsigned long long>
          { typedef signed long long type;};

          template<typename _T>
          struct __make_unsigned_impl
          { };

          template<>
          struct __make_unsigned_impl<signed char>
          { typedef unsigned char type;};
          template<>
          struct __make_unsigned_impl<unsigned char>
          { typedef unsigned char type;};
          template<>
          struct __make_unsigned_impl<signed short>
          { typedef unsigned short type;};
          template<>
          struct __make_unsigned_impl<unsigned short>
          { typedef unsigned short type;};
          template<>
          struct __make_unsigned_impl<signed int>
          { typedef unsigned int type;};
          template<>
          struct __make_unsigned_impl<unsigned int>
          { typedef unsigned int type;};
          template<>
          struct __make_unsigned_impl<signed long>
          { typedef unsigned long type;};
          template<>
          struct __make_unsigned_impl<unsigned long>
          { typedef unsigned long type;};
          template<>
          struct __make_unsigned_impl<signed long long>
          { typedef unsigned long long type;};
          template<>
          struct __make_unsigned_impl<unsigned long long>
          { typedef unsigned long long type;};

          template<typename _T>
          struct __change_helper :
            public trait::integral_constant<bool,
              trait::type::categories::is_integral<_T>::value
              && !is_same<_T, bool>::value
              && !is_same<_T, wchar_t>::value
#ifndef UTILITY_NO_UNICODE
              && !is_same<_T, char16_t>::value
              && !is_same<_T, char32_t>::value
#endif // ! UTILITY_NO_UNICODE
              >
          { };

          template<typename _T, bool = __change_helper<_T>::value>
          struct __make_signed_helper
          { };
          template<typename _T>
          struct __make_signed_helper<_T, true>
          { typedef typename __make_signed_impl<_T>::type type;};
          template<typename _T, bool = __change_helper<_T>::value>
          struct __make_unsigned_helper
          { };
          template<typename _T>
          struct __make_unsigned_helper<_T, true>
          { typedef typename __make_unsigned_impl<_T>::type type;};
        }
        template<typename _T>
        struct make_signed :
          public __change_sign_impl::__make_signed_helper<_T>
        { };
        template<typename _T>
        struct make_unsigned :
          public __change_sign_impl::__make_unsigned_helper<_T>
        { };

        template<typename _T>
        using make_signed_t = typename make_signed<_T>::type;
        template<typename _T>
        using make_unsigned_t = typename make_unsigned<_T>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_CHANGE_SIGN__
