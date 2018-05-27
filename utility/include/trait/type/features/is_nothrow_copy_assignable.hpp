
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPY_ASSIGNABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPY_ASSIGNABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/transform/add_cv.hpp>
#include<utility/trait/type/features/is_nothrow_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_copy_assignable
        template<typename _T>
        struct is_nothrow_copy_assignable : public
          trait::type::features::is_nothrow_assignable<
            typename trait::type::transform::add_lvalue_reference<_T>::type,
            typename trait::type::transform::add_lvalue_reference
            <typename
              trait::type::transform::add_const<_T>::type>::type>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPY_ASSIGNABLE__
