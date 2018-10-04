
#ifndef __UTILITY_FUNCTIONAL_FUNCTION__
#define __UTILITY_FUNCTIONAL_FUNCTION__

#include<utility/config/utility_config.hpp>

#include<utility/container/compressed_pair.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/memory/destroy_at.hpp>
#include<utility/memory/allocator.hpp>

#include<utility/functional/invoke.hpp>
#include<utility/functional/reference_wrapper.hpp>

#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_invocable.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/miscellaneous/invoke_result.hpp>
#include<utility/trait/type/miscellaneous/aligned_storage.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

#include<utility/sstd/new.hpp>

namespace utility
{
  namespace functional
  {
    template<typename>
    class function;

    namespace __detail
    {
      using trait::__type_and__;
      using trait::type::transform::decay;
      using trait::type::features::is_invocable;
      using trait::type::features::is_nothrow_constructible;
      using trait::type::releations::is_same;
      using trait::type::miscellaneous::aligned_storage;
      using trait::type::miscellaneous::invoke_result;
      using trait::type::miscellaneous::conditional;
      using trait::type::miscellaneous::enable_if;
      using container::compressed_pair;

      template<typename _Func>
      bool is_vaild(const _Func&)
      { return true;}
      template<typename _Func>
      bool is_vaild(_Func* _ptr)
      { return _ptr != nullptr;}
      template<typename _Func, typename _C>
      bool is_vaild(_Func _C::* _ptr)
      { return _ptr != nullptr;}

      template<typename _Buffer, typename _T,
        bool _Safe = is_nothrow_constructible<_T, _T&&>::value,
        bool _Fits = (sizeof(_T) <= sizeof(_Buffer)) &&
          (alignof(_T) <= alignof(_Buffer))>
      struct __is_small_function_object
      { constexpr static bool value = _Safe && _Fits;};

      enum class __function_operator
      {
        access,
        copy,
        move,
        destroy,
        info
      };

      template<typename _T>
      union __function_args
      {
        void*           __ptr;
        function<_T>*   __func;
      };

      template<unsigned short _L = 2U>
      union __function_storage
      {
        void* __ptr;
        typename aligned_storage<sizeof(void*[_L]), alignof(void*)>::type __buffer;

        constexpr __function_storage() noexcept: __ptr{nullptr}
        { }

        __function_storage(const __function_storage&) = delete;
        __function_storage(__function_storage&&) = delete;
      };

      template<typename, typename, typename, unsigned short _L = 2U>
      class __small_function_manager;
      template<typename, typename, typename, unsigned short _L = 2U>
      class __large_function_manager;

      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      class __small_function_manager<_F, _Alloc, _R(_Args...), _L>
      {
        public:
          typedef _F        cast_type;
          typedef _R        result_type;
          typedef _Alloc    allocator_type;

        public:
          typedef __function_operator             function_op;
          typedef __function_args<_R(_Args...)>   function_args;
          typedef __function_storage<_L>          function_storage;
          typedef function<_R(_Args...)>          _function;

        public:
          static inline void operate(
            function_op _op, const _function* _func, function_args* _args
          );
          static inline void create(
            function_storage& _storage, const allocator_type&,
            cast_type&& _func
          );
          static inline _R process(
            function_storage& _storage, _Args&&... _args
          );
      };

      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      class __large_function_manager<_F, _Alloc, _R(_Args...), _L>
      {
        public:
          typedef _F        cast_type;
          typedef _R        result_type;
          typedef _Alloc    allocator_type;

        public:
          typedef __function_operator             function_op;
          typedef __function_args<_R(_Args...)>   function_args;
          typedef __function_storage<_L>          function_storage;
          typedef function<_R(_Args...)>          _function;

        public:
          static inline void operate(
            function_op _op, const _function* _func, function_args* _args
          );
          static inline void create(
            function_storage& _storage, const allocator_type&,
            cast_type&& _func
          );
          static inline _R process(
            function_storage& _storage, _Args&&... _args
          );
      };

      template<unsigned short _L, typename _Alloc, typename _Fn, typename _R, typename... _Args>
      using __function_manager =
        conditional<
          __is_small_function_object<
            __function_storage<_L>, compressed_pair<_Fn, _Alloc>
          >::value,
          __small_function_manager<_Fn, _Alloc, _R(_Args...), _L>,
          __large_function_manager<_Fn, _Alloc, _R(_Args...), _L>>;

      template<typename _Fn, typename _R, typename... _Args>
      using __is_vaild_callable = __type_and__<
        is_invocable<_Fn, _Args...>,
        is_same<typename invoke_result<_Fn, _Args...>::type, _R>
      >;

    }

    template<typename _R, typename... _Args>
    class function<_R(_Args...)>
    {
      private:
        template<typename, typename, typename, unsigned short>
        friend class __detail::__small_function_manager;
        template<typename, typename, typename, unsigned short>
        friend class __detail::__large_function_manager;

