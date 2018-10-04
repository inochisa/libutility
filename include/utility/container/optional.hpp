
#ifndef __UTILITY_CONTAINER_OPTIONAL__
#define __UTILITY_CONTAINER_OPTIONAL__

#include<utility/config/utility_config.hpp>

#include<utility/container/container_helper.hpp>
#include<utility/container/helper/nullopt_t.hpp>
#include<utility/container/helper/in_place_t.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/forward.hpp>

#include<utility/memory/addressof.hpp>
#include<utility/memory/destroy_at.hpp>

#include<utility/trait/type/categories/is_scalar.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/transform/remove_cv_ref.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/features/is_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>
#include<utility/trait/type/features/is_trivially_constructible.hpp>
#include<utility/trait/type/features/is_trivially_assignable.hpp>
#include<utility/trait/type/features/is_trivially_copy_constructible.hpp>
#include<utility/trait/type/features/is_trivially_copy_assignable.hpp>
#include<utility/trait/type/features/is_trivially_move_constructible.hpp>
#include<utility/trait/type/features/is_trivially_move_assignable.hpp>
#include<utility/trait/type/features/is_trivially_destructible.hpp>
#include<utility/trait/type/features/is_destructible.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_assignable.hpp>
#include<utility/trait/type/miscellaneous/aligned_storage.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

#include<utility/sstd/new.hpp>

namespace utility
{
  namespace container
  {
    namespace __detail
    {
      using trait::__and__;
      using trait::type::categories::is_scalar;
      using trait::type::categories::is_reference;
      using trait::type::releations::is_same;
      using trait::type::releations::is_convertible;
      using trait::type::transform::decay_t;
      using trait::type::transform::remove_cv_ref_t;
      using trait::type::features::is_constructible;
      using trait::type::features::is_copy_constructible;
      using trait::type::features::is_move_constructible;
      using trait::type::features::is_nothrow_constructible;
      using trait::type::features::is_nothrow_assignable;
      using trait::type::features::is_nothrow_copy_constructible;
      using trait::type::features::is_nothrow_move_constructible;
      using trait::type::features::is_nothrow_copy_assignable;
      using trait::type::features::is_nothrow_move_assignable;
      using trait::type::features::is_trivially_constructible;
      using trait::type::features::is_trivially_destructible;
      using trait::type::features::is_trivially_copy_constructible;
      using trait::type::features::is_trivially_copy_assignable;
      using trait::type::features::is_trivially_move_constructible;
      using trait::type::features::is_trivially_move_assignable;
      using trait::type::features::is_destructible;
      using trait::type::features::is_nothrow_copy_constructible;
      using trait::type::features::is_assignable;
      using trait::type::features::is_nothrow_swappable;
      using trait::type::miscellaneous::enable_if;

      template<
        typename _T,
        bool = is_reference<_T>::value
      >
      struct __optional_storage
      {
        public:
          typedef _T                            value_type;

        public:
          union
          {
            unsigned char __empty;
            _T val;
          };
          unsigned char __info;

        constexpr __optional_storage() noexcept:
          __empty{}, __info{0U}
        { }
        template<
          typename... _Args,
          typename enable_if<
            is_constructible<_T, _Args&&...>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit __optional_storage(
          helper::in_place_t, _Args&&... _args
        ) noexcept(
          is_nothrow_constructible<_T, _Args&&...>::value
        ): val{algorithm::forward<_Args>(_args)...}, __info{1U}
        { }

        ~__optional_storage()
        {
          reset();
        }

        public:
          __UTILITY_CPP14_CONSTEXPR__
          inline value_type& __value() & noexcept
          { return val;}
          __UTILITY_CPP14_CONSTEXPR__
          inline value_type&& __value() && noexcept
          {
            using algorithm::move;
            return move(val);
          }
          __UTILITY_CPP14_CONSTEXPR__
          inline const value_type& __value() const & noexcept
          { return val;}
          __UTILITY_CPP14_CONSTEXPR__
          inline const value_type&& __value() const && noexcept
          {
            using algorithm::move;
            return move(val);
          }

