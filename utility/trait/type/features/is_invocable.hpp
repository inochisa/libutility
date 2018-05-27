
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_INVOCABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_INVOCABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/miscellaneous/invoke_result.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        namespace __invoke_related
        {
          using namespace trait::type::miscellaneous::__invoke_related;
          using trait::void_t;
          using trait::__type_and__;

          template<bool/*Select*/, typename _Res, typename _T, typename = void>
          struct __is_invocable_helper :
            public trait::false_type
          { };
          template<typename _Res, typename _T>
          struct __is_invocable_helper<false, _Res, _T, void_t<typename _Res::type>> :
            public trait::true_type
          { };
          template<typename _Res, typename _T>
          struct __is_invocable_helper<true, _Res, _T, void_t<typename _Res::type>> :
            public trait::integral_constant<bool,
              trait::type::releations::is_convertible<typename _Res::type, _T>::value>
          { };

          template<typename _Tag, typename _Fn, typename... _Args>
          struct __is_noexcept_invoke_test
          { constexpr static bool value = false;};
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __is_noexcept_invoke_test<__invoke_member_function_unpacked, _Fn, _Arg, _Args...>
          {
            private:
              typedef typename __wrapper<_Arg, typename __decay<_Arg>::type>::type _Ori;
            public:
              constexpr static bool value = noexcept(((trait::type::special::declval<_Ori>()).*trait::type::special::declval<_Fn>())(trait::type::special::declval<_Args>()...));
          };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __is_noexcept_invoke_test<__invoke_member_function_packed, _Fn, _Arg, _Args...>
          {
            public:
              constexpr static bool value = noexcept(((*trait::type::special::declval<_Arg>()).*trait::type::special::declval<_Fn>())(trait::type::special::declval<_Args>()...));
          };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __is_noexcept_invoke_test<__invoke_member_object_unpacked, _Fn, _Arg, _Args...>
          {
            private:
              typedef typename __wrapper<_Arg, typename __decay<_Arg>::type>::type _Ori;
            public:
              constexpr static bool value = noexcept(trait::type::special::declval<_Ori>().*trait::type::special::declval<_Fn>());
          };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __is_noexcept_invoke_test<__invoke_member_object_packed, _Fn, _Arg, _Args...>
          {
            public:
              constexpr static bool value = noexcept((*trait::type::special::declval<_Arg>()).*trait::type::special::declval<_Fn>());
          };
          template<typename _Fn, typename... _Args>
          struct __is_noexcept_invoke_test<__invoke_operators, _Fn, _Args...>
          {
            public:
              constexpr static bool value = noexcept(trait::type::special::declval<_Fn>()(trait::type::special::declval<_Args>()...));
          };

        }
        // is_invocable
        template<class _Fn, typename... _ArgTypes>
        struct is_invocable :
          public __invoke_related::__is_invocable_helper<
            false, typename __invoke_related::__invoke_result<_Fn, _ArgTypes...>::type,
            void>
        { };

        // is_invocable_r
        template<typename _R, class _Fn, typename... _ArgTypes>
        struct is_invocable_r :
          public __invoke_related::__is_invocable_helper<
            true, typename __invoke_related::__invoke_result<_Fn, _ArgTypes...>::type,
            _R>
        { };

        // is_nothrow_invocable
        template<class _Fn, typename... _ArgTypes>
        struct is_nothrow_invocable :
          public __type_and__<is_invocable<_Fn, _ArgTypes...>,
            __invoke_related::__is_noexcept_invoke_test<
              typename __invoke_related::__invoke_result<_Fn, _ArgTypes...>::invoke_tag,
              _Fn, _ArgTypes...>
          >
        { };

        // is_nothrow_invocable_r
        template<typename _R, class _Fn, typename... _ArgTypes>
        struct is_nothrow_invocable_r :
          public __type_and__<is_invocable_r<_R, _Fn, _ArgTypes...>,
            __invoke_related::__is_noexcept_invoke_test<
              typename __invoke_related::__invoke_result<_Fn, _ArgTypes...>::invoke_tag,
              _Fn, _ArgTypes...>
          >
        { };

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_INVOCABLE__
