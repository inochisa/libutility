
#ifndef __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__
#define __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__

#include<utility/trait/config/trait_config.hpp>
#include<utility/trait/trait_helper.hpp>
#undef __utility_has_is_base_of
#define __utility_has_is_base_of 0
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
          public trait::integral_constant<
            bool, __utility_is_base_of(_T1, _T2)>
        { };

      }
    }
  }
}

#else

#include<utility/trait/opt/__twochar__.hpp>
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
          using __two = trait::__opt__::__twochar__;

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

          template<typename _T1, typename _T2>
          struct __is_base_of_test
          {
            private:
              template<typename __T1, typename __T2>
              static auto __test(int) ->decltype(__is_base_of_base_helper<__T1>(
                trait::type::special::declval<__is_base_of_helper<__T2>>()
              ), char('\0'));
              template<typename __T1, typename __T2>
              static __two __test(...);

            public:
              constexpr static bool value =
                trait::type::categories::is_class<_T1>::value &&
                sizeof(__test<_T1, _T2>(0)) == 2;
          };

          template<typename _T>
          struct __is_base_of_test<void, _T>
          {
            public:
              constexpr static bool value = false;
          };
        }
        template<typename _T1, typename _T2>
        struct is_base_of :
          public trait::integral_constant<bool,
            __is_base_of_impl::__is_base_of_test<_T1, _T2>::value
          >
        { };

      }
    }
  }
}

#endif // ! __utility_has_is_base_of

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {
#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T1, typename _T2>
        constexpr bool is_base_of_v = is_base_of<_T1, _T2>::value;
#endif

      }
    }
  }
}

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_BASE_OF__
