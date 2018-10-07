
#ifndef __UTILITY_CONTAINER_COMPRESSED_PAIR__
#define __UTILITY_CONTAINER_COMPRESSED_PAIR__

/**
 * \file compressed_pair.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm//possible_swap.hpp>

#include<utility/container/container_helper.hpp>
#include<utility/container/impl/compressed_index.hpp>

#include<utility/trait/opt/__types__.hpp>

namespace utility
{
  namespace container
  {
    template<typename _T1, typename _T2>
    class compressed_pair : public compressed_index<_T1, 0>,
                            public compressed_index<_T2, 1>
    {
      private:
        typedef compressed_index<_T1, 0> first_base;
        typedef compressed_index<_T2, 1> second_base;

      public:
        typedef _T1 first_type;
        typedef _T2 second_type;

      public:
        template<typename _U1 = _T1, typename _U2 = _T2,
          typename
            trait::type::miscellaneous::enable_if<
              trait::type::features::is_default_constructible<_U1>::value &&
              trait::type::features::is_default_constructible<_U2>::value &&
              (trait::type::features::is_implicit_constructible<_U1>::value &&
               trait::type::features::is_implicit_constructible<_U2>::value),
              bool>::type = true>
        constexpr compressed_pair() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T1>::value &&
          trait::type::features::is_nothrow_default_constructible<_T2>::value
        ):first_base(), second_base()
        { }

        template<typename _U1 = _T1, typename _U2 = _T2,
          typename
            trait::type::miscellaneous::enable_if<
              trait::type::features::is_default_constructible<_U1>::value &&
              trait::type::features::is_default_constructible<_U2>::value &&
              !(trait::type::features::is_implicit_constructible<_U1>::value &&
               trait::type::features::is_implicit_constructible<_U2>::value),
              bool>::type = false>
        constexpr explicit compressed_pair() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T1>::value &&
          trait::type::features::is_nothrow_default_constructible<_T2>::value
        ):first_base(), second_base()
        { }

        template<typename _U1 = _T1, typename _U2 = _T2,
        typename
          trait::type::miscellaneous::enable_if<
            trait::type::features::is_copy_constructible<_U1>::value &&
            trait::type::features::is_copy_constructible<_U2>::value &&
            (trait::type::releations::is_convertible<const _U1&, _U1>::value &&
             trait::type::releations::is_convertible<const _U2&, _U2>::value),
            bool
          >::type = true>
        constexpr compressed_pair(const _T1& __first, const _T2& __second) noexcept(
          trait::type::features::is_nothrow_copy_constructible<_T1>::value &&
          trait::type::features::is_nothrow_copy_constructible<_T2>::value
        ):first_base(__first), second_base(__second)
        { }
        template<typename _U1 = _T1, typename _U2 = _T2,
        typename
          trait::type::miscellaneous::enable_if<
            trait::type::features::is_copy_constructible<_U1>::value &&
            trait::type::features::is_copy_constructible<_U2>::value &&
            !(trait::type::releations::is_convertible<const _U1&, _U1>::value &&
             trait::type::releations::is_convertible<const _U2&, _U2>::value),
            bool
          >::type = false>
        constexpr explicit compressed_pair(const _T1& __first, const _T2& __second) noexcept(
          trait::type::features::is_nothrow_copy_constructible<_T1>::value &&
          trait::type::features::is_nothrow_copy_constructible<_T2>::value
        ):first_base(__first), second_base(__second)
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_constructible<_T2, _U2&&>::value &&
          (trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        constexpr compressed_pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T2, _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tfirst)),
          second_base(algorithm::forward<_U2>(__tsecond))
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_constructible<_T2, _U2&&>::value &&
          !(trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = false>
        constexpr explicit compressed_pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T2, _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tfirst)),
          second_base(algorithm::forward<_U2>(__tsecond))
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, const _U1&>::value &&
          trait::type::features::is_constructible<_T2, const _U2&>::value &&
          (trait::type::releations::is_convertible<const _U1&, _T1>::value &&
           trait::type::releations::is_convertible<const _U2&, _T2>::value),
          bool>::type = true>
        constexpr compressed_pair(
          const compressed_pair<_U1, _U2>& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, const _U1&>::value &&
          trait::type::features::is_nothrow_constructible<_T2, const _U2&>::value
        ):first_base(__tpair.first()), second_base(__tpair.second())
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, const _U1&>::value &&
          trait::type::features::is_constructible<_T2, const _U2&>::value &&
          !(trait::type::releations::is_convertible<const _U1&, _T1>::value &&
           trait::type::releations::is_convertible<const _U2&, _T2>::value),
          bool>::type = false>
        constexpr explicit compressed_pair(
          const compressed_pair<_U1, _U2>& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, const _U1&>::value &&
          trait::type::features::is_nothrow_constructible<_T2, const _U2&>::value
        ):first_base(__tpair.first()), second_base(__tpair.second())
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_constructible<_T2, _U2&&>::value &&
          (trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        constexpr compressed_pair(
          compressed_pair<_U1, _U2>&& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T2,  _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tpair.first())),
          second_base(algorithm::forward<_U2>(__tpair.second()))
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_constructible<_T2, _U2&&>::value &&
          !(trait::type::releations::is_convertible<_U1&&, _T1>::value &&
           trait::type::releations::is_convertible<_U2&&, _T2>::value),
          bool>::type = true>
        constexpr explicit compressed_pair(
          compressed_pair<_U1, _U2>&& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T1, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T2,  _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tpair.first())),
          second_base(algorithm::forward<_U2>(__tpair.second()))
        { }


      public:
        UTILITY_ALWAYS_INLINE
        inline first_type& first() noexcept
        { return static_cast<first_base&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline const first_type& first() const noexcept
        { return static_cast<first_base const&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline second_type& second() noexcept
        { return static_cast<second_base&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline const second_type& second() const noexcept
        { return static_cast<second_base const&>(*this).get();}

      public:
        void swap(compressed_pair& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T1>::value &&
          trait::type::features::is_nothrow_swappable<_T2>::value
        )
        {
          using algorithm::swap;
          swap(this->first(),   __other.first());
          swap(this->second(),  __other.second());
        }
        void possible_swap(compressed_pair& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T1>::value &&
          trait::type::features::is_nothrow_swappable<_T2>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->first(),  __other.first());
          possible_swap(this->second(), __other.second());
        }
    };
    template<typename _T>
    class compressed_pair<_T, _T> : public compressed_index<_T, 0, false>,
                                    public compressed_index<_T, 1, false>
    {
      public:
        typedef compressed_index<_T, 0> first_base;
        typedef compressed_index<_T, 1> second_base;

      public:
        typedef _T first_type;
        typedef _T second_type;

      public:
        template<typename _U = _T,
          typename
            trait::type::miscellaneous::enable_if<
              trait::type::features::is_default_constructible<_U>::value &&
              (trait::type::features::is_implicit_constructible<_U>::value),
              bool>::type = true>
        constexpr compressed_pair() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T>::value
        ):first_base(), second_base()
        { }

        template<typename _U = _T,
          typename
            trait::type::miscellaneous::enable_if<
              trait::type::features::is_default_constructible<_U>::value &&
              !(trait::type::features::is_implicit_constructible<_U>::value),
              bool>::type = false>
        constexpr explicit compressed_pair() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T>::value
        ):first_base(), second_base()
        { }

        template<typename _U = _T,
        typename
          trait::type::miscellaneous::enable_if<
            trait::type::features::is_constructible<_U, const _U&>::value &&
            (trait::type::releations::is_convertible<const _U&, _U>::value),
            bool
          >::type = true>
        constexpr compressed_pair(const _T& __first, const _T& __second) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _T&>::value
        ):first_base(__first), second_base(__second)
        { }
        template<typename _U = _T,
        typename
          trait::type::miscellaneous::enable_if<
            trait::type::features::is_constructible<_U, const _U&>::value &&
            !(trait::type::releations::is_convertible<const _U&, _U>::value),
            bool
          >::type = false>
        constexpr explicit compressed_pair(const _T& __first, const _T& __second) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _T&>::value
        ):first_base(__first), second_base(__second)
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U1&&>::value &&
          trait::type::features::is_constructible<_T, _U2&&>::value &&
          (trait::type::releations::is_convertible<_U1&&, _T>::value &&
           trait::type::releations::is_convertible<_U2&&, _T>::value),
          bool>::type = true>
        constexpr compressed_pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T, _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tfirst)),
          second_base(algorithm::forward<_U2>(__tsecond))
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U1&&>::value &&
          trait::type::features::is_constructible<_T, _U2&&>::value &&
          !(trait::type::releations::is_convertible<_U1&&, _T>::value &&
           trait::type::releations::is_convertible<_U2&&, _T>::value),
          bool>::type = false>
        constexpr explicit compressed_pair(_U1&& __tfirst, _U2&& __tsecond) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T, _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tfirst)),
          second_base(algorithm::forward<_U2>(__tsecond))
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, const _U1&>::value &&
          trait::type::features::is_constructible<_T, const _U2&>::value &&
          (trait::type::releations::is_convertible<const _U1&, _T>::value &&
           trait::type::releations::is_convertible<const _U2&, _T>::value),
          bool>::type = true>
        constexpr compressed_pair(
          const compressed_pair<_U1, _U2>& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _U1&>::value &&
          trait::type::features::is_nothrow_constructible<_T, const _U2&>::value
        ):first_base(__tpair.first()), second_base(__tpair.second())
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, const _U1&>::value &&
          trait::type::features::is_constructible<_T, const _U2&>::value &&
          !(trait::type::releations::is_convertible<const _U1&, _T>::value &&
           trait::type::releations::is_convertible<const _U2&, _T>::value),
          bool>::type = false>
        constexpr explicit compressed_pair(
          const compressed_pair<_U1, _U2>& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _U1&>::value &&
          trait::type::features::is_nothrow_constructible<_T, const _U2&>::value
        ):first_base(__tpair.first()), second_base(__tpair.second())
        { }

        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U1&&>::value &&
          trait::type::features::is_constructible<_T, _U2&&>::value &&
          (trait::type::releations::is_convertible<_U1&&, _T>::value &&
           trait::type::releations::is_convertible<_U2&&, _T>::value),
          bool>::type = true>
        constexpr compressed_pair(
          compressed_pair<_U1, _U2>&& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U1&&>::value &&
          trait::type::features::is_nothrow_constructible<_T,  _U2&&>::value
        ):first_base(algorithm::forward<_U1>(__tpair.first())),
          second_base(algorithm::forward<_U2>(__tpair.second()))
        { }
        template<typename _U1, typename _U2,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U1&&>::value &&
          trait::type::features::is_constructible<_T, _U2&&>::value &&
          !(trait::type::releations::is_convertible<_U1&&, _T>::value &&
           trait::type::releations::is_convertible<_U2&&, _T>::value),
          bool>::type = true>
        constexpr explicit compressed_pair(
          compressed_pair<_U1, _U2>&& __tpair
        ) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U1&&>::value
        ):first_base(algorithm::forward<_U1>(__tpair.first())),
          second_base(algorithm::forward<_U2>(__tpair.second()))
        { }


      public:
        UTILITY_ALWAYS_INLINE
        inline first_type& first() noexcept
        { return static_cast<first_base&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline const first_type& first() const noexcept
        { return static_cast<first_base const&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline second_type& second() noexcept
        { return static_cast<second_base&>(*this).get();}
        UTILITY_ALWAYS_INLINE
        inline const second_type& second() const noexcept
        { return static_cast<second_base const&>(*this).get();}

      public:
        void swap(compressed_pair& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T>::value
        )
        {
          using algorithm::swap;
          swap(this->first(),   __other.first());
          swap(this->second(),  __other.second());
        }
        void possible_swap(compressed_pair& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->first(),  __other.first());
          possible_swap(this->second(), __other.second());
        }
    };
  }

  namespace trait
  {
    namespace __opt__
    {
      template<typename _T1, typename _T2>
      struct __type_tuple_size__<container::compressed_pair<_T1, _T2>>
      { constexpr static size_t value = 2;};
      template<typename _T1, typename _T2>
      struct __checkout_type_feature__<container::compressed_pair<_T1, _T2>>
      { typedef __type_pair__<_T1, _T2> type;};
    }
  }

  namespace algorithm
  {
    template<typename _T1, typename _T2>
    void swap(
      container::compressed_pair<_T1, _T2>& _x,
      container::compressed_pair<_T1, _T2>& _y
    ) noexcept(noexcept(_x.swap(_y)))
    { _x.swap(_y);}
    template<typename _T1, typename _T2>
    void possible_swap(
      container::compressed_pair<_T1, _T2>& _x,
      container::compressed_pair<_T1, _T2>& _y
    ) noexcept(noexcept(_x.possible_swap(_y)))
    { _x.possible_swap(_y);}
  }

  namespace container
  {
    namespace __detail
    {
      using trait::__opt__::__checkout_type_feature__;
      using trait::__opt__::__type_tuple_get__;
      template<size_t _Id>
      struct __get_compressed_pair;

      template<>
      struct __get_compressed_pair<0>
      {
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static _T1& get(compressed_pair<_T1, _T2>& _pair) noexcept
        { return _pair.first();}
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static const _T1& get(const compressed_pair<_T1, _T2>& _pair) noexcept
        { return _pair.first();}
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static _T1&& get(compressed_pair<_T1, _T2>&& _pair) noexcept
        {
          using algorithm::forward;
          return forward<_T1>(_pair.first());
        }
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static const _T1&& get(
          const compressed_pair<_T1, _T2>&& _pair
        ) noexcept
        {
          using algorithm::forward;
          return forward<const _T1>(_pair.first());
        }
      };

      template<>
      struct __get_compressed_pair<1>
      {
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static _T2& get(compressed_pair<_T1, _T2>& _pair) noexcept
        { return _pair.second();}
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static const _T2& get(const compressed_pair<_T1, _T2>& _pair) noexcept
        { return _pair.second();}
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static _T2&& get(compressed_pair<_T1, _T2>&& _pair) noexcept
        {
          using algorithm::forward;
          return forward<_T2>(_pair.second());
        }
        template<typename _T1, typename _T2>
        __UTILITY_CPP14_CONSTEXPR__
        static const _T2&& get(
          const compressed_pair<_T1, _T2>&& _pair
        ) noexcept
        {
          using algorithm::forward;
          return forward<const _T2>(_pair.second());
        }
      };
    }

    template<size_t _Id, typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    typename __detail::__type_tuple_get__<
      _Id,
      typename __detail::__checkout_type_feature__<
        compressed_pair<_T1, _T2>
      >::type
    >::type&
    get(compressed_pair<_T1, _T2>& _pair) noexcept
    { return __detail::__get_compressed_pair<_Id>::get(_pair);}
    template<size_t _Id, typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    const typename __detail::__type_tuple_get__<
      _Id,
      typename __detail::__checkout_type_feature__<
        compressed_pair<_T1, _T2>
      >::type
    >::type&
    get(const compressed_pair<_T1, _T2>& _pair) noexcept
    { return __detail::__get_compressed_pair<_Id>::get(_pair);}
    template<size_t _Id, typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    typename __detail::__type_tuple_get__<
      _Id,
      typename __detail::__checkout_type_feature__<
        compressed_pair<_T1, _T2>
      >::type
    >::type&&
    get(compressed_pair<_T1, _T2>&& _pair) noexcept
    {
      using algorithm::move;
      return __detail::__get_compressed_pair<_Id>::get(move(_pair));
    }
    template<size_t _Id, typename _T1, typename _T2>
    __UTILITY_CPP14_CONSTEXPR__
    const typename __detail::__type_tuple_get__<
      _Id,
      typename __detail::__checkout_type_feature__<
        compressed_pair<_T1, _T2>
      >::type
    >::type&&
    get(const compressed_pair<_T1, _T2>&& _pair) noexcept
    {
      using algorithm::move;
      return __detail::__get_compressed_pair<_Id>::get(move(_pair));
    }
  }
}

#endif // ! __UTILITY_CONTAINER_COMPRESSED_PAIR__
