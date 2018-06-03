
#ifndef __UTILITY_CONTAINER_ANY__
#define __UTILITY_CONTAINER_ANY__

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>
#include<utility/container/helper/in_place_t.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/sstd/new.hpp>

#include<utility/memory/destroy_at.hpp>

#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/transform/remove_cv_ref.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/type/miscellaneous/aligned_storage.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>

namespace utility
{
  namespace container
  {
    class any;

    namespace __detail
    {
      using trait::type::transform::decay;
      using trait::type::releations::is_same;
      using trait::type::miscellaneous::aligned_storage;
      using trait::type::miscellaneous::enable_if;
      using trait::type::miscellaneous::conditional;
      using trait::type::features::is_constructible;
      using trait::type::features::is_copy_constructible;
      using trait::type::features::is_nothrow_move_constructible;
      using trait::type::transform::remove_cv_ref;
      using container::helper::in_place_type_t;
      using container::helper_traits::is_in_place_type;

      template<typename _Buffer, typename _T,
        bool _Safe = is_nothrow_move_constructible<_T>::value,
        bool _Fits = (sizeof(_T) <= sizeof(_Buffer)) &&
          (alignof(_T) <= alignof(_Buffer))>
      struct __is_small_object
      { constexpr static bool value = _Safe && _Fits;};

      enum class __any_operator
      {
        any_access,
        any_copy,
        any_move,
        any_destroy,
        any_info
      };

      union __any_args
      {
        void* __ptr;
        any*  __any;
      };

      template<unsigned short _L = 1U>
      union __any_storage
      {
        constexpr __any_storage() noexcept
          :__ptr{nullptr}
        { }

        __any_storage(const __any_storage&) = delete;
        __any_storage& operator=(const __any_storage&) = delete;

        void* __ptr;
        typename aligned_storage<sizeof(void*[_L]), alignof(void*)>::type __buffer;
      };

      template<typename _T,unsigned short _L = 1U>
      class __small_object_manager
      {
        public:
          typedef _T                                  cast_type;

        public:
          typedef __any_operator        any_op;
          typedef __any_args            any_args;
          typedef __any_storage<_L>     any_storage;

        public:
          static inline void operate(
            any_op __op, const any* __any, any_args* __args
          );
          template<typename _ValueType>
          static inline void create(any_storage& __storage, _ValueType&& __val);
          template<typename... _Args>
          static inline void create(any_storage& __storage, _Args&&... __args);
      };
      template<typename _T, unsigned short _L = 1U>
      class __large_object_manager
      {
        public:
          typedef _T                                  cast_type;

        public:
          typedef __any_operator        any_op;
          typedef __any_args            any_args;
          typedef __any_storage<_L>     any_storage;

        public:
          static inline void operate(
            any_op __op, const any* __any, any_args* __args
          );
          template<typename _ValueType>
          static inline void create(any_storage& __storage, _ValueType&& __val);
          template<typename... _Args>
          static inline void create(any_storage& __storage, _Args&&... __args);
      };

      template<typename _T, unsigned short _L = 1U>
      using __object_manager =
        conditional<__is_small_object<__any_storage<_L>, _T>::value,
          __small_object_manager<_T, _L>,
          __large_object_manager<_T, _L>>;

      template<typename _T>
      using __is_inplace_type =
        is_in_place_type<typename remove_cv_ref<_T>::type>;
    }

    class any
    {
      private:
        template<typename, typename>
        friend class __detail::__small_object_manager;
        template<typename, typename>
        friend class __detail::__large_object_manager;

      private:
        typedef __detail::__any_storage<1U>       any_stroge;
        typedef __detail::__any_operator          any_op;
        typedef __detail::__any_args              any_args;

      private:
        typedef void(*any_manager)(any_op, const any*, any_args*);

      private:
        any_manager   __manager;
        any_stroge    __stroge;

      public:
        constexpr any() noexcept:
          __manager{nullptr}, __stroge{}
        { }
        any(const any& __other):
          __manager{nullptr}, __stroge{}
        {
          if(__other.has_value())
          {
            any_args __args;
            __args.__any = this;
            __other.__manager(any_op::any_copy, &__other, &__args);
          }
        }

