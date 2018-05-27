
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_ASSIGNABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_ASSIGNABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_trivially_assignable

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_trivially_assignable
        template<typename _T, typename _U>
        struct is_trivially_assignable :
          public trait::integral_constant<bool,
            __utility_is_trivially_assignable(_T, _U)>
        { };

      }
    }
  }
}

#else // __utility_has_is_trivially_assignable

#include<utility/trait/type/categories/is_scalar.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_trivially_assignable
        template<typename _T, typename _U>
        struct is_trivially_assignable :
          public trait::false_type
        { };
        template<typename _T>
        struct is_trivially_assignable<_T&, _T> : public
          trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<typename _T>
        struct is_trivially_assignable<_T&, _T&> : public
          trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<typename _T>
        struct is_trivially_assignable<_T&, const _T&> : public
          trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
        template<typename _T>
        struct is_trivially_assignable<_T&, _T&&> : public
          trait::integral_constant<bool,
            trait::type::categories::is_scalar<_T>::value>
        { };
      }
    }
  }
}

#endif // __utility_has_is_trivially_assignable

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_ASSIGNABLE__
