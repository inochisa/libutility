
#ifndef __UTILITY_ALGORITHM_POSSIBLE_SWAP_SINGLE__
#define __UTILITY_ALGORITHM_POSSIBLE_SWAP_SINGLE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_moveable.hpp>
#include<utility/trait/type/features/is_copyable.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_copyable.hpp>
#include<utility/trait/type/features/is_nothrow_moveable.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace __possible_swap_impl
    {
      template<typename _T>
      struct __has_possible_swap_test
      {
        private:
          template<typename __T>
          static auto __test(__T&& __x, __T&& __y)
            ->decltype(__x.possible_swap(__y),
              trait::true_type());
          template<typename __T>
          static auto __test(const __T& __x, const __T& __y)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_T>(
                trait::type::special::declval<_T>(),
                trait::type::special::declval<_T>()))
            >::value;
      };
      template<typename _T>
      struct __has_swap_test
      {
        private:
          template<typename __T>
          static auto __test(__T&& __x, __T&& __y)
            ->decltype(__x.swap(__y),
              trait::true_type());
          template<typename __T>
          static auto __test(const __T& __x, const __T& __y)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_T>(
                trait::type::special::declval<_T>(),
                trait::type::special::declval<_T>()))
            >::value;
      };

      template<typename _T,
        bool = __has_possible_swap_test<_T>::value,
        bool = __has_swap_test<_T>::value,
        bool = trait::type::features::is_moveable<_T>::value,
        bool = trait::type::features::is_copyable<_T>::value
      >
      struct __possible_swap;

      template<typename _T, bool _Swap, bool _Move, bool _Copy>
      struct __possible_swap<_T, true, _Swap, _Move, _Copy>
      {
        static void __aux(_T& __x, _T& __y) noexcept(
          noexcept(__x.possible_swap(__y))
        )
        { __x.possible_swap(__y);}
      };
      template<typename _T, bool _Move, bool _Copy>
      struct __possible_swap<_T, false, true, _Move, _Copy>
      {
        static void __aux(_T& __x, _T& __y) noexcept(
          noexcept(__x.swap(__y))
        )
        { __x.swap(__y);}
      };
      template<typename _T, bool _Copy>
      struct __possible_swap<_T, false, false, true, _Copy>
      {
        static void __aux(_T& __x, _T& __y) noexcept(
          trait::type::features::is_nothrow_move_constructible<_T>::value &&
          trait::type::features::is_nothrow_move_assignable<_T>::value
        )
        {
          _T __tmp(algorithm::move(__x));
          __x = algorithm::move(__y);
          __y = algorithm::move(__tmp);
        }
      };
      template<typename _T>
      struct __possible_swap<_T, false, false, false, true>
      {
        static void __aux(_T& __x, _T& __y)  noexcept(
          trait::type::features::is_nothrow_copy_constructible<_T>::value &&
          trait::type::features::is_nothrow_copy_assignable<_T>::value
        )
        {
          _T __tmp(__x);
          __x = __y;
          __y = __tmp;
        }
      };
    }

    /**
     * \brief Exchange values of two objects
     *
     * Swaps the values \a __a and \a __b.
     * Copy if necessary.
     *
     * \param __a,__b the values to be swapped
     * \note This function is vaild when one of the following condition
     *       is \b satisfied:<br/>
     *       1. The object has member function \c possible_swap.<br/>
     *       2. The object has member function \c swap.<br/>
     *       3. The object can move construct and move assign.<br/>
     *       4. The object can copy construct and copy assign.<br/>
     * The condition order is 1 > 2 > 3 > 4.
     *
     * \exception This function is \b noexcept when
     *            (let _T is the object type)
     *       1. The member function \c possible_swap is \b noexcept.<br/>
     *       2. The object member function \c swap is \b noexcept.<br/>
     *       3. \c is_nothrow_move_constructible<_T> &&
     *          \c is_nothrow_move_assignable<_T> is \b true.<br/>
     *       4. \c is_nothrow_copy_constructible<_T> &&
     *          \c is_nothrow_copy_assignable<_T> is \b true.<br/>
     * \related algorithm::swap
     */
    template<typename _T>
    typename trait::type::miscellaneous::enable_if<
      __possible_swap_impl::__has_possible_swap_test<_T>::value ||
      __possible_swap_impl::__has_swap_test<_T>::value ||
      trait::type::features::is_moveable<_T>::value ||
      trait::type::features::is_copyable<_T>::value,
    void>::type
    possible_swap(_T& __x, _T& __y) noexcept(
      noexcept(__possible_swap_impl::__possible_swap<_T>::__aux(__x, __y))
    )
    {
      __possible_swap_impl::__possible_swap<_T>::__aux(__x, __y);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_POSSIBLE_SWAP_SINGLE__
