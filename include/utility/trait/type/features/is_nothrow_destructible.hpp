
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_DESTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_DESTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/features/is_destructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_destructible
        namespace __is_nothrow_destructible_impl
        {
          template<bool, typename _T>
          struct __is_nothrow_destructible_helper;

          template<typename _T>
          struct __is_nothrow_destructible_helper<false, _T> : public
            trait::false_type
          { };
          template<typename _T>
          struct __is_nothrow_destructible_helper<true, _T> : public
            trait::integral_constant<bool,
              noexcept(trait::type::special::declval<_T>().~_T())>
          { };
        }
        template<typename _T>
        struct is_nothrow_destructible : public
          __is_nothrow_destructible_impl::__is_nothrow_destructible_helper<
            trait::type::features::is_destructible<_T>::value,
            _T>
        { };
        template<typename _T>
        struct is_nothrow_destructible<_T&> :
          public trait::true_type
        { };
        template<typename _T>
        struct is_nothrow_destructible<_T&&> :
          public trait::true_type
        { };
        template<typename _T, size_t _Size>
        struct is_nothrow_destructible<_T[_Size]> :
          public is_nothrow_destructible<_T>
        { };
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_DESTRUCTIBLE__