        public:
          __UTILITY_CPP14_CONSTEXPR__
          bool has_value() const noexcept
          { return __info != 0U;}
          __UTILITY_CPP14_CONSTEXPR__
          bool empty() const noexcept
          { return __info == 0U;}

        public:
          void reset() noexcept
          {
            using memory::destroy_at;
            if(__info != 0U)
            {
              destroy_at(reinterpret_cast<_T*>(&val));
              __info = 0U;
            }
          }
          void swap(__optional_storage& _other)
          {
            using algorithm::move;
            if(this->__info && _other.__info)
            {
              using algorithm::swap;
              swap(val, _other.val);
            }
            else if(this->__info)
            {
              _other.__construct(move(val));
              reset();
            }
            else if(_other.__info)
            {
              this->__construct(move(_other.val));
              _other.reset();
            }
          }

        public:
          template<
            typename... _Args,
            typename enable_if<
              is_constructible<_T, _Args&&...>::value,
            bool>::type = true
          >
          value_type& __emplace(_Args&&... _args) noexcept(
            is_nothrow_constructible<_T, _Args&&...>::value
          )
          {
            using algorithm::forward;
            using memory::addressof;
            using memory::destroy_at;

            if(__info != 0U)
            { destroy_at(addressof(val));}
            ::new(addressof(val)) value_type(forward<_Args>(_args)...);
            __info = 1U;
            return __value();
          }
          template<
            typename _U, typename... _Args,
            typename __detail::enable_if<
              __detail::is_constructible<
                _T, initializer_list<_U>&, _Args&&...
              >::value,
            bool>::type = true
          >
          value_type& __emplace(
            initializer_list<_U> _init, _Args&&... _args
          ) noexcept(
            __detail::is_nothrow_constructible<
              _T, initializer_list<_U>&, _Args&&...
            >::value
          )
          {
            using algorithm::forward;
            using memory::addressof;
            using memory::destroy_at;

            if(__info != 0U)
            { destroy_at(addressof(val));}
            ::new(addressof(val)) value_type(_init, forward<_Args>(_args)...);
            __info = 1U;
            return __value();
          }

        public:
          template<
            typename... _Args,
            typename enable_if<
              is_constructible<_T, _Args&&...>::value,
            bool>::type = true
          >
          void __construct(_Args&&... _args) noexcept(
            is_nothrow_constructible<_T, _Args&&...>::value
          )
          {
            using algorithm::forward;
            using memory::addressof;

            ::new(addressof(val)) value_type(forward<_Args>(_args)...);
            __info = 1U;
          }
          template<
            typename _U, typename... _Args,
            typename enable_if<
              is_constructible<_T, _Args&&...>::value,
            bool>::type = true
          >
          void __construct(
            initializer_list<_U> _init, _Args&&... _args
          ) noexcept(
            __detail::is_nothrow_constructible<
              _T, initializer_list<_U>&, _Args&&...
            >::value
          )
          {
            using algorithm::forward;
            using memory::addressof;

            ::new(addressof(val)) value_type(_init, forward<_Args>(_args)...);
            __info = 1U;
          }

          template<typename _Optional>
          void __assign(_Optional&& _other)
          {
            using algorithm::forward;
            if(has_value() && _other.has_value())
            { val = forward<_Optional>(_other).__value();}
            else if(_other.has_value())
            { __construct(forward<_Optional>(_other).__value());}
            else if(has_value())
            { reset();}
          }

      };

      template<typename _T>
      struct __optional_storage<_T, true>
      {
        // static_assert(false, "");
      };

      template<
        typename _T,
        bool = is_trivially_copy_constructible<_T>::value
      >
      struct __optional_copy_construct: __optional_storage<_T>
      { using __optional_storage<_T>::__optional_storage;};

