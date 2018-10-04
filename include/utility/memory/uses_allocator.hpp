
#ifndef __UTILITY_MEMORY_USES_ALLOCATOR__
#define __UTILITY_MEMORY_USES_ALLOCATOR__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>

#include<utility/trait/opt/__twochar__.hpp>

namespace utility
{
  namespace memory
  {
    namespace __detail
    {
      using trait::__opt__::__twochar__;
      using trait::type::releations::is_convertible;
      template<typename _T, typename _Alloc>
      struct __check_uses_allocator
      {
        private:
          template<typename _U>
          static __twochar__ __test(...);
          template<typename _U>
          static char __test(typename _U::allocator_type* = 0);

        public:
          constexpr static bool value = sizeof(__test<_T>(0)) == 1;
      };

      template<
        typename _T, typename _Alloc,
        bool = __check_uses_allocator<_T, _Alloc>::value
      >
      struct __uses_allocator: public trait::false_type
      { };

      template<typename _T, typename _Alloc>
      struct __uses_allocator: public trait::integral_constant<
        bool, is_convertible<_Alloc, typename _T::allocator_type>::value>
      { };
    }
    template<typename _T, typename _Alloc>
    struct uses_allocator: __detail::__uses_allocator<_T, _Alloc>
    { };

#if !defined(__UTILITY_NO_CPP14__)
      template<typename _T, typename _Alloc>
      constexpr bool uses_allocator_v = uses_allocator<_T, _Alloc>::value;
#endif

  }
}

#endif // ! __UTILITY_MEMORY_USES_ALLOCATOR__
