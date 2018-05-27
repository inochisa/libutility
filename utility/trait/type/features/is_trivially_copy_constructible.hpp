
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_COPY_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_COPY_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/transform/add_cv.hpp>
#include<utility/trait/type/features/is_trivially_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_trivially_copy_constructible
        template<typename _T>
        struct is_trivially_copy_constructible : public
          trait::type::features::is_trivially_constructible<_T,
            typename trait::type::transform::add_lvalue_reference<
              typename
              trait::type::transform::add_const<_T>::type
            >::type>
        { };


      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_TRIVIALLY_COPY_CONSTRUCTIBLE__
