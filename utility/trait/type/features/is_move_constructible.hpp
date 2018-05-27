
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/features/is_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_move_constructible
        template<typename _T>
        struct is_move_constructible : public
          trait::type::features::is_constructible<_T,
            typename
            trait::type::transform::add_rvalue_reference<_T>::type>
        { };


      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_CONSTRUCTIBLE__
