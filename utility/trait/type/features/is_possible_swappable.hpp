
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_POSSIBLE_SWAPPABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_POSSIBLE_SWAPPABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/algorithm/impl/possible_swap_single.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/categories/is_void.hpp>
#include<utility/trait/type/transform/is_referenceable.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_possible_swappable_with
        // is_possible_swappable
        // is_nothrow_possible_swappable_with
        // is_nothrow_possible_swappable
        namespace __possible_swap_impl
        {
          using __two = utility::trait::__impl_helper::__twochar;

          template<typename _T, typename _U = _T,
            bool = !utility::trait::type::categories::is_void<_T>::value
              && !utility::trait::type::categories::is_void<_U>::value>
          struct __is_possible_swap_with_helper
          {
            private:
              template<typename __T, typename __U>
              static decltype(utility::algorithm::possible_swap(
                utility::trait::type::special::declval<__T>(),
                utility::trait::type::special::declval<__U>()
              ), char(0)) __test(int);
              template<typename __T, typename __U>
              static __two __test(...);

              typedef decltype((__test<_T, _U>(0))) __type1;
              typedef decltype((__test<_U, _T>(0))) __type2;

            public:
              constexpr static bool value =
                (sizeof(char) == sizeof(__type1)) &&
                (sizeof(char) == sizeof(__type2));
          };
          template<typename _T, typename _U>
          struct __is_possible_swap_with_helper<_T, _U, false>
          {
            public:
              constexpr static bool value = false;
          };

          template<typename _T, typename _U = _T,
            bool = __is_possible_swap_with_helper<_T, _U>::value>
          struct __is_nothrow_possible_swap_with_helper
          {
            constexpr static bool value =
              noexcept(utility::algorithm::possible_swap(
                utility::trait::type::special::declval<_T>(),
                utility::trait::type::special::declval<_U>())) &&
              noexcept(utility::algorithm::possible_swap(
                utility::trait::type::special::declval<_U>(),
                utility::trait::type::special::declval<_T>()));
          };
          template<typename _T, typename _U>
          struct __is_nothrow_possible_swap_with_helper<_T, _U, false>
          { constexpr static bool value = false;};

        }
        template<typename _T, typename _U>
        struct is_possible_swappable_with : public
          utility::trait::integral_constant<bool,
            __possible_swap_impl::__is_possible_swap_with_helper<_T, _U>::value>
        { };
        template<typename _T>
        struct is_possible_swappable : public
          utility::trait::type::miscellaneous::conditional
          <
            utility::trait::type::transform::is_referenceable<_T>::value,
            is_possible_swappable_with
            <
              typename utility::trait::type::transform::add_lvalue_reference<_T>::type,
              typename utility::trait::type::transform::add_lvalue_reference<_T>::type
            >,
            utility::trait::false_type
          >::type
        { };

        template<typename _T, typename _U>
        struct is_nothrow_possible_swappable_with : public
          utility::trait::integral_constant<bool,
            __possible_swap_impl::__is_nothrow_possible_swap_with_helper<_T, _U>::value>
        { };
        template<typename _T>
        struct is_nothrow_possible_swappable : public
          utility::trait::type::miscellaneous::conditional
          <
            utility::trait::type::transform::is_referenceable<_T>::value,
            is_nothrow_possible_swappable_with
            <
              typename utility::trait::type::transform::add_lvalue_reference<_T>::type,
              typename utility::trait::type::transform::add_lvalue_reference<_T>::type
            >,
            utility::trait::false_type
          >::type
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_POSSIBLE_SWAPPABLE__
