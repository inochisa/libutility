
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_constructible

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_constructible
        template<class _T, typename... _Args>
        struct is_constructible :
          public trait::integral_constant<bool,
            __utility_is_constructible(_T, _Args...)>
        { };
      }
    }
  }
}

#else // __utility_has_is_constructible

# include<utility/trait/type/type_trait_special.hpp>
# include<utility/trait/type/categories/is_reference.hpp>
# include<utility/trait/type/categories/is_function.hpp>
# include<utility/trait/type/categories/is_void.hpp>
# include<utility/trait/type/transform/remove_cv_ref.hpp>
# include<utility/trait/type/transform/remove_all_extents.hpp>
# include<utility/trait/type/releations/is_same.hpp>
# include<utility/trait/type/releations/is_base_of.hpp>
# include<utility/trait/type/features/is_destructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        namespace __is_constructible_impl
        {
          template<typename _T>
          using __remove_cv_ref = trait::type::transform::remove_cv_reference<_T>;
          template<typename _T, typename... _Args>
          struct __is_constructible_helper;

          template<typename _To, typename _From>
          struct __is_invaild_base_to_derived_cast
          {
            static_assert(trait::type::categories::is_reference<_To>::value,
              "Can not convert to a lvalue"
            );
            using __rawFrom = typename __remove_cv_ref<_From>::type;
            using __rawTo = typename __remove_cv_ref<_To>::type;
            constexpr static bool value = trait::__type_and__<
              trait::__type_not__<
                trait::type::releations::is_same<__rawFrom,__rawTo>>,
              trait::type::releations::is_base_of<__rawFrom,__rawTo>,
              trait::__type_not__<__is_constructible_helper<__rawTo, _From>>>::value;
          };

          template<typename _To, typename _From>
          struct __is_invalid_lvalue_to_rvalue_cast : public
            trait::false_type
          { };

          template<typename _To_ref, typename _From_ref>
          struct __is_invalid_lvalue_to_rvalue_cast<_To_ref&&, _From_ref&>
          {
            using __rawFrom = typename __remove_cv_ref<_From_ref>::type;
            using __rawTo = typename __remove_cv_ref<_To_ref>::type;
            constexpr static bool value = trait::__type_and__<
              trait::__type_not__<
                trait::type::categories::is_function<__rawTo>>,
              trait::__type_or__<
                trait::type::releations::is_same<__rawFrom, __rawTo>,
                trait::type::releations::is_base_of<__rawTo, __rawFrom>>>::value;
          };

          struct __is_constructible_test_helper
          {
            private:
              template<typename _T>
              static void __help(_T);

            public:
              template<typename _To, typename _From,
                typename = decltype(__help<_To>(trait::type::special::declval<_From>()))>
              static trait::true_type __test_cast(int);

              template<typename _To, typename _From,
                typename = decltype(static_cast<_To>(trait::type::special::declval<_From>()))>
              static trait::integral_constant<bool,
                !__is_invaild_base_to_derived_cast<_To, _From>::value &&
                !__is_invalid_lvalue_to_rvalue_cast<_To, _From>::value>
                __test_cast(long);
              template<typename, typename>
              static trait::false_type __test_cast(...);

            public:
              template<typename _T, typename... _Args,
                typename = decltype(_T(trait::type::special::declval<_Args>()...))>
              static trait::true_type __test_nary(int);
              template<typename _T, typename...>
              static trait::false_type __test_nary(...);

            public:
              template<typename _T, typename _U, typename =
                decltype(new _T(trait::type::special::declval<_U>()))>
              static trait::type::features::is_destructible<_T>
                __test_unary(int);
              template<typename, typename>
              static trait::false_type __test_unary(...);
          };

          template<typename _T, bool =
            trait::type::categories::is_void<_T>::value>
          struct __is_default_constructible_test :
            public decltype(__is_constructible_test_helper::__test_nary<_T>(0))
          { };
          template<typename _T>
          struct __is_default_constructible_test<_T, true> : public
            trait::false_type
          { };
          template<typename _T>
          struct __is_default_constructible_test<_T[], false> : public
            trait::false_type
          { };
          template<typename _T, trait::size_t _Size>
          struct __is_default_constructible_test<_T[_Size], false>: public
            __is_default_constructible_test<typename
              trait::type::transform::remove_all_extents<_T>::type>
          { };
          template<typename _T, typename... _Args>
          struct __is_constructible_helper
          {
            static_assert(sizeof...(_Args) > 1, "");
            typedef
              decltype(__is_constructible_test_helper::__test_nary<_T, _Args...>(0)) type;
          };
          template<typename _T>
          struct __is_constructible_helper<_T> : public __is_default_constructible_test<_T>
          { };
          template<typename _T, typename _Arg>
          struct __is_constructible_helper<_T, _Arg> : public
            decltype(__is_constructible_test_helper::__test_unary<_T, _Arg>(0))
          { };
          template<typename _T, typename _Arg>
          struct __is_constructible_helper<_T&, _Arg> : public
            decltype(__is_constructible_test_helper::__test_unary<_T&, _Arg>(0))
          { };
          template<typename _T, typename _Arg>
          struct __is_constructible_helper<_T&&, _Arg> : public
            decltype(__is_constructible_test_helper::__test_unary<_T&&, _Arg>(0))
          { };
        }
        template<class _T, class... _Args>
        struct is_constructible : public
          __is_constructible_impl::__is_constructible_helper<_T, _Args...>::type
        { };
      }
    }
  }
}

#endif // __utility_has_is_constructible

#include<utility/trait/config/trait_undef.hpp>

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_CONSTRUCTIBLE__
