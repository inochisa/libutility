
#ifndef __UTILITY_MEMORY_UNIQUE_PTR__
#define __UTILITY_MEMORY_UNIQUE_PTR__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/forward.hpp>

#include<utility/memory/default_delete.hpp>

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__twochar__.hpp>
#include<utility/trait/type/categories/is_null_pointer.hpp>
#include<utility/trait/type/categories/is_pointer.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/categories/is_array.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/transform/remove_pointer.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/features/is_move_constructible.hpp>
#include<utility/trait/type/features/is_copy_assignable.hpp>
#include<utility/trait/type/features/is_move_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_copy_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_default_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>
#include<utility/trait/type/miscellaneous/common_type.hpp>

namespace utility
{
  namespace memory
  {
    namespace __unique_ptr_impl
    {
      using __two = trait::__opt__::__twochar__;
      template<typename _Deleter>
      struct __unique_ptr_pointer_test
      {
        private:
          template<typename _T>
          static char __test(int, typename _T::pointer* = 0);
          template<typename _T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(decltype(__test<_Deleter>(0))) == sizeof(char);
      };

      template<typename _Value, typename _Deleter,
        bool = __unique_ptr_pointer_test<
          typename
          trait::type::transform::remove_reference<_Deleter>::type>::value>
      struct __unique_ptr_pointer;

      template<typename _Value, typename _Deleter>
      struct __unique_ptr_pointer<_Value, _Deleter, true>
      {
        typedef typename trait::type::transform::remove_reference<_Deleter>::type::pointer type;
      };
      template<typename _Value, typename _Deleter>
      struct __unique_ptr_pointer<_Value, _Deleter, false>
      { typedef _Value* type;};
    }

    template
    <
      typename _T,
      typename _Deleter = default_delete<_T>
    >
    class unique_ptr
    {
      public:
        typedef _T element_type;
        typedef _Deleter deleter_type;
        typedef typename
          __unique_ptr_impl::__unique_ptr_pointer<_T, _Deleter>::type
          pointer;

      private:
        typedef typename
          trait::type::transform::remove_reference<_Deleter>::type
          __unref_delete_type;

      private:
        pointer __ptr;
        deleter_type __deleter;

      public:
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        constexpr unique_ptr() noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(nullptr), __deleter()
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        constexpr unique_ptr(nullptr_t) noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(nullptr), __deleter()
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        explicit unique_ptr(pointer __optr) noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(__optr), __deleter()
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::features::is_copy_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(
          pointer __optr,
          typename
          trait::type::miscellaneous::conditional
          <
            trait::type::categories::is_reference<deleter_type>::value,
            deleter_type,
            typename
            trait::type::transform::add_lvalue_reference<
              const deleter_type>::type
          >::type __odeleter
        ) noexcept(
          trait::type::features::is_nothrow_copy_constructible<deleter_type>::value
        ): __ptr(__optr), __deleter(__odeleter)
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::features::is_move_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(
          pointer __optr,
          __unref_delete_type&& __odeleter
        ) noexcept(
          trait::type::features::is_nothrow_move_constructible<deleter_type>::value
        ): __ptr(__optr),
           __deleter(algorithm::forward<decltype(__odeleter)>(__odeleter))
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_move_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_move_constructible<deleter_type>::value
        ): __ptr(__other.release()),
           __deleter(algorithm::move(__other.__deleter))
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_copy_constructible<_Del>::value,
            bool
          >::type = false
        >
        unique_ptr(
          unique_ptr&& __other,
          typename trait::type::miscellaneous::enable_if<
            !trait::type::features::is_move_constructible<_Del>::value,
            void>::type* = nullptr
        ) noexcept(
          trait::type::features::is_nothrow_copy_constructible<deleter_type>::value
        ): __ptr(__other.release()),
           __deleter(__other.__deleter)
        { }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::releations::is_convertible
            <
              typename unique_ptr<_U, _UDelete>::pointer,
              pointer
            >::value &&
            !trait::type::categories::is_array<_U>::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_move_constructible<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_move_constructible<_UDelete>::value
        ): __ptr(__other.release()),
           __deleter(algorithm::move(__other.__deleter))
        { }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::releations::is_convertible
            <
              typename unique_ptr<_U, _UDelete>::pointer,
              pointer
            >::value &&
            !trait::type::categories::is_array<_U>::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_copy_constructible<_UDelete>::value,
            bool
          >::type = false
        >
        unique_ptr(unique_ptr<_U, _UDelete>&& __other, int* = nullptr) noexcept(
          trait::type::features::is_nothrow_copy_constructible<_UDelete>::value
        ): __ptr(__other.release()),
           __deleter(__other.__deleter)
        { }

