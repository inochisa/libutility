
#ifndef __UTILITY_BASIC_ALLOCATOR__
#define __UTILITY_BASIC_ALLOCATOR__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/algorithm/max.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/sstd/new.hpp>

namespace utility
{
  namespace memory
  {
    template<typename _T>
    inline _T* default_allocate(utility::size_t __size)
    { return  static_cast<_T*>(::operator new(__size* sizeof(_T)));}
    template<typename _T>
    inline void default_deallocate(_T* __buffer)
    { ::operator delete(__buffer);}

    template<typename _T>
    class basic_allocator
    {
      public:
        typedef _T value_type;
        typedef _T* pointer;
        typedef const _T* const_pointer;
        typedef _T& reference;
        typedef const _T& const_reference;
        typedef _T&& __rreference;
        typedef utility::size_t size_type;
        typedef utility::ptrdiff_t difference_type;

      public:
        template<typename _U>
        struct rebind
        { typedef basic_allocator<_U> other;};

      public:
        pointer allocate() const
        { return utility::memory::default_allocate<_T>(1UL);}
        pointer allocate(size_type __size) const
        {
          // if(__size > this->max_size())
          // { return nullptr;}
          return utility::memory::default_allocate<_T>(__size);
        }
        pointer allocate(size_type __size, const void*) const
        {
          // if(__size > this->max_size())
          // { return nullptr;}
          return utility::memory::default_allocate<_T>(__size);
        }
        void deallocate(pointer __ptr) const
        { utility::memory::default_deallocate(__ptr);}
        void deallocate(pointer __ptr, utility::size_t __len) const
        { utility::memory::default_deallocate(__ptr);}

      public:
        pointer address(reference __ref) const
        { return utility::memory::addressof(__ref);}
        const_pointer address(const_reference __ref) const
        { return utility::memory::addressof(__ref);}

      public:
        size_type max_size() const
        { return size_type(~0)/sizeof(_T) ;}

      public:
        template<typename... _Args>
        void construct(pointer __ptr, _Args&&... __args)
        {
          ::new(static_cast<void*>(__ptr))
          value_type(utility::algorithm::forward<_Args>(__args)...);
        }
        void destroy(pointer __ptr)
        { __ptr->~_T();}

        /*!
        * \brief Construct the pointer safely.
        *
        * this construct function will check whether the \a __args
        * is vaild. If the \a __args is invaild, it will result in
        * Compiling Error.
        *
        * \param  __ptr a poiner needed constructing
        * \param __args construct function args
        * \see basic_allocator::construct
        */
        template<typename... _Args>
        void safe_construct(pointer __ptr, _Args&&... __args)
        {
          static_assert(
            utility::trait::type::features::is_constructible<_T, _Args...>::value,
            "Cannot construct the pointer from these args");
          this->construct(__ptr, utility::algorithm::forward<_Args>(__args)...);
          return;
        }
    };
    /*!
    * \brief the specific of the basic allocator
    */
    template<>
    class basic_allocator<void>
    {
      public:
        typedef void*         pointer;
        typedef const void*   const_pointer;
        typedef void          value_type;

      public:
        template<typename _U>
        struct rebind
        { typedef basic_allocator<_U> other;};
    };
    template<>
    class basic_allocator<const void>
    {
      public:
        typedef const void*   pointer;
        typedef const void*   const_pointer;
        typedef const void    value_type;

      public:
        template<typename _U>
        struct rebind
        { typedef basic_allocator<_U> other;};
    };

    class basic_global_allocator
    {
      public:
        typedef utility::size_t size_type;
        typedef utility::ptrdiff_t difference_type;

      public:
        struct rebind
        { typedef basic_global_allocator other;};

      public:
        template<typename _T>
        _T* allocate(size_type __size) const
        { return utility::memory::default_allocate<_T>(__size);}
        template<typename _T>
        void deallocate(_T* __ptr) const
        { utility::memory::default_deallocate(__ptr);}

      public:
        template<typename _T>
        _T* address(_T& __ref) const
        { return utility::memory::addressof(__ref);}
        template<typename _T>
        const _T* address(const _T& __ref) const
        { return utility::memory::addressof(__ref);}

      public:
        template<typename _T, typename... _Args>
        void construct(_T* __ptr, _Args&&... __args)
        {
          ::new(static_cast<void*>(__ptr))
          _T(utility::algorithm::forward<_Args>(__args)...);
        }
        template<typename _T>
        void destroy(_T* __ptr)
        { __ptr->~_T();}

        /*!
        * \brief Construct the pointer safely.
        *
        * this construct function will check whether the \a __args
        * is vaild. If the \a __args is invaild, it will result in
        * Compiling Error.
        *
        * \param  __ptr a poiner needed constructing
        * \param __args construct function args
        * \see basic_allocator::construct
        */
        template<typename _T, typename... _Args>
        void safe_construct(_T* __ptr, _Args&&... __args)
        {
          static_assert(
            utility::trait::type::features::is_constructible<_T, _Args...>::value,
            "Cannot construct the pointer from these args");
          this->construct(__ptr, utility::algorithm::forward<_Args>(__args)...);
          return;
        }

    };

    template<typename _T1, typename _T2>
    bool operator==(
      const basic_allocator<_T1>,
      const basic_allocator<_T2>) noexcept
    { return true;}
    template<typename _T1, typename _T2>
    bool operator!=(
      const basic_allocator<_T1>,
      const basic_allocator<_T2>) noexcept
    { return false;}
  }
}

#endif // ! __UTILITY_BASIC_ALLOCATOR__
