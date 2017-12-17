
#ifndef __UTILITY_CONTAINER_PAIR__
#define __UTILITY_CONTAINER_PAIR__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/features/is_implicit_constructible.hpp>
#include<utility/trait/type/features/is_assignable.hpp>
#include<utility/trait/type/features/is_copy_assignable.hpp>
#include<utility/trait/type/features/is_move_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

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
        template<typename _U1 = _T1, typename _U2 = _T2,
          typename
            utility::trait::type::miscellaneous::enable_if<
              utility::trait::type::features::is_default_constructible<_U1>::value &&
              utility::trait::type::features::is_default_constructible<_U2>::value &&
              (::utility::trait::type::features::is_implicit_constructible<_U1>::value &&
               utility::trait::type::features::is_implicit_constructible<_U2>::value),
              bool>::type = true>
        constexpr pair():first(), second()
        { }

        template<typename _U1 = _T1, typename _U2 = _T2,
        typename
          utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_default_constructible<_U1>::value &&
            utility::trait::type::features::is_default_constructible<_U2>::value &&
            !(::utility::trait::type::features::is_implicit_constructible<_U1>::value &&
              utility::trait::type::features::is_implicit_constructible<_U2>::value),
            bool>::type = false>
        explicit constexpr pair():first(), second()
        { }

        template<typename _U1 = _T1, typename _U2 = _T2,
        typename
          utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_copy_constructible<_U1>::value &&
            utility::trait::type::features::is_copy_constructible<_U2>::value &&
            (::utility::trait::type::releations::is_convertible<const _U1&, _U1>::value &&
             utility::trait::type::releations::is_convertible<const _U2&, _U2>::value),
            bool
          >::type = true>
        constexpr pair(const _T1& __first, const _T2& __second):
          first(__first), second(__second)
        { }

        template<typename _U1 = _T1, typename _U2 = _T2,
        typename
          utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_default_constructible<_U1>::value &&
            utility::trait::type::features::is_default_constructible<_U2>::value &&
            !(::utility::trait::type::releations::is_convertible<const _U1&, _U1>::value &&
              utility::trait::type::releations::is_convertible<const _U2&, _U2>::value),
            bool>::type = false>
        explicit constexpr pair(const _T1& __first, const _T2& __second):
          first(__first), second(__second)
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, _U1&&>::value &&
          utility::trait::type::features::is_constructible<_T2, _U2&&>::value &&
          (::utility::trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           utility::trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        constexpr pair(_U1&& __tfirst, _U2&& __tsecond):
          first(::utility::algorithm::forward<_U1>(__tfirst)),
          second(::utility::algorithm::forward<_U2>(__tsecond))
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, _U1&&>::value &&
          utility::trait::type::features::is_constructible<_T2, _U2&&>::value &&
          !(::utility::trait::type::releations::is_convertible<_U1&&, _T1>::value &&
            utility::trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = false>
        explicit constexpr pair(_U1&& __tfirst, _U2&& __tsecond):
          first(::utility::algorithm::forward<_U1>(__tfirst)),
          second(::utility::algorithm::forward<_U2>(__tsecond))
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, const _U1&>::value &&
          utility::trait::type::features::is_constructible<_T2, const _U2&>::value &&
          (::utility::trait::type::releations::is_convertible<const _U1&, _T1>::value &&
           utility::trait::type::releations::is_convertible<const _U2&, _T2>::value),
          bool>::type = true>
        constexpr pair(const pair<_U1, _U2>& __tpair):
          first(__tpair.first), second(__tpair.second)
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, const _U1&>::value &&
          utility::trait::type::features::is_constructible<_T2, const _U2&>::value &&
          !(::utility::trait::type::releations::is_convertible<const _U1&, _T1>::value &&
            utility::trait::type::releations::is_convertible<const _U2&, _T2>::value),
          bool>::type = false>
        explicit constexpr pair(const pair<_U1, _U2>& __tpair):
          first(__tpair.first), second(__tpair.second)
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, _U1&&>::value &&
          utility::trait::type::features::is_constructible<_T2, _U2&&>::value &&
          (::utility::trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           utility::trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        constexpr pair(pair<_U1, _U2>&& __tpair):
          first(::utility::algorithm::forward<_U1>(__tpair.first)),
          second(::utility::algorithm::forward<_U1>(__tpair.second))
        { }

        template<typename _U1, typename _U2,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_constructible<_T1, _U1&&>::value &&
          utility::trait::type::features::is_constructible<_T2, _U2&&>::value &&
          !(::utility::trait::type::releations::is_convertible<_U1&&, _T1>::value &&
            utility::trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        explicit constexpr pair(pair<_U1, _U2>&& __tpair):
          first(::utility::algorithm::forward(__tpair.first)),
          second(::utility::algorithm::forward(__tpair.second))
        { }

        pair(const pair&) = default;
        pair(pair&&) = default;

      public:
        // typename utility::trait::type::miscellaneous::enable_if<
        //   utility::trait::type::features::is_copy_assignable<_T1>::value &&
        //   utility::trait::type::features::is_copy_assignable<_T2>::value,
        //   pair&>::type
        // operator= (const pair& __other)
        // {
        //   this->first   = __other.first;
        //   this->second  = __other.second;
        //   return *this;
        // }

        template<typename _U1, typename _U2,
        typename utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_assignable<_T1&, const _U1&>::value &&
            utility::trait::type::features::is_assignable<_T2&, const _U2&>::value,
          bool>::type = true
        >
        pair& operator= (const pair<_U1, _U2>& __other)
        {
          this->first   = __other.first;
          this->second  = __other.second;
          return *this;
        }

      public:
        // typename utility::trait::type::miscellaneous::enable_if<
        //   utility::trait::type::features::is_move_assignable<_T1>::value &&
        //   utility::trait::type::features::is_move_assignable<_T2>::value,
        //   pair&>::type
        // operator= (pair&& __other) noexcept(
        //   utility::trait::type::features::is_nothrow_move_assignable<_T1>::value &&
        //   utility::trait::type::features::is_nothrow_move_assignable<_T2>::value)
        // {
        //   this->first   = utility::algorithm::forward<_T1>(__other.first);
        //   this->second  = utility::algorithm::forward<_T2>(__other.second);
        //   return *this;
        // }

        template<typename _U1, typename _U2,
          typename utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_assignable<_T1&, _U1&&>::value &&
            utility::trait::type::features::is_assignable<_T2&, _U2&&>::value,
          bool>::type = true
        >
        pair& operator= (pair<_U1, _U2>&& __other)
        {
          this->first   = utility::algorithm::forward<_U1>(__other.first);
          this->second  = utility::algorithm::forward<_U2>(__other.second);
          return *this;
        }

      public:
        template<typename _U1 = _T1, typename _U2 = _T2,
        typename utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_swappable<_U1>::value &&
          utility::trait::type::features::is_swappable<_U2>::value,
        bool>::type = true
        >
        void swap(pair& __other) noexcept(
          utility::trait::type::features::is_nothrow_swappable<_T1>::value &&
          utility::trait::type::features::is_nothrow_swappable<_T2>::value)
        {
          using utility::algorithm::swap;
          swap(this->first,   __other.first);
          swap(this->second,  __other.second);
        }
        template<typename _U1 = _T1, typename _U2 = _T2,
          typename utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_possible_swappable<_U1>::value &&
            utility::trait::type::features::is_possible_swappable<_U2>::value,
          bool>::type = true
        >
        void possible_swap(pair& __other) noexcept(
          utility::trait::type::features::is_nothrow_possible_swappable<_T1>::value &&
          utility::trait::type::features::is_nothrow_possible_swappable<_T2>::value)
        {
          using utility::algorithm::possible_swap;
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

    namespace __make_pair_impl
    {
      template<typename _T>
      struct __make_pair_type_helper
      { typedef _T type;};

      template<typename _T>
      struct __make_pair_type
      {
        typedef typename
          __make_pair_type_helper<typename
            utility::trait::type::transform::decay<_T>::type
          >::type type;
      };
    }

    template<typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    inline
    pair<
      typename __make_pair_impl::__make_pair_type<_T1>::type,
      typename __make_pair_impl::__make_pair_type<_T2>::type
    >
    make_pair(_T1&& __first, _T2&& __second)
    {
      return pair<
        typename __make_pair_impl::__make_pair_type<_T1>::type,
        typename __make_pair_impl::__make_pair_type<_T2>::type
      >(
        utility::algorithm::forward<_T1>(__first),
        utility::algorithm::forward<_T2>(__second)
      );
    }

  }


  namespace algorithm
  {
    template<typename _T1, typename _T2>
    void swap(
      ::utility::container::pair<_T1, _T2>& __a,
      ::utility::container::pair<_T1, _T2>& __b
    ) noexcept(noexcept(__a.swap(__b)))
    { __a.swap(__b);}
    template<typename _T1, typename _T2>
    void possible_swap(
      ::utility::container::pair<_T1, _T2>& __a,
      ::utility::container::pair<_T1, _T2>& __b
    ) noexcept(noexcept(__a.possible_swap(__b)))
    { __a.possible_swap(__b);}
  }

}


#endif // ! __UTILITY_CONTAINER_PAIR__
