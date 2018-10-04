
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/transform/remove_pointer.hpp>
#include<utility/trait/type/transform/remove_all_pointer.hpp>
#include<utility/trait/type/transform/remove_cv_ref.hpp>
#include<utility/trait/type/transform/remove_cv_pointer.hpp>
#include<utility/trait/type/transform/remove_all_pointer_reference.hpp>
#include<utility/trait/type/transform/remove_extent.hpp>
#include<utility/trait/type/transform/remove_all_extents.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        template<typename _T>
        struct remove_all
        {
          typedef
            typename remove_cv<
              typename remove_all_pointer_reference<
                typename remove_all_extents<_T>::type
              >::type
            >::type type;
        };

        template<typename _T>
        using remove_all_t = typename remove_all<_T>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_REMOVE_ALL__
