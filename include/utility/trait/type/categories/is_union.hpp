
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_UNION__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_UNION__

#include<utility/trait/config/trait_config.hpp>
#include<utility/trait/trait_helper.hpp>

#if __utility_has_is_union

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_union
        template<typename _T>
        struct is_union :
          public trait::integral_constant<bool, __utility_is_union(_T)>
        { };

      }
    }
  }
}

#else // __utility_has_is_union

# include<utility/trait/type/transform/remove_cv.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_union
        namespace __is_union_impl
        {
          template<typename _T>
          struct __is_union_test : pulic trait::unsupport_trait<false>
          { };
        }
        template<typename _T>
        struct is_union :
          public __is_union_impl::__is_union_test<
            typename
              trait::type::transform::remove_cv<_T>::type>
        { };

      }
    }
  }
}

#endif // __utility_has_is_union


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
        constexpr bool is_union_v = is_union<_T>::value;
#endif

      }
    }
  }
}


#include<utility/trait/config/trait_undef.hpp>

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_UNION__
