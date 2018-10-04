
#ifndef __UTILITY_CONTAINER_IMPL_COMPRESSED_INDEX__
#define __UTILITY_CONTAINER_IMPL_COMPRESSED_INDEX__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/trait/type/property/is_empty.hpp>
#include<utility/trait/type/property/is_final.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_implicit_constructible.hpp>
#include<utility/trait/type/features/is_assignable.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_default_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace container
  {
    template<typename _T, size_t _Index,
      bool = trait::type::property::is_empty<_T>::value &&
        !trait::type::property::is_final<_T>::value
    >
    class compressed_index
    {
      public:
        typedef _T            pair_value_type;
        typedef const _T      pair_const_value_type;
        typedef _T&           pair_reference;
        typedef const _T&     pair_const_reference;

      public:
        __UTILITY_CPP17_INLINE__
        constexpr static size_t index = _Index;

      private:
        pair_value_type __val;

      public:
        template<typename __U = _T,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_default_constructible<__U>::value &&
          (trait::type::features::is_implicit_constructible<__U>::value),
          bool
        >::type = true>
        constexpr compressed_index() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T>::value
        ): __val()
        { }
        template<typename __U = _T,
          typename trait::type::miscellaneous::enable_if<
            trait::type::features::is_default_constructible<__U>::value &&
            !(trait::type::features::is_implicit_constructible<__U>::value),
            bool
          >::type = true>
        constexpr explicit compressed_index() noexcept(
          trait::type::features::is_nothrow_default_constructible<_T>::value
        ): __val()
        { }

        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, const _U&>::value &&
          (trait::type::releations::is_convertible<const _U&, _T>::value),
          bool
        >::type = true>
        constexpr compressed_index(const _T& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _U&>::value
        ): __val(__value)
        { }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, const _U&>::value &&
          !(trait::type::releations::is_convertible<const _U&, _T>::value),
          bool
        >::type = true>
        constexpr explicit compressed_index(const _U& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, const _U&>::value
        ): __val(__value)
        { }

        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U&&>::value &&
          (trait::type::releations::is_convertible<_U&&, _T>::value),
          bool
        >::type = true>
        constexpr compressed_index(_U&& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U&&>::value
        ): __val(algorithm::forward<_U>(__value))
        { }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U&&>::value &&
          !(trait::type::releations::is_convertible<_U&&, _T>::value),
          bool
        >::type = true>
        constexpr explicit compressed_index(_U&& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U&&>::value
        ): __val(algorithm::forward<_U>(__value))
        { }

        compressed_index(const compressed_index&) = default;
        compressed_index(compressed_index&&) = default;

      public:
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_assignable<_T, const _U&>::value,
          bool
        >::type = true>
        compressed_index& operator=(const _U& __value) noexcept(
          trait::type::features::is_nothrow_assignable<_T, const _U&>::value
        )
        {
          this->__val = __value;
          return *this;
        }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_assignable<_T, _U&&>::value,
          bool
        >::type = true>
        compressed_index& operator=(_U&& __value) noexcept(
          trait::type::features::is_nothrow_assignable<_T, _U&&>::value
        )
        {
          this->__val = algorithm::forward<_U>(__value);
          return *this;
        }
        compressed_index& operator=(const compressed_index&) = default;
        compressed_index& operator=(compressed_index&&) = default;

      public:
        inline pair_reference get() noexcept
        { return this->__val;}
        inline pair_const_reference get() const noexcept
        { return this->__val;}

      public:
        template<typename _U = _T,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_swappable<_U>::value,
          bool
        >::type = true>
        inline int swap(compressed_index& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T>::value
        )
        {
          using algorithm::swap;
          swap(this->__val, __other.__val);
          return 0;
        }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_swappable_with<_T, _U>::value,
          bool
        >::type = true>
        inline int swap(_U& __other) noexcept(
          trait::type::features::is_nothrow_swappable_with<_T, _U>::value
        )
        {
          using algorithm::swap;
          swap(this->__val, __other);
          return 0;
        }
        template<typename _U = _T,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_possible_swappable<_U>::value,
          bool
        >::type = true>
        inline void possible_swap(compressed_index& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<_T>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__val, __other.__val);
        }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_possible_swappable_with<_T, _U>::value,
          bool
        >::type = true>
        inline void possible_swap(_U& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable_with<_T, _U>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__val, __other);
        }
    };

    template<typename _T, size_t _Index>
    class compressed_index<_T, _Index, true> : public _T
    {
      public:
        typedef _T            pair_value_type;
        typedef const _T      pair_const_value_type;
        typedef _T&           pair_reference;
        typedef const _T&     pair_const_reference;

      public:
        __UTILITY_CPP17_INLINE__
        constexpr static size_t index = _Index;

      public:
        constexpr compressed_index() = default;
        constexpr compressed_index(const compressed_index&) = default;
        constexpr compressed_index(compressed_index&&) = default;

      public:
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U&&>::value &&
          // !trait::type::releations::is_same<_T, _U>::value &&
          (trait::type::releations::is_convertible<_U&&, _T>::value),
          bool
        >::type = true>
        constexpr compressed_index(_U&& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U&&>::value
        ): _T(algorithm::forward<_U>(__value))
        { }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_constructible<_T, _U&&>::value &&
          // !trait::type::releations::is_same<_T, _U>::value &&
          !(trait::type::releations::is_convertible<_U&&, _T>::value),
          bool
        >::type = true>
        constexpr explicit compressed_index(_U&& __value) noexcept(
          trait::type::features::is_nothrow_constructible<_T, _U&&>::value
        ): _T(algorithm::forward<_U>(__value))
        { }

      public:
        compressed_index& operator=(const compressed_index&) = default;
        compressed_index& operator=(compressed_index&&) = default;

      public:
        inline pair_reference get() noexcept
        { return *this;}
        inline pair_const_reference get() const noexcept
        { return *this;}

      public:
        template<typename _U = _T,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_swappable<_U>::value,
          bool
        >::type = true>
        inline int swap(compressed_index& __other) noexcept(
          trait::type::features::is_nothrow_swappable<_T>::value
        )
        { return 0;}
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_swappable_with<_T, _U>::value,
          bool
        >::type = true>
        inline int swap(_U& __other) noexcept(
          trait::type::features::is_nothrow_swappable_with<_T, _U>::value
        )
        { return 0;}
        template<typename _U = _T,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_possible_swappable<_U>::value,
          bool
        >::type = true>
        inline void possible_swap(compressed_index& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<_T>::value
        )
        { }
        template<typename _U,
        typename trait::type::miscellaneous::enable_if<
          trait::type::features::is_possible_swappable_with<_T, _U>::value,
          bool
        >::type = true>
        inline void possible_swap(_U& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable_with<_T, _U>::value
        )
        { }
    };
  }
}

#endif // ! __UTILITY_CONTAINER_IMPL_COMPRESSED_INDEX__
