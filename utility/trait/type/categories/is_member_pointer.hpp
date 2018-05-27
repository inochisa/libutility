
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_member_pointer
        namespace __is_member_pointer_impl
        {
          template<typename _T>
          struct __is_member_pointer_test :
            public trait::false_type
          { };

          template<typename _T, class _Inn>
          struct __is_member_pointer_test<_T _Inn::*> :
            public trait::true_type
          { };
        }
        template<typename _T>
        struct is_member_pointer :
          public __is_member_pointer_impl::__is_member_pointer_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_POINTER__
