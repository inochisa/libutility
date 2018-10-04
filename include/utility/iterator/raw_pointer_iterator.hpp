
#ifndef __UTILITY_ITERATOR_RAW_POINTER_ITERATOR__
#define __UTILITY_ITERATOR_RAW_POINTER_ITERATOR__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>

namespace utility
{
  namespace iterator
  {
    template<typename _T>
    class raw_pointer_iterator
    {
      public:
        typedef contiguous_iterator_tag     iterator_category;
        typedef _T                          value_type;
        typedef value_type&                 reference;
        typedef typename
          trait::miscellaneous::pointer_traits<_T*>::pointer pointer;
        typedef typename
          trait::miscellaneous::pointer_traits<_T*>::difference_type difference_type;

      public:
        typedef raw_pointer_iterator<value_type> self;

      public:
        pointer __ptr;

      public:
        inline raw_pointer_iterator() noexcept:
          __ptr(nullptr)
        { }
        inline explicit raw_pointer_iterator(pointer _tptr) noexcept:
          __ptr(_tptr)
        { }

      public:
        inline raw_pointer_iterator& operator=(
          const raw_pointer_iterator& _other
        ) noexcept = default;

      public:
        reference operator*() const noexcept
        { return *(this->__ptr);}
        pointer operator->() const noexcept
        { return (this->__ptr);}

      public:
        self& operator++() noexcept
        {
          ++(this->__ptr);
          return *this;
        }
        self operator++(int) noexcept
        {
          self __it = *this;
          ++(this->__ptr);
          return __it;
        }
        self& operator--() noexcept
        {
          --(this->__ptr);
          return *this;
        }
        self operator--(int) noexcept
        {
          self __it = *this;
          --(this->__ptr);
          return __it;
        }

      public:
        self& operator+=(difference_type _len) noexcept
        {
          this->__ptr += _len;
          return *this;
        }
        self& operator-=(difference_type _len) noexcept
        {
          this->__ptr -= _len;
          return *this;
        }
        self operator+(difference_type _len) const noexcept
        { return self(this->__ptr + _len);}
        self operator-(difference_type _len) const noexcept
        { return self(this->__ptr - _len);}

      public:
        friend bool operator==(const self& _x, const self& _y) noexcept
        { return _x.__ptr == _y.__ptr;}
        friend bool operator!=(const self& _x, const self& _y) noexcept
        { return _x.__ptr != _y.__ptr;}

      public:
        friend bool operator<(const self& _x, const self& _y) noexcept
        { return _x.__ptr < _y.__ptr;}
        friend bool operator>(const self& _x, const self& _y) noexcept
        { return _x.__ptr > _y.__ptr;}
        friend bool operator<=(const self& _x, const self& _y) noexcept
        { return _x.__ptr <= _y.__ptr;}
        friend bool operator>=(const self& _x, const self& _y) noexcept
        { return _x.__ptr >= _y.__ptr;}

      public:
        friend difference_type operator-(const self& _x, const self _y) noexcept
        { return _x.__ptr - _y.__ptr;}

    };
    template<typename _T>
    class raw_pointer_iterator<const _T>
    {
      public:
        typedef contiguous_iterator_tag     iterator_category;
        typedef const _T                    value_type;
        typedef _T                          non_const_value_type;
        typedef const value_type&           reference;
        typedef typename
          trait::miscellaneous::pointer_traits<value_type*>::pointer pointer;
        typedef typename
          trait::miscellaneous::pointer_traits<value_type*>::difference_type difference_type;

      public:
        typedef raw_pointer_iterator<value_type> self;

      public:
        pointer __ptr;

      public:
        inline raw_pointer_iterator() noexcept:
          __ptr(nullptr)
        { }
        inline explicit raw_pointer_iterator(pointer _tptr) noexcept:
          __ptr(_tptr)
        { }
        inline raw_pointer_iterator(
          const raw_pointer_iterator<non_const_value_type>& _other
        ) noexcept:
          __ptr(_other.__ptr)
        { }

      public:
        inline raw_pointer_iterator& operator=(
          const raw_pointer_iterator& _other
        ) noexcept = default;

        inline self& operator=(
          const raw_pointer_iterator<non_const_value_type>& _other
        ) noexcept
        {
          this->__ptr = _other.__ptr;
          return *this;
        }

      public:
        reference operator*() const noexcept
        { return *(this->__ptr);}
        pointer operator->() const noexcept
        { return (this->__ptr);}

      public:
        self& operator++() noexcept
        {
          ++(this->__ptr);
          return *this;
        }
        self operator++(int) noexcept
        {
          self __it = *this;
          ++(this->__ptr);
          return __it;
        }
        self& operator--() noexcept
        {
          --(this->__ptr);
          return *this;
        }
        self operator--(int) noexcept
        {
          self __it = *this;
          --(this->__ptr);
          return __it;
        }

      public:
        self& operator+=(difference_type _len) noexcept
        {
          this->__ptr += _len;
          return *this;
        }
        self& operator-=(difference_type _len) noexcept
        {
          this->__ptr -= _len;
          return *this;
        }
        self operator+(difference_type _len) const noexcept
        { return self(this->__ptr + _len);}
        self operator-(difference_type _len) const noexcept
        { return self(this->__ptr - _len);}

      public:
        friend bool operator==(const self& _x, const self& _y) noexcept
        { return _x.__ptr == _y.__ptr;}
        friend bool operator!=(const self& _x, const self& _y) noexcept
        { return _x.__ptr != _y.__ptr;}

      public:
        friend bool operator<(const self& _x, const self& _y) noexcept
        { return _x.__ptr < _y.__ptr;}
        friend bool operator>(const self& _x, const self& _y) noexcept
        { return _x.__ptr > _y.__ptr;}
        friend bool operator<=(const self& _x, const self& _y) noexcept
        { return _x.__ptr <= _y.__ptr;}
        friend bool operator>=(const self& _x, const self& _y) noexcept
        { return _x.__ptr >= _y.__ptr;}

      public:
        friend difference_type operator-(const self& _x, const self _y) noexcept
        { return _x.__ptr - _y.__ptr;}

    };
  }
}

#endif // ! __UTILITY_ITERATOR_RAW_POINTER_ITERATOR__
