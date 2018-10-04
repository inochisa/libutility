
#ifndef __UTILITY_CONTAINER_DETAIL_TUPLE_HELPER__
#define __UTILITY_CONTAINER_DETAIL_TUPLE_HELPER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__types__.hpp>
#include<utility/trait/integer_sequence.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/transform/add_cv.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/features/is_implicit_constructible.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_assignable.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>

namespace utility
{
  namespace container
  {
    namespace __detail
    {
      using trait::make_index_sequence;
      using trait::__and__;
      using trait::__opt__::__type_tuple__;
      using trait::__opt__::__type_tuple_get_array__;
      using trait::type::releations::is_convertible;
      using trait::type::transform::add_const;
      using trait::type::transform::add_lvalue_reference;
      using trait::type::features::is_constructible;
      using trait::type::features::is_implicit_constructible;
      using trait::type::features::is_nothrow_constructible;
      using trait::type::features::is_assignable;
      using trait::type::features::is_nothrow_assignable;
      using trait::type::features::is_swappable;
      using trait::type::features::is_possible_swappable;
      using trait::type::features::is_nothrow_swappable;
      using trait::type::features::is_nothrow_possible_swappable;
      using trait::type::miscellaneous::enable_if;

      template<typename _T>
      using __add_const_ref = typename add_lvalue_reference<typename add_const<_T>::type>::type;

      template<typename _T, typename _U1, typename _T2>
      struct __left_attr;

      template<typename... _Type, typename... _UType, typename... _Type2>
      struct __left_attr<
        __type_tuple__<_Type...>,
        __type_tuple__<_UType...>,
        __type_tuple__<_Type2...>
      >
      {
        constexpr static bool __construct =
          __and__<is_constructible<_Type, _UType>::value...>::value &&
          __and__<is_constructible<_Type2>::value...>::value;


        constexpr static bool __explict =
          (__and__<is_implicit_constructible<_Type, _UType>::value...>::value &&
          __and__<is_implicit_constructible<_Type2>::value...>::value);

        using __noexcept = __and__<
          is_nothrow_constructible<_Type, _UType>::value...,
          is_nothrow_constructible<_Type2>::value...
        >;
      };


      template<typename... _Type>
      struct __construct
      {
        using __default = enable_if<
          __and__<is_constructible<_Type>::value...>::value,
          bool>;

        template<typename... _UType>
        using __copy = enable_if<
          __and__<is_constructible<_Type, __add_const_ref<_UType>>::value...>::value,
          bool>;

        template<typename... _Utype>
        using __move = enable_if<
          __and__<is_constructible<_Type, _Utype&&>::value...>::value,
          bool>;

        template<typename... _Utype>
        using __left = enable_if<
          __left_attr<
            __type_tuple_get_array__<
              make_index_sequence<sizeof...(_Utype)>,
              __type_tuple__<_Type...>
            >,
            __type_tuple__<_Utype...>,
            __type_tuple_get_array__<
              make_index_sequence<sizeof...(_Type), sizeof...(_Utype)>,
              __type_tuple__<_Type...>
            >
          >::__construct,
          bool>;
      };

      template<typename... _Type>
      struct __explict_construct
      {
        struct __default
        {
          constexpr static bool value =
            __and__<is_implicit_constructible<_Type>::value...>::value;
        };

        template<typename... _UType>
        struct __copy
        {
          constexpr static bool value =
            __and__<is_convertible<__add_const_ref<_UType>, _Type>::value...>::value;
        };

        template<typename... _Utype>
        struct __move
        {
          constexpr static bool value =
            __and__<is_convertible<_Utype&&, _Type>::value...>::value;
        };

        template<typename... _Utype>
        struct __left
        {
          constexpr static bool value = __left_attr<
              __type_tuple_get_array__<
                make_index_sequence<sizeof...(_Utype)>,
                __type_tuple__<_Type...>
              >,
              __type_tuple__<_Utype...>,
              __type_tuple_get_array__<
                make_index_sequence<sizeof...(_Type), sizeof...(_Utype)>,
                __type_tuple__<_Type...>
              >
            >::__explict;
        };

      };

      template<typename... _Type>
      struct __noexcept_construct
      {
        using __default = trait::__and__<
          is_nothrow_constructible<_Type>::value...
        >;

        template<typename... _UType>
        using __copy = trait::__and__<
          is_nothrow_constructible<_Type, __add_const_ref<_UType>>::value...
        >;

        template<typename... _Utype>
        using __move = trait::__and__<
          is_nothrow_constructible<_Type, _Utype&&>::value...
        >;

        template<typename... _Utype>
        using __left = typename __left_attr<
          __type_tuple_get_array__<
            make_index_sequence<sizeof...(_Utype)>,
            __type_tuple__<_Type...>
          >,
          __type_tuple__<_Utype...>,
          __type_tuple_get_array__<
            make_index_sequence<sizeof...(_Type), sizeof...(_Utype)>,
            __type_tuple__<_Type...>
          >
        >::__noexcept;
      };

      template<typename... _Type>
      struct __assign
      {
        template<typename... _Utype>
        using __copy = __and__<
          is_assignable<_Type&, __add_const_ref<_Utype>>::value...
        >;


        template<typename... _Utype>
        using __copy_noexcept = __and__<
          is_assignable<_Type&, __add_const_ref<_Utype>>::value...
        >;

        template<typename... _Utype>
        using __move = __and__<
          is_assignable<_Type&, _Utype&&>::value...
        >;

        template<typename... _Utype>
        using __move_noexcept = trait::__and__<
          is_assignable<_Type&, _Utype&&>::value...
        >;
      };

      template<typename... _Type>
      struct __miscellaneous
      {
        using __swap = enable_if<
          __and__<is_swappable<_Type>::value...>::value,
          bool>;

        using __swap_noexcept = trait::__and__<
          is_nothrow_swappable<_Type>::value...
        >;

        using __possible_swap = enable_if<
          __and__<is_possible_swappable<_Type>::value...>::value,
          bool>;

        using __possible_swap_noexcept = trait::__and__<
          is_nothrow_possible_swappable<_Type>::value...
        >;
      };


    }
  }
}

#endif // ! __UTILITY_CONTAINER_DETAIL_TUPLE_HELPER__
