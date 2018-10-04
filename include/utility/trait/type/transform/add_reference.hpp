
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_REFERENCE__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_REFERENCE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/is_referenceable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // add_lvalue_reference
        namespace __add_lvalue_reference_impl
        {
          template<typename _T, bool =
          trait::type::transform::is_referenceable<_T>::value>
          struct __add_lvalue_reference_helper
          { typedef _T type;};
          template<typename _T>
          struct __add_lvalue_reference_helper<_T, true>
          { typedef _T& type;};

        }
        template<typename _T>
        struct add_lvalue_reference
        {
          typedef typename
            __add_lvalue_reference_impl::
              __add_lvalue_reference_helper<_T>::type type;
        };

        // add_rvalue_reference
        namespace __add_rvalue_reference_impl
        {
          template<typename _T, bool =
           trait::type::transform::is_referenceable<_T>::value>
          struct __add_rvalue_reference_helper
          { typedef _T type;};
          template<typename _T>
          struct __add_rvalue_reference_helper<_T, true>
          { typedef _T&& type;};
        }
        template<typename _T>
        struct add_rvalue_reference
        {
          typedef typename
            __add_rvalue_reference_impl::
              __add_rvalue_reference_helper<_T>::type type;
        };

        template<typename _T>
        using add_lvalue_reference_t = typename add_lvalue_reference<_T>::type;
        template<typename _T>
        using add_rvalue_reference_t = typename add_rvalue_reference<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_REFERENCE__
