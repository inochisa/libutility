
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL_COPYABLE__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL_COPYABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_trivially_copyable

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_trivially_copyable
        template<typename _T>
        struct is_trivially_copyable : public
          trait::integral_constant<bool, __utility_is_trivially_copyable(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_is_trivially_copyable

#include<utility/trait/type/categories/is_scalar.hpp>
#include<utility/trait/type/transform/remove_all_extents.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_trivially_copyable
        template<typename _T>
        struct is_trivially_copyable : public
          trait::integral_constant<bool,
            categories::is_scalar<typename
              transform::remove_all_extents<_T>::type>::value>
        { };

      }
    }
  }
}

#endif // __utility_has_is_trivially_copyable

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_TRIVIAL_COPYABLE__
