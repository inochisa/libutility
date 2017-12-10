
#ifndef ___UTILITY__ALGORITHM__ALGORITHM__AUXILIARY___
#define ___UTILITY__ALGORITHM__ALGORITHM__AUXILIARY___

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T = void>
    struct plus
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x, const _T& __y) const
      { return __x + __y;}
    };
    template<typename _T = void>
    struct minus
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x, const _T& __y) const
      { return __x - __y;}
    };
    template<typename _T = void>
    struct multiplies
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x, const _T& __y) const
      { return __x * __y;}
    };
    template<typename _T = void>
    struct divides
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x, const _T& __y) const
      { return __x / __y;}
    };
    template<typename _T = void>
    struct modulus
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x, const _T& __y) const
      { return __x % __y;}
    };
    template<typename _T = void>
    struct negate
    {
      __UTILITY_CPP14_CONSTEXPR__
      _T operator()(const _T& __x) const
      { return -__x;}
    };

    template<typename _T = void>
    struct equal_to
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x == __y;}
    };
    template<typename _T = void>
    struct not_equal_to
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x != __y;}
    };
    template<typename _T = void>
    struct less
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x < __y;}
    };
    template<typename _T = void>
    struct less_equal
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x <= __y;}
    };
    template<typename _T = void>
    struct greater
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x > __y;}
    };
    template<typename _T = void>
    struct greater_equal
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x >= __y;}
    };

    template<typename _T = void>
    struct logical_and
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x && __y;}
    };
    template<typename _T = void>
    struct logical_or
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x || __y;}
    };
    template<typename _T = void>
    struct logical_not
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x) const
      { return !__x;}
    };

    template<typename _T = void>
    struct bit_and
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x & __y;}
    };
    template<typename _T = void>
    struct bit_or
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x | __y;}
    };
    template<typename _T = void>
    struct bit_xor
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x, const _T& __y) const
      { return __x ^ __y;}
    };
    template<typename _T = void>
    struct bit_not
    {
      __UTILITY_CPP14_CONSTEXPR__
      bool operator()(const _T& __x) const
      { return ~__x;}
    };

    template<>
    struct plus<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x + __y)
      { return __x + __y;}
    };
    template<>
    struct minus<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x - __y)
      { return __x - __y;}
    };
    template<>
    struct multiplies<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x * __y)
      { return __x * __y;}
    };
    template<>
    struct divides<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x / __y)
      { return __x / __y;}
    };
    template<>
    struct modulus<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x % __y)
      { return __x % __y;}
    };
    template<>
    struct negate<void>
    {
      template<typename _T>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x) const
        ->decltype(-__x)
      { return -__x;}
    };

    template<>
    struct equal_to<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x == __y)
      { return __x == __y;}
    };
    template<>
    struct not_equal_to<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x != __y)
      { return __x != __y;}
    };
    template<>
    struct greater<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x > __y)
      { return __x > __y;}
    };
    template<>
    struct less<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x < __y)
      { return __x < __y;}
    };
    template<>
    struct greater_equal<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x >= __y)
      { return __x >= __y;}
    };
    template<>
    struct less_equal<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x <= __y)
      { return __x <= __y;}
    };

    template<>
    struct logical_and<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x && __y)
      { return __x && __y;}
    };
    template<>
    struct logical_or<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x || __y)
      { return __x || __y;}
    };
    template<>
    struct logical_not<void>
    {
      template<typename _T>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x) const
        ->decltype(!__x)
      { return !__x;}
    };

    template<>
    struct bit_and<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x & __y)
      { return __x & __y;}
    };
    template<>
    struct bit_or<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x | __y)
      { return __x | __y;}
    };
    template<>
    struct bit_xor<void>
    {
      template<typename _T, typename _U>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x, const _U& __y) const
        ->decltype(__x ^ __y)
      { return __x ^ __y;}
    };
    template<>
    struct bit_not<void>
    {
      template<typename _T>
      __UTILITY_CPP14_CONSTEXPR__
      auto operator()(const _T& __x) const
        ->decltype(~__x)
      { return ~__x;}
    };
  }
}

#endif // ! ___UTILITY__ALGORITHM__ALGORITHM__AUXILIARY___
