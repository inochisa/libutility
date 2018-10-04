
#ifndef __UTILITY_CONTAINER_HELPER_IN_PLACE_T__
#define __UTILITY_CONTAINER_HELPER_IN_PLACE_T__


/**
 * \file ignore_t.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace container
  {

    namespace helper
    {
      struct in_place_t
      { explicit in_place_t() = default;};
      __UTILITY_CPP17_INLINE__
      constexpr in_place_t in_place{};

      template<typename _T>
      struct in_place_type_t
      { explicit in_place_type_t() = default;};

#ifndef __UTILITY_NO_CPP14__
      template<typename _T>
      __UTILITY_CPP17_INLINE__
      constexpr in_place_type_t<_T> in_place_type{};
#endif // ! __UTILITY_NO_CPP14__

      template<size_t _I>
      struct in_place_index_t
      { explicit in_place_index_t() = default;};

#ifndef __UTILITY_NO_CPP14__
      template<size_t _I>
      __UTILITY_CPP17_INLINE__
      constexpr in_place_index_t<_I> in_place_index{};
#endif // ! __UTILITY_NO_CPP14__

    } // helper

    namespace helper_traits
    {
      template<typename _T>
      struct is_in_place_type: public trait::false_type
      { };

      template<typename _T>
      struct is_in_place_type<helper::in_place_type_t<_T>>:  public trait::true_type
      { };
    }
  }
}

#endif // ! __UTILITY_CONTAINER_HELPER_IN_PLACE_T__
