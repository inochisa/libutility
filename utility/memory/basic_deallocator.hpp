
#ifndef __UTILITY_MEMORY_BASIC_DEALLOCATOR__
#define __UTILITY_MEMORY_BASIC_DEALLOCATOR__

#include<utility/config/utility_config.hpp>
#include<utility/memory/allocator_traits.hpp>

namespace utility
{
  namespace memory
  {
    template<typename _Alloc>
    class basic_deallocator
    {
      public:
        typedef memory::allocator_traits<_Alloc>
          allocator_traits_type;

      public:
        typedef _Alloc      allocator_type;
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::size_type size_type;

      private:
        allocator_type& __allocator;
        size_type __size;
      public:
        basic_deallocator(
          allocator_type& __alloc, size_type __s = 1
        )noexcept: __allocator(__alloc), __size(__s)
        { }

        inline void operator()(pointer __ptr) noexcept
        { allocator_traits_type::deallocate(__allocator, __ptr, __size);}
    };
  }
}

#endif // ! __UTILITY_MEMORY_BASIC_DEALLOCATOR__
