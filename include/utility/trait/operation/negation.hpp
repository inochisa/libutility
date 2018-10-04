
#ifndef __UTILITY_TRAIT_OPERATION_NEGATION__
#define __UTILITY_TRAIT_OPERATION_NEGATION__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace operation
    {
      // negation
      template<typename _T>
      struct negation: __type_not__<_T>
      { };

#if !defined(__UTILITY_NO_CPP14__)
      template<typename _T>
      constexpr bool negation_v = negation<_T>::value;
#endif

    }
  }
}

#endif // ! __UTILITY_TRAIT_OPERATION_NEGATION__
