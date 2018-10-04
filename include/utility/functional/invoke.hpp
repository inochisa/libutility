
#ifndef __UTILITY_FUNCTIONAL_INVOKE__
#define __UTILITY_FUNCTIONAL_INVOKE__

#include<utility/config/utility_config.hpp>
#include<utility/trait/trait_helper.hpp>

#include<utility/algorithm/forward.hpp>

#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/property_query/belong_to.hpp>
#include<utility/trait/type/categories/is_member_pointer.hpp>
#include<utility/trait/type/categories/is_member_object_pointer.hpp>
#include<utility/trait/type/categories/is_member_function_pointer.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>
#include<utility/trait/type/features/is_invocable.hpp>
#include<utility/trait/type/features/is_nothrow_invocable.hpp>
#include<utility/trait/type/miscellaneous/invoke_result.hpp>

namespace utility
{
  namespace functional
  {
    namespace __invoke_detail
    {
      using namespace trait::type::miscellaneous::__invoke_related;
      using trait::__opt__::__is_reference_wrapper__;

      template<typename _T>
      struct __belong_to
      { typedef void type;};
      template<typename _T, class _Inn>
      struct __belong_to<_T _Inn::*>
      { typedef _Inn type;};


      template<
        bool /*invocable*/,
        bool /*Member_function*/,
        bool /*Object*/,
        bool /*conditions*/,
        bool /*is_wrapper*/
      >
      struct __invoke;

      template<bool _Conditions, bool _Is_wrapper>
      struct __invoke<true, false, false, _Conditions, _Is_wrapper>
      {
        template<typename _Fn, typename... _Args>
        static inline auto __aux(_Fn&& __func, _Args&&... __args) noexcept(
          noexcept(algorithm::forward<_Fn>(__func)(algorithm::forward<_Args>(__args)...))
        ) -> decltype(algorithm::forward<_Fn>(__func)(algorithm::forward<_Args>(__args)...))
        {
          return algorithm::forward<_Fn>(__func)(algorithm::forward<_Args>(__args)...);
        }
      };
      template<bool _Object, bool _Is_wrapper>
      struct __invoke<true, true, _Object, true, _Is_wrapper>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __func, _Other&& __other, _Args&&... __args) noexcept(
          noexcept((algorithm::forward<_Other>(__other).*__func)(algorithm::forward<_Args>(__args)...))
        ) -> decltype((algorithm::forward<_Other>(__other).*__func)(algorithm::forward<_Args>(__args)...))
        {
          return (algorithm::forward<_Other>(__other).*__func)(algorithm::forward<_Args>(__args)...);
        }
      };
      template<bool _Object>
      struct __invoke<true, true, _Object, false, false>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __func, _Other&& __other, _Args&&... __args) noexcept(
          noexcept((algorithm::forward<_Other>(__other).*__func)(algorithm::forward<_Args>(__args)...))
        ) -> decltype((algorithm::forward<_Other>(__other).*__func)(algorithm::forward<_Args>(__args)...))
        {
          return ((*algorithm::forward<_Other>(__other)).*__func)(algorithm::forward<_Args>(__args)...);
        }
      };
      template<bool _Is_wrapper>
      struct __invoke<true, false, true, true, _Is_wrapper>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __mem, _Other&& __other, _Args&&... __args) noexcept(
          noexcept(algorithm::forward<_Other>(__other).*__mem)
        ) -> decltype(algorithm::forward<_Other>(__other).*__mem)
        {
          return algorithm::forward<_Other>(__other).*__mem;
        }
      };
      template<>
      struct __invoke<true, false, true, false, false>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __mem, _Other&& __other, _Args&&... __args) noexcept(
          noexcept((*algorithm::forward<_Other>(__other)).*__mem)
        ) -> decltype((*algorithm::forward<_Other>(__other)).*__mem)
        {
          return (*algorithm::forward<_Other>(__other)).*__mem;
        }
      };
    }
    template<typename _Fn>
    inline auto invoke(_Fn&& __func) noexcept(
      trait::type::features::is_invocable<_Fn>::value
    ) -> typename trait::type::miscellaneous::invoke_result<_Fn>::type
    {
      typedef __invoke_detail::__invoke<
        trait::type::features::is_invocable<_Fn>::value,
        false, false, false, false
      > __invoke_object;
      return __invoke_object::__aux(algorithm::forward<_Fn>(__func));
    }
    template<typename _Fn, typename _Other, typename... _Args>
    inline auto invoke(_Fn&& __func, _Other&& __other, _Args&&... __args) noexcept(
      trait::type::features::is_invocable<_Fn, _Other, _Args...>::value
    ) -> typename trait::type::miscellaneous::invoke_result<_Fn, _Other, _Args...>::type
    {
      typedef typename trait::type::miscellaneous::conditional<
        trait::type::categories::is_member_pointer<_Fn>::value,
        /*typename trait::type::property_query::belong_to<_Fn>::type,*/
        typename __invoke_detail::__belong_to<_Fn>::type,
        void
      >::type __base_type;
      typedef typename trait::type::transform::decay<_Other>::type __Object;
      typedef __invoke_detail::__invoke<
        trait::type::features::is_invocable<_Fn, _Other, _Args...>::value,
        trait::type::categories::is_member_function_pointer<_Fn>::value,
        trait::type::categories::is_member_object_pointer<_Fn>::value,
        trait::type::releations::is_base_of<__base_type, __Object>::value,
        __invoke_detail::__is_reference_wrapper__<__Object>::value
      > __invoke_object;
      return __invoke_object::__aux(
        algorithm::forward<_Fn>(__func),
        algorithm::forward<_Other>(__other),
        algorithm::forward<_Args>(__args)...
      );
    }
  }
}

#endif // ! __UTILITY_FUNCTIONAL_INVOKE__