        any(any&& __other) noexcept:
          __manager{nullptr}, __stroge{}
        {
          if(__other.has_value())
          {
            any_args __args;
            __args.__any = this;
            __other.__manager(any_op::any_move, &__other, &__args);
            __other.__manager = nullptr;
          }
        }

        template<
          typename _ValueType,
          typename _T = typename __detail::decay<_ValueType>::type,
          typename _Manager =
            typename __detail::__object_manager<_T, 1U>::type,
          typename __detail::enable_if<trait::__and__<
            !__detail::is_same<_T, any>::value,
            !__detail::__is_inplace_type<_T>::value,
            __detail::is_constructible<_T, _ValueType&&>::value,
            __detail::is_copy_constructible<_T>::value>::value,
          bool>::type = true
        >
        any(_ValueType&& __val):
          __manager{&_Manager::operate}, __stroge{}
        {
          _Manager::create(
            this->__stroge, algorithm::forward<_ValueType>(__val)
          );
        }

        template<
          typename _ValueType,
          typename _T = typename __detail::decay<_ValueType>::type,
          typename _Manager =
            typename __detail::__object_manager<_T, 1U>::type,
          typename __detail::enable_if<trait::__and__<
            !__detail::is_same<_T, any>::value,
            !__detail::__is_inplace_type<_T>::value,
            !__detail::is_constructible<_T, _ValueType&&>::value,
            __detail::is_copy_constructible<_T>::value>::value,
          bool>::type = true
        >
        any(_ValueType&& __val):
          __manager{&_Manager::operate}, __stroge{}
        { _Manager::create(this->__stroge, __val);}


        template<
          typename _ValueType,
          typename... _Args,
          typename _T = __detail::decay<_ValueType>::type,
          typename _Manager =
            typename __detail::__object_manager<_T, 1U>::type,
          typename __detail::enable_if<trait::__and__<
            __detail::is_constructible<_T, _Args&&...>::value,
            __detail::is_copy_constructible<_T>::value>::value,
          bool>::type = true
        >
        explicit any(__detail::in_place_type_t<_ValueType>, _Args&&... __args):
          __manager{&_Manager::operate}, __stroge{}
        {
          _Manager::create(
            this->__stroge, algorithm::forward<_ValueType>(__args)
          );
        }
        template<
          typename _ValueType,
          typename _U,
          typename... _Args,
          typename _T = __detail::decay<_ValueType>::type,
          typename _Manager =
            typename __detail::__object_manager<_T, 1U>::type,
          typename __detail::enable_if<trait::__and__<
            __detail::is_constructible<_T, initializer_list<_U>, _Args&&...>::value,
            __detail::is_copy_constructible<_T>::value>::value,
          bool>::type = true
        >
        explicit any(
          __detail::in_place_type_t<_ValueType>,
          initializer_list<_U> __init, _Args&&... __args
        ):__manager{&_Manager::operate}, __stroge{}
        {
          _Manager::create(
            this->__stroge, __init, algorithm::forward<_ValueType>(__args)
          );
        }

      public:
        any& operator=(const any& __other)
        {
          if(&__other != this)
          {
            this->reset();
            any_args __args;
            __args.__any = this;
            if(__other.has_value())
            { __other.__manager(any_op::any_move, &__other, &__args);}
          }
          return *this;
        }
        any& operator=(any&& __other) noexcept
        {
          if(&__other != this)
          {
            this->reset();
            any_args __args;
            __args.__any = this;
            if(__other.has_value())
            {
              __other.__manager(any_op::any_move, &__other, &__args);
              __other.__manager = nullptr;
            }
          }
          return *this;
        }
        template<typename _ValueType>
        any& operator=(_ValueType&& __val)
        {
          this->operator=(any{algorithm::forward<_ValueType&&>(__val)});
          return *this;
        }

      public:
        ~any()
        { this->reset();}

