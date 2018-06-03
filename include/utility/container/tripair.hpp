
#ifndef __UTILITY_CONTAINER_TRIPAIR__
#define __UTILITY_CONTAINER_TRIPAIR__

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/container/detail/tripair_helper.hpp>


namespace utility
{
  namespace container
  {
    template<typename _T1, typename _T2, typename _T3>
    class tripair
    {
      public:
        typedef _T1             first_type;
        typedef _T2             second_type;
        typedef _T3             third_type;

      public:
        first_type              first;
        second_type             second;
        third_type              third;

      public:
        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_default<_U1, _U2, _U3>::type = true
        >
        constexpr tripair() noexcept(
          __detail::__tripair_default_noexcept<_T1, _T2, _T3>::value
        ):first(), second(), third()
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_explicit_default<_U1, _U2, _U3>::type = false
        >
        explicit constexpr tripair() noexcept(
          __detail::__tripair_default_noexcept<_T1, _T2, _T3>::value
        ):first(), second(), third()
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_copy<_U1, _U2, _U3>::type = true
        >
        constexpr tripair(
          const first_type& __c1, const second_type& __c2,
          const third_type& __c3
        ) noexcept(
          __detail::__tripair_copy_noexcept<_T1, _T2, _T3>::value
        ):first(__c1), second(__c2), third(__c3)
        { }

        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_explicit_copy<_U1, _U2, _U3>::type = false
        >
        explicit constexpr tripair(
          const first_type& __c1, const second_type& __c2,
          const third_type& __c3
        ) noexcept(
          __detail::__tripair_copy_noexcept<_T1, _T2, _T3>::value
        ):first(__c1), second(__c2), third(__c3)
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_move<_T1, _T2, _T3, _U1, _U2, _U3>::type = true
        >
        constexpr tripair(_U1&& __c1, _U2&& __c2, _U3&& __c3) noexcept(
          __detail::__tripair_move_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(algorithm::forward<_U1>(__c1)),
          second(algorithm::forward<_U2>(__c2)),
          third(algorithm::forward<_U3>(__c3))
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_explicit_move<_T1, _T2, _T3, _U1, _U2, _U3>::type = false
        >
        explicit constexpr tripair(_U1&& __c1, _U2&& __c2, _U3&& __c3) noexcept(
          __detail::__tripair_move_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(algorithm::forward<_U1>(__c1)),
          second(algorithm::forward<_U2>(__c2)),
          third(algorithm::forward<_U3>(__c3))
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_copy<_T1, _T2, _T3, _U1, _U2, _U3>::type = true
        >
        constexpr tripair(const tripair<_U1, _U2, _U3>& __other) noexcept(
          __detail::__tripair_copy_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(__other.first), second(__other.second), third(__other.third)
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_explicit_copy<_T1, _T2, _T3, _U1, _U2, _U3>::type = false
        >
        explicit constexpr tripair(const tripair<_U1, _U2, _U3>& __other) noexcept(
          __detail::__tripair_copy_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(__other.first), second(__other.second), third(__other.third)
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_move<_T1, _T2, _T3, _U1, _U2, _U3>::type = true
        >
        constexpr tripair(tripair<_U1, _U2, _U3>&& __other) noexcept(
          __detail::__tripair_move_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(algorithm::forward<_U1>(__other.first)),
          second(algorithm::forward<_U1>(__other.second)),
          third(algorithm::forward<_U1>(__other.third))
        { }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_explicit_move<_T1, _T2, _T3, _U1, _U2, _U3>::type = false
        >
        explicit constexpr tripair(tripair<_U1, _U2, _U3>&& __other) noexcept(
          __detail::__tripair_move_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        ):first(algorithm::forward<_U1>(__other.first)),
          second(algorithm::forward<_U1>(__other.second)),
          third(algorithm::forward<_U1>(__other.third))
        { }

        tripair(const tripair&) = default;
        tripair(tripair&&) = default;

      public:
        tripair& operator=(const tripair&);

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_copy_assign<_T1, _T2, _T3, _U1, _U2, _U3>::type = true
        >
        tripair& operator=(const tripair<_U1, _U2, _U3>& __other) noexcept(
          __detail::__tripair_copy_assign_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        )
        {
          this->first   = __other.first;
          this->second  = __other.second;
          this->third   = __other.third;
          return *this;
        }

        template<
          typename _U1, typename _U2, typename _U3,
          typename __detail::__tripair_move_assign<_T1, _T2, _T3, _U1, _U2, _U3>::type = true
        >
        tripair& operator=(tripair<_U1, _U2, _U3>&& __other) noexcept(
          __detail::__tripair_move_assign_noexcept<_T1, _T2, _T3, _U1, _U2, _U3>::value
        )
        {
          this->first   = algorithm::forward<_U1>(__other.first);
          this->second  = algorithm::forward<_U1>(__other.second);
          this->third   = algorithm::forward<_U1>(__other.third);
          return *this;
        }

      public:
        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_swap<_U1, _U2, _U3>::type = true
        >
        void swap(tripair& __other) noexcept(
          __detail::__tripair_swap_noexcept<_U1, _U2, _U3>::value
        )
        {
          using algorithm::swap;
          swap(this->first,   __other->first);
          swap(this->second,  __other->second);
          swap(this->third,   __other->third);
        }

        template<
          typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3,
          typename __detail::__tripair_possible_swap<_U1, _U2, _U3>::type = true
        >
        void possible_swap(tripair& __other) noexcept(
          __detail::__tripair_possible_swap_noexcept<_U1, _U2, _U3>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->first,   __other->first);
          possible_swap(this->second,  __other->second);
          possible_swap(this->third,   __other->third);
        }
    };

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator== (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    { return (__x.first == __y.first) && (__x.second == __y.second);}

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator!= (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    { return !(__x == __y);}

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator< (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    {
      if(!(__x.first == __y.first))
      { return __x.first < __y.first;}
      if(!(__x.second == __y.second))
      { return __x.second < __y.second;}
      return __x.third < __y.third;
    }

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator<= (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    { return !(__y < __x);}

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator> (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    { return __y < __x;}

    template<typename _T1, typename _T2, typename _T3>
    inline
    __UTILITY_CPP14_CONSTEXPR__
    bool operator>= (const tripair<_T1, _T2, _T3>& __x, const tripair<_T1, _T2, _T3>& __y)
    { return !(__x < __y);}

    template<typename _T1, typename _T2, typename _T3>
    __UTILITY_CPP14_CONSTEXPR__
    inline
    tripair<
      typename __detail::__make_tripair_type<_T1>::type,
      typename __detail::__make_tripair_type<_T2>::type,
      typename __detail::__make_tripair_type<_T3>::type
    >
    make_tripair(_T1&& __first, _T2&& __second, _T3&& __third)
    {
      return tripair<
        typename __detail::__make_tripair_type<_T1>::type,
        typename __detail::__make_tripair_type<_T2>::type,
        typename __detail::__make_tripair_type<_T3>::type
      >{
        algorithm::forward<_T1>(__first),
        algorithm::forward<_T2>(__second),
        algorithm::forward<_T3>(__third)
      };
    }

  }

  namespace algorithm
  {
    template<typename _T1, typename _T2, typename _T3>
    void swap(
      container::tripair<_T1, _T2, _T3>& __a,
      container::tripair<_T1, _T2, _T3>& __b
    ) noexcept(noexcept(__a.swap(__b)))
    { __a.swap(__b);}
    template<typename _T1, typename _T2, typename _T3>
    void possible_swap(
      container::tripair<_T1, _T2, _T3>& __a,
      container::tripair<_T1, _T2, _T3>& __b
    ) noexcept(noexcept(__a.possible_swap(__b)))
    { __a.possible_swap(__b);}
  }
}

#endif // ! __UTILITY_CONTAINER_TRIPAIR__