        ~unique_ptr()
        { this->reset();}

      public:
        unique_ptr& operator=(nullptr_t) noexcept
        { this->reset();}
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_move_assignable<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr& operator=(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_move_assignable<_Del>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = algorithm::move(__other.__deleter);
          }
          return *this;
        }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_copy_assignable<_Del>::value,
            bool
          >::type = false
        >
        unique_ptr& operator=(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_copy_assignable<deleter_type>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = __other.__deleter;
          }
          return *this;
        }

        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::releations::is_convertible
            <
              typename unique_ptr<_U, _UDelete>::pointer,
              pointer
            >::value &&
            trait::type::categories::is_array<_U>::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_move_assignable<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr& operator=(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_move_assignable<_UDelete>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = algorithm::move(__other.__deleter);
          }
          return *this;
        }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::releations::is_convertible
            <
              typename unique_ptr<_U, _UDelete>::pointer,
              pointer
            >::value &&
            trait::type::categories::is_array<_U>::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_copy_assignable<_UDelete>::value,
            bool
          >::type = false
        >
        unique_ptr& operator=(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_copy_assignable<_UDelete>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = __other.__deleter;
          }
          return *this;
        }

      public:
        typename
        trait::type::transform::add_lvalue_reference<element_type>::type
        operator*() const
        { return *(this->__ptr);}
        pointer operator->() const noexcept
        { return this->__ptr;}

      public:
        operator bool() const noexcept
        { return this->__ptr == nullptr;}

      public:
        pointer get() const noexcept
        { return this->__ptr;}
        deleter_type& get_deleter() noexcept
        { return this->__deleter;}
        const deleter_type& get_deleter() const noexcept
        { return this->__deleter;}

      public:
        inline void clear() noexcept
        {
          if(this->__ptr)
          { (this->__deleter)(this->__ptr);}
          this->__ptr = pointer();
        }
        inline pointer release() noexcept
        {
          pointer __tptr = this->__ptr;
          this->__ptr = pointer();
          return __tptr;
        }
        inline void reset(pointer __tptr = pointer())
        {
          using algorithm::swap;
          swap(this->__ptr, __tptr);
          if(__tptr)
          { (this->__deleter)(__tptr);}
        }

      public:
        inline void swap(unique_ptr& __other) noexcept
        {
          using algorithm::swap;
          swap(this->__ptr, __other.__ptr);
        }
    };

    template
    <
      typename _T,
      typename _Deleter
    >
    class unique_ptr<_T[], _Deleter>
    {
      public:
        typedef _T element_type;
        typedef _Deleter deleter_type;
        typedef typename
          __unique_ptr_impl::__unique_ptr_pointer<_T, _Deleter>::type
          pointer;

      private:
        typedef typename
          trait::type::transform::remove_reference<_Deleter>::type
          __unref_delete_type;

      private:
        pointer __ptr;
        deleter_type __deleter;

      public:
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        constexpr unique_ptr() noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(nullptr), __deleter()
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        constexpr unique_ptr(nullptr_t) noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(nullptr), __deleter()
        { }
        template
        <
          typename _U,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (
             trait::type::releations::is_same<_U, pointer>::value ||
             trait::type::categories::is_null_pointer<_U>::pointer ||
             (
              trait::type::releations::is_same<pointer, element_type*>::value &&
              trait::type::categories::is_pointer<_U>::value &&
              trait::type::releations::is_convertible<
                typename
                trait::type::transform::remove_pointer<_U>::pointer(*)[],
                element_type(*)[]
              >::value
             )
            ) &&
            (!trait::type::categories::is_pointer<_Del>::value) &&
            trait::type::features::is_default_constructible<_Del>::value,
            bool
          >::type = true
        >
        explicit unique_ptr(_U __optr) noexcept(
          trait::type::features::is_nothrow_default_constructible<deleter_type>::value
        ): __ptr(__optr), __deleter()
        { }
        template
        <
          typename _U,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (
             trait::type::releations::is_same<_U, pointer>::value ||
             trait::type::categories::is_null_pointer<_U>::pointer ||
             (
              trait::type::releations::is_same<pointer, element_type*>::value &&
              trait::type::categories::is_pointer<_U>::value &&
              trait::type::releations::is_convertible<
                typename
                trait::type::transform::remove_pointer<_U>::pointer(*)[],
                element_type(*)[]
              >::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::features::is_copy_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(
          _U __optr,
          typename
          trait::type::miscellaneous::conditional
          <
            trait::type::categories::is_reference<deleter_type>::value,
            deleter_type,
            typename
            trait::type::transform::add_lvalue_reference<
              const deleter_type>::type
          >::type __odeleter
        ) noexcept(
          trait::type::features::is_nothrow_copy_constructible<deleter_type>::value
        ): __ptr(__optr), __deleter(__odeleter)
        { }
        template
        <
          typename _U,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            (
             trait::type::releations::is_same<_U, pointer>::value ||
             trait::type::categories::is_null_pointer<_U>::pointer ||
             (
              trait::type::releations::is_same<pointer, element_type*>::value &&
              trait::type::categories::is_pointer<_U>::value &&
              trait::type::releations::is_convertible<
                typename
                trait::type::transform::remove_pointer<_U>::pointer(*)[],
                element_type(*)[]
              >::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::features::is_copy_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(
          _U __optr,
          __unref_delete_type&& __odeleter
        ) noexcept(
          trait::type::features::is_nothrow_copy_constructible<deleter_type>::value
        ): __ptr(__optr),
           __deleter(algorithm::forward<decltype(__odeleter)>(__odeleter))
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_move_constructible<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_move_constructible<deleter_type>::value
        ): __ptr(__other.release()),
           __deleter(algorithm::move(__other.__deleter))
        { }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_copy_constructible<_Del>::value,
            bool
          >::type = false
        >
        unique_ptr(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_copy_constructible<deleter_type>::value
        ): __ptr(__other.release()),
           __deleter(__other.__deleter)
        { }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_array<_U>::value &&
            trait::type::releations::is_same<pointer, element_type*>::value &&
            trait::type::releations::is_same<
              typename unique_ptr<_U, _UDelete>::pointer,
              typename unique_ptr<_U, _UDelete>::element_type*
            >::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_move_constructible<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_move_constructible<_UDelete>::value
        ): __ptr(__other.release()),
           __deleter(algorithm::move(__other.__deleter))
        { }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_array<_U>::value &&
            trait::type::releations::is_same<pointer, element_type*>::value &&
            trait::type::releations::is_same<
              typename unique_ptr<_U, _UDelete>::pointer,
              typename unique_ptr<_U, _UDelete>::element_type*
            >::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_copy_constructible<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_copy_constructible<_UDelete>::value
        ): __ptr(__other.release()),
           __deleter(algorithm::move(__other.__deleter))
        { }

        ~unique_ptr()
        { this->reset();}

      public:
        unique_ptr& operator=(nullptr_t) noexcept
        { this->reset();}
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_move_assignable<_Del>::value,
            bool
          >::type = true
        >
        unique_ptr& operator=(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_move_assignable<_Del>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = algorithm::move(__other.__deleter);
          }
          return *this;
        }
        template
        <
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_Del>::value &&
            trait::type::features::is_copy_assignable<_Del>::value,
            bool
          >::type = false
        >
        typename
        trait::type::miscellaneous::enable_if
        <
          trait::type::features::is_copy_assignable<_Del>::value &&
          !trait::type::features::is_move_assignable<_Del>::value,
          unique_ptr&
        >::type
        operator=(unique_ptr&& __other) noexcept(
          trait::type::features::is_nothrow_copy_assignable<deleter_type>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = __other.__deleter;
          }
          return *this;
        }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_array<_U>::value &&
            trait::type::releations::is_same<pointer, element_type*>::value &&
            trait::type::releations::is_same<
              typename unique_ptr<_U, _UDelete>::pointer,
              typename unique_ptr<_U, _UDelete>::element_type*
            >::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            !trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_nothrow_move_assignable<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr& operator=(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_move_assignable<_UDelete>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = algorithm::move(__other.__deleter);
          }
          return *this;
        }
        template
        <
          typename _U, typename _UDelete,
          typename _Del = deleter_type,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_array<_U>::value &&
            trait::type::releations::is_same<pointer, element_type*>::value &&
            trait::type::releations::is_same<
              typename unique_ptr<_U, _UDelete>::pointer,
              typename unique_ptr<_U, _UDelete>::element_type*
            >::value &&
            (
             (
              trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_same<_UDelete, _Del>::value
             ) ||
             (
              !trait::type::categories::is_reference<_UDelete>::value &&
              trait::type::releations::is_convertible<_UDelete, _Del>::value
             )
            ),
            bool
          >::type = true,
          typename
          trait::type::miscellaneous::enable_if
          <
            trait::type::categories::is_reference<_UDelete>::value &&
            trait::type::features::is_copy_assignable<_UDelete>::value,
            bool
          >::type = true
        >
        unique_ptr& operator=(unique_ptr<_U, _UDelete>&& __other) noexcept(
          trait::type::features::is_nothrow_copy_assignable<_UDelete>::value
        )
        {
          if(this != &__other)
          {
            __ptr = __other.release();
            __deleter = __other.__deleter;
          }
          return *this;
        }


      public:
        typename
        trait::type::transform::add_lvalue_reference<element_type>::type
        operator*() const
        { return *(this->__ptr);}
        pointer operator->() const noexcept
        { return this->__ptr;}
        element_type& operator[](size_t __len) const
        { return (this->__ptr)[__len];}

      public:
        operator bool() const noexcept
        { return this->__ptr == nullptr;}

      public:
        pointer get() const noexcept
        { return this->__ptr;}
        deleter_type& get_deleter() noexcept
        { return this->__deleter;}
        const deleter_type& get_deleter() const noexcept
        { return this->__deleter;}

      public:
        inline void clear() noexcept
        {
          if(this->__ptr)
          { (this->__deleter)(this->__ptr);}
          this->__ptr = pointer();
        }
        inline pointer release() noexcept
        {
          pointer __tptr = this->__ptr;
          this->__ptr = pointer();
          return __tptr;
        }
        inline void reset(pointer __tptr = pointer())
        {
          algorithm::swap(this->__ptr, __tptr);
          if(__tptr)
          { (this->__deleter)(__tptr);}
        }

      public:
        inline void swap(unique_ptr& __other) noexcept
        {
          algorithm::swap(this->__ptr, __other.__ptr);
        }

    };

    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator==(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    { return __x.get() == __y.get();}
    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator!=(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    { return __x.get() != __y.get();}
    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator<(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    {
      typedef typename
        trait::type::miscellaneous::common_type<
          typename unique_ptr<_T1, _D1>::pointer,
          typename unique_ptr<_T2, _D2>::pointer
        >::type
        __pointer_type;
      return algorithm::less<__pointer_type>()(
        __x.get(), __y.get());
    }
    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator<=(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    { return !(__y < __x);}
    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator>(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    { return __y < __x;}
    template<typename _T1, typename _D1, typename _T2, typename _D2>
    inline bool operator>=(
      const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
    { return !(__x < __y);}
    template<typename _T1, typename _D1>
    inline bool operator==(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    { return __x;}
    template<typename _T1, typename _D1>
    inline bool operator!=(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    { return !(__x);}
    template<typename _T1, typename _D1>
    inline bool operator<(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    {
      return algorithm::less<
        typename unique_ptr<_T1, _D1>::pointer>()(__x, nullptr);
    }
    template<typename _T1, typename _D1>
    inline bool operator<=(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    { return !(nullptr < __x);}
    template<typename _T1, typename _D1>
    inline bool operator>(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    { return __x < nullptr;}
    template<typename _T1, typename _D1>
    inline bool operator>=(
      const unique_ptr<_T1, _D1>& __x, nullptr_t)
    { return !(nullptr < __x);}

    template<typename _T2, typename _D2>
    inline bool operator==(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    { return __y;}
    template<typename _T2, typename _D2>
    inline bool operator!=(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    { return !(__y);}
    template<typename _T2, typename _D2>
    inline bool operator<(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    {
      return algorithm::less<
        typename unique_ptr<_T2, _D2>::pointer>()(nullptr, __y);
    }
    template<typename _T2, typename _D2>
    inline bool operator<=(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    { return !(__y < nullptr);}
    template<typename _T2, typename _D2>
    inline bool operator>(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    { return __y < nullptr;}
    template<typename _T2, typename _D2>
    inline bool operator>=(
      nullptr_t, const unique_ptr<_T2, _D2>& __y)
    { return !(nullptr < __y);}

  }

  namespace algorithm
  {
    template<typename _T, typename _D>
    inline void swap(
      memory::unique_ptr<_T, _D> __x,
      memory::unique_ptr<_T, _D> __y
    ) noexcept
    { __x.swap(__y);}
  }
}

namespace utility
{
  namespace memory
  {
    template<typename _T>
    using unique_array = memory::unique_ptr<_T[], memory::default_delete<_T[]>>;

  }

}

#endif // ! __UTILITY_MEMORY_UNIQUE_PTR__


