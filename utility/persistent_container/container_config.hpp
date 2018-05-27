
#ifndef ___UTILITY__PERSISTENT__CONTAINER__CONFIG___
#define ___UTILITY__PERSISTENT__CONTAINER__CONFIG___

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace persistent_container
  {
    namespace config
    {
      struct cache_config
      {
        public:
          typedef unsigned short counter_type;

        public:
          constexpr static size_t max_record = 65535UL;

        public:
          UTILITY_ALWAYS_INLINE
          static inline counter_type init_state(counter_type __now) noexcept
          { return 0;}
          UTILITY_ALWAYS_INLINE
          static inline counter_type discard_state(counter_type __now) noexcept
          { return __now;}
          UTILITY_ALWAYS_INLINE
          static inline void update_state(counter_type& __now) noexcept
          { ++__now;}

        public:
          UTILITY_ALWAYS_INLINE
          static inline bool is_vaild(
            counter_type __init, counter_type __discard
          ) noexcept
          { return __discard == 0;}
          UTILITY_ALWAYS_INLINE
          static inline bool is_vaild(
            counter_type __need, counter_type __init, counter_type __discard
          ) noexcept
          { return __need <= __discard && __need > __init;}
          UTILITY_ALWAYS_INLINE
          static inline bool is_invaild(
            counter_type __init, counter_type __discard
          ) noexcept
          { return __discard != 0;}
          UTILITY_ALWAYS_INLINE
          static inline bool is_invaild(
            counter_type __need, counter_type __init, counter_type __discard
          ) noexcept
          { return !is_vaild(__need, __discard, __init);}
          UTILITY_ALWAYS_INLINE
          static inline bool is_reserved(
            counter_type __need, counter_type __init
          )
          { return __need > __init;}

        public:
          UTILITY_ALWAYS_INLINE
          static inline size_t steps(counter_type __now) noexcept
          { return __now-1;}
          UTILITY_ALWAYS_INLINE
          static inline size_t next(counter_type __now, size_t __len) noexcept
          { return __now+__len;}
          static inline size_t prev(counter_type __now, size_t __len) noexcept
          { return __now-__len;}

      };

      typedef cache_config base_cache_sg;
    }

    using config::base_cache_sg;
  }
  namespace p_container
  {
    namespace config
    {
      using persistent_container::config::base_cache_sg;
    }
    using persistent_container::config::base_cache_sg;
  }
}

#endif // ! ___UTILITY__PERSISTENT__CONTAINER__CONFIG___
