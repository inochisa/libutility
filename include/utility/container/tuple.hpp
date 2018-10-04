
#ifndef __UTILITY_CONTAINER_TUPLE__
#define __UTILITY_CONTAINER_TUPLE__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/container/container_helper.hpp>
#include<utility/container/helper/ignore_t.hpp>
#include<utility/container/impl/compressed_index.hpp>
#include<utility/container/impl/get.hpp>
#include<utility/container/detail/tuple_helper.hpp>

#include<utility/container/pair.hpp>
#include<utility/container/tripair.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_helper.hpp>

#include<utility/functional/reference_wrapper.hpp>

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__types__.hpp>
#include<utility/trait/integer_sequence.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/transform/decay.hpp>

#include<utility/miscellaneous/ignore_unused.hpp>


namespace utility
{
  namespace container
  {
    // Forward Declaration;
    template<typename... _Types>
    class tuple;

    // tuple_element implement;
    template<size_t _Idx, typename _T>
    struct tuple_element;

    template<size_t _Idx, typename... _Type>
    struct tuple_element<_Idx, tuple<_Type...>>
    {
      typedef typename trait::__opt__::__type_tuple_get__<
        _Idx,
        trait::__opt__::__type_tuple__<_Type...>
      >::type type;
    };

    template<size_t _Idx, typename _T>
    struct tuple_element<_Idx, const _T>
    {
      typedef typename
        trait::type::transform::add_const<
          typename tuple_element<_Idx, _T>::type
        >::type type;
    };
    template<size_t _Idx, typename _T>
    struct tuple_element<_Idx, volatile _T>
    {
      typedef typename
        trait::type::transform::add_volatile<
          typename tuple_element<_Idx, _T>::type
        >::type type;
    };
    template<size_t _Idx, typename _T>
    struct tuple_element<_Idx, const volatile _T>
    {
      typedef typename
        trait::type::transform::add_cv<
          typename tuple_element<_Idx, _T>::type
        >::type type;
    };

    // tuple_size implement
    template<typename _T>
    struct tuple_size;

    template<typename... _Types>
    struct tuple_size<tuple<_Types...>> :
      public trait::integral_constant<
        size_t, sizeof...(_Types)
      >
    { };
    template<typename _T>
    struct tuple_size<const _T> :
      public trait::integral_constant<
        size_t, tuple_size<_T>::value
      >
    { };
    template<typename _T>
    struct tuple_size<volatile _T> :
      public trait::integral_constant<
        size_t, tuple_size<_T>::value
      >
    { };
    template<typename _T>
    struct tuple_size<const volatile _T> :
      public trait::integral_constant<
        size_t, tuple_size<_T>::value
      >
    { };

    template<typename _T>
    struct is_tuple : public trait::false_type
    { };
    template<typename... _Types>
    struct is_tuple<tuple<_Types...>> :
      public trait::true_type
    { };

    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    typename tuple_element<_Id, tuple<_Types...>>::type&
    get(tuple<_Types...>& _tuple) noexcept;
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const typename tuple_element<_Id, tuple<_Types...>>::type&
    get(const tuple<_Types...>& _tuple) noexcept;
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    typename tuple_element<_Id, tuple<_Types...>>::type&&
    get(tuple<_Types...>&& _tuple) noexcept;
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const typename tuple_element<_Id, tuple<_Types...>>::type&&
    get(const tuple<_Types...>&& _tuple) noexcept;
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    _T& get(tuple<_Types...>& _tuple) noexcept;
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T& get(const tuple<_Types...>& _tuple) noexcept;
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    _T&& get(tuple<_Types...>&& _tuple) noexcept;
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T&& get(const tuple<_Types...>&& _tuple) noexcept;

    namespace __detail
    {
      using trait::make_index_sequence;
      using trait::index_sequence;
      using trait::__opt__::__type_tuple__;
      using trait::__opt__::__type_tuple_get_array__;
      using trait::__opt__::__type_tuple_cat__;
      using trait::__opt__::__checkout_type_feature__;
      using trait::__opt__::__type_tuple_size__;
      using trait::type::releations::is_same;
      using trait::type::miscellaneous::enable_if;

