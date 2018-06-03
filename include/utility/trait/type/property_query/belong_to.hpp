
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_BELONG_TO__
#define __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_BELONG_TO__

#include<utility/trait/trait_helper.hpp>
#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property_query
      {
        // belong_to
        template<typename _T>
        struct belong_to
        { };
        template<typename _T, class _Inn>
        struct belong_to<_T _Inn::*>
        { typedef _Inn type;};

      }
    }
  }
}


#endif // __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_BELONG_TO__
