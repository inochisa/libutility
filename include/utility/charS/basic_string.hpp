
#ifndef __UTILITY_CHARS_BASIC_STRING__
#define __UTILITY_CHARS_BASIC_STRING__

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/max.hpp>
#include<utility/algorithm/min.hpp>
#include<utility/algorithm/find.hpp>
#include<utility/algorithm/find_first_of.hpp>

#include<utility/container/pair.hpp>
#include<utility/container/compressed_pair.hpp>
#include<utility/container/initializer_list.hpp>

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/property/is_pod.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/uninitialized_copy.hpp>
#include<utility/memory/uninitialized_possible_move.hpp>

#include<utility/charS/char_traits.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace charS
  {
    namespace __detail
    {
      using namespace iterator;
      using trait::type::property::is_pod;
      using trait::type::releations::is_same;

      template<typename _CharT, typename _ST>
      struct string_union_traits
      {
        struct __cal
        {
          _ST __cap;
          _CharT* __ptr;
        };
        constexpr static _ST value = sizeof(__cal);
        constexpr static _ST capacity = value / sizeof(_CharT);
        constexpr static _ST length = capacity > 2 ? capacity : 2;
      };

      template<typename _CharT, typename _ST>
      union string_union
      {
        struct
        {
          _CharT*   ptr;
          _ST       capacity;
        } longs;
        struct
        {
          _CharT array[string_union_traits<_CharT, _ST>::length];
        } shorts;
      };
    }

    template<
      typename _CharT,
      typename _Char_Traits = charS::char_traits<_CharT>,
      typename _Alloc = memory::allocator<_CharT>
    >
    class basic_string
    {
      private:
        template<typename __CharT>
        class __basic_string_iterator
        {
          private:
            template<typename, typename, typename>
            friend class basic_string;
            template<typename>
            friend class __basic_string_const_iterator;

          public:
            typedef __detail::contiguous_iterator_tag
              iterator_category;
            typedef __CharT value_type;
            typedef value_type& reference;
            typedef typename
              trait::miscellaneous::pointer_traits<__CharT*>::pointer pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<__CharT*>::difference_type difference_type;

          public:
            typedef __basic_string_iterator<__CharT> self;

          private:
            pointer __ptr;

          public:
            inline __basic_string_iterator() noexcept:
              __ptr(nullptr)
            { }
            inline explicit __basic_string_iterator(pointer _tptr) noexcept:
              __ptr(_tptr)
            { }

            inline ~__basic_string_iterator()
            { }

          public:
            inline self& operator=(const self& _other)
            {
              if(this != &_other)
              { this->__ptr = _other.__ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__ptr);}
            pointer operator->() const
            { return (this->__ptr);}

          public:
            self& operator++()
            {
              ++(this->__ptr);
              return *this;
            }
            self operator++(int)
            {
              self __it = *this;
              ++(this->__ptr);
              return __it;
            }
            self& operator--()
            {
              --(this->__ptr);
              return *this;
            }
            self operator--(int)
            {
              self __it = *this;
              --(this->__ptr);
              return __it;
            }

          public:
            self& operator+=(difference_type _len)
            {
              this->__ptr += _len;
              return *this;
            }
            self& operator-=(difference_type _len)
            {
              this->__ptr -= _len;
              return *this;
            }
            self operator+(difference_type _len) const
            { return self(this->__ptr + _len);}
            self operator-(difference_type _len) const
            { return self(this->__ptr - _len);}

          public:
            friend bool operator==(const self& _x, const self& _y)
            { return _x.__ptr == _y.__ptr;}
            friend bool operator!=(const self& _x, const self& _y)
            { return _x.__ptr != _y.__ptr;}

          public:
            friend bool operator<(const self& _x, const self& _y)
            { return _x.__ptr < _y.__ptr;}
            friend bool operator>(const self& _x, const self& _y)
            { return _x.__ptr > _y.__ptr;}
            friend bool operator<=(const self& _x, const self& _y)
            { return _x.__ptr <= _y.__ptr;}
            friend bool operator>=(const self& _x, const self& _y)
            { return _x.__ptr >= _y.__ptr;}

          public:
            friend difference_type operator-(const self& _x, const self _y)
            { return _x.__ptr - _y.__ptr;}

        };
        template<typename __CharT>
        class __basic_string_const_iterator
        {
          private:
            template<typename, typename, typename>
            friend class basic_string;

          public:
            typedef __detail::contiguous_iterator_tag
              iterator_category;
            typedef __CharT value_type;
            typedef const __CharT const_value_type;
            typedef const value_type& reference;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::pointer pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::difference_type difference_type;

          public:
            typedef __basic_string_const_iterator<__CharT> self;

          private:
            pointer __ptr;

          public:
            inline __basic_string_const_iterator() noexcept:
             __ptr(nullptr)
            { }
            inline __basic_string_const_iterator(pointer _tptr) noexcept:
             __ptr(_tptr)
            { }
            inline __basic_string_const_iterator(
              const __basic_string_iterator<__CharT>& _other
            ) noexcept:
              __ptr(_other.__ptr)
            { }
            ~__basic_string_const_iterator()
            { }

          public:
            inline self& operator=(const self& _other)
            {
              if(this != &_other)
              { this->__ptr = _other.__ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__ptr);}
            pointer operator->() const
            { return (this->__ptr);}

          public:
            self& operator++()
            {
              ++(this->__ptr);
              return *this;
            }
            self operator++(int)
            {
              self __it = *this;
              ++(this->__ptr);
              return __it;
            }
            self& operator--()
            {
              --(this->__ptr);
              return *this;
            }
            self operator--(int)
            {
              self __it = *this;
              --(this->__ptr);
              return __it;
            }

          public:
            self& operator+=(difference_type _len)
            {
              this->__ptr += _len;
              return *this;
            }
            self& operator-=(difference_type _len)
            {
              this->__ptr -= _len;
              return *this;
            }
            self operator+(difference_type _len) const
            { return self(this->__ptr + _len);}
            self operator-(difference_type _len) const
            { return self(this->__ptr - _len);}

          public:
            friend bool operator==(const self& _x, const self& _y)
            { return _x.__ptr == _y.__ptr;}
            friend bool operator!=(const self& _x, const self& _y)
            { return _x.__ptr != _y.__ptr;}

          public:
            friend bool operator<(const self& _x, const self& _y)
            { return _x.__ptr < _y.__ptr;}
            friend bool operator>(const self& _x, const self& _y)
            { return _x.__ptr > _y.__ptr;}
            friend bool operator<=(const self& _x, const self& _y)
            { return _x.__ptr <= _y.__ptr;}
            friend bool operator>=(const self& _x, const self& _y)
            { return _x.__ptr >= _y.__ptr;}

          public:
            friend difference_type operator-(const self& _x, const self _y)
            { return _x.__ptr - _y.__ptr;}

        };

      public:
        typedef _CharT                                  value_type;
        typedef _CharT                                  char_type;
        typedef value_type&                             reference;
        typedef const value_type                        const_value_type;
        typedef const value_type&                       const_reference;
        typedef _Char_Traits                            traits_type;
        typedef _Alloc                                  allocator_type;
        typedef memory::allocator_traits<_Alloc>        allocator_traits_type;

      public:
        typedef typename allocator_traits_type::size_type       size_type;
        typedef typename allocator_traits_type::difference_type difference_type;
        typedef typename allocator_traits_type::pointer         pointer;
        typedef typename allocator_traits_type::const_pointer   const_pointer;

      public:
        typedef __basic_string_iterator<value_type>         iterator;
        typedef __basic_string_const_iterator<value_type>   const_iterator;
        typedef __detail::reverse_iterator<iterator>        reverse_iterator;
        typedef __detail::reverse_iterator<const_iterator>  const_reverse_iterator;

      private:
        typedef __detail::string_union_traits<char_type, size_type>
          string_union_traits;
        typedef __detail::string_union<char_type, size_type>
          string_union;
        typedef container::compressed_pair<size_type, allocator_type> __mis_type;

      public:
        constexpr static size_type npos       = /*static_cast<size_type>*/(-1);
        constexpr static size_type pod_length = string_union_traits::capacity;

      public:
        constexpr static size_type short_mask = ~size_type{0} >> 1;
        constexpr static size_type short_tag = ~(short_mask);

      public:
        static_assert(
          __detail::is_pod<value_type>::value,
          "The char type of the basic_string must be pod."
        );
        static_assert(
          __detail::is_same<typename traits_type::char_type, value_type>::value,
          "The traits_type::char_type must be the same as value_type(_CharT)."
        );
        static_assert(
          __detail::is_same<typename allocator_type::value_type, value_type>::value,
          "the allocator's alloc type must be the same as value_type(_CharT)."
        );


      private:
        string_union  __un;
        __mis_type    __mis;

      public:
        basic_string(): basic_string{allocator_type{}}
        { }

        explicit basic_string(const allocator_type& _alloc):
          __un{}, __mis{short_tag, _alloc}
        { }

        basic_string(
          size_type _count, char_type _ch,
          const allocator_type& _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_count, _ch);}

        basic_string(
          const basic_string& _str, size_type _pos,
          const allocator_type _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_str, _pos);}

        basic_string(
          const basic_string& _str, size_type _pos,
          size_type _count,
          const allocator_type _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_str, _pos, _count);}

        basic_string(
          const char_type* _str, size_type _pos,
          const allocator_type _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_str, _pos);}

        basic_string(
          const char_type* _str,
          const allocator_type _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_str);}

        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        basic_string(
          _Iterator _first, _Iterator _last,
          const allocator_type _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_first, _last);}

        basic_string(const basic_string& _other):
          __un{}, __mis{short_tag, _other.__mis.second()}
        { this->append(_other);}

        basic_string(
          const basic_string& _other,
          const allocator_type& _alloc
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_other);}

        basic_string(basic_string&& _other):
          __un{},
          __mis{algorithm::move(_other.__mis)}
        {
          if(_is_short_string())
          { this->__un = _other.__un;}
          else
          {
            this->__un.longs.capacity = _other.__un.longs.capacity;
            this->__un.longs.ptr = _other.__un.longs.ptr;
            _other.__mis.first() = short_tag;
          }
        }

        basic_string(
          basic_string&& _other,
          const allocator_type& _alloc
        ):__un{}, __mis{_other.__mis.first(), _alloc}
        {
          if(_is_short_string())
          { this->__un = _other.__un;}
          else
          {
            this->__un.longs.capacity = _other.__un.longs.capacity;
            this->__un.longs.ptr = _other.__un.longs.ptr;
            _other.__mis.first() = short_tag;
          }
        }

        basic_string(
          container::initializer_list<char_type> _init,
          const allocator_type& _alloc = allocator_type{}
        ):__un{}, __mis{short_tag, _alloc}
        { this->append(_init.begin(), _init.end());}

      public:
        ~basic_string()
        { this->give_up();}

      public:
        basic_string& operator=(const basic_string& _other)
        {
          if(&_other != this)
          {
            this->clear();
            this->append(_other);
          }
          return *this;
        }
        basic_string& operator=(basic_string&& _other)
        {
          using algorithm::move;

          if(&_other != this)
          {
            this->give_up();
            if(_other._is_short_string())
            {
              this->__un = _other.__un;
              this->__mis = move(_other.__mis);
            }
            else
            {
              this->__un.longs.capacity = _other.__un.longs.capacity;
              this->__un.longs.ptr = _other.__un.longs.ptr;
              this->__mis = move(_other.__mis);
              _other.__mis.first() = short_tag;
            }
          }
          return *this;
        }
        basic_string& operator=(const char_type* _str)
        {
          if(this->data() != _str)
          {
            this->clear();
            this->append(_str);
          }
          return *this;
        }
        basic_string& operator=(char_type _ch) noexcept
        {
          this->clear();
          this->append(_ch);
          return *this;
        }
        basic_string& operator=(
          container::initializer_list<char_type> _init
        )
        {
          this->clear();
          this->append(_init.begin(), _init.end());
          return *this;
        }

      public:
        basic_string& assign(size_type _count, char_type _ch)
        {
          if(!check_reallocate(_count))
          { return *this;}
          if(_count >= this->capacity())
          { this->reallocate(__fix_capacity(capacity(), _count));}
          char_type* __ptr = this->data();
          for(; _count; --_count)
          { *__ptr++ = _ch;}
          *__ptr = char_type{};
          __length(this->__mis, _count);
          return *this;
        }
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        basic_string& assign(_Iterator _first, _Iterator _last)
        {
          using memory::uninitialized_copy;

          size_type __ns =
            static_cast<size_type>(__detail::distance(_first, _last));
          if(!check_reallocate(__ns))
          { return *this;}
          if(__ns >= this->capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}
          *uninitialized_copy(_first, _last, this->data()) = char_type{};
          __length(this->__mis, __ns);
          return *this;
        }
        basic_string& assign(const basic_string& _str)
        { return this->assign(_str.data(), _str.data_end());}
        basic_string& assign(
          const basic_string& _str,
          size_type _pos, size_type _count = npos
        )
        {
          if(&_str == this)
          { return *this;}
          container::pair<const char_type*, const char_type*> __sp =
            _str.substr_ptr(_pos, _count);
          return this->assign(__sp.first, __sp.second);
        }
        basic_string& assign(basic_string&& _str) noexcept
        {
          using algorithm::move;
          return *this = move(_str);
        }
        basic_string& assign(const char_type* _str, size_type _count)
        { return this->assign(_str, _str+_count);}
        basic_string& assign(const char_type* _str)
        {
          const char_type* __send = _str;
          for(; *__send; ++__send)
          { }
          return this->assign(_str, __send);
        }
        basic_string& assign(
          container::initializer_list<char_type> _init
        )
        { return this->assign(_init.begin(), _init.end());}

      public:
        allocator_type get_allocator() const
        { return this->__mis.second();}

      public:
        reference operator[](size_type _pos)
        { return data()[_pos];}
        const_reference operator[](size_type _pos) const
        { return data()[_pos];}
        reference at(size_type _pos)
        {
#ifdef __UTILITY_USE_EXCEPTION
          if(_pos > this->size())
          { }
#endif
          return data()[_pos];
        }
        const_reference at(size_type _pos) const
        {
#ifdef __UTILITY_USE_EXCEPTION
          if(_pos > this->size())
          { }
#endif
          return data()[_pos];
        }

      public:
        bool empty() const noexcept
        { return this->size() == 0U;}
        inline size_type size() const noexcept
        { return __length(this->__mis);}
        inline size_type length() const noexcept
        { return __length(this->__mis);}
        inline size_type capacity() const noexcept
        { return _is_short_string() ? pod_length-1 : this->__un.longs.capacity;}
        inline size_type max_size() const noexcept
        { return short_mask;}
        bool _is_short_string() const noexcept
        { return this->__mis.first() & short_tag;}

      public:
        char_type& front() noexcept
        { return *data();}
        const char_type& front() const noexcept
        { return *data();}
        char_type& back() noexcept
        { return data()[this->size()-1];}
        const char_type& back() const noexcept
        { return data()[this->size()-1];}


      public:
        inline pointer data() noexcept
        { return char_pointer(this->__mis, this->__un);}
        inline const_pointer data() const noexcept
        { return char_pointer(this->__mis, this->__un);}
        inline const_pointer c_str() const noexcept
        { return char_pointer(this->__mis, this->__un);}
      private:
        inline pointer data_end() noexcept
        { return char_pointer(this->__mis, this->__un) + this->size();}
        inline const_pointer data_end() const noexcept
        { return char_pointer(this->__mis, this->__un) + this->size();}


      public:
        iterator begin() noexcept
        { return iterator{this->data()};}
        const_iterator begin() const noexcept
        { return const_iterator{this->data()};}
        const_iterator cbegin() const noexcept
        { return const_iterator{this->data()};}
        iterator end() noexcept
        { return iterator{this->data() + this->size()};}
        const_iterator end() const noexcept
        { return const_iterator{this->data() + this->size()};}
        const_iterator cend() const noexcept
        { return const_iterator{this->data() + this->size()};}

      public:
        reverse_iterator rbegin() noexcept
        { return reverse_iterator{this->end()};}
        const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator{this->end()};}
        const_reverse_iterator crbegin() const noexcept
        { return const_reverse_iterator{this->end()};}
        reverse_iterator rend() noexcept
        { return reverse_iterator{this->begin()};}
        const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator{this->begin()};}
        const_reverse_iterator crend() const noexcept
        { return const_reverse_iterator{this->begin()};}

      public:
        inline size_type iterator_index(const_iterator __it) const noexcept
        { return static_cast<size_type>(__it.__ptr - this->data());}
        inline iterator _where(size_type _idx) const noexcept
        { return iterator{this->data()+_idx};}

      public:
        inline void reserve(size_type __cap = 0U)
        { this->reallocate(__cap);}
        inline void shrink_to_fit()
        { this->reallocate(0);}
      public:
        void resize(size_type _count, char_type _ch = char_type{})
        {
          if(check_reallocate(_count))
          { return;}
          if(_count > this->capacity())
          { this->reallocate(__fix_capacity(capacity(), _count));}
          if(_count < this->size())
          {
            this->data()[_count] = char_type{};
            __length(this->__mis, _count);
          }
          else
          {
            size_type __sfill = _count - this->size();
            *traits_type::assign(this->data_end(), __sfill, _ch) = char_type{};
            __length(this->__mis, _count);
          }
          return;
        }


      public:
        void clear() noexcept
        {
#ifdef UTILITY_BASIC_STRING_USE_DEALLOCATE_CLEAR
          if(!_is_short_string())
          {
            allocator_traits_type::deallocate(
              __mis.second(), __un.longs.ptr, capacity()
            );
          }
          __un.shorts.array[0] = char_type{0};
          __mis.first() = short_tag;
#else
          if(_is_short_string())
          {
            __un.shorts.array[0] = char_type{0};
            __mis.first() = short_tag;
          }
          else
          {
            *data() = char_type{0};
            __mis.first() = 0;
          }
#endif
        }
        void reset() noexcept
        {
          give_up();
          __mis.first() = short_tag;
          __un.shorts.array[0] = char_type{};
        }

      public:
        inline void push_back(char_type _ch)
        { this->append(1U, _ch);}
        inline void pop_back() noexcept
        {
          *this->data_end() = char_type{0};
          --this->__mis.first();
        }

      public:
        basic_string& append(size_type _count, char_type _ch)
        {
          if(_count == 0)
          { return *this;}
          size_type __ns = this->size() + _count;
          if(__ns > capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}
          char_type* __pos = this->data_end();
          for(; _count; --_count)
          { *__pos++ = _ch;}
          *__pos = char_type{0};
          __length(this->__mis, __ns);
          return *this;
        }
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        basic_string& append(_Iterator _first, _Iterator _last)
        {
          using memory::uninitialized_copy;

          if(_first != _last)
          {
            size_type __ns = this->size() +
              static_cast<size_type>(__detail::distance(_first, _last));
            if(__ns > capacity())
            { this->reallocate(__fix_capacity(capacity(), __ns));}
            char_type* __ptr =
              uninitialized_copy(_first, _last, this->data_end());
            *__ptr = char_type{0};
            __length(this->__mis, __ns);
          }
          return *this;
        }
        inline basic_string& append(const basic_string& _str)
        { return this->append(_str.data(), _str.data_end());}
        inline basic_string& append(
          const basic_string& _str,
          size_type _pos, size_type _count = npos
        )
        {
          if(_pos > _str.size())
#ifdef __UTILITY_USE_EXCEPTION
          { return *this;}
#else
          { return *this;}
#endif
          if(_pos+_count > _str.size())
          { _count = _str.size();}
          else
          { _count += _pos;}
          return this->append(this->data()+_pos, this->data()+_count);
        }
        inline basic_string& append(const char_type* _str, size_type _count)
        { return this->append(_str, _str+_count);}
        inline basic_string& append(const char_type* _str)
        {
          const char_type* __send = _str;
          for(; *__send; ++__send)
          { }
          return this->append(_str, __send);
        }
        inline basic_string& append(container::initializer_list<char_type> _init)
        { return this->append(_init.first(), _init.end());}
        inline basic_string& append(char_type _ch)
        { return this->append(1, _ch);}

      private:
        iterator __insert(size_type _pos, size_type _count, char_type _ch)
        {
          using memory::uninitialized_possible_move_backward;

          if(!check_pos(_pos))
          { return this->end();}

          size_type __ns = this->size() + _count;
          if(!check_reallocate(__ns))
          { return iterator{this->data()+_pos};}

          if(__ns > capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}

          char_type* __ptr= this->data()+_pos;
          uninitialized_possible_move_backward(
            __ptr, this->data_end()+1,
            this->data_end()+1+_count
          );
          traits_type::assign(__ptr, _count, _ch);
          __length(this->__mis, __ns);

          return iterator{__ptr};
        }
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        iterator __insert(size_type _pos, _Iterator _first, _Iterator _last)
        {
          using memory::uninitialized_possible_move_backward;
          using memory::uninitialized_copy;

          if(!check_pos(_pos))
          { return this->end();}

          size_type _count =
            static_cast<size_type>(__detail::distance(_first, _last));
          size_type __ns = this->size() + _count;

          if(!check_reallocate(__ns) || _first == _last)
          { return iterator{this->data()+_pos};}

          if(__ns > capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}

          char_type* __ptr= this->data()+_pos;

          uninitialized_possible_move_backward(
            __ptr, this->data_end()+1,
            this->data_end()+1+_count
          );
          uninitialized_copy(_first, _last, __ptr);
          __length(this->__mis, __ns);

          return iterator{__ptr};
        }

      public:
        inline basic_string& insert(size_type _pos, size_type _count, char_type _ch)
        {
          this->__insert(_pos, _count, _ch);
          return *this;
        }
        inline basic_string& insert(size_type _pos, const char_type* _str)
        {
          char_type* __send = _str;
          for(; *__send; ++__send)
          { }
          this->__insert(_pos, _str, __send);
          return *this;
        }
        inline basic_string& insert(
          size_type _pos, const char_type* _str, size_type _count
        )
        {
          this->__insert(_pos, _str, _str+_count);
          return *this;
        }
        inline basic_string& insert(size_type _pos, const basic_string& _str)
        {
          this->__insert(_pos, _str.data(), _str.data_end());
          return *this;
        }
        inline basic_string& insert(
          size_type _pos, const basic_string& _str,
          size_type _idx, size_type _count = npos
        )
        {
          container::pair<const char_type*, const char_type*> __sp =
            _str.substr_ptr(_idx, _count);
          this->__insert(_pos, __sp.first, __sp.second);
          return *this;
        }
        inline iterator insert(const_iterator _pos, char_type _ch)
        { return this->__insert(iterator_index(_pos), 1U, _ch);}
        inline iterator insert(const_iterator _pos, size_type _count, char_type _ch)
        { return this->__insert(iterator_index(_pos), _count, _ch);}
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        inline iterator __insert(
          const_iterator _pos,
          _Iterator _first, _Iterator _last
        )
        { return this->__insert(iterator_index(_pos), _first, _last);}
        inline iterator insert(
          const_iterator _pos,
          container::initializer_list<char_type> _init
        )
        {
          return this->__insert(
            iterator_index(_pos), _init.first(), _init.end()
          );
        }

      public:
        basic_string& erase(
          size_type _idx = 0U, size_type _count = npos
        ) noexcept
        {
          using algorithm::min;
          using memory::uninitialized_possible_move;

          if(!check_pos(_idx))
          { return *this;}
          _count = min(_count, size()-_idx);
          char_type* __ebegin = this->data() + _idx;
          char_type* __eend = __ebegin + _count;
          *uninitialized_possible_move(
            __eend, this->data_end(), __ebegin
          ) = char_type{0};
          this->__mis.first() -= _count;
          return *this;
        }
        inline iterator erase(const_iterator _pos) noexcept
        {
          size_type __where = this->iterator_index(_pos);
          this->erase(__where, 1U);
          return this->_where(__where);
        }
        inline iterator erase(const_iterator _first, const_iterator _last) noexcept
        {
          size_type __where = this->iterator_index(_first);
          this->erase(__where, static_cast<size_type>(_last-_first));
          return this->_where(__where);
        }

      public:
        basic_string& replace(
          size_type _pos, size_type _count,
          size_type _slen, char_type _ch
        )
        {
          if(!check_pos(_pos))
          { return *this;}
          _count = min(size()-_pos, _count);
          size_type __ns = size() - _count + _slen;
          if(!check_reallocate(__ns))
          { return *this;}

          if(__ns > capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}

          traits_type::move(
            this->data()+_pos+_slen, this->data()+_pos+_count,
            __ns-_pos-_count+1
          );
          char_type* __ptr = this->data()+_pos;
          for( ; _slen; --_slen)
          { *__ptr++ = _ch;}
          __length(this->__mis, __ns);

          return *this;
        }
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        basic_string& replace(
          size_type _pos, size_type _count,
          _Iterator _first, _Iterator _last
        )
        {
          if(!check_pos(_pos))
          { return *this;}
          _count = min(size()-_pos, _count);
          size_type __slen =
            static_cast<size_type>(__detail::distance(_first, _last));
          size_type __ns = size() - _count + __slen;
          if(!check_reallocate(__ns))
          { return *this;}

          if(__ns > capacity())
          { this->reallocate(__fix_capacity(capacity(), __ns));}

          traits_type::move(
            this->data()+_pos+__slen, this->data()+_pos+_count,
            __ns-_pos-_count+1
          );
          char_type* __ptr = this->data()+_pos;

          for(; _first != _last;)
          { *__ptr++ = *_first++;}

          __length(this->__mis, __ns);

          return *this;
        }
        basic_string& replace(
          const_iterator _first, const_iterator _last,
          size_type _slen, char_type _ch
        )
        {
          return this->replace(
            this->iterator_index(_first),
            static_cast<size_type>(_last-_first),
            _slen, _ch
          );
        }
        basic_string& replace(
          size_type _pos, size_type _count,
          const basic_string& _str
        )
        { return this->replace(_pos, _count, _str.data(), _str.data_end());}
        basic_string& replace(
          const_iterator _first, const_iterator _last,
          const basic_string& _str
        )
        {
          return this->replace(
            this->iterator_index(_first),
            static_cast<size_type>(_last-_first),
            _str.data(), _str.data_end()
          );
        }
        basic_string& replace(
          size_type _pos, size_type _count,
          const basic_string& _str,
          size_type _idx, size_type _slen = npos
        )
        {
          container::pair<const char_type*, const char_type*> __sp =
            _str.substr_ptr(_idx, _slen);
          return this->replace(_pos, _count, __sp.first, __sp.second);
        }
        template<
          typename _Iterator,
          typename trait::type::miscellaneous::enable_if<
            __detail::is_iterator<_Iterator>::value,
            bool
          >::type = true
        >
        basic_string& replace(
          const_iterator _first, const_iterator _last,
          _Iterator _sfirst, _Iterator _slast
        )
        {
          return this->replace(
            this->iterator_index(_first),
            static_cast<size_type>(_last-_first),
            _sfirst, _slast
          );
        }
        basic_string& replace(
          size_type _pos, size_type _count,
          const char_type* _str, size_type _slen
        )
        { return this->replace(_pos, _count, _str, _str+_slen);}
        basic_string& replace(
          const_iterator _first, const_iterator _last,
          const char_type* _str, size_type _slen
        )
        {
          return this->replace(
            this->iterator_index(_first),
            static_cast<size_type>(_last-_first),
            _str, _str+_slen
          );
        }
        basic_string& replace(
          size_type _pos, size_type _count,
          const char_type* _str
        )
        {
          const char_type* __send = _str;
          for(; *__send; ++__send)
          { }
          return this->replace(_pos, _count, _str, __send);
        }
        basic_string& replace(
          const_iterator _first, const_iterator _last,
          const char_type* _str
        )
        {
          const char_type* __send = _str;
          for(; *__send; ++__send)
          { }
          return this->replace(
            this->iterator_index(_first),
            static_cast<size_type>(_last-_first),
            _str, __send
          );
        }

      public:
        int compare(
          size_type _pos, size_type _count,
          const char_type* _str, size_type _clen
        ) const noexcept
        {
          container::pair<const char_type*, const char_type*> __sp =
            this->substr_ptr(_pos, _count);
          _count = static_cast<size_type>(__sp.second-__sp.first);
          size_type __len = algorithm::min(_count, _clen);
          int __res = traits_type::compare(__sp.first, _str, __len);
          if(__res)
          { return __res;}
          return _count == _clen ? 0 : (_count < _clen ? -1 : 1);
        }
        int compare(const basic_string& _str) const noexcept
        { return this->compare(0U, npos, _str.data(), _str.size());}
        int compare(
          size_type _pos, size_type _count,
          const basic_string& _str
        ) const noexcept
        { return this->compare(_pos, _count, _str.data(), _str.size());}
        int compare(
          size_type _pos, size_type _count,
          const basic_string& _str,
          size_type _idx, size_type _clen
        ) const noexcept
        {
          container::pair<const char_type*, const char_type*> __sp =
            _str.substr_ptr(_idx, _clen);
          return this->compare(
            _pos, _count, __sp.first,
            static_cast<size_type>(__sp.second-__sp.first)
          );
        }
        int compare(const char_type* _str) const noexcept
        {
          size_type __clen = 0U;
          for(; *_str; ++_str, ++__clen)
          { }
          return this->compare(0U, npos, _str, __clen);
        }
        int compare(
          size_type _pos, size_type _count,
          const char_type* _str
        ) const noexcept
        {
          size_type __clen = 0U;
          for(; *_str; ++_str, ++__clen)
          { }
          return this->compare(_pos, _count, _str, __clen);
        }

      public:
        size_type copy(
          char_type* _dest, size_type _count = npos, size_type _pos = 0U
        ) const
        {
          container::pair<const char_type*, const char_type*> __sp =
            this->substr_ptr(_pos, _count);
          size_type __ns = static_cast<size_type>(__sp.second-__sp.first);
          traits_type::assign(_dest, __sp.first, __ns);
          return __ns;
        }
        basic_string substr(size_type _pos = 0U, size_type _count = npos) const
        {
          container::pair<const char_type*, const char_type*> __sp =
            this->substr_ptr(_pos, _count);
          return basic_string{__sp.first, __sp.second};
        }

      public:
        void swap(basic_string& _other) noexcept(
          utility::trait::type::features::is_nothrow_swappable<allocator_type>::value
        )
        {
          using utility::algorithm::swap;
          swap(this->__mis, _other.__mis);
          swap(this->__un,  _other.__un);
        }

        void possible_swap(basic_string& _other) noexcept(
          utility::trait::type::features::is_nothrow_possible_swappable<allocator_type>::value
        )
        {
          using utility::algorithm::possible_swap;
          possible_swap(this->__mis, _other.__mis);
          possible_swap(this->__un,  _other.__un);
        }

      public:
        inline basic_string operator+=(const basic_string& _str)
        { return this->append(_str);}
        inline basic_string operator+=(char_type _ch)
        { return this->append(_ch);}
        inline basic_string operator+=(const char_type* _str)
        { return this->append(_str);}
        inline basic_string operator+=(container::initializer_list<char_type> _init)
        { return this->append(_init);}

      private:
        bool check_pos(size_type& _pos) const
        {
          if(_pos > this->size())
#ifdef UTILITY_BASIC_STRING_CORRECT_OUTRANGE_POS
          { _pos = this->size();}
#elif defined(__UTILITY_USE_EXCEPTION)
          { ;}
#else
          { return false;}
#endif
          return true;
        }
        bool check_reallocate(size_type _count) const
        {
          if(_count > max_size())
#if defined(__UTILITY_USE_EXCEPTION)
          { ;}
#else
          { return false;}
#endif
          return true;
        }

      private:
        container::pair<const char_type*, const char_type*>
        substr_ptr(size_type _idx, size_type _count = npos) const noexcept
        {
          typedef container::pair<const char_type*, const char_type*> __result;
          if(!check_pos(_idx))
          { return __result{this->data_end(), this->data_end()};}
          if(_idx+_count > this->size())
          { _count = this->size();}
          else
          { _count += _idx;}
          return __result{this->data()+_idx, this->data()+_count};
        }

      private:
        void reallocate(size_type _new)
        {
          using algorithm::max;
          using algorithm::min;
          using memory::uninitialized_possible_move;

          size_type __alloc = min(this->max_size(), _new)+1;
          if(_is_short_string())
          {
            // not need reallocate
            if(__alloc <= pod_length)
            { return;}

            // allocate length > pod length
            char_type* __ptr =
              allocator_traits_type::allocate(this->__mis.second(), __alloc);
            uninitialized_possible_move(data(), data_end()+1, __ptr);
            this->__un.longs.capacity = __alloc-1;
            this->__un.longs.ptr = __ptr;
            this->__mis.first() &= short_mask;
          }
          else
          {
            // need reallocate storage
            if(this->size() < pod_length && __alloc <= pod_length)
            {
              // use pod storage
              char_type __tmp[pod_length];
              uninitialized_possible_move(data(), data_end()+1, __tmp);
              allocator_traits_type::deallocate(
                this->__mis.second(), this->__un.longs.ptr, capacity()
              );
              uninitialized_possible_move(
                __tmp, __tmp + this->__mis.first()+1,
                this->__un.shorts.array
              );
              this->__mis.first() |= short_tag;
            }
            else
            {
              char_type* __ptr =
                allocator_traits_type::allocate(this->__mis.second(), __alloc);
              uninitialized_possible_move(data(), data_end()+1, __ptr);
              allocator_traits_type::deallocate(
                this->__mis.second(), this->__un.longs.ptr, capacity()
              );
              this->__un.longs.capacity = __alloc-1;
              this->__un.longs.ptr = __ptr;
              this->__mis.first() &= short_mask;
            }
          }

          return;
        }

      private:
        void give_up() noexcept
        {
          if(!_is_short_string())
          {
            allocator_traits_type::deallocate(
              __mis.second(), __un.longs.ptr, capacity()
            );
          }
        }

      private:
        static inline bool _is_shorts(const __mis_type& _tag) noexcept
        { return _tag.first() & short_tag;}

      private:
        static inline char_type* char_pointer(
          const __mis_type& _tag, string_union& _su
        ) noexcept
        { return _is_shorts(_tag) ? _su.shorts.array : _su.longs.ptr;}
        static inline const char_type* char_pointer(
          const __mis_type& _tag, const string_union& _su
        ) noexcept
        { return _is_shorts(_tag) ? _su.shorts.array : _su.longs.ptr;}

      private:
        static inline size_type __fix_capacity(
          size_type _capacity, size_type _new
        ) noexcept
        {
          _capacity = _capacity < pod_length ? pod_length : _capacity;
          for(; _capacity < _new; _capacity <<= 1U)
          { }
          return _capacity;
        }

      private:
        static inline void __length(__mis_type& _tag, size_type _size) noexcept
        {
          if(_is_shorts(_tag))
          { __short_length(_tag, _size);}
          else
          { __long_length(_tag, _size);}
        }
        static inline size_type __length(const __mis_type& _tag) noexcept
        {
          return _is_shorts(_tag) ? __short_length(_tag) :
                 __long_length(_tag);
        }
        static inline void __long_length(__mis_type& _tag, size_type _size) noexcept
        { _tag.first() = _size;}
        static inline size_type __long_length(const __mis_type& _tag) noexcept
        { return _tag.first();}
        static inline void __short_length(__mis_type& _tag, size_type _size) noexcept
        { _tag.first() = _size | short_tag;}
        static inline size_type __short_length(const __mis_type& _tag) noexcept
        { return _tag.first() & short_mask;}
    };

    template<
      typename _CharT,
      typename _Char_Traits,
      typename _Alloc
    >
    constexpr typename basic_string<_CharT, _Char_Traits,_Alloc>::size_type
      basic_string<_CharT, _Char_Traits,_Alloc>::short_tag;
    template<
      typename _CharT,
      typename _Char_Traits,
      typename _Alloc
    >
    constexpr typename basic_string<_CharT, _Char_Traits,_Alloc>::size_type
      basic_string<_CharT, _Char_Traits,_Alloc>::short_mask;

    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator==(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) == 0;}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator!=(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) != 0;}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator<(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) < 0;}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator>(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) > 0;}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator<=(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) <= 0;}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    bool operator>=(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return _x.compare(_y) >= 0;}

    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    )
    { return basic_string<_CharT, _Char_Traits, _Alloc>{_x}.append(_y);}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const _CharT* _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    )
    { return basic_string<_CharT, _Char_Traits, _Alloc>{_x}.append(_y);}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      _CharT _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    )
    { return basic_string<_CharT, _Char_Traits, _Alloc>{1, _x}.append(_y);}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      const _CharT* _y
    )
    { return basic_string<_CharT, _Char_Traits, _Alloc>{_x}.append(_y);}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      _CharT _y
    )
    { return basic_string<_CharT, _Char_Traits, _Alloc>{_x}.append(_y);}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      basic_string<_CharT, _Char_Traits, _Alloc>&& _x,
      const basic_string<_CharT, _Char_Traits, _Alloc>& _y
    ) noexcept
    { return algorithm::move(_x.append(_y));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      basic_string<_CharT, _Char_Traits, _Alloc>&& _x,
      const _CharT* _y
    ) noexcept
    { return algorithm::move(_x.append(_y));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      basic_string<_CharT, _Char_Traits, _Alloc>&& _x,
      _CharT _y
    ) noexcept
    { return algorithm::move(_x.append(_y));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const basic_string<_CharT, _Char_Traits, _Alloc>& _x,
      basic_string<_CharT, _Char_Traits, _Alloc>&& _y
    ) noexcept
    { return algorithm::move(_y.insert(0U, _x));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      const _CharT* _x,
      basic_string<_CharT, _Char_Traits, _Alloc>&& _y
    ) noexcept
    { return algorithm::move(_y.insert(0U, _x));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      _CharT _x,
      basic_string<_CharT, _Char_Traits, _Alloc>&& _y
    ) noexcept
    { return algorithm::move(_y.insert(0U, _x));}
    template<typename _CharT, typename _Char_Traits, typename _Alloc>
    basic_string<_CharT, _Char_Traits, _Alloc> operator+(
      basic_string<_CharT, _Char_Traits, _Alloc>&& _x,
      basic_string<_CharT, _Char_Traits, _Alloc>&& _y
    ) noexcept
    { return algorithm::move(_x.append(_y));}

    typedef basic_string<char>        string;
    typedef basic_string<wchar_t>     wstring;
    typedef basic_string<char16_t>    u16string;
    typedef basic_string<char32_t>    u32string;
  }
}

#endif // ! __UTILITY_CHARS_BASIC_STRING__
