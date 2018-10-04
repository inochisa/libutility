
#ifndef __UTILITY_FUNCTIONAL_PLACEHOLDERS__
#define __UTILITY_FUNCTIONAL_PLACEHOLDERS__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace functional
  {
    namespace placeholders
    {
      template<int _ID>
      struct phid
      { };

      constexpr phid<1> _1{};
      constexpr phid<2> _2{};
      constexpr phid<3> _3{};
      constexpr phid<4> _4{};
      constexpr phid<5> _5{};
      constexpr phid<6> _6{};
      constexpr phid<7> _7{};
      constexpr phid<8> _8{};
      constexpr phid<9> _9{};
      constexpr phid<10> _10{};
      constexpr phid<11> _11{};
      constexpr phid<12> _12{};
      constexpr phid<13> _13{};
      constexpr phid<14> _14{};
      constexpr phid<15> _15{};
      constexpr phid<16> _16{};
      constexpr phid<17> _17{};
      constexpr phid<18> _18{};
      constexpr phid<19> _19{};
      constexpr phid<20> _20{};
    }

    template<typename _T>
    struct is_placeholder: public trait::integral_constant<int, 0>
    { };
    template<int _ID>
    struct is_placeholder<placeholders::phid<_ID>>:
      public trait::integral_constant<int, _ID>
    { };
  }
}

#endif // ! __UTILITY_FUNCTIONAL_PLACEHOLDERS__
