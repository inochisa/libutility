
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_HAS_VIRTUAL_DESTRUCTOR__
#define __UTILITY_TRAIT_TYPE_FEATURES_HAS_VIRTUAL_DESTRUCTOR__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_has_virtual_destructor

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // has_virtual_destructor
        template<typename _T>
        struct has_virtual_destructor :
          public trait::integral_constant<bool,
            __utility_has_virtual_destructor(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_has_virtual_destructor

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // has_virtual_destructor
        /*!
        * \todo
        */
        template<typename _T>
        struct has_virtual_destructor :
          public trait::unsupport_trait<false>
        { };

      }
    }
  }
}

#endif // ! __utility_has_has_virtual_destructor

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_FEATURES_HAS_VIRTUAL_DESTRUCTOR__