      public:
        typedef _R     result_type;

      private:
        typedef __detail::__function_storage<2U>        function_storage;
        typedef __detail::__function_operator           function_op;
        typedef __detail::__function_args<_R(_Args...)> function_args;

      private:
        typedef void(*function_manager)(
          function_op, const function*, function_args*
        );
        typedef _R(*function_invoke)(function_storage&, _Args&&...);

      private:
        function_manager    __manager;
        function_invoke     __invoke;
        function_storage    __storage;

      public:
        function() noexcept:
          __manager{nullptr}, __invoke{}, __storage{}
        { }
        function(nullptr_t) noexcept:
          __manager{nullptr}, __invoke{}, __storage{}
        { }
        function(const function& _other):
          __manager{nullptr}, __invoke{}, __storage{}
        {
          if(_other.has_value())
          {
            function_args __args;
            __args.__func = this;
            _other.__manager(function_op::copy, &_other, &__args);
          }
        }

        function(function&& _other) noexcept:
          __manager{nullptr}, __invoke{}, __storage{}
        {
          if(_other.has_value())
          {
            function_args __args;
            __args.__func = this;
            _other.__manager(function_op::move, &_other, &__args);
            _other.__manager = nullptr;
          }
        }

        template<
          typename _Fn,
          typename _Manager =
            typename __detail::__function_manager<
              2U, memory::allocator<_Fn>, _Fn, _R, _Args...
            > ::type,
          typename  __detail::enable_if<
            __detail::__is_vaild_callable<_Fn, _R, _Args...>::value,
          bool>::type = true
        >
        function(_Fn _func):
          __manager{&_Manager::operate},
          __invoke{&_Manager::process},
          __storage{}
        {
          using algorithm::move;
          using memory::allocator;
          _Manager::create(__storage, allocator<_Fn>{}, move(_func));
        }

        ~function()
        { reset();}

      public:
        function& operator=(const function& _other)
        {
          if(&_other != this)
          {
            reset();
            function_args __args;
            __args.__func = this;
            if(_other.has_value())
            { _other.__manager(function_op::copy, &_other, &__args);}
          }
          return *this;
        }
        function& operator=(function&& _other) noexcept
        {
          if(&_other != this)
          {
            reset();
            function_args __args;
            __args.__func = this;
            if(_other.has_value())
            {
              _other.__manager(function_op::move, &_other, &__args);
              _other.__manager = nullptr;
            }
          }
          return *this;
        }
        function& operator=(nullptr_t) noexcept
        {
          reset();
          return *this;
        }
        template<typename _Fn>
        function& operator=(_Fn&& _func)
        {
          using algorithm::forward;
          this->operator=(function{forward<_Fn&&>(_func)});
          return *this;
        }
        template<typename _Fn>
        function& operator=(reference_wrapper<_Fn>&& _other) noexcept
        {
          using algorithm::forward;
          this->operator=(function{forward<_Fn&&>(_other)});
          return *this;
        }

      public:
        result_type operator()(_Args... _args) const
        {
          using algorithm::forward;
          if(empty())
          { }
          return this->__invoke(this->__storage, forward<_Args>(_args)...);
        }

      public:
        void reset() noexcept
        {
          if(has_value())
          {
            __manager(function_op::destroy, this, nullptr);
            __manager = nullptr;
          }
        }
        void swap(function& _other) noexcept
        {
          if(empty() && _other.empty())
          { return;}
          if(empty())
          {
            function_args __args;
            __args.__func = this;
            _other.__manager(function_op::move, &_other, &__args);
            _other.__manager = nullptr;
          }
          else if(_other.empty())
          {
            function_args __args;
            __args.__func = &_other;
            this->__manager(function_op::move, this, &__args);
            this->__manager = nullptr;
          }
          else
          {
            function_args __args;
            function __tmp;
            __args.__func = &__tmp;
            _other.__manager(function_op::move, &_other, &__args);
            __args.__func = &_other;
            this->__manager(function_op::move, this, &__args);
            __args.__func = this;
            __tmp.__manager(function_op::move, &__tmp, &__args);
          }
        }
        void possible_swap(function& _other) noexcept
        { this->swap(_other);}

      public:
        explicit operator bool() const noexcept
        { return __manager;}
        bool empty() const noexcept
        { return __manager == nullptr;}
        bool has_value() const noexcept
        { return __manager != nullptr;}

