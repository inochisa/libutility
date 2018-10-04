
#ifndef __UTILITY_CONTAINER_VECTOR__
#define __UTILITY_CONTAINER_VECTOR__

/**
 * \file vector.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/move_forward.hpp>
#include<utility/algorithm/move_backward.hpp>
#include<utility/algorithm/equal.hpp>
#include<utility/algorithm/lexicographical_compare.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/uninitialized_copy.hpp>
#include<utility/memory/uninitialized_fill_n.hpp>
#include<utility/memory/uninitialized_move.hpp>
#include<utility/memory/uninitialized_possible_move.hpp>

#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/raw_pointer_iterator.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _T,
      typename _Allocator = memory::allocator<_T>
    >
    class vector
    {
      public:
        typedef _T                    value_type;
        typedef _Allocator            allocator_type;
        typedef size_t                size_type;
        typedef ptrdiff_t             difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;

      public:
        typedef memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef helper::raw_pointer_iterator<_T>        iterator;
        typedef helper::raw_pointer_iterator<const _T>  const_iterator;
        typedef
          helper::reverse_iterator<iterator>
          reverse_iterator;
        typedef
          helper::reverse_iterator<const_iterator>
          const_reverse_iterator;

      public: // assert
        static_assert(trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        pointer __begin;
        pointer __end;
        pointer __mend;
        allocator_type __allocator;

      public:
        vector() noexcept(noexcept(allocator_type())):
          vector(allocator_type())
        { }
        explicit vector(const allocator_type& __alloc) noexcept:
          __allocator(__alloc)
        { this->__begin = this->__end = this->__mend = nullptr;}

        explicit vector(
          size_type __count, const value_type& __val,
          const allocator_type& __alloc = allocator_type()
        ):__allocator(__alloc)
        {
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __count);
          this->__mend = this->__begin + (__count);
          this->__end = this->__begin;
          for(;__count; --__count)
          {
            allocator_traits_type::construct(
              this->__allocator, __end++, __val
            );
          }
        }

        explicit vector(
          size_type __count,
          const allocator_type& __alloc = allocator_type()
        ):__allocator(__alloc)
        {
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __count);
          this->__end = this->__begin;
          this->__mend = this->__begin + (__count);
          for(;__count; --__count)
          {
            allocator_traits_type::construct(
              this->__allocator, __end++
            );
          }
        }

        template<typename _Inputiterator,
          typename
          trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
            bool
          >::type = true
        >
        vector(
          _Inputiterator __first, _Inputiterator __last,
          const allocator_type& __alloc = allocator_type()
        ): __allocator(__alloc)
        {
          size_type __len =
            helper::distance(__first, __last);
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __len);
          this->__end = this->__begin;
          this->__mend = this->__begin + (__len);
          for(; __len; --__len)
          {
            allocator_traits_type::construct(
              this->__allocator, __end++, *__first++
            );
          }
        }

        vector(const vector& __other)
        {
          size_type __len = __other.size();
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __len);
          this->__end = this->__begin;
          this->__mend = this->__begin + (__len);
          for(const_iterator __it = __other.begin(); __len; --__len)
          {
            allocator_traits_type::construct(
              this->__allocator, this->__end++, *__it++
            );
          }
        }
        vector(const vector& __other, const allocator_type& __alloc):
          __allocator(__alloc)
        {
          size_type __len = __other.size();
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __len);
          this->__end = this->__begin;
          this->__mend = this->__begin + (__len);
          for(const_iterator __it = __other.begin(); __len; --__len)
          {
            allocator_traits_type::construct(
              this->__allocator, __end++, *__it++
            );
          }
        }
        vector(vector&& __other) noexcept
        {
          this->__allocator = __other.__allocator;
          this->__begin = __other.__begin;
          this->__end = __other.__end;
          this->__mend = __other.__mend;
          __other.__begin = __other.__end = __other.__mend = nullptr;
        }
        vector(vector&& __other, const allocator_type& __alloc):
          __allocator(__alloc)
        {
          this->__begin = __other.__begin;
          this->__end = __other.__end;
          this->__mend = __other.__mend;
          __other.__begin = __other.__end = __other.__mend = nullptr;
        }

        vector(
          initializer_list<value_type> __initlist,
          const allocator_type& __alloc = allocator_type()
        ):__allocator(__alloc)
        {
          typedef typename
            initializer_list<value_type>::iterator __iterator;
          size_type __len = __initlist.size();
          this->__begin =
            allocator_traits_type::allocate(this->__allocator, __len);
          this->__end = this->__begin;
          this->__mend = this->__begin + (__len);
          for(__iterator __it = __initlist.begin(); __len; --__len)
          {
            allocator_traits_type::construct(
              this->__allocator, __end++, *__it++
            );
          }
        }

        ~vector()
        {
          this->force_clear();
        }

      public:
        vector& operator=(const vector& __other)
        {
          if(&__other != this)
          {
            this->clear();
            this->__allocator = __other.__allocator;
            this->assign(__other.begin(), __other.end());
          }
          return *this;
        }
        vector& operator=(vector&& __other) noexcept
        {
          if(&__other != this)
          {
            this->force_clear();
            this->__begin = __other.__begin;
            this->__end = __other.__end;
            this->__mend = __other.__mend;
            this->__allocator =
              algorithm::move(__other.__allocator);
            __other.__begin = __other.__end = __other.__mend = nullptr;
          }
          return *this;
        }
        vector& operator=(initializer_list<value_type> __initlist)
        {
          this->assign(__initlist.begin(), __initlist.end());
          return *this;
        }

      public:
        void assign(size_type __count, const value_type& __val)
        {
          this->clear();
          if(__count > this->capacity())
          { this->reallocate(__count * 2);}
          memory::uninitialized_fill_n(
            this->__begin, __count, __val
          );
          this->__end += __count;
        }
        template<typename _Inputiterator,
          typename
          trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
            bool
          >::type = true
        >
        void assign(_Inputiterator __first, _Inputiterator __last)
        {
          size_type __count =
            helper::distance(__first, __last);
          this->clear();
          if(__count > this->capacity())
          { this->reallocate(__count * 2);}
          memory::uninitialized_copy(
            __first, __last, this->__begin
          );
          this->__end += __count;
        }
        void assign(initializer_list<value_type> __initlist)
        { this->assign(__initlist.begin(), __initlist.end());}

      public:
        allocator_type get_allocator() const
        { return this->__allocator;}

      public:

#ifdef __UTILITY_USE_EXCEPTION

        reference at(size_type __pos)
        {
          if(__pos >= this->size())
          { throw 1;}
          return (this->__begin)[__pos];
        }
        const_reference at(size_type __pos) const
        {
          if(__pos >= this->size())
          { throw 1;}
          return (this->__begin)[__pos];
        }

#endif // ! __UTILITY_USE_EXCEPTION

      public:
        inline reference operator[](size_type __pos)
        { return (this->__begin)[__pos];}
        inline const_reference operator[](size_type __pos) const
        { return (this->__begin)[__pos];}

      public:
        reference front()
        { return *(this->__begin);}
        const_reference front() const
        { return *(this->__begin);}
        reference back()
        { return *(this->__end-1);}
        const_reference back() const
        { return *(this->__end-1);}
        pointer data() noexcept
        { return this->__begin;}
        const_pointer data() const noexcept
        { return this->__begin;}

      public:
        inline bool empty() const noexcept
        { return this->__begin == this->__end;}
        inline size_type size() const noexcept
        { return this->__end - this->__begin;}
        inline size_type capacity() const noexcept
        { return this->__mend - this->__begin;}

      public:
        iterator begin() noexcept
        { return iterator(this->__begin);}
        const_iterator begin() const noexcept
        { return const_iterator(this->__begin);}
        const_iterator cbegin() const noexcept
        { return const_iterator(this->__begin);}
        iterator end() noexcept
        { return iterator(this->__end);}
        const_iterator end() const noexcept
        { return const_iterator(this->__end);}
        const_iterator cend() const noexcept
        { return const_iterator(this->__end);}

      public:
        reverse_iterator rbegin() noexcept
        { return iterator{end()};}
        const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator{end()};}
        const_reverse_iterator crbegin() const noexcept
        { return const_reverse_iterator{cend()};}
        reverse_iterator rend() noexcept
        { return iterator{begin()};}
        const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator{begin()};}
        const_reverse_iterator crend() const noexcept
        { return const_reverse_iterator{cbegin()};}

      public:
        void push_back(const value_type& __val)
        {
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          allocator_traits_type::construct(
            this->__allocator, (this->__end)++, __val
          );
        }
        void push_back(value_type&& __val)
        {
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          allocator_traits_type::construct(
            this->__allocator, (this->__end)++,
            algorithm::move(__val)
          );
        }

      public:
        template<typename... _Args>
        iterator emplace(const_iterator __pos, _Args&&... __args)
        {
          difference_type __len = __pos.__ptr - this->__begin;
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          memory::uninitialized_move_backward(
            (this->__begin)+__len, this->__end, (this->__end)+1
          );
          ++this->__end;
          allocator_traits_type::construct(
            this->__allocator,
            (this->__begin)+__len,
            algorithm::move(__args)...
          );
          return iterator((this->__begin)+__len);
        }
        template<typename... _Args>
        reference emplace_back(_Args&&... __args)
        {
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          allocator_traits_type::construct(
            this->__allocator, (this->__end)++,
            algorithm::move(__args)...
          );
          return this->back();
        }

      public:
        void pop_back()
        {
          allocator_traits_type::destroy(
            this->__allocator, --(this->__end)
          );
        }

      public:
        ///< \todo add strong exception guarantee, now is weak
        iterator insert(const_iterator __pos, const value_type& __val)
        {
          difference_type __len = __pos.__ptr - this->__begin;
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          memory::uninitialized_move_backward(
            (this->__begin)+__len, this->__end, (this->__end)+1
          );
          allocator_traits_type::construct(
            (this->__begin)+__len, __val
          );
          ++this->__end;
          return iterator((this->__begin)+__len);
        }
        iterator insert(const_iterator __pos, value_type&& __val)
        {
          difference_type __len = __pos.__ptr - this->__begin;
          if(this->__end == this->__mend)
          { this->reallocate(this->size() * 2);}
          memory::uninitialized_move_backward(
            (this->__begin)+__len, this->__end, (this->__end)+1
          );
          allocator_traits_type::construct(
            this->__allocator,
            (this->__begin)+__len,
            algorithm::move(__val)
          );
          ++this->__end;
          return iterator((this->__begin)+__len);
        }
        iterator insert(
          const_iterator __pos, size_type __count ,const value_type& __val
        )
        {
          difference_type __len = __pos.__ptr - this->__begin;
          if((this->size() + __count) > this->capacity())
          { this->reallocate((this->size() + __count) * 2);}
          memory::uninitialized_move_backward(
            (this->__begin)+__len, this->__end, (this->__end)+__count
          );
          memory::uninitialized_fill_n(
            (this->__begin)+__len, __count, __val
          );
          (this->__end) += __count;
          return iterator((this->__begin)+__len);
        }
        template<typename _Inputiterator,
          typename
          trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
            bool
          >::type = true
        >
        iterator insert(
          const_iterator __pos, _Inputiterator __first, _Inputiterator __last
        )
        {
          difference_type __len =
            helper::distance(__first, __last);
          difference_type __tpos = __pos.__ptr - this->__begin;
          if((this->size() + __len) > this->capacity())
          { this->reallocate((this->size() + __len) * 2);}
          memory::uninitialized_move_backward(
            (this->__begin) + __tpos,
            this->__end, (this->__end)+__len
          );
          (this->__end) += __len;
          memory::uninitialized_copy(
            __first, __last, (this->__begin)+__tpos
          );
          return iterator((this->__begin)+__tpos);
        }
        iterator insert(
          const_iterator __pos, initializer_list<value_type> __initlist
        )
        {
          return this->insert(
            __pos, __initlist.begin(), __initlist.end()
          );
        }

      public:
        iterator erase(const_iterator __pos)
        {
          pointer __tptr = const_cast<pointer>(__pos.__ptr);
          allocator_traits_type::destroy(this->__allocator, __tptr);
          memory::uninitialized_move(
            __tptr+1, this->__end, __tptr
          );
          --(this->__end);
          return iterator(__tptr);
        }
        iterator erase(const_iterator __first, const_iterator __last)
        {
          difference_type __len =
            helper::distance(__first, __last);
          pointer __tptr = const_cast<pointer>(__first.__ptr);
          for(difference_type __i = 0; __i < __len; ++__i)
          { allocator_traits_type::destroy(this->__allocator, __tptr+__i);}
          memory::uninitialized_move(
            __tptr+__len, this->__end, __tptr
          );
          (this->__end) -= __len;
          return iterator(__tptr);
        }

      public:
        void clear() noexcept
        {
          for(pointer __i = __begin; __i != __end; ++__i)
          { allocator_traits_type::destroy(this->__allocator, __i);}
          this->__end = this->__begin;
        }
        void reserve(size_type __new_size)
        {
          if(__new_size > this->capacity())
          { this->reallocate(__new_size);}
        }
        void shrink_to_fit()
        {
          if(this->size() != this->capacity())
          { this->reallocate(this->size());}
        }
        void resize(size_type __count)
        {
          static_assert(
            trait::type::features::is_default_constructible<
              value_type>::value,
            "vector::resize(size_type) request value type can be "
            "default constructible"
          );
          if(__count == this->size())
          { return;}
          if(__count < this->capacity())
          {
            if(__count < this->size())
            {
              this->erase(
                const_iterator(this->__begin+__count),
                this->end()
              );
              return;
            }
          }
          else
          { this->reallocate(__count * 2);}
          for(size_type __s = this->size(); __s != __count; ++__s)
          { this->emplace_back();}
        }
        void resize(size_type __count, const value_type& __val)
        {
          if(__count == this->size())
          { return;}
          if(__count < this->capacity())
          {
            if(__count < this->size())
            {
              this->erase(
                const_iterator(this->__begin+__count),
                this->end()
              );
              return;
            }
          }
          else
          { this->reallocate(__count * 2);}
          for(size_type __s = this->size(); __s != __count; ++__s)
          { this->emplace_back(__val);}
        }

      public:
        void swap(vector& __other) noexcept(
          trait::type::features::is_nothrow_swappable<allocator_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__allocator,   __other.__allocator);
          swap(this->__begin,       __other.__begin);
          swap(this->__end,         __other.__end);
          swap(this->__mend,        __other.__mend);
        }
        void possible_swap(vector& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<allocator_type>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__allocator, __other.__allocator);
          possible_swap(this->__begin,     __other.__begin    );
          possible_swap(this->__end,       __other.__end      );
          possible_swap(this->__mend,      __other.__mend     );
        }

      private:
        void force_clear()
        {
          this->clear();
          allocator_traits_type::deallocate(
            this->__allocator, this->__begin, capacity()
          );
          this->__begin = this->__end = this->__mend = nullptr;
        }
        void reallocate(size_type __need_size)
        {
          if(__need_size == 0)
          { __need_size = 1;}
          size_type __old_size = this->size();
          pointer __new_begin =
            allocator_traits_type::allocate(this->__allocator, __need_size);
          memory::uninitialized_possible_move(
            this->__begin, this->__end, __new_begin
          );
          allocator_traits_type::deallocate(
            this->__allocator, this->__begin, capacity()
          );
          this->__begin = __new_begin;
          this->__end = this->__begin + __old_size;
          this->__mend = this->__begin + __need_size;
        }

    };

    template<typename _T, typename _Alloc>
    inline bool operator==(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    {
      return __x.size() == __y.size() &&
        algorithm::equal(__x.begin(), __x.end(), __y.begin());
    }
    template<typename _T, typename _Alloc>
    inline bool operator!=(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    { return !(__x == __y);}
    template<typename _T, typename _Alloc>
    inline bool operator<(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    {
      return algorithm::lexicographical_compare(
        __x.begin(), __x.end(), __y.begin(), __y.end()
      );
    }
    template<typename _T, typename _Alloc>
    inline bool operator>(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    { return __y < __x;}
    template<typename _T, typename _Alloc>
    inline bool operator<=(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    { return !(__y < __x);}
    template<typename _T, typename _Alloc>
    inline bool operator>=(const vector<_T, _Alloc>& __x, const vector<_T, _Alloc>& __y)
    { return !(__x < __y);}
  }

  namespace algorithm
  {
    template<typename _T, typename _Alloc>
    inline void swap(
      container::vector<_T, _Alloc>& __x,
      container::vector<_T, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<typename _T, typename _Alloc>
    inline void possible_swap(
      container::vector<_T, _Alloc>& __x,
      container::vector<_T, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_VECTOR__