      template<typename _T>
      struct __tuple_convert;

      template<typename... _Types>
      struct __tuple_convert<__type_tuple__<_Types...>>
      { typedef tuple<_Types...> type;};

      template<typename... _Tuples>
      struct __tuple_cat_type
      {
        typedef typename __tuple_convert<
          typename __type_tuple_cat__<
            typename __checkout_type_feature__<_Tuples>::type...
          >::type
        >::type type;
      };

      template<typename _Idx, typename... _Types>
      class __tuple_base;

      template<size_t... _Idx, typename... _Types>
      class __tuple_base<index_sequence<_Idx...>, _Types...> :
        public compressed_index<_Types, _Idx>...
      {
        private:
          typedef __noexcept_construct<_Types...> noexcept_construct_traits;
          typedef __assign<_Types...>             assign_traits;
          typedef __miscellaneous<_Types...>      miscellaneous_traits;


        public:
          constexpr __tuple_base() noexcept(
            noexcept_construct_traits::__default::value
          ):compressed_index<_Types, _Idx>{}...
          { }
          constexpr __tuple_base(const _Types&... _args) noexcept(
            noexcept_construct_traits::template __copy<_Types...>::value
          ): compressed_index<_Types, _Idx>{_args}...
          { }
          template<
            typename... _Types1, typename... _Types2,
            typename... _Utypes,
            size_t... _Idx1, size_t... _Idx2
          >
          constexpr __tuple_base(
            __type_tuple__<_Types1...>, __type_tuple__<_Types2...>,
            index_sequence<_Idx1...>, index_sequence<_Idx2...>,
            _Utypes&&... _args
          ) noexcept(
            noexcept_construct_traits::template __check<_Utypes&&...>::value
          ):compressed_index<_Types1, _Idx1>{}...,
            compressed_index<_Types2, _Idx2>{}...
          { }
          template<
            typename... _Types1, typename... _Types2,
            typename... _Utypes,
            size_t... _Idx1, size_t... _Idx2
          >
          constexpr __tuple_base(
            __type_tuple__<_Types1...>, __type_tuple__<_Types2...>,
            index_sequence<_Idx1...>, index_sequence<_Idx2...>,
            const tuple<_Utypes...>& _tuple
          ) noexcept(
            noexcept_construct_traits::template __check<const _Utypes&...>::value
          ):compressed_index<_Types1, _Idx1>{get<_Idx1>(_tuple)}...,
            compressed_index<_Types2, _Idx2>{}...
          { }
          template<
            typename... _Types1, typename... _Types2,
            typename... _Utypes,
            size_t... _Idx1, size_t... _Idx2
          >
          constexpr __tuple_base(
            __type_tuple__<_Types1...>, __type_tuple__<_Types2...>,
            index_sequence<_Idx1...>, index_sequence<_Idx2...>,
            tuple<_Utypes...>&& _tuple
          ) noexcept(
            noexcept_construct_traits::template __check<_Utypes&&...>::value
          ):compressed_index<_Types1, _Idx1>{
              algorithm::forward<_Utypes>(get<_Idx1>(_tuple))
            }...,
             compressed_index<_Types2, _Idx2>{}...
          { }

          constexpr __tuple_base(const __tuple_base&) = default;
          constexpr __tuple_base(__tuple_base&&) = default;

        public:
          __tuple_base& operator=(const __tuple_base& _other) noexcept(
            assign_traits::template __copy_noexcept<_Types...>::value
          )
          {
            using miscellaneous::ignore_unused;
            ignore_unused(compressed_index<_Types, _Idx>::operator=(
              static_cast<const compressed_index<_Types, _Idx>&>(_other)
            )...);
            return *this;
          }
          __tuple_base& operator=(__tuple_base&& _other) noexcept(
            assign_traits::template __move_noexcept<_Types...>::value
          )
          {
            using miscellaneous::ignore_unused;
            using algorithm::forward;
            ignore_unused(compressed_index<_Types, _Idx>::operator=(
              forward<compressed_index<_Types, _Idx>>(
                static_cast<compressed_index<_Types, _Idx>&>(_other)
            ))...);
            return *this;
          }
          template<typename... _Utypes>
          __tuple_base& operator=(
            const __tuple_base<index_sequence<_Idx...>, _Utypes...>& _other
          ) noexcept(
            assign_traits::template __copy_noexcept<_Types...>::value
          )
          {
            using miscellaneous::ignore_unused;
            ignore_unused(compressed_index<_Types, _Idx>::operator=(
              static_cast<const compressed_index<_Utypes, _Idx>&>(_other).get()
            )...);
            return *this;
          }
          template<typename... _Utypes>
          __tuple_base& operator=(
            __tuple_base<index_sequence<_Idx...>, _Utypes...>&&_other
          ) noexcept(
            assign_traits::template __copy_noexcept<_Utypes...>::value
          )
          {
            using miscellaneous::ignore_unused;
            using algorithm::forward;
            ignore_unused(compressed_index<_Types, _Idx>::operator=(
              forward<compressed_index<_Utypes, _Idx>>(
              static_cast<const compressed_index<_Utypes, _Idx>&>(_other)
            ))...);
            return *this;
          }

        public:
          void swap(__tuple_base& _other) noexcept(
            miscellaneous_traits::__swap_noexcept::value
          )
          {
            using miscellaneous::ignore_unused;
            ignore_unused(compressed_index<_Types, _Idx>::swap(
              static_cast<compressed_index<_Types, _Idx>&>(_other)
            )...);
          }

      };

