
#ifndef __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_CV__
#define __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_CV__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_function.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/property/is_const.hpp>
#include<utility/trait/type/property/is_volatile.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace transform
      {
        // add_const
        namespace __add_const_impl
        {
          template<typename _T, bool =
            trait::type::property::is_const<_T>::value       ||
            trait::type::categories::is_function<_T>::value  ||
            trait::type::categories::is_reference<_T>::value>
          struct __add_const_helper
          { typedef _T type;};
          template<typename _T>
          struct __add_const_helper<_T, false>
          { typedef const _T type;};
        }
        template<typename _T>
        struct add_const
        { typedef typename
            __add_const_impl::__add_const_helper<_T>::type type;};

        // add_volatile
        namespace __add_volatile_impl
        {
          template<typename _T, bool =
            trait::type::property::is_volatile<_T>::value    ||
            trait::type::categories::is_function<_T>::value  ||
            trait::type::categories::is_reference<_T>::value>
          struct __add_volatile_helper
          { typedef _T type;};
          template<typename _T>
          struct __add_volatile_helper<_T, false>
          { typedef volatile _T type;};
        }
        template<typename _T>
        struct add_volatile
        { typedef typename
            __add_volatile_impl::__add_volatile_helper<_T>::type type;};

        // add_cv
        template<typename _T>
        struct add_cv
        { typedef typename add_const<typename
            add_volatile<_T>::type>::type type;};

        template<typename _T>
        using add_cv_t = typename add_cv<_T>::type;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_TRANSFORM_ADD_CV__
