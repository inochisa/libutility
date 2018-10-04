
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_POLYMORPHIC__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_POLYMORPHIC__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_is_polymorphic

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_polymorphic
        template<typename _T>
        struct is_polymorphic :
          public trait::integral_constant<bool,
            __utility_is_polymorphic(_T)>
        { };

      }
    }
  }
}

#else

# include<utility/trait/opt/__twochar__.hpp>
# include<utility/trait/type/miscellaneous/enable_if.hpp>
# include<utility/trait/type/type_trait_special.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_polymorphic
        namespace __is_polymorphic_impl
        {
          template<typename _T>
          char& __is_polymorphic_test(
            typename trait::type::miscellaneous::enable_if<
              sizeof(reinterpret_cast<_T*>(dynamic_cast<const volatile void*>(trait::type::special::declval<_T>()))) != 0,
              int>::type
              );
          template<typename _T>
          trait::__opt__::__twochar__&
            __is_polymorphic_test(...);
        }
        template<typename _T>
        struct is_polymorphic :
          public trait::integral_constant<bool,
            sizeof(__is_polymorphic_impl::__is_polymorphic_test<_T>(0)) == 1>
        { };

      }
    }
  }
}

#endif

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_POLYMORPHIC__
