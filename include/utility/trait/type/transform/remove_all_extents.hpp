
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL_EXTENT__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL_EXTENT__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // remove_all_extents
        template<typename _T>
        struct remove_all_extents
        { typedef _T type;};
        template<typename _T>
        struct remove_all_extents<_T[]>
        { typedef typename remove_all_extents<_T>::type type;};
        template<typename _T, size_t _size>
        struct remove_all_extents<_T[_size]>
        { typedef typename remove_all_extents<_T>::type type;};

        template<typename _T>
        using remove_all_extents_t = typename remove_all_extents<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL_EXTENT__
