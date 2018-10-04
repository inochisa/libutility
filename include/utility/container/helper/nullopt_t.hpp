
#ifndef __UTILITY_CONTAINER_HELPER_NULLOPT_T__
#define __UTILITY_CONTAINER_HELPER_NULLOPT_T__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace container
  {
    namespace helper
    {
      struct nullopt_t
      {
        public:
          explicit constexpr nullopt_t() noexcept
          { }
#if defined(UTILITY_USE_NULL_NULLOPT)
          explicit constexpr nullopt_t(nullptr_t) noexcept
          { }
#endif
      };

      __UTILITY_CPP17_INLINE__ constexpr nullopt_t nullopt{};
    }
  }
} // utility


#endif // ! __UTILITY_CONTAINER_HELPER_NULLOPT_T__
