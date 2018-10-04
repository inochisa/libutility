
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_CLASS__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_CLASS__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_class

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_class
        template<typename _T>
        struct is_class :
          public trait::integral_constant<bool, __utility_is_class(_T)>
        { };

      }
    }
  }
}

#else

# include<utility/trait/opt/__twochar__.hpp>
namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_class
        namespace __is_class_impl
        {
          template<typename _T>
          char __is_class_test (int _T::*);
          template<typename _T>
          trait::__opt__::__twochar__ __is_class_test(...);
        }
        template<typename _T>
        struct is_class :
          public trait::integral_constant<
            bool, sizeof(__is_class_impl::__is_class_test(0)) == 1 &&
                  !is_union<_T>::value>
        { };

      }
    }
  }
}

#endif

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_class_v = is_class<_T>::value;
#endif

      }
    }
  }
}
#include<utility/trait/config/trait_undef.hpp>

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_CLASS__
