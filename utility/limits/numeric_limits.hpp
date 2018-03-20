
#ifndef __UTILITY_LIMITS_NUMERIC_LIMITS__
#define __UTILITY_LIMITS_NUMERIC_LIMITS__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace limits
  {
    /*!
    * \brief Floating-point rounding style
    *
    * This enum indicate the rounding style used by floating-point
    * arithmetics whenever a result of an expression is stored in
    * an object of a floating-point type.
    *
    */
    enum float_round_style
    {
      round_indeterminate       = -1, //!< Rounding style is indetermined
      round_toward_zero         = 0,  //!< Rounding toward zero
      round_to_nearest          = 1,  //!< Rounding toward nearest representable value
      round_toward_infinity     = 2,  //!< Rounding toward positive infinity
      round_toward_neg_infinity = 3   //!< Rounding toward negative infinity
    };

    /*!
    * \brief Floating-point subnormal support
    *
    * This class indicate support of subnormal values
    * by floating-point type.
    *
    */
    enum float_denorm_style
    {
      denorm_indeterminate = -1, //!< Support of subnormal values cannot be determined
      denorm_absent        = 0,  //!< The type does not support subnormal values
      denorm_present       = 1   //!< The type allows subnormal values
    };

    template<typename _T>
    class numeric_limits
    {
      public:
        constexpr static bool is_specialized = false;

        constexpr static _T min() noexcept
        { return _T(); }
        constexpr static _T max() noexcept
        { return _T(); }
        constexpr static _T lowest() noexcept
        { return _T(); }

        constexpr static int digits = 0;
        constexpr static int digits10 = 0;
        constexpr static int max_digits10 = 0;

        constexpr static bool is_signed = false;
        constexpr static bool is_integer = false;
        constexpr static bool is_exact = false;
        constexpr static _T epsilon() noexcept
        { return _T(); }
        constexpr static _T round_error() noexcept
        { return _T(); }

        constexpr static int min_exponent = 0;
        constexpr static int min_exponent10 = 0;
        constexpr static int max_exponent = 0;
        constexpr static int max_exponent10 = 0;

        constexpr static bool has_infinity = false;
        constexpr static bool has_quiet_NaN = false;
        constexpr static bool has_signaling_NaN = false;
        constexpr static _T infinity() noexcept
        { return _T(); }
        constexpr static _T quiet_NaN() noexcept
        { return _T(); }
        constexpr static _T signaling_NaN() noexcept
        { return _T(); }
        constexpr static _T denorm_min() noexcept
        { return _T(); }

        constexpr static bool is_bounded = false;
        constexpr static bool traps = false;

    };
  }
}

#endif // ! __UTILITY_LIMITS_NUMERIC_LIMITS__
