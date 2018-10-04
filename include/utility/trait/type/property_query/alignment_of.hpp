
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_ALIGNMENT_OF__
#define __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_ALIGNMENT_OF__

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
        // alignment_of
        template<typename _T>
        struct alignment_of :
          public trait::integral_constant<
            size_t, __utility_alignof(_T)>
        { };

      }
    }
  }
}


#endif // __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_ALIGNMENT_OF__
