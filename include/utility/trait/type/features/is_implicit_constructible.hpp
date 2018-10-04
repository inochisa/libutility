
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_IMPLICIT_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_IMPLICIT_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__twochar__.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/features/is_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_implicit_constructible
        namespace __is_implicit_constructible
        {
          using __two = trait::__opt__::__twochar__;

          template<typename _T, typename... _Args>
          struct __is_implicit_constructible_test
          {
            private:
              template<typename __T>
              static void __help(const __T&);

              template<typename __T, typename... __Args>
              static char __test(const __T&,
                decltype(__help<const _T&>(
                  { trait::type::special::declval<__Args>()...}))* = 0);

              template<typename __T, typename... __Args>
              static __two __test(...);

            public:
              constexpr static bool value = sizeof(char) ==
                sizeof(decltype(
                  __test<_T, _Args...>(trait::type::special::declval<_T>())
                ));
          };
          template<bool, typename _T, typename... _Args>
          struct __is_implicit_constructible_helper;

          template<typename _T, typename... _Args>
          struct __is_implicit_constructible_helper<false, _T, _Args...> :
            public trait::false_type
          { };
          template<typename _T, typename... _Args>
          struct __is_implicit_constructible_helper<true, _T, _Args...> :
            public trait::integral_constant<bool,
              __is_implicit_constructible_test<_T, _Args...>::value>
          { };
        }
        template<typename _T, typename... _Args>
        struct is_implicit_constructible :
          public __is_implicit_constructible::__is_implicit_constructible_helper<
            trait::type::features::is_constructible<_T, _Args...>::value,
            _T, _Args...>
        { };

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_IMPLICIT_CONSTRUCTIBLE__
