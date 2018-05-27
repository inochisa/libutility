
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_ASSIGNABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_ASSIGNABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/features/is_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_assignable
        namespace __is_nothrow_assignable_impl
        {
          template<bool, typename _To, typename _From>
          struct __is_nothrow_assignable_helper;

          template<typename _To, typename _From>
          struct __is_nothrow_assignable_helper<false, _To, _From> :
            public trait::false_type
          { };
          template<typename _To, typename _From>
          struct __is_nothrow_assignable_helper<true, _To, _From> :
            public trait::integral_constant<bool,
              noexcept(trait::type::special::declval<_To>() = trait::type::special::declval<_From>())>
          { };
        }
        template<typename _T, typename _U>
        struct is_nothrow_assignable : public
          __is_nothrow_assignable_impl::__is_nothrow_assignable_helper<
            trait::type::features::is_assignable<_T, _U>::value,
            _T, _U>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_ASSIGNABLE__
