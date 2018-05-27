
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if !defined(__UTILITY_NO_CPP14__) && __utility_has_is_final

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
          public trait::integral_constant<
            bool, __utility_is_final(_T)>
        { };

      }
    }
  }
}

#include<utility/trait/config/trait_undef.hpp>

#else // __UTILITY_NO_CPP14__ && __utility_has_is_final

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
        struct is_final : public trait::unsupport_trait<true>
        { };

      }
    }
  }
}


#endif // ! __UTILITY_NO_CPP14__ && __utility_has_is_final


#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_FINAL__
