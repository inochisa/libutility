
#ifndef __UTILITY_CONTAINER_DETAIL_TRIPAIR_HELPER__
#define __UTILITY_CONTAINER_DETAIL_TRIPAIR_HELPER__

#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/transform/add_cv.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_implicit_constructible.hpp>
#include<utility/trait/type/features/is_assignable.hpp>
#include<utility/trait/type/features/is_copy_assignable.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace container
  {
    namespace __detail
    {
      using trait::type::releations::is_convertible;
      using trait::type::features::is_constructible;
      using trait::type::features::is_implicit_constructible;
      using trait::type::features::is_copy_constructible;
      using trait::type::features::is_nothrow_constructible;
      using trait::type::features::is_nothrow_copy_constructible;
      using trait::type::features::is_assignable;
      using trait::type::features::is_nothrow_assignable;
      using trait::type::features::is_swappable;
      using trait::type::features::is_possible_swappable;
      using trait::type::features::is_nothrow_swappable;
      using trait::type::features::is_nothrow_possible_swappable;
      using trait::type::miscellaneous::enable_if;

      template<typename _T>
      using __add_cv = typename trait::type::transform::add_cv<_T>::type;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_default = enable_if<
          is_constructible<_T1>::value &&
          is_constructible<_T2>::value &&
          is_constructible<_T3>::value &&
          (is_implicit_constructible<_T1>::value &&
          is_implicit_constructible<_T2>::value &&
          is_implicit_constructible<_T3>::value),
          bool>;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_explicit_default = enable_if<
          is_constructible<_T1>::value &&
          is_constructible<_T2>::value &&
          is_constructible<_T3>::value &&
          !(is_implicit_constructible<_T1>::value &&
          is_implicit_constructible<_T2>::value &&
          is_implicit_constructible<_T3>::value),
          bool>;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_default_noexcept =
        trait::__type_and__<
          is_nothrow_constructible<_T1>,
          is_nothrow_constructible<_T2>,
          is_nothrow_constructible<_T3>
        >;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_copy = enable_if<
          is_constructible<_T1, __add_cv<_U1>>::value &&
          is_constructible<_T2, __add_cv<_U2>>::value &&
          is_constructible<_T3, __add_cv<_U3>>::value &&
          (is_convertible<__add_cv<_U1>, _T1>::value &&
          is_convertible<__add_cv<_U2>, _T2>::value &&
          is_convertible<__add_cv<_U3>, _T3>::value),
          bool>;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_explicit_copy = enable_if<
          is_constructible<_T1, __add_cv<_U1>>::value &&
          is_constructible<_T2, __add_cv<_U2>>::value &&
          is_constructible<_T3, __add_cv<_U3>>::value &&
          !(is_convertible<__add_cv<_U1>, _T1>::value &&
          is_convertible<__add_cv<_U2>, _T2>::value &&
          is_convertible<__add_cv<_U3>, _T3>::value),
          bool>;


      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_copy_noexcept =
        trait::__type_and__<
          is_nothrow_constructible<_T1, __add_cv<_U1>>,
          is_nothrow_constructible<_T2, __add_cv<_U2>>,
          is_nothrow_constructible<_T3, __add_cv<_U3>>
        >;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_move = enable_if<
          is_constructible<_T1, _U1&&>::value &&
          is_constructible<_T2, _U2&&>::value &&
          is_constructible<_T3, _U3&&>::value &&
          (is_convertible<_U1&&, _T1>::value &&
          is_convertible<_U2&&, _T2>::value &&
          is_convertible<_U3&&, _T3>::value),
          bool>;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_explicit_move = enable_if<
          is_constructible<_T1, _U1&&>::value &&
          is_constructible<_T2, _U2&&>::value &&
          is_constructible<_T3, _U3&&>::value &&
          !(is_convertible<_U1&&, _T1>::value &&
          is_convertible<_U2&&, _T2>::value &&
          is_convertible<_U3&&, _T3>::value),
          bool>;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_move_noexcept =
        trait::__type_and__<
          is_nothrow_constructible<_T1, _U1&&>,
          is_nothrow_constructible<_T2, _U2&&>,
          is_nothrow_constructible<_T3, _U3&&>
        >;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_copy_assign = enable_if<
          is_assignable<_T1&, const _U1&>::value &&
          is_assignable<_T2&, const _U2&>::value &&
          is_assignable<_T3&, const _U3&>::value,
          bool>;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_copy_assign_noexcept =
        trait::__type_and__<
          is_nothrow_assignable<_T1&, const _U1&>,
          is_nothrow_assignable<_T2&, const _U1&>,
          is_nothrow_assignable<_T3&, const _U1&>
        >;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_move_assign = enable_if<
          is_assignable<_T1&, _U1&&>::value &&
          is_assignable<_T2&, _U2&&>::value &&
          is_assignable<_T3&, _U3&&>::value,
          bool>;

      template<
        typename _T1, typename _T2, typename _T3,
        typename _U1 = _T1, typename _U2 = _T2, typename _U3 = _T3
      >
      using __tripair_move_assign_noexcept =
        trait::__type_and__<
          is_nothrow_assignable<_T1&, _U1&&>,
          is_nothrow_assignable<_T2&, _U2&&>,
          is_nothrow_assignable<_T3&, _U3&&>
        >;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_swap = enable_if<
          is_swappable<_T1>::value &&
          is_swappable<_T2>::value &&
          is_swappable<_T3>::value,
          bool>;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_swap_noexcept =
        trait::__type_and__<
          is_nothrow_swappable<_T1>,
          is_nothrow_swappable<_T2>,
          is_nothrow_swappable<_T3>
        >;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_possible_swap = enable_if<
          is_possible_swappable<_T1>::value &&
          is_possible_swappable<_T2>::value &&
          is_possible_swappable<_T3>::value,
          bool>;

      template<typename _T1, typename _T2, typename _T3>
      using __tripair_possible_swap_noexcept =
        trait::__type_and__<
          is_nothrow_possible_swappable<_T1>,
          is_nothrow_possible_swappable<_T2>,
          is_nothrow_possible_swappable<_T3>
        >;

      template<typename _T>
      struct __make_tripair_type_helper
      { typedef _T type;};

      template<typename _T>
      struct __make_tripair_type
      {
        typedef typename
          __make_tripair_type_helper<typename
            trait::type::transform::decay<_T>::type
          >::type type;
      };

    }
  }

}


#endif // ! __UTILITY_CONTAINER_DETAIL_TRIPAIR_HELPER__
