
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_ABSTRACT__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_ABSTRACT__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__twochar__.hpp>
#include<utility/trait/type/categories/is_class.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_abstract
        namespace __is_abstract_impl
        {
          template<typename _T>
          char __is_abstract_helper(_T(*)[1]);
          template<typename _T>
          trait::__opt__::__twochar__
            __is_abstract_helper(...);
          template<typename _T, bool =
            trait::type::categories::is_class<_T>::value>
          struct __is_abstract_test :
            public trait::integral_constant<bool,
              sizeof(__is_abstract_impl::__is_abstract_helper<_T>(0)) != 1>
          { };
          template<typename _T>
          struct __is_abstract_test<_T, false> :
            public trait::false_type
          { };
        }
        template<typename _T>
        struct is_abstract :
          public __is_abstract_impl::__is_abstract_test<_T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_ABSTRACT__
