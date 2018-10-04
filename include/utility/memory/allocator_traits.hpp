
#ifndef __UTILITY_MEMORY_ALLOCATOR_TRAITS__
#define __UTILITY_MEMORY_ALLOCATOR_TRAITS__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/forward.hpp>

#include<utility/memory/basic_allocator.hpp>

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__twochar__.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_trivially_destructible.hpp>
#include<utility/trait/type/property/is_empty.hpp>
#include<utility/trait/type/miscellaneous/change_sign.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>
#include<utility/sstd/new.hpp>

namespace utility
{
  namespace memory
  {
    namespace __alloc_traits_impl
    {
      using __two = trait::__opt__::__twochar__;

      template<typename _T>
      struct __alloc_pointer_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::pointer* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_const_pointer_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::const_pointer* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_void_pointer_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::void_pointer* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_const_void_pointer_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::const_void_pointer* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_difference_type_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::difference_type* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_size_type_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::size_type* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_propagate_on_container_copy_assignment_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::propagate_on_container_copy_assignment* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_propagate_on_container_move_assignment_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::propagate_on_container_move_assignment	* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_propagate_on_container_swap_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::propagate_on_container_swap* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };
      template<typename _T>
      struct __alloc_is_always_equal_test
      {
        private:
          template<typename __T>
          static char __test(typename __T::is_always_equal* = 0);
          template<typename __T>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T>(0)));
      };

      template<typename _T, typename _U>
      struct __alloc_rebind_test
      {
        private:
          template<typename __T, typename __U>
          static char __test(typename __T::template rebind<__U>* = 0);
          template<typename __T, typename __U>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T, _U>(0)));
      };

      template<typename _T, typename _U,
        bool = __alloc_rebind_test<_T, _U>::value>
      struct __alloc_rebind_other_test;

      template<typename _T, typename _U>
      struct __alloc_rebind_other_test<_T, _U, true>
      {
        private:
          template<typename __T, typename __U>
          static char __test(typename __T::template rebind<__U>::other* = 0);
          template<typename __T, typename __U>
          static __two __test(...);

        public:
          constexpr static bool value =
            sizeof(char) == sizeof(decltype(__test<_T, _U>(0)));
      };
      template<typename _T, typename _U>
      struct __alloc_rebind_other_test<_T, _U, false>
      {
        public:
          constexpr static bool value = false;
      };

      template<typename _T, typename _Allocator,
        bool = __alloc_pointer_test<_Allocator>::value>
      struct __alloc_pointer;

      template<typename _T, typename _Allocator>
      struct __alloc_pointer<_T, _Allocator, true>
      { typedef typename _Allocator::pointer type;};
      template<typename _T, typename _Allocator>
      struct __alloc_pointer<_T, _Allocator, false>
      { typedef _T* type;};

      template<typename _T, typename _Pointer, typename _Allocator,
        bool = __alloc_const_pointer_test<_Allocator>::value>
      struct __alloc_const_pointer;

      template<typename _T, typename _Pointer, typename _Allocator>
      struct __alloc_const_pointer<_T, _Pointer, _Allocator, true>
      { typedef typename _Allocator::const_pointer type;};
      template<typename _T, typename _Pointer, typename _Allocator>
      struct __alloc_const_pointer<_T, _Pointer, _Allocator, false>
      { typedef typename trait::miscellaneous::pointer_traits<_Pointer
          >::template rebind<const _T> type;};


      template<typename _Allocator, typename _Pointer,
        bool = __alloc_void_pointer_test<_Allocator>::value>
      struct __alloc_void_pointer;

      template<typename _Allocator, typename _Pointer>
      struct __alloc_void_pointer<_Allocator, _Pointer, true>
      { typedef typename _Allocator::void_pointer type;};
      template<typename _Allocator, typename _Pointer>
      struct __alloc_void_pointer<_Allocator, _Pointer, false>
      { typedef typename trait::miscellaneous::pointer_traits<_Pointer
        >::template rebind<void> type;};

      template<typename _Allocator,  typename _Pointer,
        bool = __alloc_const_void_pointer_test<_Allocator>::value>
      struct __alloc_const_void_pointer;

      template<typename _Allocator, typename _Pointer>
      struct __alloc_const_void_pointer<_Allocator, _Pointer, true>
      { typedef typename _Allocator::const_void_pointer type;};
      template<typename _Allocator, typename _Pointer>
      struct __alloc_const_void_pointer<_Allocator, _Pointer, false>
      { typedef typename trait::miscellaneous::pointer_traits<_Pointer
        >::template rebind<const void> type;};

      template<typename _Pointer, typename _Allocator,
        bool = __alloc_difference_type_test<_Allocator>::value>
      struct __alloc_difference_type;

      template<typename _Pointer, typename _Allocator>
      struct __alloc_difference_type<_Pointer, _Allocator, true>
      { typedef typename _Allocator::difference_type type;};
      template<typename _Pointer, typename _Allocator>
      struct __alloc_difference_type<_Pointer, _Allocator, false>
      { typedef typename trait::miscellaneous::pointer_traits<_Pointer
        >::difference_type type;};

      template<typename _Difference, typename _Allocator,
        bool = __alloc_size_type_test<_Allocator>::value>
      struct __alloc_size_type;

      template<typename _Difference, typename _Allocator>
      struct __alloc_size_type<_Difference, _Allocator, true>
      { typedef typename _Allocator::size_type type;};
      template<typename _Difference, typename _Allocator>
      struct __alloc_size_type<_Difference, _Allocator, false>
      { typedef typename trait::type::miscellaneous::make_unsigned<_Difference
        >::type type;};

      template<typename _Allocator,
        bool = __alloc_propagate_on_container_copy_assignment_test<_Allocator
          >::value>
      struct __alloc_propagate_on_container_copy_assignment;

      template<typename _Allocator>
      struct __alloc_propagate_on_container_copy_assignment<_Allocator, true>
      { typedef typename _Allocator::propagate_on_container_copy_assignment type;};
      template<typename _Allocator>
      struct __alloc_propagate_on_container_copy_assignment<_Allocator, false>
      { typedef trait::false_type type;};

      template<typename _Allocator,
        bool = __alloc_propagate_on_container_move_assignment_test<_Allocator
          >::value>
      struct __alloc_propagate_on_container_move_assignment;

      template<typename _Allocator>
      struct __alloc_propagate_on_container_move_assignment<_Allocator, true>
      { typedef typename _Allocator::propagate_on_container_move_assignment type;};
      template<typename _Allocator>
      struct __alloc_propagate_on_container_move_assignment<_Allocator, false>
      { typedef trait::false_type type;};

      template<typename _Allocator,
        bool = __alloc_propagate_on_container_swap_test<_Allocator
          >::value>
      struct __alloc_propagate_on_container_swap;

      template<typename _Allocator>
      struct __alloc_propagate_on_container_swap<_Allocator, true>
      { typedef typename _Allocator::propagate_on_container_swap type;};
      template<typename _Allocator>
      struct __alloc_propagate_on_container_swap<_Allocator, false>
      { typedef trait::false_type type;};

      template<typename _Allocator,
        bool = __alloc_is_always_equal_test<_Allocator>::value>
      struct __alloc_is_always_equal;

      template<typename _Allocator>
      struct __alloc_is_always_equal<_Allocator, true>
      { typedef typename _Allocator::is_always_equal type;};
      template<typename _Allocator>
      struct __alloc_is_always_equal<_Allocator, false>
      {
        typedef typename
        trait::type::property::is_empty<_Allocator>::type type;
      };

      template<typename _Allocator, typename _U,
        bool = __alloc_rebind_other_test<_Allocator, _U>::value>
      struct __alloc_rebind;

      template<typename _Allocator, typename _U>
      struct __alloc_rebind<_Allocator, _U, true>
      { typedef typename _Allocator::template rebind<_U>::other type;};
      template<template<typename, typename...>class _Allocator,
        typename _T, typename... _Args, typename _U>
      struct __alloc_rebind<_Allocator<_T, _Args...>, _U, true>
      {
        typedef typename
          _Allocator<_T, _Args...>::template rebind<_U>::other type;
      };
      template<typename _Allocator, typename _U>
      struct __alloc_rebind<_Allocator, _U, false>
      { };
      template<template<typename, typename...>class _Allocator,
        typename _T, typename... _Args, typename _U>
      struct __alloc_rebind<_Allocator<_T, _Args...>, _U, false>
      { typedef _Allocator<_T, _Args...> type;};
    }

    namespace __alloc_traits_impl
    {
      using trait::type::special::declval;
      template<typename _Allocator, typename _Size, typename _Const_Void_Ptr>
      struct __alloc_has_hint_test
      {
        private:
          template<typename __T, typename __Size, typename __Ptr>
          static auto __test(__T&& __alloc, __Size&& __n, __Ptr&& __ptr)
            -> decltype(__alloc.allocate(__n, __ptr),
            trait::true_type());
          template<typename __T, typename __Size, typename __Ptr>
          static auto __test(const __T& __alloc, __Size&& __n, __Ptr&& __ptr)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_Allocator, _Size, _Const_Void_Ptr>(
                declval<_Allocator>(), declval<_Size>(),
                declval<_Const_Void_Ptr>()))
            >::value;
      };

      template<typename _Allocator, typename _Size, typename _Const_Void_Ptr>
      struct __alloc_has_hint : public
        trait::integral_constant<bool,
          __alloc_has_hint_test<_Allocator, _Size, _Const_Void_Ptr>::value>
      { };

      template<typename _Allocator, typename _Size, typename _Const_Void_Ptr, typename _Return>
      _Return __allocate(_Allocator& __alloc, _Size __size,_Const_Void_Ptr __hint, trait::true_type)
      { return __alloc.allocate(__size, __hint);}
      template<typename _Allocator, typename _Size, typename _Const_Void_Ptr, typename _Return>
      _Return __allocate(_Allocator& __alloc, _Size __size,_Const_Void_Ptr __hint, trait::false_type)
      { return __alloc.allocate(__size);}


      template<typename _Allocator, typename _Ptr, typename... _Args>
      struct __alloc_has_construct_test
      {
        private:
          template<typename __T, typename __P, typename... __Args>
          static auto __test(__T&& __alloc, __P* __ptr, __Args&&... __args)
            ->decltype(__alloc.construct(__ptr, __args...),
              trait::true_type());
          template<typename __T, typename __P, typename... __Args>
          static auto __test(const __T& __alloc, __P* __ptr, __Args&&... __args)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_Allocator, _Ptr, _Args...>(
                declval<_Allocator>(), declval<_Ptr*>(),
                declval<_Args>()...))
            >::value;
      };

      template<typename _Allocator, typename _Ptr, typename... _Args>
      struct __alloc_has_construct : public
        trait::integral_constant<bool,
          __alloc_has_construct_test<_Allocator, _Ptr, _Args...>::value>
      { };

      template<typename _Allocator, typename _P_T, typename... _Args>
      void __construct(trait::true_type, _Allocator& __alloc,
         _P_T* __ptr, _Args&&... __args)
      { __alloc.construct(__ptr, algorithm::forward<_Args>(__args)...);}
      template<typename _Allocator, typename _P_T, typename... _Args>
      void __construct(trait::false_type, _Allocator& __alloc,
        _P_T* __ptr, _Args&&... __args)
      { ::new (static_cast<void*>(__ptr))
        _P_T(algorithm::forward<_Args>(__args)...);}

      template<typename _Allocator, typename _Ptr>
      struct __alloc_has_destroy_test
      {
        private:
          template<typename __T, typename __P>
          static auto __test(__T&& __alloc, __P* __ptr)
            ->decltype(__alloc.destroy(__ptr),
              trait::true_type());
          template<typename __T, typename __P>
          static auto __test(const __T& __alloc, __P* __ptr)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_Allocator, _Ptr>(
                declval<_Allocator>(), declval<_Ptr*>()))
            >::value;
      };

      template<typename _Allocator, typename _Ptr>
      struct __alloc_has_destroy : public
        trait::integral_constant<bool,
          __alloc_has_destroy_test<_Allocator, _Ptr>::value>
      { };

      template<typename _Allocator, typename _Ptr,
        bool = __alloc_has_destroy_test<_Allocator, _Ptr>::value,
        bool =
          trait::type::features::is_trivially_destructible<_Ptr>::value
      >
      struct __alloc_destroy
      {
        static inline void __aux(_Allocator& __alloc, _Ptr* __ptr)
        { __ptr->~_T();}
      };

      template<typename _Allocator, typename _Ptr>
      struct __alloc_destroy<_Allocator, _Ptr, true, true>
      {
        static inline void __aux(_Allocator& __alloc, _Ptr* __ptr)
        { }
      };
      template<typename _Allocator, typename _Ptr>
      struct __alloc_destroy<_Allocator, _Ptr, false, true>
      {
        static inline void __aux(_Allocator& __alloc, _Ptr* __ptr)
        { }
      };
      template<typename _Allocator, typename _Ptr>
      struct __alloc_destroy<_Allocator, _Ptr, true, false>
      {
        static inline void __aux(_Allocator& __alloc, _Ptr* __ptr)
        { __alloc.destroy(__ptr);}
      };

      template<typename _Allocator>
      struct __alloc_has_max_size_test
      {
        private:
          template<typename __T>
          static auto __test(__T&& __alloc)
            ->decltype(__alloc.max_size(),
              trait::true_type());
          template<typename __T>
          static auto __test(const __T& __alloc)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_Allocator>(declval<_Allocator>()))
            >::value;
      };

      template<typename _Allocator, typename _Size, typename _T,
        bool = __alloc_has_max_size_test<_Allocator>::value>
      struct __max_size
      {
        static _Size __aux(const _Allocator& __alloc) noexcept
        { return _Size(65535) / sizeof(_T) == 0 ? 1 : _Size(65535) / sizeof(_T);}
      };
      template<typename _Allocator, typename _Size, typename _T>
      struct __max_size<_Allocator, _Size, _T, true>
      {
        static _Size __aux(const _Allocator& __alloc) noexcept
        { return __alloc.max_size();}
      };

      template<typename _Allocator>
      struct __alloc_has_select_on_container_copy_construction_test
      {
        private:
          template<typename __T>
          static auto __test(__T&& __alloc)
            ->decltype(__alloc.select_on_container_copy_construction(),
              trait::true_type());
          template<typename __T>
          static auto __test(const __T& __alloc)
            -> trait::false_type;

        public:
          constexpr static bool value =
            trait::type::releations::is_same<
              trait::true_type,
              decltype(__test<_Allocator>(declval<_Allocator>()))
            >::value;
      };

      template<typename _Allocator,
        bool = __alloc_has_select_on_container_copy_construction_test<_Allocator>::value>
      struct __select_on_container_copy_construction
      {
        static inline _Allocator __aux(const _Allocator& __alloc)
        { return __alloc;}
      };

      template<typename _Allocator>
      struct __select_on_container_copy_construction<_Allocator, true>
      {
        static inline _Allocator __aux(const _Allocator& __alloc)
        { return __alloc.select_on_container_copy_construction();}
      };
    }

    template<typename _Allocator>
    struct allocator_traits
    {
      public:
        typedef _Allocator allocator_type;
        typedef typename allocator_type::value_type value_type;
        typedef typename
          __alloc_traits_impl::__alloc_pointer<value_type, _Allocator
            >::type pointer;
        typedef typename
          __alloc_traits_impl::__alloc_const_pointer<value_type, pointer, _Allocator
            >::type const_pointer;
        typedef typename
          __alloc_traits_impl::__alloc_void_pointer<_Allocator, pointer
            >::type void_pointer;
        typedef typename
          __alloc_traits_impl::__alloc_const_void_pointer<_Allocator, pointer
            >::type const_void_pointer;
        typedef typename
          __alloc_traits_impl::__alloc_difference_type<pointer, _Allocator
            >::type difference_type;
        typedef typename
          __alloc_traits_impl::__alloc_size_type<difference_type, _Allocator
            >::type size_type;

      public:
        typedef typename
          __alloc_traits_impl::__alloc_propagate_on_container_copy_assignment<
            _Allocator>::type propagate_on_container_copy_assignment;
        typedef typename
          __alloc_traits_impl::__alloc_propagate_on_container_move_assignment<
          _Allocator>::type propagate_on_container_move_assignment;
        typedef typename
          __alloc_traits_impl::__alloc_propagate_on_container_swap<
            _Allocator>::type propagate_on_container_swap;

      public:
        typedef typename
          __alloc_traits_impl::__alloc_is_always_equal<_Allocator
            >::type is_always_equal;

      public:
        template<typename _T>
        using rebind_alloc =
         typename
          __alloc_traits_impl::__alloc_rebind<_Allocator, _T>::type;
        template<typename _T>
        using rebind_traits = allocator_traits<rebind_alloc<_T>>;

      public:
        static inline pointer allocate(allocator_type& __alloc)
        { return __alloc.allocate(1U);}
        static inline pointer allocate(allocator_type& __alloc, size_type __size)
        { return __alloc.allocate(__size);}
        static pointer allocate(allocator_type& __alloc, size_type __size,const_void_pointer __hint)
        {
          return __alloc_traits_impl::__allocate<
            allocator_type, size_type, const_void_pointer, pointer>
            (__alloc, __size, __hint,
              __alloc_traits_impl::__alloc_has_hint<
              allocator_type, size_type, const_void_pointer>());
        }

        static inline void deallocate(allocator_type& __alloc, pointer __ptr, size_type __size)
        { __alloc.deallocate(__ptr, __size);}

      public:
        template<typename _T, typename... _Args>
        static inline void construct(allocator_type& __alloc, _T* __ptr, _Args&&... __args)
        {
          static_assert(
            trait::type::features::is_constructible<_T, _Args...>::value,
            "The args is not vaild.");
          __alloc_traits_impl::__construct(
            __alloc_traits_impl::__alloc_has_construct<allocator_type, _T, _Args...>(),
            __alloc, __ptr,
            algorithm::forward<_Args>(__args)...);
        }

        template<typename _T>
        static inline void destroy(allocator_type& __alloc, _T* __ptr)
        {
          __alloc_traits_impl::__alloc_destroy<allocator_type, _T
            >::__aux(__alloc, __ptr);
        }

      public:
        static inline size_type max_size(const allocator_type& __alloc) noexcept
        {
          return __alloc_traits_impl::__max_size<allocator_type,
            size_type, value_type>::__aux(__alloc);
        }

      public:
        static inline allocator_type
          select_on_container_copy_construction(const allocator_type& __alloc)
        {
          return
            __alloc_traits_impl::__select_on_container_copy_construction<
              allocator_type>::__aux(__alloc);
        }
    };
  }
}

#endif // ! __UTILITY_MEMORY_ALLOCATOR_TRAITS__
