
#ifndef __UTILITY_MEMORY_DESTROY__
#define __UTILITY_MEMORY_DESTROY__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/memory/destroy_at.hpp>
#include<utility/trait/type/features/is_trivially_destructible.hpp>
#include<utility/trait/type/type_trait_special.hpp>

namespace utility
{
  namespace memory
  {
    namespace detail
    {
      template<typename _ForwardIterator,
        bool =
          trait::type::features::is_trivially_destructible<
            decltype(*trait::type::special::declval<_ForwardIterator>())
          >::value
      >
      struct __destroy
      {
        static inline void __aux(_ForwardIterator __first, _ForwardIterator __last)
        {
          for(; __first != __last; ++__first)
          {
            memory::destroy_at(
              memory::addressof(*__first)
            );
          }
        }
      };
      template<typename _ForwardIterator>
      struct __destroy<_ForwardIterator, true>
      {
        static inline void __aux(_ForwardIterator __first, _ForwardIterator __last)
        { }
      };
    }
    template<typename _ForwardIterator>
    void destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      detail::__destroy<_ForwardIterator>::__aux(__first, __last);
    }
  }
}

#endif // ! __UTILITY_MEMORY_DESTROY__
