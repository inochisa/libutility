
#ifndef __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__
#define __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__

#include<utility/trait/config/trait_config.hpp>
#include<utility/trait/trait_helper.hpp>

#if __utility_has_is_base_of

# include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {
        // is_base_of
        template<typename _T1, typename _T2>
        struct is_base_of :
          public ::utility::trait::integral_constant<
            bool, __utility_is_base_of(_T1, _T2)>
        { };

      }
    }
  }
}

#else

#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/categories/is_class.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {
        // is_base_of
        namespace __is_base_of_impl
        {
          template<typename _T>
          struct __is_base_of_base_helper
          {
            __is_base_of_base_helper(const volatile _T&);
          };
          template<typename _T>
          struct __is_base_of_helper
          {
            operator const volatile _T&();
            template<typename _Base>
            operator const __is_base_of_base_helper<_Base>&();
          };
          template<::utility::trait::size_t>
          struct __conv_helper
          { typedef char type;};
          template<typename _T1, typename _T2>
          typename __conv_helper<sizeof(__is_base_of_base_helper<_T1>(
            ::utility::trait::type::special::declval<__is_base_of_helper<_T2>>()
          ))>::type __is_base_of_test(int);
          template<typename _T1, typename _T2>
          ::utility::trait::__impl_helper::__twochar
            __is_base_of_test(...);
        }
        template<typename _T1, typename _T2>
        struct is_base_of :
          public ::utility::trait::integral_constant<bool,
            ::utility::trait::type::categories::is_class<_T1> &&
            sizeof(__is_base_of_impl::__is_base_of_test<_T1, _T2>(0)) == 2
            >
        { };

      }
    }
  }
}

#endif // ! __utility_has_is_base_of

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__