      public:
        template<typename _T>
        _T* target() noexcept
        {
          typedef typename __detail::__function_manager<
            2U, memory::allocator<_T>, _T, _R, _Args...
          >::type _Manager;
          if(empty() || this->__manager != &_Manager::operate)
          { return nullptr;}
          function_args __args;
          this->__manager(function_op::access, this, &__args);
          return static_cast<_T*>(__args.__ptr);
        }
        template<typename _T>
        const _T* target() const noexcept
        {
          typedef typename __detail::__function_manager<
            2U, memory::allocator<_T>, _T, _R, _Args...
          >::type _Manager;
          if(empty() || this->__manager != &_Manager::operate)
          { return nullptr;}
          function_args __args;
          this->__manager(function_op::access, this, &__args);
          return static_cast<const _T*>(__args.__ptr);
        }
    };

    template<typename _R, typename... _Args>
    bool operator==(const function<_R(_Args...)>& _x, nullptr_t)
    { return _x.empty();}
    template<typename _R, typename... _Args>
    bool operator==(nullptr_t, const function<_R(_Args...)>& _y)
    { return _y.empty();}
    template<typename _R, typename... _Args>
    bool operator!=(const function<_R(_Args...)>& _x, nullptr_t)
    { return _x.has_value();}
    template<typename _R, typename... _Args>
    bool operator!=(nullptr_t, const function<_R(_Args...)>& _y)
    { return _y.has_value();}

    namespace __detail
    {
      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      void __large_function_manager<_F, _Alloc, _R(_Args...), _L>::operate(
        function_op _op, const _function* _func, function_args* _args
      )
      {
        switch(_op)
        {
          case function_op::access:
            _args->__ptr = const_cast<cast_type*>(
              static_cast<const cast_type*>(_func->__storage.__ptr)
            );
            break;
          case function_op::copy:
            _args->__func->__storage.__ptr = new _F(
              *static_cast<const cast_type*>(_func->__storage.__ptr)
            );
            _args->__func->__manager = _func->__manager;
            _args->__func->__invoke = _func->__invoke;
            break;
          case function_op::destroy:
            // memory::destroy_at(
            //   static_cast<cast_type*>(_func->__storage.__ptr)
            // );
            delete static_cast<const cast_type*>(_func->__storage.__ptr);
            break;
          case function_op::move:
            _args->__func->__storage.__ptr = _func->__storage.__ptr;
            _args->__func->__manager = _func->__manager;
            _args->__func->__invoke = _func->__invoke;
            break;
          case function_op::info:
            break;
        }

        return;
      }
      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      void __large_function_manager<_F, _Alloc, _R(_Args...), _L>::create(
        function_storage& _storage, const allocator_type&,
        cast_type&& _func
      )
      {
        using algorithm::move;
        _storage.__ptr = new cast_type(move(_func));
      }
      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      _R __large_function_manager<_F, _Alloc, _R(_Args...), _L>::process(
        function_storage& _storage, _Args&&... _args
      )
      {
        using functional::invoke;
        using algorithm::forward;
        cast_type* __ptr = static_cast<cast_type*>(&_storage.__ptr);

        return invoke(*__ptr, forward<_Args>(_args)...);
      }

      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      void __small_function_manager<_F, _Alloc, _R(_Args...), _L>::operate(
        function_op _op, const _function* _func, function_args* _args
      )
      {
        using algorithm::move;

        const cast_type* __ptr =
          reinterpret_cast<const cast_type*>(&_func->__storage.__buffer);
        switch(_op)
        {
          case function_op::access:
            _args->__ptr = const_cast<cast_type*>(__ptr);
            break;
          case function_op::copy:
            ::new(&_args->__func->__storage.__buffer) _F(*__ptr);
            _args->__func->__manager = _func->__manager;
            _args->__func->__invoke = _func->__invoke;
            break;
          case function_op::destroy:
            memory::destroy_at(const_cast<cast_type*>(__ptr));
            break;
          case function_op::move:
            ::new(&_args->__func->__storage.__buffer) _F(
              move(*const_cast<cast_type*>(__ptr)));
            _args->__func->__manager = _func->__manager;
            _args->__func->__invoke = _func->__invoke;
            break;
          case function_op::info:
            break;
        }

        return;
      }

      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      void __small_function_manager<_F, _Alloc, _R(_Args...), _L>::create(
        function_storage& _storage, const allocator_type&,
        cast_type&& _func
      )
      {
        using algorithm::move;
        ::new(static_cast<void*>(&_storage.__buffer)) cast_type(
          move(_func)
        );
      }
      template<
        typename _F, typename _Alloc,
        typename _R, typename... _Args,
        unsigned short _L
      >
      _R __small_function_manager<_F, _Alloc, _R(_Args...), _L>::process(
        function_storage& _storage, _Args&&... _args
      )
      {
        using functional::invoke;
        using algorithm::forward;
        cast_type* __ptr = reinterpret_cast<cast_type*>(&_storage.__buffer);

        return invoke(*__ptr, forward<_Args>(_args)...);
      }
    }
  }
}

#endif // ! __UTILITY_FUNCTIONAL_FUNCTION__
