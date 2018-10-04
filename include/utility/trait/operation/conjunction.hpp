
#ifndef __UTILITY_TRAIT_OPERATION_CONJUNCTION__
#define __UTILITY_TRAIT_OPERATION_CONJUNCTION__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace operation
    {
      // conjunction
      template<typename... _Types>
      struct conjunction: __type_and__<_Types...>
      { };

#if !defined(__UTILITY_NO_CPP14__)
      template<typename... _Types>
      constexpr bool conjunction_v = conjunction<_Types...>::value;
#endif

    }
  }
}

#endif // ! __UTILITY_TRAIT_OPERATION_CONJUNCTION__
