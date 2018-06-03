
#ifndef __UTILITY_TRAIT_TRAIT_HELPER__
#define __UTILITY_TRAIT_TRAIT_HELPER__

#include<utility/config/utility_config.hpp>
#include<utility/trait/integral_constant.hpp>

// Forward declaration
namespace utility
{
  namespace functional
  {
    template<typename _T>
    class reference_wrapper;
  }
}

namespace utility
{
  namespace trait
  {
    // type declaration
    template<typename ...>
    using void_t = void;
    using nullptr_t = decltype(nullptr);
    using size_t = decltype(sizeof(char));

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
    template<bool _Default = false>
    struct unsupport_trait
    {
      constexpr static bool value = _Default;
      typedef bool value_type;
      typedef unsupport_trait type;
      constexpr operator value_type() const noexcept
      { return _Default;}
      constexpr value_type operator()() const noexcept
      { return _Default;}
    };

    // meta programming operators
    namespace __logical
    {
      template<bool _B>
      struct __not__;
      template<>
      struct __not__<true> : public trait::false_type
      { };
      template<>
      struct __not__<false> : public trait::true_type
      { };

      template<bool... _LB>
      struct __and__;
      template<bool... _LB>
      struct __and__<true, _LB...> : public __and__<_LB...>
      { };
      template<bool... _LB>
      struct __and__<false, _LB...> : public trait::false_type
      { };
      template<>
      struct __and__<false> : public trait::false_type
      { };
      template<>
      struct __and__<true> : public trait::true_type
      { };

      template<bool... _LB>
      struct __or__;
      template<bool... _LB>
      struct __or__<true, _LB...> : public trait::true_type
      { };
      template<bool... _LB>
      struct __or__<false, _LB...> : public __or__<_LB...>
      { };
      template<>
      struct __or__<false> : public trait::false_type
      { };
      template<>
      struct __or__<true> : public trait::true_type
      { };

      template<bool... _LB>
      struct __xor__;
      template<>
      struct __xor__<true> : public trait::true_type
      { };
      template<>
      struct __xor__<false> : public trait::false_type
      { };
      template<bool _B1, bool _B2>
      struct __xor__<_B1, _B2> : public trait::true_type
      { };
      template<>
      struct __xor__<true, true> : public trait::false_type
      { };
      template<>
      struct __xor__<false, false> : public trait::false_type
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
        public trait::true_type
      { };
      template<>
      struct __type_and_impl__<false> :
        public trait::false_type
      { };
      template<typename _T, typename... _Ts>
      struct __type_and_impl__<true, _T, _Ts...> :
        public __type_and_impl__<_T::value, _Ts...>
      { };
      template<typename _T, typename... _Ts>
      struct __type_and_impl__<false, _T, _Ts...> :
        public trait::false_type
      { };

      template<bool _B = false, typename... _Ts>
      struct __type_or_impl__;
      template<>
      struct __type_or_impl__<true> :
        public trait::true_type
      { };
      template<>
      struct __type_or_impl__<false> :
        public trait::false_type
      { };
      template<typename _T, typename... _Ts>
      struct __type_or_impl__<true, _T, _Ts...> :
        public trait::true_type
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
      {
        __empty() = delete;
        __empty(const __empty&) = delete;
        __empty(__empty&&) = delete;
        ~__empty() = delete;
      };
      template<typename... _Ts>
      struct __template_empty
      {
        __template_empty() = delete;
        __template_empty(const __template_empty&) = delete;
        __template_empty(__template_empty&&) = delete;
        ~__template_empty() = delete;
      };

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

      template<typename _T, typename _U>
      struct __wrapper
      { typedef _T type;};
      template<typename _T, typename _U>
      struct __wrapper<_T, functional::reference_wrapper<_U>>
      { typedef _U& type;};

      template<typename _T>
      struct __is_reference_wrapper : public trait::false_type
      { };
      template<typename _T>
      struct __is_reference_wrapper<functional::reference_wrapper<_T>> :
        public trait::false_type
      { };
    }
  }
}


#endif // ! __UTILITY_TRAIT_TRAIT_HELPER__
