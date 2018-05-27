
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_DESTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_DESTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/categories/is_function.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/transform/remove_all_extents.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_destructible
        namespace __is_destructible_impl
        {
          template<typename _T>
          using __int = trait::__impl_helper::__int_type<_T>;
          using __two = trait::__impl_helper::__twochar;

          template<typename _T>
          struct __is_destructible_test_helper
          {
            private:
              template<typename __T>
              static char __test(typename __int<
                decltype(trait::type::special::declval<__T&>().~__T())
                >::type);
              template<typename __T>
              static __two __test(...);
            public:
              constexpr static bool value = sizeof(__test<_T>(0)) == sizeof(char);
          };

          template<typename _T, bool>
          struct __is_destructible_test;

          template<typename _T>
          struct __is_destructible_test<_T, false> : public
            trait::integral_constant<bool,
            __is_destructible_test_helper<typename
              trait::type::transform::remove_all_extents<_T>::type
            >::value>
          { };
          template<typename _T>
          struct __is_destructible_test<_T, true> :
            public trait::true_type
          { };

          template<typename _T, bool>
          struct __is_destructible_helper;

          template<typename _T>
          struct __is_destructible_helper<_T, false> :
            public __is_destructible_test<_T,
              trait::type::categories::is_reference<_T>::value>
          { };
          template<typename _T>
          struct __is_destructible_helper<_T, true> :
            public trait::false_type
          { };
        }
        template<typename _T>
        struct is_destructible : public
          __is_destructible_impl::__is_destructible_helper<_T,
            trait::type::categories::is_function<_T>::value>
        { };
        template<typename _T>
        struct is_destructible<_T[]> : public trait::false_type
        { };
        template<>
        struct is_destructible<void> : public trait::false_type
        { };
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_DESTRUCTIBLE__
