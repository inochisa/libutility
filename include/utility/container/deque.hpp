

#ifndef __UTILITY_CONTAINER_DEQUE__
#define __UTILITY_CONTAINER_DEQUE__


#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/fill_n.hpp>
#include<utility/algorithm/move_forward.hpp>
#include<utility/algorithm/move_backward.hpp>
#include<utility/algorithm/equal.hpp>
#include<utility/algorithm/lexicographical_compare.hpp>

#include<utility/container/helper/allocator_deleter.hpp>
#include<utility/container/helper/underly_move.hpp>
#include<utility/container/compressed_pair.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/unique_ptr.hpp>
#include<utility/memory/uninitialized_copy.hpp>
#include<utility/memory/uninitialized_fill_n.hpp>
#include<utility/memory/uninitialized_move.hpp>
#include<utility/memory/uninitialized_possible_move.hpp>

#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace container
  {
    template<
      typename _T,
      typename _Alloc = memory::allocator<_T>,
      unsigned long _Block = 1024UL
    >
    class deque;

    namespace __detail
    {
      template<typename _T, unsigned long _Block>
      constexpr inline size_t deque_buffer_size() noexcept
      { return _Block/sizeof(_T) > 0 ? _Block/sizeof(_T) : 1;}

      template<typename _Vt, unsigned long _Block>
      class __deque_const_iterator;
      template<typename _Vt, unsigned long _Block>
      class __deque_iterator
      {
        private:
          template<typename, unsigned long>
          friend class __deque_const_iterator;
          template<typename, typename, unsigned long>
          friend class container::deque;

        public:
          typedef helper::random_access_iterator_tag         iterator_category;
          typedef _Vt                               value_type;
          typedef value_type&                       reference;
          typedef typename
            trait::miscellaneous::pointer_traits<_Vt*>::pointer pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<_Vt*>::difference_type
            difference_type;

        public:
          typedef __deque_iterator<_Vt, _Block>     self;

        private:
          typedef pointer*                          map_pointer;

        private:
          pointer         __now;
          pointer         __first;
          pointer         __last;
          map_pointer     __cur;

        public:
          __deque_iterator() noexcept = default;
          explicit __deque_iterator(
            pointer _now, pointer _first, pointer _last, map_pointer _cur
          ) noexcept:
            __now{_now}, __first{_first},
            __last{_last}, __cur{_cur}
          { }
          __deque_iterator(const __deque_iterator&) noexcept = default;
          __deque_iterator(__deque_iterator&&) noexcept = default;

        public:
          __deque_iterator& operator=(
            const __deque_iterator&
          ) noexcept = default;
          __deque_iterator& operator=(__deque_iterator&&) noexcept = default;

        public:
          reference operator*() const noexcept
          { return *(this->__now);}
          pointer operator->() const noexcept
          { return this->__now;}

        private:
          void jump(difference_type _len = 1) noexcept
          {
            this->__cur += _len;
            this->__first = *(this->__cur);
            this->__last = (this->__first) + deque_buffer_size<value_type, _Block>();
          }

        public:
          __deque_iterator& operator++() noexcept
          {
            ++(this->__now);
            if(this->__now == this->__last)
            {
              this->jump();
              this->__now = this->__first;
            }
            return *this;
          }
          __deque_iterator operator++(int) noexcept
          {
            self __it = *this;
            this->operator++();
            return __it;
          }
          __deque_iterator& operator--() noexcept
          {
            if(this->__now == this->__first)
            {
              this->jump(-1);
              this->__now = this->__last;
            }
            --(this->__now);
            return *this;
          }
          __deque_iterator operator--(int) noexcept
          {
            self __it = *this;
            this->operator--();
            return __it;
          }
          __deque_iterator& operator+=(difference_type _len) noexcept
          {
            _len += (this->__now - this->__first);
            difference_type __fpos = _len / deque_buffer_size<value_type, _Block>();
            difference_type __fcur = _len % deque_buffer_size<value_type, _Block>();

            this->jump(__fpos);
            this->__now = this->__first + __fcur;

            return *this;
          }
          __deque_iterator operator+(difference_type _len) noexcept
          {
            self __it = *this;
            __it.operator+=(_len);
            return __it;
          }
          __deque_iterator& operator-=(difference_type _len) noexcept
          {
            _len = (this->__now - this->__first) - _len;
            difference_type __fpos = _len / deque_buffer_size<value_type, _Block>();
            difference_type __fcur = _len % deque_buffer_size<value_type, _Block>();
            __fcur += deque_buffer_size<value_type, _Block>();
            __fcur %= deque_buffer_size<value_type, _Block>();

            this->jump(__fpos);
            this->__now = this->__first + __fcur;

            return *this;
          }
          __deque_iterator operator-(difference_type _len) noexcept
          {
            self __it = *this;
            __it.operator-=(_len);
            return __it;
          }
          difference_type operator-(__deque_iterator _oit) noexcept
          {
            difference_type __len = this->__now - this->__first;
            __len += ((this->__cur) - (_oit.__cur)) *
                      deque_buffer_size<value_type, _Block>();
            __len -= (_oit.__now - _oit.__first);
            return __len;
          }

        public:
          bool operator<(const __deque_iterator& _oit) const noexcept
          {
            if(this->__first == _oit.__first)
            { return this->__now < _oit.__now;}
            return this->__cur < _oit.__cur;
          }
          bool operator>(const __deque_iterator& _oit) const noexcept
          { return _oit.operator<(*this);}
          bool operator<=(const __deque_iterator& _oit) const noexcept
          { return !(_oit.operator<(*this));}
          bool operator>=(const __deque_iterator& _oit) const noexcept
          { return !(this->operator<(_oit));}

        public:
          bool operator==(const __deque_iterator& _other) const noexcept
          { return this->__now == _other.__now;}
          bool operator!=(const __deque_iterator& _other) const noexcept
          { return !(this->operator==(_other));}
      };

      template<typename _Vt, unsigned long _Block>
      class __deque_const_iterator
      {
        private:
          template<typename, typename, unsigned long>
          friend class container::deque;

        public:
          typedef helper::random_access_iterator_tag  iterator_category;
          typedef const _Vt                           value_type;
          typedef _Vt                                 non_const_value_type;
          typedef const _Vt&                          reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __deque_const_iterator<_Vt, _Block>       self;

        private:
          typedef typename
            trait::miscellaneous::pointer_traits<_Vt*>::pointer
            non_const_pointer;
          typedef non_const_pointer*       map_pointer;

        private:
          non_const_pointer __now;
          non_const_pointer __first;
          non_const_pointer __last;
          map_pointer       __cur;

        public:
          __deque_const_iterator() noexcept = default;
          explicit __deque_const_iterator(
            non_const_pointer _now, non_const_pointer _first,
            non_const_pointer _last, map_pointer _cur
          ) noexcept:
            __now{_now}, __first{_first},
            __last{_last}, __cur{_cur}
          { }
          __deque_const_iterator(
            __deque_iterator<_Vt, _Block> _oit
          ) noexcept:
            __now{_oit.__now}, __first{_oit.__first},
            __last{_oit.__last}, __cur{_oit.__cur}
          { }
          __deque_const_iterator(const __deque_const_iterator&) noexcept = default;
          __deque_const_iterator(__deque_const_iterator&&) noexcept = default;

        public:
          __deque_const_iterator& operator=(
            const __deque_const_iterator&
          ) noexcept = default;
          __deque_const_iterator& operator=(__deque_const_iterator&&) noexcept = default;

        public:
          reference operator*() const noexcept
          { return *(this->__now);}
          pointer operator->() const noexcept
          { return this->__now;}

        private:
          void jump(difference_type _len = 1) noexcept
          {
            this->__cur += _len;
            this->__first = *(this->__cur);
            this->__last = (this->__first) + deque_buffer_size<value_type, _Block>();
          }

        public:
          __deque_const_iterator& operator++() noexcept
          {
            ++(this->__now);
            if(this->__now == this->__last)
            {
              this->jump();
              this->__now = this->__first;
            }
            return *this;
          }
          __deque_const_iterator operator++(int) noexcept
          {
            self __it = *this;
            this->operator++();
            return __it;
          }
          __deque_const_iterator& operator--() noexcept
          {
            if(this->__now == this->__first)
            {
              this->jump(-1);
              this->__now = this->__last;
            }
            --(this->__now);
            return *this;
          }
          __deque_const_iterator operator--(int) noexcept
          {
            self __it = *this;
            this->operator--();
            return __it;
          }
          __deque_const_iterator& operator+=(difference_type _len) noexcept
          {
            _len += (this->__now - this->__first);
            difference_type __fpos = _len / deque_buffer_size<value_type, _Block>();
            difference_type __fcur = _len % deque_buffer_size<value_type, _Block>();

            this->jump(__fpos);
            this->__now = this->__first + __fcur;

            return *this;
          }
          __deque_const_iterator operator+(difference_type _len) noexcept
          {
            self __it = *this;
            __it.operator+=(_len);
            return __it;
          }
          __deque_const_iterator& operator-=(difference_type _len) noexcept
          {
            _len = (this->__now - this->__first) - _len;
            difference_type __fpos = _len / deque_buffer_size<value_type, _Block>();
            difference_type __fcur = _len % deque_buffer_size<value_type, _Block>();
            __fcur += deque_buffer_size<value_type, _Block>();
            __fcur %= deque_buffer_size<value_type, _Block>();

            this->jump(__fpos);
            this->__now = this->__first + __fcur;

            return *this;
          }
          __deque_const_iterator operator-(difference_type _len) noexcept
          {
            self __it = *this;
            __it.operator-=(_len);
            return __it;
          }
          difference_type operator-(__deque_const_iterator _oit) noexcept
          {
            difference_type __len = this->__now - this->__first;
            __len += ((this->__cur) - (_oit.__cur)) *
                      deque_buffer_size<value_type, _Block>();
            __len -= (_oit.__now - _oit.__first);
            return __len;
          }

        public:
          bool operator<(const __deque_const_iterator& _oit) const noexcept
          {
            if(this->__first == _oit.__first)
            { return this->__now < _oit.__now;}
            return this->__cur < _oit.__cur;
          }
          bool operator>(const __deque_const_iterator& _oit) const noexcept
          { return _oit.operator<(*this);}
          bool operator<=(const __deque_const_iterator& _oit) const noexcept
          { return !(_oit.operator<(*this));}
          bool operator>=(const __deque_const_iterator& _oit) const noexcept
          { return !(this->operator<(_oit));}

        public:
          bool operator==(const __deque_const_iterator& _other) const noexcept
          { return this->__now == _other.__now;}
          bool operator!=(const __deque_const_iterator& _other) const noexcept
          { return !(this->operator==(_other));}
      };
    }
    template<typename _T, typename _Alloc, unsigned long _Block>
    class deque
    {
      public:
        enum class behavior: unsigned char
        {
          front = 0,
          back = 1,
        };

      public:
        typedef _T                    value_type;
        typedef _Alloc                allocator_type;
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
        typedef __detail::__deque_iterator<_T, _Block>        iterator;
        typedef __detail::__deque_const_iterator<_T, _Block>  const_iterator;
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
        typedef pointer*                  map_pointer;
        typedef memory::basic_allocator<pointer>    map_allocator_type;
        typedef memory::allocator_traits<map_allocator_type>
             map_allocator_traits_type;

      public:
        typedef compressed_pair<map_pointer, map_allocator_type>  __base_type;
        typedef compressed_pair<size_type, allocator_type>  __mis_type;

      private:
        map_pointer     __map_cap;
        map_pointer     __map_acur;
        map_pointer     __map_aecur;
        map_pointer     __map_cur;
        map_pointer     __map_ecur;
        pointer         __data_begin;
        pointer         __data_end;
        __base_type     __base;
        __mis_type      __mis;

      public:
        deque(): deque(allocator_type{})
        { }
        explicit deque(const allocator_type& _alloc):
          __map_cap{},
          __map_acur{}, __map_aecur{},
          __map_cur{}, __map_ecur{},
          __data_begin{}, __data_end{},
          __base{}, __mis{0U, _alloc}
        { }
        deque(
          size_type _count, const value_type& _val,
          const allocator_type& _alloc = allocator_type{}
        ): deque(_alloc)
        { this->resize(_count, _val);}
        explicit deque(
          size_type _count,
          const allocator_type& _alloc = allocator_type{}
        ): deque(_alloc)
        { this->resize(_count);}
        template<
          typename _InputIterator,
          typename trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        deque(
          _InputIterator _first, _InputIterator _last,
          const allocator_type& _alloc = allocator_type{}
        ): deque(_alloc)
        { this->behavior_insert(behavior::back, begin(), _first, _last);}
        deque(const deque& _other): deque(_other.get_allocator())
        {
          this->behavior_insert(
            behavior::back, begin(), _other.begin(), _other.end()
          );
        }
        deque(const deque& _other, const allocator_type& _alloc): deque(_alloc)
        {
          this->behavior_insert(
            behavior::back, begin(), _other.begin(), _other.end()
          );
        }
        deque(deque&& _other) noexcept(
          trait::type::features::is_nothrow_constructible<allocator_type,
            allocator_type&&>::value
        ):__map_cap{_other.__map_cap},
          __map_acur{_other.__map_acur}, __map_aecur{_other.__map_aecur},
          __map_cur{_other.__map_cur}, __map_ecur{_other.__map_ecur},
          __data_begin{_other.__data_begin}, __data_end{_other.__data_end},
          __base{algorithm::move(_other.__base)},
          __mis{algorithm::move(_other.__mis)}
        {
          _other.__base.first() = _other.__map_cap = nullptr;
          _other.__map_acur = _other.__map_aecur = nullptr;
          _other.__map_cur = _other.__map_ecur = nullptr;
          _other.__data_begin = _other.__data_end = nullptr;
          _other.__mis.first() = 0;
        }
        deque(deque&& _other, const allocator_type& _alloc): deque(_alloc)
        {
          _other.__base.first() = _other.__map_cap = nullptr;
          _other.__map_acur = _other.__map_aecur = nullptr;
          _other.__map_cur = _other.__map_ecur = nullptr;
          _other.__data_begin = _other.__data_end = nullptr;
          _other.__mis.first() = 0;
        }
        deque(
          initializer_list<value_type> _init,
          const allocator_type& _alloc = allocator_type{}
        ): deque(_alloc)
        {
          this->behavior_insert(
            behavior::back, begin(), _init.begin(), _init.end()
          );
        }


        ~deque()
        {
          this->give_up();
        }

      public:
        deque& operator=(const deque& _other)
        {
          if(&_other != this)
          {
            if(allocator_traits_type::propagate_on_container_copy_assignment::value)
            { __mis.second() = _other.__mis.second();}
            clear();
            behavior_insert(
              behavior::back, begin(), _other.begin(), _other.end()
            );
          }
          return *this;
        }
        // deque& operator=(deque&& _other) noexcept(
        //   allocator_traits_type::is_always_equal::value
        // )
        // {
        //   if(&_other != this)
        //   {
        //     if(allocator_traits_type::propagate_on_container_copy_assignment::value)
        //     { __mis.second() = _other.__mis.second();}
        //     if()
        //     clear();
        //     behavior_insert(
        //       behavior::back, begin(), _other.begin(), _other.end()
        //     );
        //   }
        //   return *this;
        // }
        deque& operator=(initializer_list<value_type> _init)
        {
          clear();
          behavior_insert(
            behavior::back, begin(), _init.begin(), _init.end()
          );
          return *this;
        }

      public:
        allocator_type get_allocator() const
        { return __mis.second();}

      public:
        reference operator[](size_type _pos)
        {
          size_type __offset = (__data_begin - *__map_cur) + _pos;
          return __map_cur[__offset/_sequence_length][__offset%_sequence_length];
        }
        const_reference operator[](size_type _pos) const
        {
          size_type __offset = (__data_begin - *__map_cur) + _pos;
          return __map_cur[__offset/_sequence_length][__offset%_sequence_length];
        }

      public:
        void assign(size_type _count, const value_type& _val)
        {
          using algorithm::fill_n;

          if(_count > size())
          {
            fill_n(begin(), size(), _val);
            behavior_insert(behavior::back, end(), _count-size(), _val);
          }
          else
          {
            behavior_erase(
              behavior::back, fill_n(begin(), _count, _val), end()
            );
          }
        }
        template<
          typename _InputIterator,
          typename trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        void assign(_InputIterator _first, _InputIterator _last)
        {
          iterator __it = begin();
          iterator __eit = end();
          for(; _first != _last && __it != __eit;)
          { *__it++ = *_first++;}
          if(_first != _last)
          { behavior_insert(behavior::back, __eit, _first, _last);}
          else
          { behavior_erase(behavior::back, __it, __eit);}
        }

      private:

      public:
        reference front() noexcept
        { return *__data_begin;}
        const_reference front() const noexcept
        { return *__data_begin;}
        reference back() noexcept
        { return *--end();}
        const_reference back() const noexcept
        { return *--end();}

      public:
        iterator begin() noexcept
        {
          if(__base.first() == nullptr)
          { return iterator{};}
          return iterator{
            __data_begin,
            *__map_cur, (*__map_cur)+_sequence_length,
            __map_cur
          };
        }
        const_iterator begin() const noexcept
        {
          if(__base.first() == nullptr)
          { return const_iterator{};}
          return const_iterator{
            const_cast<pointer>(__data_begin),
            const_cast<pointer>(*__map_cur),
            const_cast<pointer>(*__map_cur)+_sequence_length,
            const_cast<map_pointer>(__map_cur)
          };
        }
        const_iterator cbegin() const noexcept
        {
          if(__base.first() == nullptr)
          { return const_iterator{};}
          return const_iterator{
            const_cast<pointer>(__data_begin),
            const_cast<pointer>(*__map_cur),
            const_cast<pointer>(*__map_cur)+_sequence_length,
            const_cast<map_pointer>(__map_cur)
          };
        }
        iterator end() noexcept
        {
          if(__base.first() == nullptr)
          { return iterator{};}
          return iterator{
            __data_end,
            *__map_ecur, (*__map_ecur)+_sequence_length,
            __map_ecur
          };
        }
        const_iterator end() const noexcept
        {
          if(__base.first() == nullptr)
          { return const_iterator{};}
          return const_iterator{
            const_cast<pointer>(__data_end),
            const_cast<pointer>(*__map_ecur),
            const_cast<pointer>(*__map_ecur)+_sequence_length,
            const_cast<map_pointer>(__map_ecur)
          };
        }
        const_iterator cend() const noexcept
        {
          if(__base.first() == nullptr)
          { return const_iterator{};}
          return const_iterator{
            const_cast<pointer>(__data_end),
            const_cast<pointer>(*__map_ecur),
            const_cast<pointer>(*__map_ecur)+_sequence_length,
            const_cast<map_pointer>(__map_ecur)
          };
        }

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
        void push_back(const value_type& _val)
        { behavior_insert(behavior::back, end(), _val);}
        void push_back(value_type&& _val)
        {
          using algorithm::move;
          behavior_insert(behavior::back, end(), move(_val));
        }
        void push_front(const value_type& _val)
        { behavior_insert(behavior::front, begin(), _val);}
        void push_front(value_type&& _val)
        {
          using algorithm::move;
          behavior_insert(behavior::front, begin(), move(_val));
        }

      public:
        template<typename... _Args>
        reference emplace_back(_Args&&... _args)
        {
          using algorithm::move;
          behavior_emplace(behavior::back, end(), move(_args)...);
          return back();
        }
        template<typename... _Args>
        reference emplace_front(_Args&&... _args)
        {
          using algorithm::move;
          behavior_emplace(behavior::front, begin(), move(_args)...);
          return front();
        }

      public:
        void pop_back() noexcept
        {
          iterator __it = end();
          --__it;
          allocator_traits_type::destroy(
            __base.second(), __it.__now
          );
          decrease_size(1);
          set_end(__it);
        }
        void pop_front() noexcept
        {
          iterator __it = begin();
          allocator_traits_type::destroy(
            __base.second(), __it.__now
          );
          decrease_size(1);
          set_begin(++__it);
        }

      public:
        iterator behavior_insert(
          behavior _be, const_iterator _pos, const value_type& _val
        )
        {
          size_type __offset = _iterator_offset(_pos);

          if(_be == behavior::back)
          {
            __check_request(1, false);
            _pos = begin() + __offset;
            __element_move(_pos, false, 1);
            __UTILITY_TRY_BEGIN
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, _val
              );
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              __element_move(_pos, false, 1);
            );
            set_end(++end());
          }
          else
          {
            __check_request(1, true);
            _pos = begin() + __offset;
            __element_move(--_pos, true, 1);
            __UTILITY_TRY_BEGIN
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, _val
              );
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              __element_move(_pos, true, 1);
            );
          }
          increase_size(1);

          return iterator{
            _pos.__now, _pos.__first, _pos.__last, _pos.__cur
          };
        }
        iterator behavior_insert(
          behavior _be, const_iterator _pos, value_type&& _val
        )
        {
          using algorithm::move;

          size_type __offset = _iterator_offset(_pos);

          if(_be == behavior::back)
          {
            __check_request(1, false);
            _pos = begin() + __offset;
            __element_move(_pos, false, 1);
            __UTILITY_TRY_BEGIN
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, move(_val)
              );
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              __element_move(_pos, false, 1);
            );
            set_end(++end());
          }
          else
          {
            __check_request(1, true);
            _pos = begin() + __offset;
            __element_move(--_pos, true, 1);
            __UTILITY_TRY_BEGIN
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, move(_val)
              );
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              __element_move(_pos, true, 1);
            );
            set_begin(--begin());
          }
          increase_size(1);

          return iterator{
            _pos.__now, _pos.__first, _pos.__last, _pos.__cur
          };
        }
        iterator behavior_insert(
          behavior _be, const_iterator _pos,
          size_type _count, const value_type& _val
        )
        {
          using algorithm::move;
          if(_count == 0)
          {
            return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          }

          size_type __offset = _iterator_offset(_pos);

          if(_be == behavior::back)
          {
            __check_request(_count, false);
            _pos = begin() + __offset;
            __element_move(_pos, false, _count);
            __UTILITY_TRY_DEFINE(const_iterator, __rpos, _pos);
            __UTILITY_TRY_BEGIN
              for(size_type __i = 0; __i != _count; ++__i, ++_pos)
              {
                allocator_traits_type::construct(
                  __mis.second(), _pos.__now, _val
                );
              }
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              for(const_iterator __eit = __rpos; __eit != _pos; ++__eit)
              {
                allocator_traits_type::destroy(
                  __mis.second(), __eit.__now
                );
              }
              __element_move(__rpos, false, _count);
            );
            set_end(end() + _count);
            _pos -= _count;
            increase_size(_count);
            return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          }

          __check_request(_count, true);
          _pos = begin() + __offset;
          __element_move(--_pos, true, _count);
          __UTILITY_TRY_DEFINE(const_iterator, __rpos, _pos);
          __UTILITY_TRY_BEGIN
            for(size_type __i = 0; __i != _count; ++__i, --_pos)
            {
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, _val
              );
            }
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(const_iterator __eit = __rpos; __eit != _pos; --__eit)
            {
              allocator_traits_type::destroy(
                __mis.second(), __eit.__now
              );
            }
            __element_move(__rpos, false, _count);
          );
          set_begin(begin() -= _count);
          increase_size(_count);
          return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
        }
        template<
          typename _InputIterator,
          typename trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        iterator behavior_insert(
          behavior _be, const_iterator _pos,
          _InputIterator _first, _InputIterator _last
        )
        {
          if(_first == _last)
          {
            return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          }

          size_type __offset = _iterator_offset(_pos);
          size_type __len =
            static_cast<size_type>(helper::distance(_first, _last));

          if(_be == behavior::back)
          {
            __check_request(__len, false);
            _pos = begin() + __offset;
            __element_move(_pos, false, __len);
            __UTILITY_TRY_DEFINE(const_iterator, __rpos, _pos);
            __UTILITY_TRY_BEGIN
              for(size_type __i = 0; __i != __len; ++__i, ++_pos)
              {
                allocator_traits_type::construct(
                  __mis.second(), _pos.__now, *_first++
                );
              }
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              for(const_iterator __eit = __rpos; __eit != _pos; ++__eit)
              {
                allocator_traits_type::destroy(
                  __mis.second(), __eit.__now
                );
              }
              __element_move(__rpos, false, __len);
            );
            set_end(end() + __len);
            _pos -= __len;
            increase_size(__len);
            return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          }
          __check_request(__len, true);
          _pos = begin() + __offset;
          __element_move(--_pos, true, __len);
          __UTILITY_TRY_DEFINE(const_iterator, __rpos, _pos);
          __UTILITY_TRY_BEGIN
            for(size_type __i = 0; __i != __len; ++__i, --_pos)
            {
              allocator_traits_type::construct(
                __mis.second(), _pos.__now, *(--_last)
              );
            }
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(const_iterator __eit = __rpos; __eit != _pos; --__eit)
            {
              allocator_traits_type::destroy(
                __mis.second(), __eit.__now
              );
            }
            __element_move(__rpos, false, __len);
          );
          set_begin(begin() -= __len);
          increase_size(__len);
          return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
        }

      public:
        template<typename... _Args>
        iterator behavior_emplace(
          behavior _be, const_iterator _pos, _Args&&... _args
        )
        {
          using algorithm::move;

          size_type __offset = _iterator_offset(_pos);

          if(_be == behavior::back)
          {
            __check_request(1, false);
            _pos = begin() + __offset;
            __element_move(_pos, false, 1);
            allocator_traits_type::construct(
              __mis.second(), _pos.__now, move(_args)...
            );
            set_end(++end());
          }
          else
          {
            __check_request(1, true);
            _pos = begin() + __offset;
            __element_move(--_pos, true, 1);
            allocator_traits_type::construct(
              __mis.second(), _pos.__now, move(_args)...
            );
            set_begin(--begin());
          }
          increase_size(1);

          return iterator{
            _pos.__now, _pos.__first, _pos.__last, _pos.__cur
          };
        }

      public:
        iterator behavior_erase(behavior _be, const_iterator _pos) noexcept
        {
          allocator_traits_type::destroy(
            __mis.second(), _pos.__now
          );
          if(_be == behavior::back)
          {
            set_end(--end());
            __element_move_release(_pos, false, 1);
          }
          else
          {
            set_begin(++begin());
            __element_move_release(_pos++, true, 1);
          }
          decrease_size(1);

          return iterator{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
        }
        iterator behavior_erase(
          behavior _be, const_iterator _first, const_iterator _last
        ) noexcept
        {
          if(_first == _last)
          {
            return iterator{
              _first.__now, _first.__first, _first.__last, _first.__cur
            };
          }
          size_type __len =
            reinterpret_cast<size_type>(helper::distance(_first, _last));
          const_iterator __pos = _first;
          for(; __pos != _last; ++__pos)
          {
            allocator_traits_type::destroy(
              __mis.second(), __pos.__now
            );
          }
          decrease_size(__len);
          if(_be == behavior::back)
          {
            set_end(end() -= __len);
            __element_move_release(_first, false, __len);
            return iterator{
              _first.__now, _first.__first, _first.__last, _first.__cur
            };
          }
          set_begin(begin() += __len);
          __element_move_release(__pos--, true, __len);
          return iterator{
            _last.__now, _last.__first, _last.__last, _last.__cur
          };
        }

      public:
        iterator insert(const_iterator _pos, const value_type& _val)
        { return behavior_insert(_behavior(_pos), _pos, _val);}
        iterator insert(const_iterator _pos, value_type&& _val)
        {
          using algorithm::move;
          return behavior_insert(_behavior(_pos), _pos, move(_val));
        }
        iterator insert(
          const_iterator _pos, size_type _count, const value_type& _val
        )
        { return behavior_insert(_behavior(_pos), _pos, _count, _val);}
        template<
          typename _InputIterator,
          typename trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        iterator insert(
          const_iterator _pos, _InputIterator _first, _InputIterator _last
        )
        { return behavior_insert(_behavior(_pos), _pos, _first, _last);}
        iterator insert(
          const_iterator _pos, initializer_list<value_type> _init
        )
        {
          return behavior_insert(
            _behavior(_pos), _pos, _init.begin(), _init.end()
          );
        }

      public:
        template<typename... _Args>
        iterator emplace(const_iterator _pos, _Args&&... _args)
        {
          using algorithm::move;
          return behavior_emplace(_behavior(_pos), _pos, move(_args)...);
        }

      public:
        iterator erase(const_iterator _pos) noexcept
        { return behavior_erase(_behavior(_pos), _pos);}
        iterator erase(const_iterator _first, const_iterator _last) noexcept
        { return behavior_erase(_behavior(_first, _last), _first, _last);}

      public:
        void clear() noexcept
        {
          if(this->empty())
          { return;}
          iterator __eit = begin();
          for(iterator __tit = end(); __eit != __tit; ++__eit)
          {
            allocator_traits_type::destroy(
              __mis.second(), __eit.__now
            );
          }
          set_size(0);
          __map_ecur = __map_cur;
          __data_end = __data_begin;
        }
        void resize(size_type _count)
        {
          size_type __size = size();
          if(__size > _count)
          {
            iterator __eit = begin() + _count;
            for(iterator __eeit = end(); __eit != __eeit; ++__eit)
            {
              allocator_traits_type::destroy(
                __mis.second(), __eit.__now
              );
            }
            set_end(begin() + _count);
          }
          else if (__size < _count)
          {
            size_type __offset = _count - __size;
            __check_request(__offset, false);
            iterator __cit = end();
            __UTILITY_TRY_BEGIN
              for(size_type __i = 0; __i != __offset; ++__i, ++__cit)
              {
                allocator_traits_type::construct(
                  __mis.second(), __cit.__now
                );
              }
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              iterator __eit = end();
              for(; __eit != __cit; ++__eit)
              {
                allocator_traits_type::destroy(
                  __mis.second(), __eit.__now
                );
              }
            );
            set_end(__cit);
          }
          set_size(_count);
        }
        void resize(size_type _count, const value_type& _val)
        {
          size_type __size = size();
          if(__size > _count)
          {
            iterator __eit = begin() + _count;
            for(iterator __eeit = end(); __eit != __eeit; ++__eit)
            {
              allocator_traits_type::destroy(
                __mis.second(), __eit.__now
              );
            }
            set_end(begin() + _count);
          }
          else if (__size < _count)
          {
            size_type __offset = _count - __size;
            __check_request(__offset, false);
            iterator __cit = end();
            __UTILITY_TRY_BEGIN
              for(size_type __i = 0; __i != __offset; ++__i, ++__cit)
              {
                allocator_traits_type::construct(
                  __mis.second(), __cit.__now, _val
                );
              }
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              iterator __eit = end();
              for(; __eit != __cit; ++__eit)
              {
                allocator_traits_type::destroy(
                  __mis.second(), __eit.__now
                );
              }
            );
            set_end(__cit);
          }
          set_size(_count);
        }
        void shrink_to_fit()
        {
          using memory::unique_ptr;
          using container::helper::allocator_deleter;

          size_type __cap = __map_aecur-__map_acur;
          if(__cap == 0)
          { return;}
          unique_ptr<pointer, allocator_deleter<map_allocator_type>>
            __map_container{map_allocator_traits_type::allocate(
              __base.second(), __cap
            ), allocator_deleter<map_allocator_type>{__base.second(), map_capacity()}
          };
          for(; __map_acur != __data_begin; ++__map_acur)
          { deallocate_container(*__map_acur);}
          for(; __map_aecur != __data_end; --__map_aecur)
          { deallocate_container(*__map_aecur);}

          map_pointer __new_cur = __map_container.get();
          __map_acur = __new_cur;
          for(; __map_cur != __map_aecur;)
          { *__new_cur++ = *__map_cur++;}
          map_allocator_traits_type::deallocate(
            __base.second(), __base.first(), map_capacity()
          );
          __base.first() = __map_container.release();
          __map_cur = __map_acur;
          __map_cap = __map_aecur = __new_cur;
          __map_ecur = --__new_cur;
        }


      public:
        inline bool empty() const noexcept
        { return __mis.first() == 0;}
        inline size_type size() const noexcept
        { return __mis.first();}

      private:
        size_type map_capacity() const noexcept
        { return __map_cap - __base.first();}
        void give_up() noexcept
        {
          if(__map_acur != nullptr)
          {
            this->clear();
            for(; __map_acur != __map_aecur; ++__map_acur)
            { this->deallocate_container(*__map_acur);}
            map_allocator_traits_type::deallocate(
              __base.second(), __base.first(), map_capacity()
            );
          }
        }

      public:
        inline size_type _iterator_offset(const_iterator _it) const noexcept
        {
          if(__base.first() == nullptr)
          { return 0;}
          size_type __map_len = _it.__cur - __map_cur;
          size_type __cur_len = _it.__now - _it.__first;
          size_type __dbegin_len = __data_begin - (*__map_cur);
          return __map_len * _sequence_length + __cur_len - __dbegin_len;
        }
        inline behavior _behavior(const_iterator _it) const noexcept
        {
          return (_iterator_offset(_it) << 1) < __mis.first() ?
              behavior::front : behavior::back;
        }
        inline bool _behavior(
          const_iterator _first, const_iterator _last
        ) const noexcept
        {
          size_type __flot = _iterator_offset(_first);
          size_type __llot = _iterator_offset(_last);
          return __flot < size() - __llot ? behavior::front : behavior::back;
        }

      private:
        void __element_move(
          const_iterator _pos, bool _direct, size_type _offset
        ) noexcept
        {
          using helper::underly_move;
          iterator __it{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          if(_direct)
          {
            iterator __rit = begin();
            iterator __dit = __rit - _offset;
            for(; __rit <= __it; ++__rit, ++__dit)
            { underly_move<value_type>(__dit.__now, __rit.__now);}
          }
          else
          {
            iterator __rit = end();
            iterator __dit = __rit + _offset;
            for(; __rit > __it; --__rit, --__dit)
            { underly_move<value_type>(__dit.__now, __rit.__now);}
          }
        }
        void __element_move_release(
          const_iterator _pos, bool _direct, size_type _offset
        ) noexcept
        {
          using helper::underly_move;
          iterator __it{_pos.__now, _pos.__first, _pos.__last, _pos.__cur};
          if(_direct)
          {
            iterator __rit = begin();
            iterator __dit = __rit - _offset;
            for(; __rit <= __it; ++__rit, ++__dit)
            { underly_move<value_type>(__rit.__now, __dit.__now);}
          }
          else
          {
            iterator __rit = end();
            iterator __dit = __rit + _offset;
            for(; __rit > __it; --__rit, --__dit)
            { underly_move<value_type>(__rit.__now, __dit.__now);}
          }
        }

      private:
        inline void set_begin(iterator _it) noexcept
        {
          __map_cur = _it.__cur;
          __data_begin = _it.__now;
        }
        inline void set_end(iterator _it) noexcept
        {
          __map_ecur = _it.__cur;
          __data_end = _it.__now;
        }

      public:
        inline void increase_size(size_type _many) noexcept
        { __mis.first() += _many;}
        inline void decrease_size(size_type _many) noexcept
        { __mis.first() -= _many;}
        inline void set_size(size_type _many) noexcept
        { __mis.first() = _many;}

      private:
        size_type find_usable_node(bool _direct) noexcept
        {
          if(_direct)
          {
            if(__data_begin == nullptr)
            { return 0;}
            return (__data_begin - *__map_cur) +
                   (__map_acur-__map_cur)*_sequence_length;
          }
          else
          {
            if(__data_end == nullptr)
            { return 0;}
            return (__map_aecur-__map_ecur)*_sequence_length -
                   (__data_end - *__map_ecur);

          }
        }
        size_type find_free_map(bool _direct) noexcept
        {
          if(_direct)
          {
            if(__data_begin == nullptr)
            { return 0;}
            return static_cast<size_type>(__map_acur - __base.first());
          }
          else
          {
            if(__data_end == nullptr)
            { return 0;}
            return static_cast<size_type>(__map_cap - __map_aecur);
          }
        }

      private:
        void __check_request(size_type _nodes, bool _direct)
        {
          size_type __vaild = find_usable_node(_direct);
          if(__vaild < _nodes)
          { __request(_nodes-__vaild, _direct);}

          return ;
        }
        void __request(size_type _nodes, bool _direct)
        {
          size_type __request_map = _nodes / _sequence_length + 1;
          size_type __free_map = find_free_map(_direct);
          if(__free_map < __request_map)
          { reallocate(__request_map, 4, _direct, true);}
          else
          { reallocate(__request_map, 0, _direct, false);}
        }
        void reallocate(
          size_type _request_maps, size_type _map_empty,
          bool _direct, bool _realloc
        )
        {
          using memory::unique_ptr;
          using container::helper::allocator_deleter;
          if(_direct) // front allocate
          {
            if(_realloc)
            {
              size_type __cap = this->map_capacity();
              unique_ptr<pointer, allocator_deleter<map_allocator_type>>
                __map_container{map_allocator_traits_type::allocate(
                  __base.second(), __cap+_request_maps+_map_empty
                ), allocator_deleter<map_allocator_type>{__base.second(), map_capacity()}
              };
              map_pointer __ptr = __map_container.get() + _map_empty;
              __UTILITY_TRY_BEGIN
                for(size_type __i = 0; __i < _request_maps; ++__i)
                { *__ptr++ = allocate_conatiner();}
              __UTILITY_TRY_END
              __UTILITY_CATCH(...)
              __UTILITY_CATCH_UNWIND(
                for(map_pointer __eptr = __map_container.get()+_map_empty; __eptr < __ptr;)
                { deallocate_container(*__eptr++);}
              );
              for(map_pointer __dptr = __map_acur; __dptr != __map_aecur;)
              { *__ptr++ = *__dptr++;}
              map_pointer __map_base = __map_container.release();
              __map_cap = __map_base + __cap+_request_maps+_map_empty;
              difference_type __vaild_offset = __map_cur - __map_acur;
              difference_type __used_offset = __map_ecur - __map_cur;
              map_allocator_traits_type::deallocate(
                __base.second(), __base.first(), map_capacity()
              );
              __base.first() = __map_base;
              __map_acur = __map_base + _map_empty;
              __map_cur = __map_acur + _request_maps + __vaild_offset;
              __map_ecur = __map_cur + __used_offset;
              __map_aecur = __ptr;
              if(__data_begin == nullptr)
              {
                __map_cur = __map_ecur = __map_aecur;
                __data_begin = *__map_cur = nullptr;
              }
            }
            else
            {
              map_pointer __dptr = __map_acur-1;
              __UTILITY_TRY_BEGIN
                for(size_type __i = 0; __i != _request_maps; ++__i, --__dptr)
                { *__dptr = allocate_conatiner();}
              __UTILITY_TRY_END
              __UTILITY_CATCH(...)
              __UTILITY_CATCH_UNWIND(
                for(map_pointer __eptr = __map_acur-1; __eptr > __dptr; --__eptr)
                { deallocate_container(*__eptr);}
              );
              __map_acur = __dptr;
            }
          }
          else
          {
            if(_realloc)
            {
              size_type __cap = this->map_capacity();
              unique_ptr<pointer, allocator_deleter<map_allocator_type>>
                __map_container{map_allocator_traits_type::allocate(
                  __base.second(), __cap+_request_maps+_map_empty
                ), allocator_deleter<map_allocator_type>{__base.second(), map_capacity()}
              };
              map_pointer __ptr = __map_container.get() + __cap+_request_maps;
              __UTILITY_TRY_BEGIN
                for(size_type __i = 0; __i < _request_maps; ++__i)
                { *--__ptr = allocate_conatiner();}
              __UTILITY_TRY_END
              __UTILITY_CATCH(...)
              __UTILITY_CATCH_UNWIND(
                for(map_pointer __eptr = __map_container.get() + __cap +_request_maps;
                    __eptr > __ptr;)
                { deallocate_container(*--__eptr);}
              );
              for(map_pointer __dptr = __map_aecur; __dptr != __map_acur;)
              { *--__ptr = *--__dptr;}

              map_pointer __map_base = __map_container.release();
              __map_cap = __map_base + __cap+_request_maps+_map_empty;
              difference_type __vaild_offset = __map_ecur - __map_cur;
              difference_type __used_offset = __map_cur - __map_acur;
              map_allocator_traits_type::deallocate(
                __base.second(), __base.first(), map_capacity()
              );
              __base.first() = __map_base;
              __map_acur = __ptr;
              __map_aecur = __map_base + __cap + _request_maps;
              __map_cur = __map_acur + __used_offset;
              __map_ecur = __map_cur + __vaild_offset;
              if(__data_begin == nullptr)
              {
                __data_begin = *__map_cur;
                __data_end = *__map_cur;
              }
            }
            else
            {
              map_pointer __dptr = __map_aecur;
              __UTILITY_TRY_BEGIN
                for(size_type __i = 0; __i < _request_maps; ++__i, ++__dptr)
                { *__dptr = allocate_conatiner();}
              __UTILITY_TRY_END
              __UTILITY_CATCH(...)
              __UTILITY_CATCH_UNWIND(
                for(map_pointer __eptr = __map_aecur; __eptr < __dptr; ++__eptr)
                { deallocate_container(*__eptr);}
              );
              __map_aecur = __dptr;
            }
          }
          if(__data_end == nullptr)
          { __data_end = *__map_ecur;}
        }

      __utility_extra:
        __UTILITY_CPP17_INLINE__
        constexpr static size_type _sequence_length =
          __detail::deque_buffer_size<value_type, _Block>();

      private:
        inline pointer allocate_conatiner()
        {
          return allocator_traits_type::allocate(
            __mis.second(), _sequence_length
          );
        }
        inline void deallocate_container(pointer _chunk)
        {
          allocator_traits_type::deallocate(
            __mis.second(), _chunk, _sequence_length
          );
        }
    };

    // test bug assert failed
    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator==(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    {
      using algorithm::equal;
      using algorithm::equal_to;
      return _x.size() == _y.size() && equal(
        _x.begin(), _x.end(), _y.begin(), equal_to<_T>{}
      );
    }
    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator!=(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    { return !(_x == _y);}

    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator<(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    {
      using algorithm::lexicographical_compare;
      return lexicographical_compare(
        _x.begin(), _x.end(), _y.begin(), _y.end(), algorithm::less<_T>{}
      );
    }
    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator>(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    { return _y < _x;}
    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator<=(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    { return !(_y < _x);}
    template<
      typename _T, typename _Alloc,
      unsigned long _Block1, unsigned long _Block2
    >
    bool operator>=(
      const deque<_T, _Alloc, _Block1>& _x,
      const deque<_T, _Alloc, _Block2>& _y
    )
    { return !(_x < _y);}
  }
}

#endif // ! __UTILITY_CONTAINER_DEQUE__
