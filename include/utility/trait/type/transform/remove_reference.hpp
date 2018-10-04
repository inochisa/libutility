
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_REFERENCE__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_REFERENCE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_reference
        template<typename _T>
        struct remove_reference
        { typedef _T type;};
        template<typename _T>
        struct remove_reference<_T&>
        { typedef _T type;};
        template<typename _T>
        struct remove_reference<_T&&>
        { typedef _T type;};

        template<typename _T>
        using remove_reference_t = typename remove_reference<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_REFERENCE__
