
#ifndef __UTILITY_TRAIT_TRAIT_HELPER__
#define __UTILITY_TRAIT_TRAIT_HELPER__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace trait
  {
    // type declaration
    template<typename ...>
    using void_t = void;
    using nullptr_t = decltype(nullptr);
    using size_t = decltype(sizeof(char));

    // helper class and declaration
    template<typename _type, _type _val>
    struct integral_constant
    {
      constexpr static _type value = _val;
      typedef _type value_type;
      typedef integral_constant<_type, _val> type;
      constexpr operator value_type() const noexcept
      { return value;}
      constexpr value_type operator()() const noexcept
      { return value;}
    };
    template<bool _B>
    using bool_constant = ::utility::trait::integral_constant<bool, _B>;
    using true_type   = ::utility::trait::bool_constant<true>;
    using false_type  = ::utility::trait::bool_constant<false>;
    template<typename _T>
    struct good_type
    { typedef _T type;};
    template<typename _T>
    struct bad_type
    { };

    /**
    * @brief unsupport tag
    * @author Inochi Amaoto
    * @warning this tag does not inherit from integral_constant,
    *          it's a independent class
    */
    struct unsupport_trait
    {
      constexpr static bool value = false;
      typedef bool value_type;
      typedef unsupport_trait type;
      constexpr operator value_type() const noexcept
      { return false;}
      constexpr value_type operator()() const noexcept
      { return false;}
    };

    // meta programming operators
    namespace __logical
    {
      template<bool _B>
      struct __not__;
      template<>
      struct __not__<true> : public ::utility::trait::false_type
      { };
      template<>
      struct __not__<false> : public ::utility::trait::true_type
      { };

      template<bool... _LB>
      struct __and__;
      template<bool... _LB>
      struct __and__<true, _LB...> : public __and__<_LB...>
      { };
      template<bool... _LB>
      struct __and__<false, _LB...> : public ::utility::trait::false_type
      { };
      template<>
      struct __and__<false> : public ::utility::trait::false_type
      { };
      template<>
      struct __and__<true> : public ::utility::trait::true_type
      { };

      template<bool... _LB>
      struct __or__;
      template<bool... _LB>
      struct __or__<true, _LB...> : public ::utility::trait::true_type
      { };
      template<bool... _LB>
      struct __or__<false, _LB...> : public __or__<_LB...>
      { };
      template<>
      struct __or__<false> : public ::utility::trait::false_type
      { };
      template<>
      struct __or__<true> : public ::utility::trait::true_type
      { };

      template<bool... _LB>
      struct __xor__;
      template<>
      struct __xor__<true> : public ::utility::trait::true_type
      { };
      template<>
      struct __xor__<false> : public ::utility::trait::false_type
      { };
      template<bool _B1, bool _B2>
      struct __xor__<_B1, _B2> : public ::utility::trait::true_type
      { };
      template<>
      struct __xor__<true, true> : public ::utility::trait::false_type
      { };
      template<>
      struct __xor__<false, false> : public ::utility::trait::false_type
      { };
      template<bool _B, bool... _LB>
      struct __xor__<_B, _LB...> :
        public __xor__<_B, __xor__<_LB...>::value>
      { };

      template<typename _T>
      struct __type_not__ : public __not__<_T::value>
      { };

      template<bool _B = true, typename... _Ts>
      struct __type_and_impl__;
      template<>
      struct __type_and_impl__<true> :
        public ::utility::trait::true_type
      { };
      template<>
      struct __type_and_impl__<false> :
        public ::utility::trait::false_type
      { };
      template<typename _T, typename... _Ts>
      struct __type_and_impl__<true, _T, _Ts...> :
        public __type_and_impl__<_T::value, _Ts...>
      { };
      template<typename _T, typename... _Ts>
      struct __type_and_impl__<false, _T, _Ts...> :
        public ::utility::trait::false_type
      { };

      template<bool _B = false, typename... _Ts>
      struct __type_or_impl__;
      template<>
      struct __type_or_impl__<true> :
        public ::utility::trait::true_type
      { };
      template<>
      struct __type_or_impl__<false> :
        public ::utility::trait::false_type
      { };
      template<typename _T, typename... _Ts>
      struct __type_or_impl__<true, _T, _Ts...> :
        public ::utility::trait::true_type
      { };
      template<typename _T, typename... _Ts>
      struct __type_or_impl__<false, _T, _Ts...> :
        public __type_or_impl__<_T::value, _Ts...>
      { };
    }

    using __logical::__not__;
    using __logical::__and__;
    using __logical::__or__;
    using __logical::__xor__;
    using __logical::__type_not__;
    template<typename _T, typename... _Ts>
    using __type_and__ = __logical::__type_and_impl__<true, _T, _Ts...>;
    template<typename _T, typename... _Ts>
    using __type_or__ = __logical::__type_or_impl__<false, _T, _Ts...>;

    namespace wrapper
    {
      template<typename T>
      struct reference_wrapper;
      template<typename T>
      struct lvalue_reference_wrapper;
      template<typename T>
      struct rvalue_reference_wrapper;
      template<typename T>
      struct pointer_wrapper;
    }

    namespace __impl_helper
    {
      template<typename>
      struct __int_type
      { typedef int type;};

      struct __empty
      { };
      template<typename... _Ts>
      struct __template_empty
      { };

      template<typename _Fp, typename _Sp>
      struct __type_pair
      {
        typedef _Fp first;
        typedef _Sp second;
      };

      struct __twochar
      { char __tmp[2];};
      struct __ldouble
      { long double __ld;};

      struct __none
      {
        __none() = delete;
        __none(const __none&)=delete;
        __none& operator=(const __none&)=delete;
        ~__none()=delete;
      };

      typedef __type_pair<signed char,
              __type_pair<signed short,
              __type_pair<signed int,
              __type_pair<signed long,
              __type_pair<signed long long,
              __none>>>>>
              __signed_type;
      typedef __type_pair<signed char,
              __type_pair<signed short,
              __type_pair<signed int,
              __type_pair<signed long,
              __type_pair<signed long long,
              __none>>>>>
              __signed_type;

    }
  }
}


#endif // ! __UTILITY_TRAIT_TRAIT_HELPER__
