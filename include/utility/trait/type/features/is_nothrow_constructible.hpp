
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/features/is_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_constructible
        namespace __is_nothrow_constructible_impl
        {
          template<class _T>
          void __is_nothrow_constructible_test(_T) noexcept
          { }

          template<bool /*is constructible*/, bool /*is reference*/,
          class _T, class... _Args>
          struct __is_nothrow_constructible_helper;

          template<class _T, class... _Args>
          struct __is_nothrow_constructible_helper<true, false, _T, _Args...> :
            public trait::integral_constant<bool,
              noexcept(_T(trait::type::special::declval<_Args>()...))>
          { };
          template<class _T, class... _Args>
          struct __is_nothrow_constructible_helper<true, true, _T, _Args...> :
            public trait::integral_constant<bool,
              noexcept(__is_nothrow_constructible_test<_T>(trait::type::special::declval<_Args>()...))>
          { };
          template<class _T, class... _Args>
          struct __is_nothrow_constructible_helper<false, true, _T, _Args...> :
            public trait::false_type
          { };
          template<class _T, class... _Args>
          struct __is_nothrow_constructible_helper<false, false, _T, _Args...> :
            public trait::false_type
          { };
        }
        template<class _T, class... _Args>
        struct is_nothrow_constructible : public
          __is_nothrow_constructible_impl::__is_nothrow_constructible_helper<
            trait::type::features::is_constructible<_T, _Args...>::value,
            trait::type::categories::is_reference<_T>::value,
            _T, _Args...>
        { };
        template<class _T, size_t __Size>
        struct is_nothrow_constructible<_T[__Size]> : public
          __is_nothrow_constructible_impl::__is_nothrow_constructible_helper<
            trait::type::features::is_constructible<_T>::value,
            trait::type::categories::is_reference<_T>::value,
            _T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_CONSTRUCTIBLE__
