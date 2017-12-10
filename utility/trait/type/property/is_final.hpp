
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#ifndef __UTILITY_NO_CPP14__

# if __utility_has_is_final

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_final
        template<typename _T>
        struct is_final :
          public ::utility::trait::integral_constant<
            bool, __utility_is_final(_T)>
        { };

      }
    }
  }
}

# else // __utility_has_is_final

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_final
        template<typename _T>
        struct is_final : public ::utility::trait::unsupport_trait
        { };

      }
    }
  }
}

# endif // ! __utility_has_is_final

#endif // ! __UTILITY_NO_CPP14__

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__