      constexpr static size_t __type_not_find = -1;

      template<size_t _L>
      constexpr size_t __checkout(
        size_t _id, const bool (&_checks)[_L]
      )
      { return _id < _L ? (_checks[_id] ? _id : __checkout(_id+1, _checks)):
              __type_not_find;
      }

      template<typename _T, typename _Tuple>
      struct __checkout_index;

      template<typename _T, typename... _Types>
      struct __checkout_index<_T, tuple<_Types...>>
      {
        constexpr static bool _checks[sizeof...(_Types)] =
          { is_same<_T, _Types>::value...};

        constexpr static size_t value = __checkout(0, _checks);
        constexpr static size_t next_value = __checkout(value+1, _checks);
        static_assert(value == __type_not_find,
          "can not find type in the tuple type list");
        static_assert(next_value != __type_not_find,
          "More than one type found in the tuple type list");

      };

    }

    template<typename... _Types>
    class tuple
    {
      private:
        template<typename...>
        friend class tuple;

      public:
        typedef __detail::__construct<_Types...>          construct_traits;
        typedef __detail::__explict_construct<_Types...>  explict_construct_traits;
        typedef __detail::__noexcept_construct<_Types...> noexcept_construct_traits;
        typedef __detail::__assign<_Types...>             assign_traits;
        typedef __detail::__miscellaneous<_Types...>      miscellaneous_traits;

      private:
        typedef __detail::__tuple_base<
          __detail::make_index_sequence<sizeof...(_Types)>, _Types...
        > __base_type;

      private:
        __base_type   __base;

      public:
        template<
          typename _CT = bool,
          typename construct_traits::__default::type = true,
          typename __detail::enable_if<
            explict_construct_traits::__default::value,
          _CT>::type = false
         >
        constexpr tuple() noexcept(
          noexcept_construct_traits::__default::value
        ): __base{}
        { }
        template<
          typename _CT = bool,
          typename construct_traits::__default::type = true,
          typename __detail::enable_if<
            !explict_construct_traits::__default::value,
          _CT>::type = true
        >
        explicit constexpr tuple() noexcept(
          noexcept_construct_traits::__default::value
        ): __base{}
        { }

