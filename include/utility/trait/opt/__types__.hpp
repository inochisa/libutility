

#ifndef __UTILITY_TRAIT_OPT___TYPES____
#define __UTILITY_TRAIT_OPT___TYPES____

#include<utility/trait/integer_sequence.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>

namespace utility
{
  namespace trait
  {
    namespace __opt__
    {
      template<typename _Fp, typename _Sp>
      struct __type_pair__
      {
        typedef _Fp first;
        typedef _Sp second;
      };

      template<typename _Fp, typename _Sp, typename _Tp>
      struct __type_tripair__
      {
        typedef _Fp first;
        typedef _Sp second;
        typedef _Tp third;
      };

      template<typename _T, size_t _Id>
      struct __index_type__
      {
        typedef _T type;
        constexpr static size_t id = _Id;
      };

      template<typename... _Type>
      struct __type_tuple__
      { };

      namespace __helper__
      {
        template<typename _IdSeq, typename _T>
        struct __tuple_index_helper__;

        template<size_t... _Id, typename... _Type>
        struct __tuple_index_helper__<
          index_sequence<_Id...>, __type_tuple__<_Type...>
        >
        { typedef __type_tuple__<__index_type__<_Type, _Id>...> type;};
      }

      template<typename... _Type>
      using __make_type_index_sequence__ =
        typename __helper__::__tuple_index_helper__<
          make_index_sequence<sizeof...(_Type)>, __type_tuple__<_Type...>
        >::type;

      template<typename _T>
      struct __type_tuple_size__
      { constexpr static size_t value = 1;};
      template<typename _Fp, typename _Sp>
      struct __type_tuple_size__<__type_pair__<_Fp, _Sp>>
      { constexpr static size_t value = 2;};
      template<typename _Fp, typename _Sp, typename _Tp>
      struct __type_tuple_size__<__type_tripair__<_Fp, _Sp, _Tp>>
      { constexpr static size_t value = 3;};
      template<typename... _Types>
      struct __type_tuple_size__<__type_tuple__<_Types...>>
      { constexpr static size_t value = sizeof...(_Types);};

      namespace __helper__
      {
        template<size_t _Idx, typename _T>
        struct __tuple_get_helper__;

        template<size_t _Idx, size_t... _Id, typename... _Type>
        struct __tuple_get_helper__<
          _Idx,
          __type_tuple__<__index_type__<_Type, _Id>...>
        >
        {
          private:
            struct __private: public __index_type__<_Type, _Id>...
            { };
            template<size_t _Ix, typename _T>
            static __index_type__<_T, _Ix> __test(const __index_type__<_T, _Ix>&);

          public:
            typedef decltype(__test<_Idx>(__private{})) __index_type;
            typedef typename __index_type::type type;
        };

      }

      template<size_t _Idx, typename _T>
      struct __type_tuple_get__;

      template<size_t _Idx, typename... _Type>
      struct __type_tuple_get__<_Idx, __type_tuple__<_Type...>>
      {
        typedef typename __helper__::__tuple_get_helper__<
          _Idx,
          __make_type_index_sequence__<_Type...>
        >::type type;
      };

      template<size_t _Idx, typename _Fp, typename _Sp>
      struct __type_tuple_get__<_Idx, __type_pair__<_Fp, _Sp>>:
        public __type_tuple_get__<_Idx, __type_tuple__<_Fp, _Sp>>
      { };

      template<size_t _Idx, typename _Fp, typename _Sp, typename _Tp>
      struct __type_tuple_get__<_Idx, __type_tripair__<_Fp, _Sp, _Tp>>:
        public __type_tuple_get__<_Idx, __type_tuple__<_Fp, _Sp, _Tp>>
      { };

      template<typename _IdSeq, typename _T>
      struct __type_tuple_get_array__;

      template<size_t... _Id, typename... _Type>
      struct __type_tuple_get_array__<index_sequence<_Id...>, __type_tuple__<_Type...>>
      {
        typedef __type_tuple__<_Type...> tuple_type;
        typedef __type_tuple__<
          typename __type_tuple_get__<_Id, tuple_type>::type...
        > type;
      };

