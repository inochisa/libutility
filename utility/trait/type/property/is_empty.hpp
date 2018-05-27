
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_EMPTY__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_EMPTY__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_empty

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_empty
        template<typename _T>
        struct is_empty :
          public trait::integral_constant<
            bool, __utility_is_empty(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_is_empty

# include<utility/trait/type/categories/is_class.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_empty
        namespace __is_empty_impl
        {
          // avoid align
          template<typename _T>
          struct __is_empty_helper : public _T
          { long __nouse;};
          struct __is_empty_base_helper
          { long __nouse;};

          template<typename _T,
            bool = trait::type::categories::is_class<_T>::value>
          struct __is_empty_test :
            public trait::integral_constant<bool,
              sizeof(__is_empty_helper<_T>) ==
              sizeof(__is_empty_base_helper)>
          { };
          template<typename _T>
          struct __is_empty_test<_T, false> :
            public trait::false_type
          { };
        }
        template<typename _T>
        struct is_empty :
          public __is_empty_impl::__is_empty_test<_T>
        { };

      }
    }
  }
}

#endif // ! __utility_has_is_empty

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_EMPTY__
