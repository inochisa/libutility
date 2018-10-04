
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
            public trait::false_type
          { };
          template<typename _F, typename _T>
          struct __is_convertible_test<_F, _T,
            decltype(__is_convertible_test_conv<_T>
              (trait::type::special::declval<_F>()))>:
            public trait::true_type
          { };

          template
          <
            typename _T,
            bool _is_array =
              trait::type::categories::is_array<_T>::value,
            bool _is_function =
              trait::type::categories::is_function<_T>::value,
            bool _is_void =
              trait::type::categories::is_void<_T>::value
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
              trait::type::transform::remove_cv<_T>::type
                >::value>
          struct __is_convertible_check
          {
            constexpr static size_t __size = 0;
          };
          template<typename _T>
          struct __is_convertible_check<_T, 0>
          {
            constexpr static size_t __size = sizeof(_T);
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
            public trait::integral_constant<bool,
              __is_convertible_test<_T1, _T2>::value &&
              !(!trait::type::categories::is_function<_T1>::value  &&
                !trait::type::categories::is_reference<_T1>::value &&
                trait::type::categories::is_reference<_T2>::value &&
                (!trait::type::property::is_const<typename
                  trait::type::transform::remove_reference<_T2
                  >::type>::value ||
                  trait::type::property::is_volatile<typename
                  trait::type::transform::remove_reference<_T2
                  >::type>::value) &&
                (trait::type::releations::is_same<typename
                  trait::type::transform::remove_cv<_T1>::type,
                  typename trait::type::transform::remove_cv<
                  typename trait::type::transform::remove_reference<_T2
                  >::type>::type>::value ||
                 trait::type::releations::is_base_of<typename
                  trait::type::transform::remove_reference<_T2
                  >::type, _T1>::value))>
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 1> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 2> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 0, 3> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 1> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 2> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 1, 3> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 1> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 2> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 2, 3> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 1> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 2> :
            public trait::false_type
          { };
          template<typename _T1, typename _T2>
          struct __is_convertible_helper<_T1, _T2, 3, 3> :
            public trait::true_type
          { };
        }
        template<typename _F, typename _T>
        struct is_convertible :
          public __is_convertible_impl::__is_convertible_helper<_F, _T>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _F, typename _T>
        constexpr bool is_convertible_v = is_convertible<_F, _T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_CONVERTIBLE__