      template<typename _T>
      struct __checkout_type_feature__
      { typedef __type_tuple__<_T> type;};
      template<typename _Fp, typename _Sp>
      struct __checkout_type_feature__<__type_pair__<_Fp, _Sp>>
      { typedef __type_pair__<_Fp, _Sp> type;};
      template<typename _Fp, typename _Sp, typename _Tp>
      struct __checkout_type_feature__<__type_tripair__<_Fp, _Sp, _Tp>>
      { typedef __type_tripair__<_Fp, _Sp, _Tp> type;};
      template<typename... _Types>
      struct __checkout_type_feature__<__type_tuple__<_Types...>>
      { typedef __type_tuple__<_Types...> type;};



      template<typename... _Types>
      struct __type_tuple_cat__;

      template<>
      struct __type_tuple_cat__<>
      { typedef __type_tuple__<> type;};
      // template<typename _Fp, typename _Sp>
      // struct __type_tuple_cat__<__type_pair__<_Fp, _Sp>>
      // { typedef __type_tuple__<_Fp, _Sp> type;};
      // template<typename _Fp, typename _Sp, typename _Tp>
      // struct __type_tuple_cat__<__type_tripair__<_Fp, _Sp, _Tp>>
      // { typedef __type_tuple__<_Fp, _Sp, _Tp> type;};
      template<typename... _Types>
      struct __type_tuple_cat__<__type_tuple__<_Types...>>
      { typedef __type_tuple__<_Types...> type;};

      template<typename _T, typename... _ArgTypes>
      struct __type_tuple_cat__<_T, _ArgTypes...>:
        public __type_tuple_cat__<__type_tuple__<_T>, _ArgTypes...>
      { };
      template<typename _Fp, typename _Sp, typename... _ArgTypes>
      struct __type_tuple_cat__<__type_pair__<_Fp, _Sp>, _ArgTypes...>:
        public __type_tuple_cat__<__type_tuple__<_Fp, _Sp>, _ArgTypes...>
      { };
      template<typename _Fp, typename _Sp, typename _Tp, typename... _ArgTypes>
      struct __type_tuple_cat__<__type_tripair__<_Fp, _Sp, _Tp>, _ArgTypes...>:
        public __type_tuple_cat__<__type_tuple__<_Fp, _Sp, _Tp>, _ArgTypes...>
      { };
      template<typename... _Types, typename _T, typename... _ArgTypes>
      struct __type_tuple_cat__<__type_tuple__<_Types...>, _T, _ArgTypes...>:
        public __type_tuple_cat__<__type_tuple__<_Types..., _T>, _ArgTypes...>
      { };
      template<
        typename... _Types, typename _Fp, typename _Sp,
        typename... _ArgTypes
      >
      struct __type_tuple_cat__<
        __type_tuple__<_Types...>,
        __type_pair__<_Fp, _Sp>,
        _ArgTypes...
      >:public __type_tuple_cat__<
          __type_tuple__<_Types..., _Fp, _Sp>, _ArgTypes...
        >
      { };
      template<
        typename... _Types, typename _Fp, typename _Sp, typename _Tp,
        typename... _ArgTypes
      >
      struct __type_tuple_cat__<
        __type_tuple__<_Types...>,
        __type_tripair__<_Fp, _Sp, _Tp>,
        _ArgTypes...
      >:public __type_tuple_cat__<
          __type_tuple__<_Types..., _Fp, _Sp, _Tp>, _ArgTypes...
        >
      { };
      template<typename... _Types, typename... _Utypes, typename... _ArgTypes>
      struct __type_tuple_cat__<
        __type_tuple__<_Types...>,
        __type_tuple__<_Utypes...>,
        _ArgTypes...
      >:public __type_tuple_cat__<
        __type_tuple__<_Types..., _Utypes...>, _ArgTypes...
      >
      { };
    }
  }
}

#endif // ! __UTILITY_TRAIT_OPT___TYPES____
