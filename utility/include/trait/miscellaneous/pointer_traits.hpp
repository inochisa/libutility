
#ifndef __UTILITY_MISCELLANEOUS_POINTER_TRAITS__
#define __UTILITY_MISCELLANEOUS_POINTER_TRAITS__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>
#include<utility/trait/type/categories/is_void.hpp>
#include<utility/memory/addressof.hpp>

namespace utility
{
  namespace trait
  {
    namespace miscellaneous
    {
      namespace __pointer_trait_impl
      {
        template<class _T>
        struct __has_element_type
        {
          private:
            struct ___
            { char __none[2];};
            template<typename _U>
            static ___ __test(...);
            template<typename _U>
            static char ___test(typename _U::element_type* = 0);
          public:
            static const bool value = sizeof(__test<_T>(0)) == 1;
        };

        template<class _T_ptr, bool = __has_element_type<_T_ptr>::value>
        struct __pointer_has_element_type;

        template<class _T_ptr>
        struct __pointer_has_element_type<_T_ptr, true>
        { typedef typename _T_ptr::element_type type;};
        template<template<typename, typename...>class _C, typename _T, typename... _Args>
        struct __pointer_has_element_type<_C<_T, _Args...>, false>
        { typedef _T type;};
        template<template<typename, typename...>class _C, typename _T,
        typename... _Args>
        struct __pointer_has_element_type<_C<_T, _Args...>, true>
        { typedef typename _C<_T, _Args...>::element_type type;};

        template<class _T>
        struct __has_difference_type
        {
          private:
            struct ___
            { char __none[2];};
            template<typename _U>
            static ___ __test(...);
            template<typename _U>
            static char ___test(typename _U::difference_type* = 0);
          public:
            static const bool value = sizeof(__test<_T>(0)) == 1;
        };

        template<typename _T_ptr, bool = __has_difference_type<_T_ptr>::value>
        struct __pointer_has_difference_type
        { typedef ptrdiff_t type;};

        template<typename _T_ptr>
        struct __pointer_has_difference_type<_T_ptr, true>
        { typedef typename _T_ptr::difference_type type;};

        template<typename _T, typename _U>
        struct __has_rebind
        {
          private:
            struct ___
            { char __none[2];};
            template<typename _R>
            static ___ __test(...);
            template<typename _R>
            static char ___test(typename _R::template rebind<_T>* = 0);
          public:
            static const bool value = sizeof(__test<_T>(0)) == 1;
        };

        template<typename _T, typename _U,
          bool = __has_rebind<_T, _U>::value>
        struct __pointer_has_rebind
        { typedef typename _T::template rebind<_U> type;};
        template<template<typename, typename...>class _C, typename _T,
          typename... _Args, typename _U>
        struct __pointer_has_rebind<_C<_T, _Args...>, _U, true>
        { typedef typename _C<_T, _Args...>::template rebind<_U> type;};
        template<template<typename, typename...>class _C, typename _T,
        typename... _Args, typename _U>
        struct __pointer_has_rebind<_C<_T, _Args...>, _U, false>
        { typedef _C<_T, _Args...> type;};

      }
      template<typename _T_ptr>
      struct pointer_traits
      {
        public:
          typedef _T_ptr pointer;
          typedef typename
            __pointer_trait_impl::__pointer_has_element_type<pointer>::type element_type;
          typedef typename
          __pointer_trait_impl::__pointer_has_difference_type<pointer>::type difference_type;

          template<typename _U>
          using rebind = typename
          __pointer_trait_impl::__pointer_has_rebind<pointer, _U>::type;
        private:
          struct __fail { };
        public:
          static pointer pointer_to(typename
            trait::type::miscellaneous::conditional<
              trait::type::categories::is_void<element_type>::value,
              __fail,
              element_type>::type& __ref)
          { return pointer::pointer_to(__ref);}
      };

      template<typename _T_ptr>
      struct pointer_traits<_T_ptr*>
      {
        public:
          typedef _T_ptr* pointer;
          typedef _T_ptr element_type;
          typedef ptrdiff_t difference_type;

          template<typename _U>
          using rebind = _U*;
        private:
          struct __fail { };
        public:
          static pointer pointer_to(typename
            trait::type::miscellaneous::conditional<
              trait::type::categories::is_void<element_type>::value,
              __fail,
              element_type>::type& __ref)
          { return memory::addressof(__ref);}
      };
    }
  }
}

#endif // ! __UTILITY_MISCELLANEOUS_POINTER_TRAITS__
