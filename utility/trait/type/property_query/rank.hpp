
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_RANK__
#define __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_RANK__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property_query
      {
        // rank
        template<typename _T>
        struct rank :
          public ::utility::trait::integral_constant<::utility::trait::size_t, 0>
        { };
        template<typename _T>
        struct rank<_T[]> :
          public ::utility::trait::integral_constant<
            ::utility::trait::size_t, rank<_T>::value+1>
        { };
        template<typename _T, ::utility::trait::size_t _size>
        struct rank<_T[_size]> :
          public ::utility::trait::integral_constant<
            ::utility::trait::size_t, rank<_T>::value+1>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_QUERY_RANK__