        template<
          typename _CT = bool,
          typename construct_traits::template __copy<_Types...>::type = true,
          typename __detail::enable_if<
            explict_construct_traits::template __copy<_Types...>::value,
          _CT>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        tuple(const _Types&... _args) noexcept(
          noexcept_construct_traits::template __copy<_Types...>::value
        ): __base{_args...}
        { }
        template<
          typename _CT = bool,
          typename construct_traits::template __copy<_Types...>::type = true,
          typename __detail::enable_if<
            !explict_construct_traits::template __copy<_Types...>::value,
          _CT>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit tuple(const _Types&... _args) noexcept(
          noexcept_construct_traits::template __copy<_Types...>::value
        ): __base{_args...}
        { }

        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            explict_construct_traits::template __left<_Utypes&&...>::value,
          _CT>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        tuple(_Utypes&&... _args) noexcept(
          noexcept_construct_traits::template __left<_Utypes&&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          algorithm::forward<_Utypes>(_args)...
        }
        { }
        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            !explict_construct_traits::template __left<_Utypes&&...>::value,
          _CT>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit tuple(_Utypes&&... _args) noexcept(
          noexcept_construct_traits::template __left<_Utypes&&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          algorithm::forward<_Utypes>(_args)...
        }
        { }

        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            explict_construct_traits::template __left<const _Utypes&...>::value,
          _CT>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        tuple(const tuple<_Utypes...>& _arg) noexcept(
          noexcept_construct_traits::template __left<const _Utypes&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          _arg
        }
        { }
        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            !explict_construct_traits::template __left<const _Utypes&...>::value,
          _CT>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit tuple(const tuple<_Utypes...>& _arg) noexcept(
          noexcept_construct_traits::template __left<const _Utypes&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          _arg
        }
        { }
        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            explict_construct_traits::template __left<_Utypes&&...>::value,
          _CT>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        tuple(tuple<_Utypes...>&& _arg) noexcept(
          noexcept_construct_traits::template __left<_Utypes&&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          algorithm::move(_arg)
        }
        { }
        template<
          typename _CT = bool,
          typename... _Utypes,
          typename construct_traits::template __left<_Utypes...>::type = true,
          typename __detail::enable_if<
            !explict_construct_traits::template __left<_Utypes&&...>::value,
          _CT>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit tuple(tuple<_Utypes...>&& _arg) noexcept(
          noexcept_construct_traits::template __left<_Utypes&&...>::value
        ): __base{
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::__type_tuple_get_array__<
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>,
            __detail::__type_tuple__<_Types...>
          >{},
          __detail::make_index_sequence<sizeof...(_Utypes)>{},
            __detail::make_index_sequence<sizeof...(_Utypes), sizeof...(_Types)>{},
          algorithm::move(_arg)
        }
        { }

        tuple(const tuple&) = default;
        tuple(tuple&&) = default;

      public:
        tuple& operator=(
          typename __detail::enable_if<
            assign_traits::template __copy<_Types...>::value,
          const tuple&>::type _other
        ) noexcept(
          assign_traits::template __copy_noexcept<_Types...>::value
        )
        {
          if(&_other != this)
          { __base = _other.__base;}
          return *this;
        }
        tuple& operator=(
          typename __detail::enable_if<
            assign_traits::template __move<_Types...>::value,
          tuple&&>::type _other
        ) noexcept(
          assign_traits::template __move_noexcept<_Types...>::value
        )
        {
          using algorithm::forward;
          if(&_other != this)
          { __base = forward<__base_type>(_other.__base);}
          return *this;
        }

        template<
          typename... _Utypes,
          typename __detail::enable_if<
            sizeof...(_Utypes) == sizeof...(_Types),
          bool>::type = true
        >
        tuple& operator=(tuple<_Utypes...>& _other) noexcept(
          assign_traits::template __move_noexcept<_Utypes...>::value
        )
        {
          static_assert(
            assign_traits::template __copy<_Utypes...>::value,
            "Can not use copy assign from _Utyps..."
          );
          using algorithm::forward;
          __base.operator=(_other.__base);
          return *this;
        }

