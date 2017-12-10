
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_CONDITIONAL__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_CONDITIONAL__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // conditional
        template<bool B, typename _IF, typename _ELSE>
        struct conditional
        { typedef _IF type;};
        template<typename _IF, typename _ELSE>
        struct conditional<false, _IF, _ELSE>
        { typedef _ELSE type;};

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_CONDITIONAL__
