
#ifndef __UTILITY_TRAIT_OPT___CONSTANT____
#define __UTILITY_TRAIT_OPT___CONSTANT____

namespace utility
{
  namespace trait
  {
    namespace __opt__
    {
      template<typename _Type, _Type _val>
      struct __constant__
      {
        constexpr static _Type value = _val;
        typedef _Type type;
      };
    }
  }
}

#endif // ! __UTILITY_TRAIT_OPT___CONSTANT____
