
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_SWAPPABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_SWAPPABLE__

#include<utility/trait/trait_helper.hpp>

#include<utility/algorithm/impl/swap/swap_single.hpp>

#include<utility/trait/opt/__twochar__.hpp>
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
        // is_swappable_with(C++17)
        // is_swappable(C++17)
        // is_nothrow_swappable_with(C++17)
        // is_nothrow_swappable(C++17)
        namespace __swappable_impl
        {
          using __two = trait::__opt__::__twochar__;

          template<typename _T, typename _U = _T,
            bool = !trait::type::categories::is_void<_T>::value
              && !trait::type::categories::is_void<_U>::value>
          struct __is_swappable_with_helper
          {
            private:
              template<typename __T, typename __U>
              static decltype(algorithm::swap(
                trait::type::special::declval<__T>(),
                trait::type::special::declval<__U>()
              ), char(0)) __test(int);
              template<typename, typename>
              static __two __test(...);

              typedef decltype((__test<_T, _U>(0))) __type1;
              typedef decltype((__test<_U, _T>(0))) __type2;

            public:
              constexpr static bool value =
                (sizeof(char) == sizeof(__type1)) &&
                (sizeof(char) == sizeof(__type2));
          };
          template<typename _T, typename _U>
          struct __is_swappable_with_helper<_T, _U, false>
          {
            public:
              constexpr static bool value = false;
          };

          template<typename _T, typename _U,
            bool = __is_swappable_with_helper<_T, _U>::value>
          struct __is_nothrow_swappable_with_helper
          {
            constexpr static bool value =
              noexcept(algorithm::swap(
                trait::type::special::declval<_T>(),
                trait::type::special::declval<_U>())) &&
              noexcept(algorithm::swap(
                trait::type::special::declval<_U>(),
                trait::type::special::declval<_T>()));
          };
          template<typename _T, typename _U>
          struct __is_nothrow_swappable_with_helper<_T, _U, false>
          { constexpr static bool value = false;};
        }
        template<typename _T, typename _U>
        struct is_swappable_with : public
          trait::integral_constant<bool,
            __swappable_impl::__is_swappable_with_helper<_T, _U>::value>
        { };
        template<typename _T>
        struct is_swappable : public
          trait::type::miscellaneous::conditional
          <
            trait::type::transform::is_referenceable<_T>::value,
            is_swappable_with
            <
              typename trait::type::transform::add_lvalue_reference<_T>::type,
              typename trait::type::transform::add_lvalue_reference<_T>::type
            >,
            trait::false_type
          >::type
        { };

        template<typename _T, typename _U>
        struct is_nothrow_swappable_with : public
          trait::integral_constant<bool,
            __swappable_impl::__is_nothrow_swappable_with_helper<_T, _U>::value>
        { };
        template<typename _T>
        struct is_nothrow_swappable : public
          trait::type::miscellaneous::conditional
          <
            trait::type::transform::is_referenceable<_T>::value,
            is_nothrow_swappable_with
            <
              typename trait::type::transform::add_lvalue_reference<_T>::type,
              typename trait::type::transform::add_lvalue_reference<_T>::type
            >,
            trait::false_type
          >::type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_SWAPPABLE__
