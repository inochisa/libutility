
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_ASSIGNABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_ASSIGNABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/features/is_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_move_assignable
        template<typename _T>
        struct is_move_assignable : public
          trait::type::features::is_assignable<
            typename trait::type::transform::add_lvalue_reference<_T>::type,
            typename trait::type::transform::add_rvalue_reference<_T>::type>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVE_ASSIGNABLE__
