

#ifndef __UTILITY_CONTAINER_HELPER_ALLOCATOR_DELETER__
#define __UTILITY_CONTAINER_HELPER_ALLOCATOR_DELETER__

#include<utility/config/utility_config.hpp>
#include<utility/memory/allocator_traits.hpp>

namespace utility
{
  namespace container
  {
    namespace helper
    {
      template<typename _Alloc>
      struct allocator_deleter
      {
        public:
          typedef _Alloc allocator_type;
          typedef utility::memory::allocator_traits<allocator_type>
            allocator_traits_type;
          typedef typename allocator_traits_type::pointer pointer;
          typedef typename allocator_traits_type::const_pointer const_pointer;

        public:
          allocator_type& __allocator;
          size_type       __length;

        public:
          void operator()(pointer _chunk) noexcept
          {
            allocator_traits_type::deallocate(
              __allocator, _chunk, __length
            );
          }
      };
    }
  }
} // utility


#endif // ! __UTILITY_CONTAINER_HELPER_ALLOCATOR_DELETER__