      public:
        void reset() noexcept
        {
          if(this->has_value())
          {
            this->__manager(any_op::any_destroy, this, nullptr);
            this->__manager = nullptr;
          }
        }
        void swap(any& __any) noexcept
        {
          if(this->empty() && __any.empty())
          { return;}
          if(this->empty())
          {
            any_args __args;
            __args.__any = this;
            __any.__manager(any_op::any_move, &__any, &__args);
            __any.__manager = nullptr;
          }
          else if(__any.empty())
          {
            any_args __args;
            __args.__any = &__any;
            this->__manager(any_op::any_move, this, &__args);
            this->__manager = nullptr;
          }
          else
          {
            any_args __args;
            any __tmp;
            __args.__any = &__tmp;
            __any.__manager(any_op::any_move, &__any, &__args);
            __args.__any = &__any;
            this->__manager(any_op::any_move, this, &__args);
            __args.__any = this;
            __tmp.__manager(any_op::any_move, &__tmp, &__args);
            __tmp.__manager = nullptr;
          }
        }
        void possible_swap(any& __any) noexcept
        { this->swap(__any);}

      public:
        bool has_value() const noexcept
        { return this->__manager != nullptr;}
        bool empty() const noexcept
        { return this->__manager == nullptr;}
        // const type_info& type() const;

      public:
        template<typename _T>
        const void* _get() const noexcept
        {
          typedef typename __detail::decay<_T>::type _U;
          typedef typename __detail::__object_manager<_U, 1U>::type _Manager;
          if(this->empty() ||
            this->__manager != &_Manager::operate)
          { return nullptr;}
          any_args __args;
          this->__manager(any_op::any_access, this, &__args);
          return __args.__ptr;
        }
        template<typename _T>
        void* _get() noexcept
        {
          typedef typename __detail::decay<_T>::type _U;
          typedef typename __detail::__object_manager<_U, 1U>::type _Manager;
          if(this->empty() ||
            this->__manager != &_Manager::operate)
          { return nullptr;}
          any_args __args;
          this->__manager(any_op::any_access, this, &__args);
          return __args.__ptr;
        }

      private:
        template<
          typename _T,
          typename _U = typename __detail::decay<_T>::type,
          typename __detail::enable_if<
            __detail::is_copy_constructible<_U>::value,
            bool>::type = true
        >
        static inline const void* caster(const any* __any) noexcept
        { return __any->_get<_T>();}
        template<
          typename _T,
          typename _U = typename __detail::decay<_T>::type,
          typename __detail::enable_if<
            __detail::is_copy_constructible<_U>::value,
            bool>::type = true
        >
        static inline void* caster(any* __any) noexcept
        { return __any->_get<_T>();}

      private:
        template<typename _T>
        friend _T* any_cast(any* __operand) noexcept;
        template<typename _T>
        friend const _T* any_cast(const any* __operand) noexcept;
        template<typename _T>
        friend _T any_cast(any& __operand);
        template<typename _T>
        friend _T any_cast(const any& __operand);
        template<typename _T>
        friend _T any_cast(any&& __operand);
    };

    template<typename _T>
    _T* any_cast(any* __operand) noexcept
    { return static_cast<_T*>(any::caster<_T>(__operand));}
    template<typename _T>
    const _T* any_cast(const any* __operand) noexcept
    { return static_cast<const _T*>(any::caster<_T>(__operand));}
    template<typename _T>
    _T any_cast(any& __operand)
    {
      typedef typename __detail::decay<_T>::type _U;
      static_assert(__detail::is_constructible<_T, _U&>::value, "ill-formed any cast");
      return static_cast<_T>(*any_cast<_U>(&__operand));
    }
    template<typename _T>
    _T any_cast(const any& __operand)
    {
      typedef typename __detail::decay<_T>::type _U;
      static_assert(__detail::is_constructible<_T, const _U&>::value, "ill-formed any cast");
      return static_cast<_T>(*any_cast<_U>(&__operand));
    }
    template<typename _T>
    _T any_cast(any&& __operand)
    {
      typedef typename __detail::decay<_T>::type _U;
      static_assert(__detail::is_constructible<_T, _U>::value, "ill-formed any cast");
      return algorithm::move(static_cast<_T>(*any_cast<_U>(&__operand)));
    }