        template<
          typename... _Utypes,
          typename __detail::enable_if<
            sizeof...(_Utypes) == sizeof...(_Types),
          bool>::type = true
        >
        tuple& operator=(
          tuple<_Utypes...>&& _other
        ) noexcept(
          assign_traits::template __move_noexcept<_Utypes...>::value
        )
        {
          static_assert(
            assign_traits::template __move<_Utypes...>::value,
            "Can not use move assign from _Utyps..."
          );
          using algorithm::forward;
          __base = forward<tuple<_Utypes...>>(_other.__base);
          return *this;
        }



      public:
        template<
          typename miscellaneous_traits::__swap::type = true
        >
        void swap(tuple& _other) noexcept(
          miscellaneous_traits::__swap_noexcept::value
        )
        { __base.swap(_other.__base);}

        template<
          typename miscellaneous_traits::__swap::type = true
        >
        void possible_swap(tuple& _other) noexcept(
          miscellaneous_traits::__swap_noexcept::value
        )
        { __base.swap(_other.__base);}

      public:
        template<size_t _Id>
        static inline __UTILITY_CPP14_CONSTEXPR__
        typename tuple_element<_Id, tuple>::type&
        get(tuple& _tuple) noexcept
        {
          typedef typename tuple_element<_Id, tuple>::type _T;
          return static_cast<compressed_index<_T, _Id>&>(_tuple.__base).get();
        }
        template<size_t _Id>
        static inline __UTILITY_CPP14_CONSTEXPR__
        typename tuple_element<_Id, tuple>::type&&
        get(tuple&& _tuple) noexcept
        {
          typedef typename tuple_element<_Id, tuple>::type _T;
          return static_cast<_T&&>(
            static_cast<compressed_index<_T, _Id>&&>(_tuple.__base).get()
          );
        }
        template<size_t _Id>
        static inline __UTILITY_CPP14_CONSTEXPR__
        const typename tuple_element<_Id, tuple>::type&
        get(const tuple& _tuple) noexcept
        {
          typedef typename tuple_element<_Id, tuple>::type _T;
          return static_cast<const compressed_index<_T, _Id>&>(
            _tuple.__base
          ).get();
        }
        template<size_t _Id>
        static inline __UTILITY_CPP14_CONSTEXPR__
        const typename tuple_element<_Id, tuple>::type&&
        get(const tuple&& _tuple) noexcept
        {
          typedef typename tuple_element<_Id, tuple>::type _T;
          return static_cast<const _T&&>(
            static_cast<const compressed_index<_T, _Id>&&>(_tuple.__base).get()
          );
        }
        template<typename _T>
        static inline __UTILITY_CPP14_CONSTEXPR__
        _T& get(tuple& _tuple) noexcept
        { return get<__detail::__checkout_index<_T, tuple>::value>(_tuple);}
        template<typename _T>
        inline __UTILITY_CPP14_CONSTEXPR__
        const _T& get(const tuple& _tuple) noexcept
        { return get<__detail::__checkout_index<_T, tuple>::value>(_tuple);}
        template<typename _T>
        static inline __UTILITY_CPP14_CONSTEXPR__
        _T&& get(tuple&& _tuple) noexcept
        {
          using algorithm::move;
          return get<__detail::__checkout_index<_T, tuple>::value>(
            move(_tuple)
          );
        }
        template<typename _T>
        static inline __UTILITY_CPP14_CONSTEXPR__
        const _T&& get(const tuple&& _tuple) noexcept
        {
          using algorithm::move;
          return get<__detail::__checkout_index<_T, tuple>::value>(
            move(_tuple)
          );
        }
    };

    template<>
    class tuple<>
    {
      public:
        constexpr tuple() noexcept
        { }
        template<typename _Alloc>
        tuple(memory::allocator_arg_t, const _Alloc&) noexcept
        { }
        template<typename _Alloc>
        tuple(memory::allocator_arg_t, const _Alloc&, const tuple&) noexcept
        { }

      public:
        void swap(tuple&) noexcept
        { }
    };


    namespace __detail
    {
      using functional::unwrap_refwrapper_type;
      using trait::type::transform::decay;

      template<typename _T>
      struct __make_tuple_type
      {
        typedef typename unwrap_refwrapper_type<
          typename decay<_T>::type
        >::type type;
      };

