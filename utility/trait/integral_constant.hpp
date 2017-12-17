
#ifndef __UTILITY_TRAIT_INTEGRAL_CONSTANT__
#define __UTILITY_TRAIT_INTEGRAL_CONSTANT__

namespace utility
{
  namespace trait
  {
    // helper class and declaration
    template<typename _type, _type _val>
    struct integral_constant
    {
      constexpr static _type value = _val;
      typedef _type value_type;
      typedef integral_constant<_type, _val> type;
      constexpr operator value_type() const noexcept
      { return value;}
      constexpr value_type operator()() const noexcept
      { return value;}

    };
    template<bool _B>
    using bool_constant = ::utility::trait::integral_constant<bool, _B>;
    using true_type   = ::utility::trait::bool_constant<true>;
    using false_type  = ::utility::trait::bool_constant<false>;

  }
}

#endif // ! __UTILITY_TRAIT_INTEGRAL_CONSTANT__
