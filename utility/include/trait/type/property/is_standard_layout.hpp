
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_STANDARD_LAYOUT__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_STANDARD_LAYOUT__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_standard_layout

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_standard_layout
        template<typename _T>
        struct is_standard_layout : public
          trait::integral_constant<bool,
            __utility_is_standard_layout(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_is_standard_layout

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
        // is_standard_layout
        template<typename _T>
        struct is_standard_layout : public
          trait::integral_constant<bool,
            trait::type::categories::is_scalar<typename
              trait::type::transform::remove_all_extents<_T>::type>::value>
        { };

      }
    }
  }
}

#endif // __utility_has_is_standard_layout

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_STANDARD_LAYOUT__