      template<typename _T>
      struct __optional_copy_construct<_T, false>: __optional_storage<_T>
      {
        using __optional_storage<_T>::__optional_storage;
        __optional_copy_construct() = default;

        __optional_copy_construct(
          const __optional_copy_construct& _other
        )
        {
          if(_other.has_value())
          { this->__construct(_other.val);}
        }

        __optional_copy_construct(__optional_copy_construct&&) = default;
        __optional_copy_construct& operator=(
          const __optional_copy_construct&
        ) = default;
        __optional_copy_construct& operator=(
          __optional_copy_construct&&
        ) = default;
      };
      template<
        typename _T,
        bool = is_trivially_move_constructible<_T>::value
      >
      struct __optional_move_construct: __optional_copy_construct<_T>
      { using __optional_copy_construct<_T>::__optional_copy_construct;};

      template<typename _T>
      struct __optional_move_construct<_T, false>:
        __optional_copy_construct<_T>
      {
        using __optional_copy_construct<_T>::__optional_copy_construct;
        __optional_move_construct() = default;

        __optional_move_construct(
          const __optional_move_construct& _other
        ) = default;

        __optional_move_construct(__optional_move_construct&& _other) noexcept(
          is_nothrow_move_constructible<_T>::value
        )
        {
          using algorithm::forward;
          if(_other.has_value())
          { this->__construct(forward<_T>(_other.val));}
        }
        __optional_move_construct& operator=(
          const __optional_move_construct&
        ) = default;
        __optional_move_construct& operator=(
          __optional_move_construct&&
        ) = default;
      };
      template<
        typename _T,
        bool = is_trivially_copy_assignable<_T>::value
      >
      struct __optional_copy_assignable: __optional_move_construct<_T>
      { using __optional_move_construct<_T>::__optional_move_construct;};

      template<typename _T>
      struct __optional_copy_assignable<_T, false>:
        __optional_move_construct<_T>
      {
        using __optional_move_construct<_T>::__optional_move_construct;
        __optional_copy_assignable() = default;

        __optional_copy_assignable(
          const __optional_copy_assignable&
        ) = default;
        __optional_copy_assignable(__optional_copy_assignable&&)  = default;

        __optional_copy_assignable& operator=(
          const __optional_copy_assignable& _other
        )
        {
          this->__assign(_other);
          return *this;
        }

        __optional_copy_assignable& operator=(
          __optional_copy_assignable&&
        ) = default;
      };
      template<
        typename _T,
        bool = is_trivially_copy_assignable<_T>::value
      >
      struct __optional_move_assignable: __optional_copy_assignable<_T>
      { using __optional_copy_assignable<_T>::__optional_copy_assignable;};

      template<typename _T>
      struct __optional_move_assignable<_T, false>:
        __optional_copy_assignable<_T>
      {
        using __optional_copy_assignable<_T>::__optional_copy_assignable;
        __optional_move_assignable() = default;

        __optional_move_assignable(
          const __optional_move_assignable&
        ) = default;
        __optional_move_assignable(__optional_move_assignable&&)  = default;

        __optional_move_assignable& operator=(
          const __optional_move_assignable&
        ) = default;

        __optional_move_assignable& operator=(
          __optional_move_assignable&& _other
        )
        {
          using algorithm::move;
          this->__assign(move(_other));
          return *this;
        }
      };


    }

    template<typename _T>
    class optional
    {
      private:
        template<typename>
        friend class optional;

      public:
        typedef _T value_type;

      private:
        static_assert(
          !__detail::is_same<value_type, helper::in_place_t>::value,
          "optional<in_place_t> is ill-formed"
        );
        static_assert(
          !__detail::is_reference<value_type>::value,
          "optional<T&/T&&> is ill-formed"
        );
        static_assert(
          !__detail::is_same<
            __detail::remove_cv_ref_t<value_type>, helper::nullopt_t
          >::value,
          "optional use nullopt_t is ill-formed"
        );
        static_assert(
          __detail::is_destructible<value_type>::value,
          "optional need a destructible type"
        );

