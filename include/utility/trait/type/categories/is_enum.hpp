
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ENUM__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ENUM__

#include<utility/trait/config/trait_config.hpp>
#include<utility/trait/trait_helper.hpp>

#if __utility_has_is_enum

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_enum
        template<typename _T>
        struct is_enum :
          public trait::integral_constant<bool, __utility_is_enum(_T)>
        { };
      }
    }
  }
}

#else // __utility_has_is_enum

# if __utility_has_is_union

# include<utility/trait/type/categories/is_void.hpp>
# include<utility/trait/type/categories/is_integral.hpp>
# include<utility/trait/type/categories/is_floating_point.hpp>
# include<utility/trait/type/categories/is_array.hpp>
# include<utility/trait/type/categories/is_pointer.hpp>
# include<utility/trait/type/categories/is_reference.hpp>
# include<utility/trait/type/categories/is_member_pointer.hpp>
# include<utility/trait/type/categories/is_union.hpp>
# include<utility/trait/type/categories/is_class.hpp>
# include<utility/trait/type/categories/is_function.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_enum
        template<typename _T>
        struct is_enum :
          public trait::integral_constant<bool,
            !is_void<_T>::value             &&
            !is_integral<_T>::value         &&
            !is_floating_point<_T>::value   &&
            !is_array<_T>::value            &&
            !is_pointer<_T>::value          &&
            !is_reference<_T>::value        &&
            !is_member_pointer<_T>::value   &&
            !is_union<_T>::value            &&
            !is_class<_T>::value            &&
            !is_function<_T>::value>
        { };
      }
    }
  }
}

# else // __utility_has_is_union

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_enum
        template<typename _T>
        struct is_enum : pulic trait::unsupport_trait<false>
        { };

      }
    }
  }
}

# endif // __utility_has_is_union

#endif // __utility_has_is_enum

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
        constexpr bool is_enum_v = is_enum<_T>::value;
#endif

      }
    }
  }
}

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ENUM__
