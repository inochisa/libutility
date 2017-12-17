
#ifndef __UTILITY_TRAIT_INTEGRAL_SEQUENCE__
#define __UTILITY_TRAIT_INTEGRAL_SEQUENCE__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/categories/is_integral.hpp>

namespace utility
{
  namespace trait
  {
    template<typename _type, _type... _vals>
    struct integral_sequence
    {
      typedef _type value_type;
      typedef integral_sequence<_type, _vals...> type;
      constexpr static ::utility::size_t size() noexcept
      { return sizeof...(_vals);}
    };

    namespace __integral_sequence_impl
    {
      template<typename _Type, _Type... _Vals>
      struct __integer_sequence
      {
        static_assert(
          ::utility::trait::type::categories::is_integral<_Type>::value,
          "The integer_sequence need integer type."
        );
        typedef ::utility::trait::integral_sequence<_Type, _Vals...> type;
      };
    }
    template<typename _type, _type... _vals>
    using integer_sequence =
      typename
      __integral_sequence_impl::__integer_sequence<_type, _vals...>::type;

    template<::utility::size_t... _Vals>
    using index_sequence = integer_sequence<::utility::size_t, _Vals...>;

    namespace __make_integer_sequence_impl
    {
      // typedef long long __i_size_t;
      using __i_size_t = long long;

      template<typename _T, __i_size_t... _Vals>
      struct __sequence_extend;

      template<typename _Type, _Type... _Valis, __i_size_t... _Now>
      struct __sequence_extend<::utility::trait::integral_sequence<_Type, _Valis...>, _Now...>
      {
        private:
          constexpr static _Type __length =
            static_cast<_Type>(sizeof...(_Valis));
        public:
          typedef ::utility::trait::integer_sequence<
            _Type, _Valis...,
            1 * __length + _Valis...,
            2 * __length + _Valis...,
            3 * __length + _Valis...,
            static_cast<_Type>(_Now)...> type;
      };

      template<typename _T, __i_size_t _Need, __i_size_t = _Need % 4>
      struct __sequence_tail;

      template<typename _T, __i_size_t _Need>
      struct __sequence_base
      {
        typedef typename  __sequence_tail<_T, _Need>::type type;
      };
      template<typename _T>
      struct __sequence_base<_T, 0>
      {
        typedef ::utility::trait::integer_sequence<_T
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 1>
      {
        typedef ::utility::trait::integer_sequence<_T,
          static_cast<_T>(0)
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 2>
      {
        typedef ::utility::trait::integer_sequence<_T,
          static_cast<_T>(0), static_cast<_T>(1)
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 3>
      {
        typedef ::utility::trait::integer_sequence<_T,
          static_cast<_T>(0), static_cast<_T>(1),
          static_cast<_T>(2)
        > type;
      };

      template<typename _T, __i_size_t _Need>
      struct __sequence_tail<_T, _Need, 0>
      {
        typedef typename __sequence_extend<
          typename __sequence_base<_T, _Need / 4>::type
        >::type type;
      };
      template<typename _T, __i_size_t _Need>
      struct __sequence_tail<_T, _Need, 1>
      {
        typedef typename __sequence_extend<
          typename __sequence_base<_T, _Need / 4>::type,
          _Need-1
        >::type type;
      };
      template<typename _T, __i_size_t _Need>
      struct __sequence_tail<_T, _Need, 2>
      {
        typedef typename __sequence_extend<
          typename __sequence_base<_T, _Need / 4>::type,
          _Need-2, _Need-1
        >::type type;
      };
      template<typename _T, __i_size_t _Need>
      struct __sequence_tail<_T, _Need, 3>
      {
        typedef typename __sequence_extend<
          typename __sequence_base<_T, _Need / 4>::type,
          _Need-3, _Need-2, _Need-1
        >::type type;
      };

      template<typename _T, _T _Need>
      struct __make_integer_sequence
      {
        static_assert(
          ::utility::trait::type::categories::is_integral<_T>::value,
          "The integer_sequence need integer type."
        );

        typedef typename __sequence_base<_T, static_cast<__i_size_t>(_Need)>::type type;
      };
    }

    template<typename _T, _T _Val>
    using make_integer_sequence =
      typename __make_integer_sequence_impl::__make_integer_sequence<_T, _Val>::type;

    template<::utility::size_t _Val>
    using make_index_sequence =
      ::utility::trait::make_integer_sequence<::utility::size_t, _Val>;
  }
}

#endif // ! __UTILITY_TRAIT_INTEGRAL_SEQUENCE__
