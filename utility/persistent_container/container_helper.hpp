
#ifndef __UTILITY_PERSISTENT_CONTAINER_CONTAINER_HELPER__
#define __UTILITY_PERSISTENT_CONTAINER_CONTAINER_HELPER__

/**
 * \file container_helper.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/initializer_list.hpp>
#include<utility/memory/allocator_helper.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace persistent_container
  {
    using iterator::is_iterator;
    using iterator::is_vaild_iterator;
    using memory::allocator_arg_t;
    using memory::allocator_arg;
    using container::initializer_list;

  }

  namespace p_container
  {
    using iterator::is_iterator;
    using iterator::is_vaild_iterator;
    using memory::allocator_arg_t;
    using memory::allocator_arg;
    using container::initializer_list;

  }
}

#endif // ! __UTILITY_PERSISTENT_CONTAINER_CONTAINER_HELPER__
