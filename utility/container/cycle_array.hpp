
#ifndef __UTILITY_CONTAINER_CYCLE_ARRAY__
#define __UTILITY_CONTAINER_CYCLE_ARRAY__

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/reverse_iterator.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _T,
      utility::size_t _Size
    >
    class cycle_array
    {
      public:
        typedef _T                      value_type;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;

      public:
        typedef utility::size_t       size_type;
        typedef utility::ptrdiff_t    difference_type;

      public:
        value_type __element[_Size > 0 ? _Size : 1];

      public:
        __UTILITY_CPP17_CONSTEXPR__
        reference at(size_type __pos)
        { return this->__element[__pos % _Size];}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference at(size_type __pos) const
        { return this->__element[__pos % _Size];}

        __UTILITY_CPP17_CONSTEXPR__
        reference operator[](size_type __pos)
        { return this->__element[__pos % _Size];}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference operator[](size_type __pos) const
        { return this->__element[__pos % _Size];}

      public:
        __UTILITY_CPP17_CONSTEXPR__
        reference front()
        { return *(this->__element);}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference front() const
        { return *(this->__element);}
        __UTILITY_CPP17_CONSTEXPR__
        reference back()
        { return this->__element[_Size];}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference back() const
        { return this->__element[_Size];}

      public:
        __UTILITY_CPP17_CONSTEXPR__
        value_type* data() noexcept
        { return this->__element;}
        __UTILITY_CPP17_CONSTEXPR__
        const value_type* data() const noexcept
        { return this->__element;}

      public:
        constexpr bool empty() const noexcept
        { return _Size == 0U;}
        constexpr size_type size() const noexcept
        { return _Size;}

    };
  }
}

#endif // ! __UTILITY_CONTAINER_CYCLE_ARRAY__
