
#ifndef __UTILITY_TRAIT_INTEGER_SEQUENCE__
#define __UTILITY_TRAIT_INTEGER_SEQUENCE__


#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_integral.hpp>

namespace utility
{
  namespace trait
  {
    template<typename _type, _type... _vals>
    struct integer_sequence
    {
      typedef _type value_type;
      typedef integer_sequence<_type, _vals...> type;
      constexpr static size_t size() noexcept
      { return sizeof...(_vals);}
      static_assert(
        trait::type::categories::is_integral<_type>::value,
        "The integer_sequence need integer type."
      );

      template<_type _offset>
      using offset_type = integer_sequence<_type, (_vals+_offset)...>;
    };

    template<size_t... _Vals>
    using index_sequence = integer_sequence<size_t, _Vals...>;

    namespace __make_integer_sequence_impl
    {
      // typedef long long __i_size_t;
      using __i_size_t = long long;

      template<typename _T, __i_size_t... _Vals>
      struct __sequence_extend;

      template<typename _Type, _Type... _Valis, __i_size_t... _Now>
      struct __sequence_extend<integer_sequence<_Type, _Valis...>, _Now...>
      {
        private:
          constexpr static _Type __length =
            static_cast<_Type>(sizeof...(_Valis));
        public:
          typedef integer_sequence<
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
        typedef integer_sequence<_T
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 1>
      {
        typedef integer_sequence<_T,
          static_cast<_T>(0)
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 2>
      {
        typedef integer_sequence<_T,
          static_cast<_T>(0), static_cast<_T>(1)
        > type;
      };
      template<typename _T>
      struct __sequence_base<_T, 3>
      {
        typedef integer_sequence<_T,
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
        typedef typename __sequence_base<_T, static_cast<__i_size_t>(_Need)>::type type;
      };

      template<typename _T, _T _En, _T _Bn>
      struct __make_integer_sequence_helper
      {
        static_assert(
          type::categories::is_integral<_T>::value,
          "The integer_sequence need integer type."
        );
        static_assert(
          _Bn <= _En,
          "Error input for make interger sequence"
        );
        typedef typename __make_integer_sequence<_T, _En-_Bn>::type::template offset_type<_Bn> type;
      };
    }

    template<typename _T, _T _EVal, _T _BVal = 0>
    using make_integer_sequence =
      typename __make_integer_sequence_impl::__make_integer_sequence_helper<_T, _EVal, _BVal>::type;

    template<size_t _EVal, size_t _BVal = 0>
    using make_index_sequence =
      make_integer_sequence<size_t, _EVal, _BVal>;
  }
}

#endif // ! __UTILITY_TRAIT_INTEGER_SEQUENCE__