    template<typename _ValueType, typename... _Args>
    any make_any(_Args&&... __args)
    {
      return any{
        __detail::in_place_type_t<_ValueType>{},
        algorithm::forward<_Args>(__args)...
      }
    }
    template<typename _ValueType, typename _U, typename... _Args>
    any make_any(initializer_list<_U> __init, _Args&&... __args)
    {
      return any{
        __detail::in_place_type_t<_ValueType>{}, __init
        algorithm::forward<_Args>(__args)...
      }
    }

    namespace __detail
    {
      template<typename _T, unsigned short _L>
      void __large_object_manager<_T, _L>::operate(
        any_op __op, const any* __any, any_args* __args
      )
      {
        switch(__op)
        {
          case any_op::any_access:
            __args->__ptr = const_cast<cast_type*>(
              static_cast<const cast_type*>(__any->__stroge.__ptr)
            );
            break;
          case any_op::any_copy:
            __args->__any->__stroge.__ptr = new _T(
              *static_cast<const cast_type*>(__any->__stroge.__ptr)
            );
            __args->__any->__manager = __any->__manager;
            break;
          case any_op::any_destroy:
            delete static_cast<const cast_type*>(__any->__stroge.__ptr);
            break;
          case any_op::any_move:
            __args->__any->__stroge.__ptr = __any->__stroge.__ptr;
            __args->__any->__manager = __any->__manager;
            break;
          case any_op::any_info:
            break;
        }

        return;
      }

      template<typename _T, unsigned short _L>
      template<typename _ValueType>
      inline void __large_object_manager<_T, _L>::create(
        any_storage& __storage, _ValueType&& __val
      )
      {
        __storage.__ptr =
          new _T(algorithm::forward<_ValueType>(__val));
      }
      template<typename _T, unsigned short _L>
      template<typename... _Args>
      inline void __large_object_manager<_T, _L>::create(
        any_storage& __storage, _Args&&... __args
      )
      {
        __storage.__ptr =
          new _T(algorithm::forward<_Args>(__args)...);
      }


      template<typename _T, unsigned short _L>
      inline void __small_object_manager<_T, _L>::operate(
        any_op __op, const any* __any, any_args* __args
      )
      {
        switch(__op)
        {
          case any_op::any_access:
            __args->__ptr = const_cast<cast_type*>(
              reinterpret_cast<const cast_type*>(&__any->__stroge.__buffer)
            );
            break;
          case any_op::any_copy:
            ::new(&__args->__any->__stroge.__buffer) _T(
              *reinterpret_cast<const cast_type*>(&__any->__stroge.__buffer)
            );
            __args->__any->__manager = __any->__manager;
            break;
          case any_op::any_destroy:
            memory::destroy_at(
              const_cast<_T*>(reinterpret_cast<const cast_type*>(
                &__any->__stroge.__buffer
              ))
            );
            break;
          case any_op::any_move:
            ::new(&__args->__any->__stroge.__buffer) _T(
              *std::move(const_cast<_T*>(
                reinterpret_cast<const cast_type*>(
                  &__any->__stroge.__buffer))));
            __args->__any->__manager = __any->__manager;
            break;
          case any_op::any_info:
            break;
        }

        return;
      }
      template<typename _T, unsigned short _L>
      template<typename _ValueType>
      inline void __small_object_manager<_T, _L>::create(
        any_storage& __storage, _ValueType&& __val
      )
      {
        ::new (static_cast<void*>(&__storage.__buffer)) _T(
          algorithm::forward<_ValueType>(__val)
        );
      }
      template<typename _T, unsigned short _L>
      template<typename... _Args>
      inline void __small_object_manager<_T, _L>::create(
        any_storage& __storage, _Args&&... __args
      )
      {
        ::new (static_cast<void*>(&__storage.__buffer)) _T(
          algorithm::forward<_Args>(__args)...
        );
      }

    }
  }

  namespace algorithm
  {
    void swap(container::any& __x, container::any& __y) noexcept
    { __x.swap(__y);}
    void possible_swap(container::any& __x, container::any& __y) noexcept
    { __x.swap(__y);}
  }
}

#endif // ! __UTILITY_CONTAINER_ANY__
