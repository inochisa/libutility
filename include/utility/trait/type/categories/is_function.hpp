
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNCTION__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNCTION__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_function
        template<typename>
        struct is_function :
          public trait::false_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...)> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...)> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) volatile> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) volatile &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) volatile &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) volatile> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) volatile &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) volatile &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const volatile> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const volatile &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args...) const volatile &&> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const volatile> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const volatile &> :
          public trait::true_type
        { };
        template<typename _Fn, typename... _Args>
        struct is_function<_Fn(_Args..., ...) const volatile &&> :
          public trait::true_type
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_function_v = is_function<_T>::value;
#endif

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNCTION__
