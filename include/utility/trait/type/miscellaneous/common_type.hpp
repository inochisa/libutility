
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_COMMON_TYPE__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_COMMON_TYPE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__empty__.hpp>
#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/type_trait_special.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // common_type
        namespace __common_type_impl
        {
          using trait::__opt__::__empty__;

          template<typename _T, typename _U>
          struct __common_type_two_helper
          {
            private:
              template<typename __T, typename __U>
              static typename
              trait::type::transform::decay<decltype(
                true ?
                trait::type::special::declval<__T>() :
                trait::type::special::declval<__U>())>
              __test(int);
              template<typename, typename>
              static __empty__ __test(...);

            public:
              typedef decltype(__test<_T, _U>(0)) type;
          };

          template<typename _T>
          struct __common_type_unfold_helper
          {
            private:
              template<typename __T>
              static typename __T::type __test(int);
              template<typename>
              static __empty__ __test(...);

            public:
              typedef decltype(__test<_T>(0)) type;
          };
          template<typename... _Args>
          struct __common_type_helper
          { };

          template<typename _T, typename... _Args>
          struct __common_type_wrapper
          { typedef __common_type_helper<_T, _Args...> type;};
          template<typename... _Args>
          struct __common_type_wrapper<__empty__, _Args...>
          { typedef __empty__ type;};

          template<typename _T>
          struct __common_type_helper<_T>
          { typedef typename trait::type::transform::decay<_T>::type type;};

          template<typename _T, typename _U>
          struct __common_type_helper<_T, _U> : public
            __common_type_two_helper<_T, _U>::type
          { };

          template<typename _T, typename _U, typename... _Args>
          struct __common_type_helper<_T, _U, _Args...> : public
            __common_type_wrapper<typename
              __common_type_unfold_helper<
                __common_type_helper<_T, _U>
                >::type, _Args...>::type
          { };
        }
        template<typename... _Ts>
        struct common_type : public
          __common_type_impl::__common_type_helper<_Ts...>
        { };

        template<typename... _Ts>
        using common_type_t = typename common_type<_Ts...>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_COMMON_TYPE__
