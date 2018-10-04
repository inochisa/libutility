
#ifndef __UTILITY_FUNCTIONAL_CREF__
#define __UTILITY_FUNCTIONAL_CREF__

#include<utility/functional/reference_wrapper.hpp>

namespace utility
{
  namespace functional
  {
    template<typename _T>
    inline reference_wrapper<const _T> cref(const _T& _val) noexcept
    { return reference_wrapper<const _T>{_val}};
    template<typename _T>
    inline reference_wrapper<const _T> cref(
      reference_wrapper<_T> _wrapper
    ) noexcept
    { return reference_wrapper<const _T>{_wrapper.get()}};
    template<typename _T>
    inline void cref(const _T&&) = delete;
  }
}

#endif // ! __UTILITY_FUNCTIONAL_CREF__
