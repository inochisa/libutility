
#ifndef __UTILITY_CONTAINER_ARRAY__
#define __UTILITY_CONTAINER_ARRAY__

/**
 * \file array.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#ifdef ___UTILITY__CHECK__USE__STD___

#include<array>

namespace utility
{
  namespace container
  {
    using std::array;
  }
}

#else // ___UTILITY__CHECK__USE__STD___

#include<utility/iterator/reverse_iterator.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _T,
      size_t _Size
    >
    class array
    {
      public:
        typedef _T                      value_type;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;

      public:
        typedef size_t       size_type;
        typedef ptrdiff_t    difference_type;

      public:
        typedef value_type*             iterator;
        typedef const value_type*       const_iterator;
        typedef
          iterator::reverse_iterator<iterator>
          reverse_iterator;
        typedef
          iterator::reverse_iterator<const_iterator>
          const_reverse_iterator;

      public:
        value_type __element[_Size > 0 ? _Size : 1];

      public:

#ifdef __UTILITY_USE_EXCEPTION

        __UTILITY_CPP17_CONSTEXPR__
        reference at(size_type __pos)
        {
          if(__pos >= _Size)
          { throw 1;}
          return this->__element[__pos];
        }
        __UTILITY_CPP14_CONSTEXPR__
        const_reference at(size_type __pos) const
        {
          if(__pos >= _Size)
          { throw 1;}
          return this->__element[__pos];
        }

#endif // ! __UTILITY_USE_EXCEPTION

        __UTILITY_CPP17_CONSTEXPR__
        reference operator[](size_type __pos)
        { return this->__element[__pos];}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference operator[](size_type __pos) const
        { return this->__element[__pos];}

      public:
        __UTILITY_CPP17_CONSTEXPR__
        iterator begin() noexcept
        { return this->__element;}
        __UTILITY_CPP17_CONSTEXPR__
        const_iterator begin() const noexcept
        { return this->__element;}
        __UTILITY_CPP17_CONSTEXPR__
        const_iterator cbegin() const noexcept
        { return this->__element;}
        __UTILITY_CPP17_CONSTEXPR__
        iterator end() noexcept
        { return this->__element+_Size;}
        __UTILITY_CPP17_CONSTEXPR__
        const_iterator end() const noexcept
        { return this->__element+_Size;}
        __UTILITY_CPP17_CONSTEXPR__
        const_iterator cend() const noexcept
        { return this->__element+_Size;}

      public:
        __UTILITY_CPP17_CONSTEXPR__
        reverse_iterator rbegin() noexcept
        { return reverse_iterator(this->end());}
        __UTILITY_CPP17_CONSTEXPR__
        const_reverse_iterator rbegin() noexcept
        { return const_reverse_iterator(this->end());}
        __UTILITY_CPP17_CONSTEXPR__
        const_reverse_iterator rbegin() noexcept
        { return const_reverse_iterator(this->end());}
        __UTILITY_CPP17_CONSTEXPR__
        reverse_iterator rbegin() noexcept
        { return reverse_iterator(this->begin());}
        __UTILITY_CPP17_CONSTEXPR__
        const_reverse_iterator rbegin() noexcept
        { return const_reverse_iterator(this->begin());}
        __UTILITY_CPP17_CONSTEXPR__
        const_reverse_iterator rbegin() noexcept
        { return const_reverse_iterator(this->begin());}

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

#endif // ! ___UTILITY__CHECK__USE__STD___

#endif // ! __UTILITY_CONTAINER_ARRAY__
