
#ifndef __UTILITY_ALGORITHM_FORWARD__
#define __UTILITY_ALGORITHM_FORWARD__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/categories/is_lvalue_reference.hpp>
#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    _T&& forward(
      typename trait::type::transform::remove_reference<_T>::type& __val) noexcept
    { return static_cast<_T&&>(__val);}

    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    _T&& forward(
      typename trait::type::transform::remove_reference<_T>::type&& __val) noexcept
    {
      static_assert(
        !trait::type::categories::is_lvalue_reference<_T>::value,
        "Can not transform a lvalue to a rvalue!"
      );
      return static_cast<_T&&>(__val);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FORWARD__
