
#ifndef __UTILITY_TRAIT_OPERATION_DISJUNCTION__
#define __UTILITY_TRAIT_OPERATION_DISJUNCTION__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace operation
    {
      // disjunction
      template<typename... _Types>
      struct disjunction: __type_or__<_Types...>
      { };

#if !defined(__UTILITY_NO_CPP14__)
      template<typename... _Types>
      constexpr bool disjunction_v = disjunction<_Types...>::value;
#endif

    }
  }
}

#endif // ! __UTILITY_TRAIT_OPERATION_DISJUNCTION__
