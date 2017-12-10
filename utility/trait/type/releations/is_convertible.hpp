
#ifndef __UTILITY_TRAIT_TYPE_RELEATIONS_IS_CONVERTIBLE__
#define __UTILITY_TRAIT_TYPE_RELEATIONS_IS_CONVERTIBLE__

#include<utility/trait/trait_helper.hpp>

# include<utility/trait/type/type_trait_special.hpp>
# include<utility/trait/type/categories/is_void.hpp>
# include<utility/trait/type/categories/is_array.hpp>
# include<utility/trait/type/categories/is_function.hpp>
# include<utility/trait/type/categories/is_reference.hpp>
# include<utility/trait/type/transform/remove_cv.hpp>
# include<utility/trait/type/transform/remove_reference.hpp>
# include<utility/trait/type/property/is_const.hpp>
# include<utility/trait/type/property/is_volatile.hpp>
# include<utility/trait/type/releations/is_base_of.hpp>
# include<utility/trait/type/releations/is_same.hpp>
namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {
        namespace __is_convertible_impl
        {
          template<typename _T>
          void __is_convertible_test_conv(_T);
          template<typename _F, typename _T, typename = void>
          struct __is_convertible_test :
            public ::utility::trait::false_type
          { };
          template<typename _F, typename _T>
          struct __is_convertible_test<_F, _T,
            decltype(__is_convertible_test_conv<_T>
              (::utility::trait::type::special::declval<_F>()))>:
            public ::utility::trait::true_type
          { };

          template
          <
            typename _T,
            bool _is_array =
              ::utility::trait::type::categories::is_array<_T>::value,
            bool _is_function =
              ::utility::trait::type::categories::is_function<_T>::value,
            bool _is_void =
              ::utility::trait::type::categories::is_void<_T>::value
          >
          struct __is_convertible_type_test
          { enum { value = 0};};
          template<typename _T>
          struct __is_convertible_type_test<_T, true, false, false>
          { enum { value = 1};};
          template<typename _T>
          struct __is_convertible_type_test<_T, false, true, false>
          { enum { value = 2};};
          template<typename _T>
          struct __is_convertible_type_test<_T, false, false, true>
          { enum { value = 3};};

          // @special
          template<typename _T, unsigned int =
            __is_convertible_type_test<typename
              ::utility::trait::type::transform::remove_cv<_T>::type
                >::value>
          struct __is_convertible_check
          {
            constexpr static ::utility::trait::size_t __size = 0;
          };
          template<typename _T>
          struct __is_convertible_check<_T, 0>
          {
            constexpr static ::utility::trait::size_t __size = sizeof(_T);
          };

          template
          <
            typename _T1,
            typename _T2,
            unsigned int _T1_type_test =
              __is_convertible_type_test<_T1>::value,
            unsigned int _T2_type_test =
              __is_convertible_type_test<_T2>::value
          >
          struct __is_convertible_helper :
            public ::utility::trait::integral_constant<bool,
              __is_convertible_test<_T1, _T2>::value &&
              !(!::utility::trait::type::categories::is_function<_T1>::value  &&
                !::utility::trait::type::categories::is_reference<_T1>::value &&
                ::utility::trait::type::categories::is_reference<_T2>::value &&
                (!::utility::trait::type::property::is_const<typename
                  ::utility::trait::type::transform::remove_reference<_T2
                  >::type>::value ||
                  ::utility::trait::type::property::is_volatile<typename
                  ::utility::trait::type::transform::remove_reference<_T2
                  >::type>::value) &&
                (::utility::trait::type::releations::is_same<typename
                  ::utility::trait::type::transform::remove_cv<_T1>::type,
                  typename ::utility::trait::type::transform::remove_cv<
                  typename ::utility::trait::type::transform::remove_reference<_T2
                  >::type>::type>::value ||
                 ::utility::trait::type::releations::is_base_of<typename
                  ::utility::trait::type::transform::remove_reference<_T2
                  >::type, _T1>::value))>
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 1> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 2> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 3> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 1> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 2> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 3> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 1> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 2> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 3> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 1> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 2> :
            public ::utility::trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 3> :
            public ::utility::trait::true_type
          { };
        }
        template<typename _F, typename _T>
        struct is_convertible :
          public __is_convertible_impl::__is_convertible_helper<_F, _T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_CONVERTIBLE__
