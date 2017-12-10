
#ifndef __UTILITY_LIMITS_BOOL_LIMITS__
#define __UTILITY_LIMITS_BOOL_LIMITS__

#include<utility/config/utility_config.hpp>
#include<utility/limits/numeric_limits.hpp>

namespace utility
{
  namespace limits
  {
    template<>
    class numeric_limits<bool>
    {
    public:
      constexpr static bool is_specialized = true;

      constexpr static bool min() noexcept
      { return false; }
      constexpr static bool max() noexcept
      { return true; }
      constexpr static bool lowest() noexcept
      { return false; }

      constexpr static int digits = 1;
      constexpr static int digits10 = 0;
      constexpr static int max_digits10 = 0;

      constexpr static bool is_signed = false;
      constexpr static bool is_integer = true;
      constexpr static bool is_exact = true;
      constexpr static bool epsilon() noexcept
      { return false; }
      constexpr static bool round_error() noexcept
      { return false; }

      constexpr static int min_exponent = 0;
      constexpr static int min_exponent10 = 0;
      constexpr static int max_exponent = 0;
      constexpr static int max_exponent10 = 0;

      constexpr static bool has_infinity = false;
      constexpr static bool has_quiet_NaN = false;
      constexpr static bool has_signaling_NaN = false;
      constexpr static bool infinity() noexcept
      { return false; }
      constexpr static bool quiet_NaN() noexcept
      { return false; }
      constexpr static bool signaling_NaN() noexcept
      { return false; }
      constexpr static bool denorm_min() noexcept
      { return false; }

      constexpr static bool is_bounded = true;
      constexpr static bool traps = true;

    };
  }
}

#endif // ! __UTILITY_LIMITS_BOOL_LIMITS__
