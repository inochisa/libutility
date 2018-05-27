
#ifndef __UTILITY_TYPE_TRAIT_OPERATOR_EQ__
#define __UTILITY_TYPE_TRAIT_OPERATOR_EQ__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace op
      {
        // operatot == -> eq
        namespace __eq_impl
        {

          template<typename _T, typename _U>
          struct __eq_test
          {
            private:
              template<typename __T>
              static void __help(const __T&);

              template<typename __T, typename __U>
              static char __test(const __T&,decltype(operator==(trait::type::special::declval<_T>(),trait::type::special::declval<_U>()))* = 0);
              template<typename __T, typename __U>
              static __two __test(...);

            public:
              constexpr static bool value = sizeof(char) ==
                sizeof(decltype(__test<_T, _U>(trait::type::special::declval<_T>())));
          };
        }
        template<typename _T, typename _U = _T>
        struct eq :
          public trait::integral_constant<bool,
            __eq_impl::__eq_test<_T, _U>::value>
        { };

      }
    }
  }
}

#endif // ! __UTILITY_TYPE_TRAIT_OPERATOR_EQ__
