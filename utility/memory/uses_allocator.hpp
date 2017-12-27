
#ifndef __UTILITY_MEMORY_USES_ALLOCATOR__
#define __UTILITY_MEMORY_USES_ALLOCATOR__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>

namespace utility
{
  namespace memory
  {
    namespace __use_allocator_impl
    {
      using __two = utility::trait::__impl_helper::__twochar;

      template<typename _T>
      struct __has_allocator_type_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::allocator_type* = nullptr);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(__test<_T>(0)) == sizeof(char);
      };

      template<typename _T, typename _Alloc,
        bool = __has_allocator_type_test<_T>::value>
      struct __uses_allocator :
        public utility::trait::integral_constant<bool,
          ::utility::trait::type::releations::is_convertible<_Alloc, typename _T::allocator_type>::value>
      { };
      template<typename _T, typename _Alloc>
      struct __uses_allocator<_T, _Alloc, false> :
        public utility::trait::false_type
      { };

    }
    template<typename _T, typename _Alloc>
    struct uses_allocator :
      public __use_allocator_impl::__uses_allocator<_T, _Alloc>
    { };

  }
}

#endif // ! __UTILITY_MEMORY_USES_ALLOCATOR__
