
#ifndef __UTILITY_CONTAINER_PAIR__
#define __UTILITY_CONTAINER_PAIR__

/**
 * \file pair.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#ifdef ___UTILITY__COMPATIBLE__WITH__STD__

#include<utility>

namespace utility
{
  namespace container
  {
    using std::pair;
  }
}

#else // ___UTILITY__COMPATIBLE__WITH__STD__

#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/container/detail/pair_helper.hpp>

namespace utility
{
  namespace container
  {
    /*!
    * \brief the pair container
    * \todo another need combine version constructor
    */
    template<typename _T1, typename _T2>
    class pair
    {
      public:
        typedef _T1   first_type;
        typedef _T2   second_type;

      public:
        _T1 first;
        _T2 second;

      public:
        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_default<_U1, _U2>::type = true
        >
        constexpr pair() noexcept(
          __detail::__pair_default_noexcept<_T1, _T2>::value
        ):first(), second()
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_explicit_default<_U1, _U2>::type = false
        >
        explicit constexpr pair() noexcept(
          __detail::__pair_default_noexcept<_T1, _T2>::value
        ):first(), second()
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_copy<_U1, _U2>::type = true
        >
        constexpr pair(const _T1& __first, const _T2& __second) noexcept(
          __detail::__pair_copy_noexcept<_T1, _T2>::value
        ):first(__first), second(__second)
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_explicit_copy<_U1, _U2>::type = false
        >
        explicit constexpr pair(const _T1& __first, const _T2& __second) noexcept(
          __detail::__pair_copy_noexcept<_T1, _T2>::value
        ):first(__first), second(__second)
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_move<_T1, _T2, _U1, _U2>::type = true
        >
        constexpr pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          __detail::__pair_move_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(algorithm::forward<_U1>(__tfirst)),
          second(algorithm::forward<_U2>(__tsecond))
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_explicit_move<_T1, _T2, _U1, _U2>::type = false
        >
        explicit constexpr pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          __detail::__pair_move_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(algorithm::forward<_U1>(__tfirst)),
          second(algorithm::forward<_U2>(__tsecond))
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_copy<_T1, _T2, _U1, _U2>::type = true
        >
        constexpr pair(const pair<_U1, _U2>& __tpair) noexcept(
          __detail::__pair_copy_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(__tpair.first), second(__tpair.second)
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_explicit_copy<_T1, _T2, _U1, _U2>::type = false
        >
        explicit constexpr pair(const pair<_U1, _U2>& __tpair) noexcept(
          __detail::__pair_copy_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(__tpair.first), second(__tpair.second)
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_move<_T1, _T2, _U1, _U2>::type = true
        >
        constexpr pair(pair<_U1, _U2>&& __tpair) noexcept(
          __detail::__pair_move_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(algorithm::forward<_U1>(__tpair.first)),
          second(algorithm::forward<_U1>(__tpair.second))
        { }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_explicit_move<_T1, _T2, _U1, _U2>::type = false
        >
        explicit constexpr pair(pair<_U1, _U2>&& __tpair) noexcept(
          __detail::__pair_move_noexcept<_T1, _T2, _U1, _U2>::value
        ):first(algorithm::forward(__tpair.first)),
          second(algorithm::forward(__tpair.second))
        { }

        pair(const pair&) = default;
        pair(pair&&) = default;

      public:
        // typename trait::type::miscellaneous::enable_if<
        //   trait::type::features::is_copy_assignable<_T1>::value &&
        //   trait::type::features::is_copy_assignable<_T2>::value,
        //   pair&>::type
        // operator= (const pair& __other)
        // {
        //   this->first   = __other.first;
        //   this->second  = __other.second;
        //   return *this;
        // }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_copy_assign<_T1, _T2, _U1, _U2>::type = true
        >
        pair& operator=(const pair<_U1, _U2>& __other) noexcept(
          __detail::__pair_copy_assign_noexcept<_T1, _T2, _U1, _U2>::value
        )
        {
          this->first   = __other.first;
          this->second  = __other.second;
          return *this;
        }

      public:
        // typename trait::type::miscellaneous::enable_if<
        //   trait::type::features::is_move_assignable<_T1>::value &&
        //   trait::type::features::is_move_assignable<_T2>::value,
        //   pair&>::type
        // operator= (pair&& __other) noexcept(
        //   trait::type::features::is_nothrow_move_assignable<_T1>::value &&
        //   trait::type::features::is_nothrow_move_assignable<_T2>::value)
        // {
        //   this->first   = algorithm::forward<_T1>(__other.first);
        //   this->second  = algorithm::forward<_T2>(__other.second);
        //   return *this;
        // }

        template<
          typename _U1, typename _U2,
          typename __detail::__pair_move_assign<_T1, _T2, _U1, _U2>::type = true
        >
        pair& operator= (pair<_U1, _U2>&& __other) noexcept(
          __detail::__pair_move_assign_noexcept<_T1, _T2, _U1, _U2>::value
        )
        {
          this->first   = algorithm::forward<_U1>(__other.first);
          this->second  = algorithm::forward<_U2>(__other.second);
          return *this;
        }

      public:
        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_swap<_U1, _U2>::type = true
        >
        void swap(pair& __other) noexcept(
          __detail::__pair_swap_noexcept<_U1, _U2>::value
        )
        {
          using algorithm::swap;
          swap(this->first,   __other.first);
          swap(this->second,  __other.second);
        }
        template<
          typename _U1 = _T1, typename _U2 = _T2,
          typename __detail::__pair_possible_swap<_U1, _U2>::type = true
        >
        void possible_swap(pair& __other) noexcept(
          __detail::__pair_possible_swap_noexcept<_U1, _U2>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->first,   __other.first);
          possible_swap(this->second,  __other.second);
        }
    };

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator== (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return (__x.first == __y.first) && (__x.second == __y.second);}

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator!= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y);}

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator< (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    {
      if(!(__x.first == __y.first))
      { return __x.first < __y.first;}
      return __x.second < __y.second;
    }

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator<= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x);}

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator> (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x;}

    template<typename _T1, typename _T2>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator>= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y);}

    template<typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    inline
    pair<
      typename __detail::__make_pair_type<_T1>::type,
      typename __detail::__make_pair_type<_T2>::type
    >
    make_pair(_T1&& __first, _T2&& __second)
    {
      return pair<
        typename __detail::__make_pair_type<_T1>::type,
        typename __detail::__make_pair_type<_T2>::type
      >(
        algorithm::forward<_T1>(__first),
        algorithm::forward<_T2>(__second)
      );
    }

  }


  namespace algorithm
  {
    template<typename _T1, typename _T2>
    void swap(
      container::pair<_T1, _T2>& __a,
      container::pair<_T1, _T2>& __b
    ) noexcept(noexcept(__a.swap(__b)))
    { __a.swap(__b);}
    template<typename _T1, typename _T2>
    void possible_swap(
      container::pair<_T1, _T2>& __a,
      container::pair<_T1, _T2>& __b
    ) noexcept(noexcept(__a.possible_swap(__b)))
    { __a.possible_swap(__b);}
  }

}

#endif // ! ___UTILITY__COMPATIBLE__WITH__STD__

#endif // ! __UTILITY_CONTAINER_PAIR__