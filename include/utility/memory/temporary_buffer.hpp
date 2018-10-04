
#ifndef __UTILITY_MEMORY_TEMPORARY_BUFFER__
#define __UTILITY_MEMORY_TEMPORARY_BUFFER__

#include<utility/config/utility_config.hpp>
#include<utility/container/pair.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/miscellaneous/change_sign.hpp>
#include<utility/memory/destroy.hpp>
#include<utility/sstd/new.hpp>

namespace utility
{
  namespace memory
  {
    namespace detail
    {
      template<typename _T>
      container::pair<
        typename trait::type::transform::remove_cv<_T>::type*,
        ptrdiff_t
      >
      get_temporary_buffer(ptrdiff_t __need)
      {
        using ptrdiff_t;
        typedef typename
          trait::type::transform::remove_cv<_T>::type
          __alloc_type;
        typedef typename
          trait::type::miscellaneous::make_unsigned<ptrdiff_t>::type
          __unsigned_ptrdiff_t;
        const ptrdiff_t __alloc_max =
          static_cast<ptrdiff_t>(
            ((~__unsigned_ptrdiff_t(0L) ^ __unsigned_ptrdiff_t(1L)) >> 1) / sizeof(_T)
          );

        if(__need > __alloc_max)
        { __need = __alloc_max;}
        for(; __need > 0;)
        {
          __alloc_type* __alloc_pointer = static_cast<__alloc_type*>(
            ::operator new(__need * sizeof(_T), sstd::nothrow)
          );
          if(__alloc_pointer != nullptr)
          {
            return container::pair<typename
              trait::type::transform::remove_cv<_T>::type*,
              ptrdiff_t
            >(__alloc_pointer, __need);
          }
          __need /= 2;
        }
        return container::pair<typename
          trait::type::transform::remove_cv<_T>::type*,
          ptrdiff_t
        >(nullptr, 0);
      }
      template<typename _T>
      void return_temporary_buffer(_T* __ptr)
      { ::operator delete(__ptr);}
    }
    template<typename _T>
    class temporary_buffer
    {
      public:
        typedef typename
          trait::type::transform::remove_cv<_T>::type
          value_type;
        typedef value_type*     pointer;
        typedef value_type&     reference;
        typedef ptrdiff_t       difference_type;
        typedef ptrdiff_t       size_type;

      public:
        typedef pointer accessor;

      private:
        size_type   __req_size;
        size_type   __size;
        pointer     __item;

      public:
        temporary_buffer():__req_size{0}, __size{0}, __item{nullptr}
        { }
        temporary_buffer(size_type __s):__req_size{__s}
        {
          container::pair<pointer, size_type> __res =
            detail::get_temporary_buffer<value_type>(__s);
          this->__size = __res.second;
          this->__item = __res.first;
        }
        temporary_buffer(temporary_buffer&& __other) noexcept:
          __req_size{__other.__req_size},
          __size{__other.__size},
          __item{__other.__item}
        { __other.__item = nullptr;}

        ~temporary_buffer()
        {
          if(this->__item != nullptr)
          {
            memory::destroy(this->__item, this->__item + this->__size);
            detail::return_temporary_buffer(this->__item);
          }
        }

      public:
        temporary_buffer(const temporary_buffer&) = delete;
        temporary_buffer& operator=(const temporary_buffer&) = delete;
        temporary_buffer& operator=(temporary_buffer&&) = delete;

      public:
        // note: only allow none-const.
        reference operator[](size_type __pos)
        { return this->__item[__pos];}

      public:
        size_type size() const noexcept
        { return this->__size;}

        size_type request_size() const noexcept
        { return this->__req_size;}

      public:
        accessor begin() noexcept
        { return this->__item;}
        accessor end() noexcept
        { return this->__item + this->__size;}

      public:
        bool is_vaild() const noexcept
        { return this->__item != nullptr;}
    };
  }
}

#endif // ! __UTILITY_MEMORY_TEMPORARY_BUFFER__
