
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_POINTER__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/is_referenceable.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/releations/is_same.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // add_pointer
        namespace __add_pointer_impl
        {
          template<typename _T, bool =
          trait::type::transform::is_referenceable<_T>::value||
            trait::type::releations::is_same<
              typename
                trait::type::transform::remove_cv<_T>::type,
                  void>::value>
          struct __add_pointer_helper
          { typedef typename remove_reference<_T>::type* type;};
          template<typename _T>
          struct __add_pointer_helper<_T, false>
          { typedef _T type;};
        }
        template<typename _T>
        struct add_pointer
        {
          typedef typename
            __add_pointer_impl::__add_pointer_helper<_T>::type type;
        };

        template<typename _T>
        using add_pointer_t = typename add_pointer<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_POINTER__
