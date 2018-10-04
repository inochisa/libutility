
#ifndef __UTILITY_FUNCTIONAL_REFERENCE_WRAPPER__
#define __UTILITY_FUNCTIONAL_REFERENCE_WRAPPER__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/forward.hpp>

#include<utility/functional/invoke.hpp>

#include<utility/trait/type/miscellaneous/invoke_result.hpp>
#include<utility/trait/type/features/is_nothrow_invocable.hpp>

#include<utility/memory/addressof.hpp>

namespace utility
{
  namespace functional
  {
    template<typename _T>
    class reference_wrapper
    {
      public:
        typedef _T type;

      private:
        type* __ptr;

      public:
        reference_wrapper(_T& __ref) noexcept:
          __ptr(memory::addressof(__ref))
        { }
        reference_wrapper(_T&&) = delete;
        reference_wrapper(const reference_wrapper&) noexcept = default;

      public:
        reference_wrapper& operator=(const reference_wrapper&) noexcept = default;

      public:
        operator type&() const noexcept
        { return *__ptr;}

      public:
        type& get() const noexcept
        { return *__ptr;}

      public:
        template<typename... _Args>
        typename trait::type::miscellaneous::invoke_result<_T&, _Args...>::type
        operator()(_Args&&... __args) const noexcept(
          trait::type::features::is_nothrow_invocable<_T&, _Args...>::value
        )
        { return invoke(this->get(), algorithm::forward<_Args>(__args)...);}
    };

    template<typename _T>
    struct unwrap_refwrapper_type
    { typedef _T type;};
    template<typename _T>
    struct unwrap_refwrapper_type<reference_wrapper<_T>>
    { typedef _T& type;};

    namespace __invoke_detail
    {
      template<bool _Object>
      struct __invoke<true, true, _Object, false, true>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __func, _Other&& __other, _Args&&... __args) noexcept(
          noexcept((__other.get().*__func)(algorithm::forward<_Args>(__args)...))
        ) -> decltype((__other.get().*__func)(algorithm::forward<_Args>(__args)...))
        {
          return (__other.get().*__func)(algorithm::forward<_Args>(__args)...);
        }
      };
      template<>
      struct __invoke<true, false, true, false, true>
      {
        template<typename _T, typename _Inn, typename _Other, typename... _Args>
        static inline auto __aux(_T _Inn::* __func, _Other&& __other, _Args&&... __args) noexcept(
          noexcept(__other.get().*__func)
        ) -> decltype(__other.get().*__func)
        {
          return __other.get().*__func;
        }
      };
    }
  }
}

#endif // ! __UTILITY_FUNCTIONAL_REFERENCE_WRAPPER__
