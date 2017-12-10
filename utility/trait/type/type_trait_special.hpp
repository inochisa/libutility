
#ifndef ___UTILITY__TRAIT__SPECIAL__
#define ___UTILITY__TRAIT__SPECIAL__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace special
      {
        // declval
        namespace __declval_impl
        {
          template<typename T>
          T&& __declval_helper(int);
          template<typename T>
          T   __declval_helper(long);
        }
        template<typename T>
        decltype(__declval_impl::__declval_helper<T>(0))
          declval() noexcept;
      }
    }
  }
}

#endif // ! ___UTILITY__TRAIT__SPECIAL__