      private:
        typedef __detail::__optional_move_assignable<_T>    __container;

      private:
        __container       __base;

      public:
        constexpr optional() noexcept: __base{}
        { }
        constexpr optional(helper::nullopt_t) noexcept: __base{}
        { }

        __UTILITY_CPP14_CONSTEXPR__
        optional(const optional& _other) = default;
        __UTILITY_CPP14_CONSTEXPR__
        optional(optional&& _other) = default;

        template<
          typename _U = _T,
          typename __detail::enable_if<
            __detail::is_constructible<_T, _U&&>::value,
          bool>::type = true,
          typename __detail::enable_if<
            __detail::is_convertible<_U&&, _T>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        optional(_U&& _val) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        ): __base{}
        {
          using algorithm::forward;
          __base.__construct(forward<_U>(_val));
        }
        template<
          typename _U = _T,
          typename __detail::enable_if<
            __detail::is_constructible<_T, _U&&>::value,
          bool>::type = true,
          typename __detail::enable_if<
            !__detail::is_convertible<_U&&, _T>::value,
          bool>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit optional(_U&& _val) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        ): __base{}
        {
          using algorithm::forward;
          __base.__construct(forward<_U>(_val));
        }

        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, const _U&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value
            >::value,
          bool>::type = true,
          typename __detail::enable_if<
            __detail::is_convertible<const _U&, _T>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        optional(const optional<_U>& _other) noexcept(
          __detail::is_nothrow_constructible<_T, const _U&>::value
        ):__base{}
        {
          if(_other.__base.has_value())
          { __base.__construct(*_other);}
        }
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, const _U&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value
            >::value,
          bool>::type = true,
          typename __detail::enable_if<
            !__detail::is_convertible<const _U&, _T>::value,
          bool>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit optional(const optional<_U>& _other) noexcept(
          __detail::is_nothrow_constructible<_T, const _U&>::value
        ):__base{}
        {
          if(_other.__base.has_value())
          { __base.__construct(*_other);}
        }
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, _U&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value
            >::value,
          bool>::type = true,
          typename __detail::enable_if<
            __detail::is_convertible<_U&&, _T>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        optional(optional<_U>&& _other) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        ): __base{}
        {
          using algorithm::forward;
          if(_other.__base.has_value())
          { __base.__construct(forward<_U>(*_other));}
        }
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, _U&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value
            >::value,
          bool>::type = true,
          typename __detail::enable_if<
            !__detail::is_convertible<_U&&, _T>::value,
          bool>::type = false
        >
        __UTILITY_CPP14_CONSTEXPR__ explicit optional(
          optional<_U>&& _other
        ) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        ): __base{}
        {
          using algorithm::forward;
          if(_other.__base.has_value())
          { __base.__construct(forward<_U>(*_other));}
        }
        template<
          typename... _Args,
          typename __detail::enable_if<
            __detail::is_constructible<_T, _Args&&...>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit optional(helper::in_place_t, _Args&&... _args) noexcept(
          __detail::is_nothrow_constructible<_T, _Args&&...>::value
        ): __base{}
        {
          using algorithm::forward;
          __base.__construct(forward<_Args>(_args)...);
        }
        template<
          typename _U,
          typename... _Args,
          typename __detail::enable_if<
            __detail::is_constructible<
            initializer_list<_U>&, _T, _Args&&...
            >::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        explicit optional(
          helper::in_place_t, initializer_list<_U> _init, _Args&&... _args
        ) noexcept(
          __detail::is_nothrow_constructible<
            initializer_list<_U>&, _T, _Args&&...
          >::value
        ): __base{}
        {
          using algorithm::forward;
          __base.__construct(_init, forward<_Args>(_args)...);
        }

        ~optional()
        {
        }

      public:
        optional& operator=(helper::nullopt_t) noexcept
        {
          __base.reset();
          return *this;
        }

      public:
        optional& operator=(const optional&) = default;
        optional& operator=(optional&&) = default;
        /**
         * \TODO
         */
        template<
          typename _U = _T,
          typename __detail::enable_if<
            __detail::is_constructible<_T, _U&&>::value &&
            (__detail::is_same<__detail::decay_t<_U>, _T>::value ||
            __detail::is_scalar<_T>::value),
          bool>::type = true
        >
        optional& operator=(_U&& _val) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        )
        {
          using algorithm::forward;

          if(__base.has_value())
          { __base.__value() = forward<_U>(_val);}
          else
          { __base.__construct(forward<_U>(_val));}
          return *this;
        }
        /**
         * \TODO
         */
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, const _U&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value,
              !__detail::is_assignable<_T&, optional<_U>&>::value,
              !__detail::is_assignable<_T&, const optional<_U>&>::value,
              !__detail::is_assignable<_T&, optional<_U>&&>::value,
              !__detail::is_assignable<_T&, const optional<_U>&&>::value
            >::value,
          bool>::type = true
        >
        optional& operator=(const optional<_U>& _other) noexcept(
          __detail::is_nothrow_constructible<_T, const _U&>::value
        )
        {
          __assign(_other);
          return *this;
        }
        /**
         * \TODO
         */
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::__and__<
              __detail::is_constructible<_T, _U&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&>::value,
              !__detail::is_constructible<_T, optional<_U>&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_constructible<_T, const optional<_U>&&>::value,
              !__detail::is_convertible<optional<_U>&, _T>::value,
              !__detail::is_convertible<const optional<_U>&, _T>::value,
              !__detail::is_convertible<optional<_U>&&, _T>::value,
              !__detail::is_convertible<const optional<_U>&&, _T>::value,
              !__detail::is_assignable<_T&, optional<_U>&>::value,
              !__detail::is_assignable<_T&, const optional<_U>&>::value,
              !__detail::is_assignable<_T&, optional<_U>&&>::value,
              !__detail::is_assignable<_T&, const optional<_U>&&>::value
            >::value,
          bool>::type = true
        >
        optional& operator=(optional<_U>&& _other) noexcept(
          __detail::is_nothrow_constructible<_T, _U&&>::value
        )
        {
          using algorithm::move;
          __assign(move(_other));
          return *this;
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline value_type* operator->()
        { return &__base.val;}
        __UTILITY_CPP14_CONSTEXPR__
        inline const value_type* operator->() const
        { return &__base.val;}
        __UTILITY_CPP14_CONSTEXPR__
        value_type& operator*() &
        { return __base.__value();}
        __UTILITY_CPP14_CONSTEXPR__
        const value_type& operator*() const &
        { return __base.__value();}
        __UTILITY_CPP14_CONSTEXPR__
        value_type&& operator*() &&
        { return std::move(__base.__value());}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline bool has_value() const noexcept
        { return __base.__info;}
        __UTILITY_CPP14_CONSTEXPR__
        inline bool empty() const noexcept
        { return __base.__info == 0U;}

        __UTILITY_CPP14_CONSTEXPR__
        inline explicit operator bool() const noexcept
        { return __base.__info;}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const value_type& value() const &
        {
          // TODO: Exception
          if(empty())
          { }
          return __base.__value();
        }
        __UTILITY_CPP14_CONSTEXPR__
        const value_type&& value() const &&
        {
          // TODO: Exception
          using algorithm::move;
          if(empty())
          { }
          return move(__base.__value());
        }
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::is_copy_constructible<_T>::value &&
            __detail::is_convertible<_U, value_type>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        value_type value_or(_U&& _val) const &
        {
          using algorithm::forward;
          if(empty())
          { return static_cast<value_type>(forward<_U>(_val));}
          return __base.__value();
        }
        template<
          typename _U,
          typename __detail::enable_if<
            __detail::is_move_constructible<_T>::value &&
            __detail::is_convertible<_U, value_type>::value,
          bool>::type = true
        >
        __UTILITY_CPP14_CONSTEXPR__
        value_type value_or(_U&& _val) &&
        {
          using algorithm::forward;
          using algorithm::move;
          if(empty())
          { return static_cast<value_type>(forward<_U>(_val));}
          return move(__base.__value());
        }

      public:
        template<
          typename... _Args,
          typename __detail::enable_if<
            __detail::is_constructible<_T, _Args&&...>::value,
          bool>::type = true
        >
        value_type& emplace(_Args&&... _args) noexcept(
          __detail::is_nothrow_constructible<_T, _Args&&...>::value
        )
        {
          using algorithm::forward;
          return __base.__emplace(forward<_Args>(_args)...);
        }
        template<
          typename _U,
          typename... _Args,
          typename __detail::enable_if<
            __detail::is_constructible<
              _T, initializer_list<_U>&, _Args&&...
            >::value,
          bool>::type = true
        >
        value_type& emplace(
          initializer_list<_U> _init, _Args&&... _args
        ) noexcept(
          __detail::is_nothrow_constructible<
            _T, initializer_list<_U>&, _Args&&...
          >::value
        )
        {
          using algorithm::forward;
          return __base.__emplace(_init, forward<_Args>(_args)...);
        }

      public:
        inline void reset() noexcept
        { __base.reset();}
        inline void swap(optional& _other) noexcept(
          __detail::is_nothrow_move_constructible<_T>::value &&
          __detail::is_nothrow_swappable<_T>::value
        )
        { this->__base.swap(_other.__base);}
    };

    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x == *_y;}
      return _x.has_value() == _y.has_value();
    }
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x != *_y;}
      return _x.has_value() != _y.has_value();
    }
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x < *_y;}
      return _y.has_value();
    }
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x > *_y;}
      return _x.has_value();
    }
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x <= *_y;}
      return _x.has_value() ? false : _y.empty();
    }
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(
      const optional<_T>& _x, const optional<_U>& _y
    )
    {
      if(_x.has_value() && _y.has_value())
      { return *_x >= *_y;}
      return _y.has_value() ? false : _x.empty();
    }
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return _x.empty();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return _y.empty();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return _x.has_value();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return _y.has_value();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return false;}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return _y.has_value();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return _x.has_value();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return false;}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return _x.empty();}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return true;}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(const optional<_T>& _x, helper::nullopt_t) noexcept
    { return true;}
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(helper::nullopt_t, const optional<_T>& _y) noexcept
    { return _y.empty();}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x == _y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x == *_y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x != _y : true;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x != *_y : true;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x < _y : true;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x < *_y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x > _y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x > *_y : true;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x <= _y : true;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x <= *_y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(const optional<_T>& _x, const _U& _y)
    { return _x.has_value() ? *_x >= _y : false;}
    template<typename _T, typename _U>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(const _U& _x, const optional<_T>& _y)
    { return _y.has_value() ? _x >= *_y : true;}

    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline optional<__detail::decay_t<_T>> make_optional(_T&& _val)
    {
      using algorithm::forward;
      return optional<__detail::decay_t<_T>>{forward<_T>(_val)};
    }
    template<typename _T, typename... _Args>
    __UTILITY_CPP14_CONSTEXPR__
    inline optional<_T> make_optional(_Args&&... _args)
    {
      using algorithm::forward;
      using helper::in_place;
      return optional<_T>{in_place, forward<_T>(_args)...};
    }
    template<typename _T, typename _U, typename... _Args>
    __UTILITY_CPP14_CONSTEXPR__
    inline optional<_T> make_optional(
      initializer_list<_U> _init, _Args&&... _args
    )
    {
      using algorithm::forward;
      using helper::in_place;
      return optional<_T>{in_place, _init, forward<_T>(_args)...};
    }

  }

  namespace algorithm
  {
    template<typename _T>
    void swap(container::optional<_T>& _x, container::optional<_T>& _y) noexcept(noexcept(_x.swap(_y)))
    {
      _x.swap(_y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_OPTIONAL__
