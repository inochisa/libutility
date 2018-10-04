
#ifndef __UTILITY_CONTAINER_HELPER_IGNORE_T__
#define __UTILITY_CONTAINER_HELPER_IGNORE_T__

/**
 * \file ignore_t.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace container
  {

    namespace helper
    {
      struct ignore_t
      {
        public:
          constexpr ignore_t() = default;

        public:
          template<typename _T>
          __UTILITY_CPP14_CONSTEXPR__
          const ignore_t& operator=(const _T&) const
          { return *this;}
      };

      __UTILITY_CPP17_INLINE__
      constexpr ignore_t ignore{};

    } // helper
  }
}

#endif // ! __UTILITY_CONTAINER_HELPER_IGNORE_T__
