
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_trivially_constructible

#include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_trivially_constructible
        template<class _T, typename... _Args>
        struct is_trivially_constructible :
          public trait::integral_constant<bool,
            __utility_is_trivially_constructible(_T, _Args...)>
        { };
      }
    }
  }
}

#else // __utility_has_has_trivial_constructor

#include<utility/trait/type/categories/is_scalar.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_trivially_constructible
        template<class _T, typename... Args>
        struct is_trivially_constructible :
          public trait::false_type
        { };
        template<class _T>
        struct is_trivially_constructible<_T> :
          public trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<class _T>
        struct is_trivially_constructible<_T, _T&> :
          public trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<class _T>
        struct is_trivially_constructible<_T, _T&&> :
          public trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<class _T>
        struct is_trivially_constructible<_T, const _T&> :
          public trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
      }
    }
  }
}

#endif // __utility_has_has_trivial_constructor

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_CONSTRUCTIBLE__
