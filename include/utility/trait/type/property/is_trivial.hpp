
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_trivial

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_trivial
        template<typename _T>
        struct is_trivial : public
          trait::integral_constant<bool, __utility_is_trivial(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_is_trivial

#include<utility/trait/type/property/is_trivially_copyable.hpp>
#include<utility/trait/type/features/is_trivially_default_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_trivial
        template<typename _T>
        struct is_trivial : public
          trait::integral_constant<bool,
            is_trivially_copyable<_T>::value &&
            features::is_trivially_default_constructible<_T>::value>
        { };

      }
    }
  }
}

#endif // __utility_has_is_trivial

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL__