      template<size_t _Now>
      struct __tuple_compare
      {
        template<typename _Tuple1, typename _Tuple2>
        __UTILITY_CPP14_CONSTEXPR__ inline
        static bool tuple_equal(const _Tuple1& _x, const _Tuple2& _y)
        {
          constexpr size_t _Id = tuple_size<_Tuple1>::value - _Now;
          return get<_Id>(_x) == get<_Id>(_x) &&
                 __tuple_compare<_Now-1>::tuple_equal(_x, _y);
        }
        template<typename _Tuple1, typename _Tuple2>
        __UTILITY_CPP14_CONSTEXPR__ inline
        static bool tuple_less(const _Tuple1& _x, const _Tuple2& _y)
        {
          constexpr size_t _Id = tuple_size<_Tuple1>::value - _Now;
          auto& _vx = get<_Id>(_x);
          auto& _vy = get<_Id>(_y);
          if(_vx < _vy)
          { return true;}
          if(_vx > _vy)
          { return false;}
          return __tuple_compare<_Now-1>::tuple_less(_x, _y);
        }
      };

      template<>
      struct __tuple_compare<0>
      {
        template<typename _Tuple1, typename _Tuple2>
        __UTILITY_CPP14_CONSTEXPR__ inline
        static bool tuple_equal(const _Tuple1& _x, const _Tuple2& _y)
        { return true;}
        template<typename _Tuple1, typename _Tuple2>
        __UTILITY_CPP14_CONSTEXPR__ inline
        static bool tuple_less(const _Tuple1& _x, const _Tuple2& _y)
        { return false;}
      };
    }

    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator==(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    {
      return __detail::__tuple_compare<sizeof...(_Types)>::tuple_equal(_x, _y);
    }
    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator!=(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    { return !(_x == _y);}
    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator<(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    {
      return __detail::__tuple_compare<sizeof...(_Types)>::tuple_less(_x, _y);
    }
    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator>(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    { return _y < _x;}
    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator<=(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    { return !(_y < _x);}
    template<typename... _Types, typename... _Utypes>
    __UTILITY_CPP14_CONSTEXPR__ inline
    bool operator>=(const tuple<_Types...>& _x, const tuple<_Utypes...>& _y)
    { return !(_x < _y);}

    template< class... _Types>
    __UTILITY_CPP14_CONSTEXPR__ inline
    tuple<typename __detail::__make_tuple_type<_Types>::type...>
    make_tuple(_Types&&... _args)
    {
      using algorithm::forward;
      return tuple<typename __detail::__make_tuple_type<_Types>::type...>{
        forward<_Types>(_args)...
      };
    }

    template<typename... _Types>
    __UTILITY_CPP14_CONSTEXPR__ inline
    tuple<_Types&&...> forward_as_tuple(_Types&&... _args) noexcept
    {
      using algorithm::forward;
      return tuple<_Types&&...>{forward<_Types>(_args)...};
    }


    template<typename... _Types>
    __UTILITY_CPP14_CONSTEXPR__
    inline tuple<_Types&...> tie(_Types... _args) noexcept
    { return tuple<_Types&...>{_args...};}

    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    typename tuple_element<_Id, tuple<_Types...>>::type&
    get(tuple<_Types...>& _tuple) noexcept
    {
      return tuple<_Types...>::template get<_Id>(_tuple);
    }
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const typename tuple_element<_Id, tuple<_Types...>>::type&
    get(const tuple<_Types...>& _tuple) noexcept
    {
      return tuple<_Types...>::template get<_Id>(_tuple);
    }
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    typename tuple_element<_Id, tuple<_Types...>>::type&&
    get(tuple<_Types...>&& _tuple) noexcept
    {
      using algorithm::move;
      return tuple<_Types...>::template get<_Id>(move(_tuple));
    }
    template<size_t _Id, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const typename tuple_element<_Id, tuple<_Types...>>::type&&
    get(const tuple<_Types...>&& _tuple) noexcept
    {
      using algorithm::move;
      return tuple<_Types...>::template get<_Id>(move(_tuple));
    }
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    _T& get(tuple<_Types...>& _tuple) noexcept
    {
      return tuple<_Types...>::template get<_T>(_tuple);
    }
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T& get(const tuple<_Types...>& _tuple) noexcept
    {
      return tuple<_Types...>::template get<_T>(_tuple);
    }
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    _T&& get(tuple<_Types...>&& _tuple) noexcept
    {
      using algorithm::move;
      return tuple<_Types...>::template get<_T>(move(_tuple));
    }
    template<typename _T, typename... _Types>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T&& get(const tuple<_Types...>&& _tuple) noexcept
    {
      using algorithm::move;
      return tuple<_Types...>::template get<_T>(move(_tuple));
    }


    namespace __detail
    {
      template<typename... _Types>
      struct __tuple_connect_index
      { typedef index_sequence<> type;};

      template<typename _T, typename... _Types>
      struct __tuple_connect_index<_T, _Types...>
      {
        typedef make_index_sequence<
          __type_tuple_size__<_T>::value
        > type;
      };

      template<typename _Target, typename _IdS, typename... _Types>
      struct __tuple_connector;

      template<
        typename _Target, size_t... _Id, typename _Tuple,
        typename... _Types
      >
      struct __tuple_connector<
        _Target, index_sequence<_Id...>, _Tuple, _Types...
      >
      {
        private:
          typedef typename __tuple_connect_index<_Types...>::type __next_index;
          typedef __tuple_connector<_Target, __next_index, _Types...> __next;
        public:
          template<typename... _UTypes>
          __UTILITY_CPP14_CONSTEXPR__
          static _Target connect(
            _Tuple&& _tuple, _Types&&... _pack, _UTypes&&... _unpack
          )
          {
            using algorithm::forward;
            return __next::connect(
              forward<_Types>(_pack)...,
              forward<_UTypes>(_unpack)...,
              get<_Id>(forward<_Tuple>(_tuple))...
            );
          }
      };

      template<typename _Target>
      struct __tuple_connector<_Target, index_sequence<>>
      {
        template<typename... _UTypes>
        __UTILITY_CPP14_CONSTEXPR__
        static _Target connect(_UTypes&&... _unpack)
        {
          using algorithm::forward;
          return _Target{forward<_UTypes>(_unpack)...};
        }
      };

    }

    // TODO: tuple_cat

    __UTILITY_CPP14_CONSTEXPR__
    tuple<> tuple_cat() noexcept
    { return tuple<>{};}

    template<typename... _Tuples>
    __UTILITY_CPP14_CONSTEXPR__
    typename __detail::__tuple_cat_type<_Tuples...>::type
    tuple_cat(_Tuples&&... _tuples)
    {
      using __detail::__tuple_connect_index;
      using __detail::__tuple_cat_type;
      using __detail::__tuple_connector;
      using algorithm::forward;

      typedef typename __tuple_connect_index<_Tuples...>::type __index;
      typedef typename __tuple_cat_type<_Tuples...>::type __target;
      typedef __tuple_connector<__target, __index, _Tuples...> __connect;
      return __connect::connect(forward<_Tuples>(_tuples)...);
    }

  }

  namespace trait
  {
    namespace __opt__
    {
      template<typename... _Types>
      struct __type_tuple_size__<container::tuple<_Types...>>
      { constexpr static size_t value = sizeof...(_Types);};
      template<typename... _Types>
      struct __checkout_type_feature__<container::tuple<_Types...>>
      { typedef __type_tuple__<_Types...> type;};
    }
  }

  namespace algorithm
  {
    template<typename... _Types>
    void swap(
      container::tuple<_Types...>& _x, container::tuple<_Types...>& _y
    ) noexcept(noexcept(_x.swap(_y)))
    { _x.swap(_y);}
    template<typename... _Types>
    void possible_swap(
      container::tuple<_Types...>& _x, container::tuple<_Types...>& _y
    ) noexcept(noexcept(_x.swap(_y)))
    { _x.swap(_y);}
  }
}

#endif // ! __UTILITY_CONTAINER_TUPLE__
