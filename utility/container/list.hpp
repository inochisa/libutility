
#ifndef __UTILITY_CONTAINER_LIST__
#define __UTILITY_CONTAINER_LIST__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/equal.hpp>
#include<utility/algorithm/lexicographical_compare.hpp>
#include<utility/container/container_helper.hpp>
#include<utility/container/initializer_list.hpp>
#include<utility/container/pair.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/unique_ptr.hpp>
#include<utility/memory/basic_deallocator.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/distance.hpp>
#include<utility/iterator/next.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _T,
      typename _Alloc = utility::memory::allocator<_T>
    >
    class list
    {
      private:
        template<typename __Value>
        struct __list_node
        {
          typedef __list_node*  __node_link;
          typedef __Value       __value_type;

          __node_link     __prev;
          __node_link     __next;
          __value_type*   __data;
          __list_node() = default;
          __list_node(__node_link __p, __node_link __n):
            __prev(__p), __next(__n), __data(nullptr)
          { }

          UTILITY_ALWAYS_INLINE
          inline void reverse()
          { utility::algorithm::swap(__prev, __next);}
        };
      private:
        template<typename __Value>
        class __list_iterator
        {
          private:
            template<typename>
            friend class __list_const_iterator;
            template<typename, typename>
            friend class list;
          public:
            typedef utility::iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Value value_type;
            typedef value_type& reference;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<__Value*>::pointer pointer;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<__Value*>::difference_type difference_type;

          public:
            typedef __list_iterator<__Value>  self;

          private:
            typedef __list_node<value_type>* __link_type;

          private:
            __link_type __ptr;

          public:
            inline __list_iterator() noexcept:
              __ptr(nullptr)
            { }
            inline explicit __list_iterator(__link_type __link) noexcept:
              __ptr(__link)
            { }
            ~__list_iterator()
            { }

          public:
            self& operator=(const self& __other)
            {
              if(this != &__other)
              { this->__ptr = __other.__ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__ptr->__data);}
            pointer operator->() const
            { return this->__ptr->__data;}

          public:
            self& operator++()
            {
              this->__ptr = this->__ptr->__next;
              return *this;
            }
            self operator++(int)
            {
              self __it = *this;
              this->__ptr = this->__ptr->__next;
              return __it;
            }
            self& operator--()
            {
              this->__ptr = this->__ptr->__prev;
              return *this;
            }
            self operator--(int)
            {
              self __it = *this;
              this->__ptr = this->__ptr->__prev;
              return __it;
            }

          public:
            bool operator==(const self& __o) const
            { return this->__ptr == __o.__ptr;}
            bool operator!=(const self& __o) const
            { return !(this->operator==(__o));}

        };
        template<typename __Value>
        class __list_const_iterator
        {
          private:
            template<typename, typename>
            friend class list;
          public:
            typedef utility::iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Value value_type;
            typedef const value_type const_value_type;
            typedef const value_type& reference;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<const_value_type*>::pointer
              pointer;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<const_value_type*>::difference_type
              difference_type;

            public:
              typedef __list_const_iterator<__Value>  self;

            private:
              typedef __list_node<value_type>* __link_type;

            private:
              __link_type __ptr;

            public:
              inline __list_const_iterator() noexcept:
                __ptr(nullptr)
              { }
              inline explicit __list_const_iterator(__link_type __link) noexcept:
                __ptr(__link)
              { }
              inline __list_const_iterator(const __list_iterator<__Value>& __it) noexcept:
                __ptr(__it.__ptr)
              { }

              inline
              ~__list_const_iterator()
              { }

            public:
              self& operator=(const self& __other)
              {
                if(this != &__other)
                { this->__ptr = __other.__ptr;}
                return *this;
              }

            public:
              reference operator*() const
              { return *(this->__ptr->__data);}
              pointer operator->() const
              { return this->__ptr->__data;}

            public:
              self& operator++()
              {
                this->__ptr = this->__ptr->__next;
                return *this;
              }
              self operator++(int)
              {
                self __it = *this;
                this->__ptr = this->__ptr->__next;
                return __it;
              }
              self& operator--()
              {
                this->__ptr = this->__ptr->__prev;
                return *this;
              }
              self operator--(int)
              {
                self __it = *this;
                this->__ptr = this->__ptr->__prev;
                return __it;
              }

            public:
              bool operator==(const self& __o) const
              { return this->__ptr == __o.__ptr;}
              bool operator!=(const self& __o) const
              { return !(this->operator==(__o));}
          };

      private:
        typedef __list_node<_T>   __node_type;
        typedef __node_type*      __link_type;
        typedef utility::memory::allocator<__node_type>
          __node_allocator_type;
        typedef utility::memory::allocator_traits<__node_allocator_type>
          __node_allocator_traits_type;

      public:
        typedef _T                    value_type;
        typedef _Alloc                allocator_type;
        typedef utility::size_t     size_type;
        typedef utility::ptrdiff_t  difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;

      public:
        typedef utility::memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef __list_iterator<value_type> iterator;
        typedef
          utility::iterator::reverse_iterator<iterator> reverse_iterator;
        typedef __list_const_iterator<value_type> const_iterator;
        typedef
          utility::iterator::reverse_iterator<const_iterator> const_reverse_iterator;

      public: // assert
        static_assert(::utility::trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        typedef utility::memory::unique_ptr<value_type>
          __value_container;
        typedef utility::memory::unique_ptr<__node_type>
          __node_container;

      private:
        __link_type __base;
        size_type __size;
        allocator_type __allocator;
        __node_allocator_type __node_allocator;

      public:
        list(): list(allocator_type())
        { }
        explicit list(const allocator_type& __alloc):
          __size(0), __allocator(__alloc), __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
        }

        explicit list(
          size_type __count,
          const value_type& __val,
          const allocator_type& __alloc = allocator_type()
        ): __size(0), __allocator(__alloc), __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(; __count > 0; --__count)
          { this->push_back(__val);}
        }

        explicit list(
          size_type __count,
          const allocator_type& __alloc = allocator_type()
        ): __size(0), __allocator(__alloc), __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(; __count > 0; --__count)
          { this->emplace_back();}
        }

        template<typename _Inputiterator,
          typename
          utility::trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
            bool
          >::type = true
        >
        explicit list(_Inputiterator __first, _Inputiterator __last,
          const allocator_type __alloc = allocator_type()
        ): __size(0), __allocator(__alloc), __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(; __first != __last; ++__first)
          { this->push_back(*__first);}
        }

        list(const list& __other):
          __size(0), __allocator(__other.__allocator),
          __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(const_iterator __it = __other.begin();
            __it != __other.end(); ++__it)
          { this->push_back(*__it);}
        }
        list(const list& __other, const allocator_type& __alloc):
          __size(0), __allocator(__alloc),
          __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(const_iterator __it = __other.begin();
            __it != __other.end(); ++__it)
          { this->push_back(*__it);}
        }

        list(list&& __other):
          __base(__other.__base), __size(__other.__size),
          __allocator(::utility::algorithm::move(__other.__allocator)),
          __node_allocator()
        { __other.__base = nullptr;}
        list(list&& __other, const allocator_type& __alloc):
          __base(__other.__base), __size(__other.__size),
          __allocator(::utility::algorithm::move(__other.__allocator)),
          __node_allocator()
        { __other.__base = nullptr;}

        list(initializer_list<value_type> __initlist,
          const allocator_type& __alloc = allocator_type()
        ): __size(0U), __allocator(__alloc), __node_allocator()
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __base->__prev = __base->__next = __base;
          for(typename initializer_list<value_type>::iterator __it = __initlist.begin();
            __it != __initlist.end(); ++__it)
          { this->push_back(*__it);}
        }

        ~list()
        {
          if(this->__base != nullptr)
          { this->force_clear();}
        }

      //!< \todo this part is not well prepared
      public:
        list& operator=(const list& __other)
        {
          if(&__other != this)
          {
            this->__allocator = __other.__allocator;
            this->__node_allocator = __other.__node_allocator;
            // is this needed?
            if(this->__base == nullptr)
            {
              this->__base =
                __node_allocator_traits_type::allocate(this->__node_allocator);
              this->__size = 0U;
              __base->__prev = __base->__next = __base;
            }
            this->assign(__other.begin(), __other.end());
          }
          return *this;
        }
        list& operator=(list&& __other)
        {
          if(&__other != this)
          {
            this->force_clear();
            this->__base = __other.__base;
            this->__size = __other.__size;
            this->__allocator =
              utility::algorithm::move(__other.__allocator);
            this->__node_allocator =
              utility::algorithm::move(__other.__node_allocator);
            __other.__base = nullptr;
          }
          return *this;
        }
        list& operator=(initializer_list<value_type> __initlist)
        {
          this->assign(__initlist.begin(), __initlist.end());
          return *this;
        }

      public:
        void assign(size_type __count, const value_type& __val)
        {
          iterator __begin = this->begin();
          iterator __end = this->end();
          for(; __begin != __end && __count; ++__begin, --__count)
          { *__begin = __val;}
          if(__count)
          {
            for(; __count; --__count)
            { this->push_back(__val);}
          }
          else
          { this->erase(__begin, __end);}
        }
        template<typename _Inputiterator>
        typename
        utility::trait::type::miscellaneous::enable_if<
          is_iterator<_Inputiterator>::value,
          void
        >::type
        assign(_Inputiterator __first, _Inputiterator __last)
        {
          iterator __begin = this->begin();
          iterator __end = this->end();
          for(; __begin != __end && __first != __last; ++__begin, ++__first)
          { *__begin = *__first;}
          if(__begin == __end)
          { this->insert(__end, __first, __last);}
          else
          { this->erase(__begin, __end);}
        }
        void assign(initializer_list<value_type> __initlist)
        { this->assign(__initlist.begin(), __initlist.end());}

      public:
        allocator_type get_allocator() const
        { return this->__allocator;}
        void change_allocator(const allocator_type& __alloc)
        { this->__allocator = __alloc;}

      public:
        reference front() noexcept
        { return *(__base->__next->__data);}
        const_reference front() const noexcept
        { return *(__base->__next->__data);}
        reference back() noexcept
        { return *(__base->__prev->__data);}
        const_reference back() const noexcept
        { return *(__base->__prev->__data);}


      public:
        iterator begin() noexcept
        { return iterator(__base->__next);}
        const_iterator begin() const noexcept
        { return const_iterator(__base->__next);}
        const_iterator cbegin() const noexcept
        { return const_iterator(__base->__next);}
        iterator end() noexcept
        { return iterator(__base);}
        const_iterator end() const noexcept
        { return const_iterator(__base);}
        const_iterator cend() const noexcept
        { return const_iterator(__base);}

      public:
        reverse_iterator rbegin() noexcept
        { return reverse_iterator(this->end());}
        const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator(this->end());}
        const_reverse_iterator crbegin() const noexcept
        { return const_reverse_iterator(this->end());}
        reverse_iterator rend() noexcept
        { return reverse_iterator(this->begin());}
        const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator(this->begin());}
        const_reverse_iterator crend() const noexcept
        { return const_reverse_iterator(this->begin());}

      public:
        bool empty() const noexcept
        { return __base == __base->__next;}
        size_type size() const noexcept
        { return this->__size;}

      public:
        void push_front(const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, this->__base->__next);
          ++(this->__size);
        }
        void push_front(value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__val));
          __node_insert(__ulink, this->__base->__next);
          ++(this->__size);
        }
        void push_back(const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, this->__base);
          ++(this->__size);
        }
        void push_back(value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__val));
          __node_insert(__ulink, this->__base);
          ++(this->__size);
        }

      public:
        template<typename... _Args>
        iterator emplace(const_iterator __pos ,_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__args)...);
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__size);
          return iterator(__pos.__ptr);
        }
        template<typename... _Args>
        reference emplace_front(_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__args)...);
          __node_insert(__ulink, this->__base->__next);
          ++(this->__size);
          return *(this->__base->__next->__data);
        }
        template<typename... _Args>
        reference emplace_back(_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__args)...);
          __node_insert(__ulink, this->__base);
          ++(this->__size);
          return *(this->__base->__prev->__data);
        }

      public:
        void pop_front()
        {
          __link_type __dlink = this->__base->__next;
          __node_connect(this->__base, this->__base->__next->__next);
          allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
          __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
          --(this->__size);
        }
        void pop_back()
        {
          __link_type __dlink = this->__base->__prev;
          __node_connect(this->__base->__prev->__prev, this->__base);
          allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
          __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
          --(this->__size);
        }

      public:
        iterator insert(const_iterator __pos, const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__size);
          return iterator(__ulink);
        }
        iterator insert(const_iterator __pos, value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(::utility::algorithm::move(__val));
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__size);
          return iterator(__ulink);
        }
        iterator insert(const_iterator __pos,
          size_type __count, const value_type& __val)
        {
          if(__count == 0)
          { return iterator(__pos.__ptr);}
          utility::container::pair<__link_type, __link_type> __chain =
            this->__allocate_node_chain(__count, __val);
          __link_type __tpos =__pos.__ptr;
          __node_connect(__tpos->__prev, __chain.first);
          __node_connect(__chain.second, __tpos);
          this->__size += __count;
          return iterator(__chain.first);
        }

        template<typename _Inputiterator,
          typename utility::trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
          bool>::type = true
        >
        iterator insert(const_iterator __pos,
          _Inputiterator __first, _Inputiterator __last)
        {
          if(__first == __last)
          { return iterator(__pos.__ptr);}
          utility::container::pair<__link_type, __link_type> __chain =
            this->__allocate_node_chain(__first, __last);
          __link_type __tpos = __pos.__ptr;
          __node_connect(__tpos->__prev, __chain.first);
          __node_connect(__chain.second, __tpos);
          this->__size += utility::iterator::distance(__first, __last);
          return iterator(__chain.first);
        }
        inline iterator insert(const_iterator __pos,
          initializer_list<value_type> __initlist)
        { return this->insert(__pos, __initlist.begin(), __initlist.end());}

      public:
        void clear() noexcept
        {
          if(!(this->empty()))
          {
            __link_type __tmp = this->__base->__prev;
            __link_type __dtmp = this->__base->__prev->__prev;
            for(;__tmp != __base;)
            {
              __tmp->__next = __tmp->__prev = nullptr;
              allocator_traits_type::deallocate(this->__allocator, __tmp->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __tmp);
              __tmp = __dtmp;
              __dtmp = __dtmp->__prev;
            }
            this->__size = 0U;
            this->__base->__prev = this->__base->__next = this->__base;
          }
        }
        void resize(size_type __count)
        {
          if(__count > this->__size)
          {
            for(;__count != this->__size;)
            { this->emplace_back();}
            return;
          }
          for(;__count != this->__size;)
          { this->pop_back();}
        }
        void resize(size_type __count, const value_type& __val)
        {
          if(__count > this->__size)
          {
            for(;__count != this->__size;)
            { this->push_back(__val);}
            return;
          }
          for(;__count != this->__size;)
          { this->pop_back();}
        }
        iterator erase(const_iterator __pos)
        {
          __link_type __dlink = __pos.__ptr;
          __link_type __elink = __dlink->__next;
          __node_connect(__dlink->__prev, __dlink->__next);
          __dlink->__prev = __dlink->__next = nullptr;
          allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
          __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
          --(this->__size);
          return iterator(__elink);
        }
        iterator erase(const_iterator __first, const_iterator __last)
        {
          __link_type __elink = __last.__ptr;
          if(__first != __last)
          {
            __link_type __dlink = __first.__ptr;
            __link_type __tlink = __dlink->__next;
            __node_connect(__dlink->__prev, __elink);
            for(;__dlink != __elink;)
            {
              __dlink->__prev = __dlink->__next = nullptr;
              allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
              __dlink = __tlink;
              __tlink = __tlink->__next;
              --(this->__size);
            }
          }
          return iterator(__elink);
        }

      public:
        void swap(list& __other) noexcept
        {
          using utility::algorithm::swap;
          swap(this->__base, __other.__base);
        }

      public:
        void reverse() noexcept
        {
          __link_type __tlink = this->__base;
          __tlink->reverse();
          __tlink = __tlink->__prev;
          for(;__tlink != this->__base;)
          {
            __tlink->reverse();
            __tlink = __tlink->__prev;
          }
        }

      public:
        void splice(const_iterator __pos, list& __con)
        {
          if(!__con.empty() && (&__con != this))
          {
            __link_type __plink = __pos.__ptr;
            __node_connect(__plink->__prev, __con.__base->__next);
            __node_connect(__con.__base->__prev, __plink);
            __con.__base->__prev = __con.__base->__next = __con.__base;
            this->__size += __con.__size;
            __con.__size = 0;
          }
        }
        void splice(const_iterator __pos, list& __con, const_iterator __it)
        {
          if(!__con.empty())
          {
            __link_type __plink = __pos.__ptr;
            __link_type __tlink = __it.__ptr;
            __node_connect(__tlink->__prev, __tlink->__next);
            __node_connect(__plink->__prev, __tlink);
            __node_connect(__tlink, __plink);
            ++(this->__size); --(__con.__size);
          }
        }
        void splice(const_iterator __pos, list& __con,
          const_iterator __first, const_iterator __last)
        {
          if(!__con.empty() && (__first != __last))
          {
            size_type __dist = utility::iterator::distance(__first, __last);
            __link_type __plink = __pos.__ptr;
            __link_type __tflink = __first.__ptr;
            __link_type __tllink = __last.__ptr->__prev;
            __node_connect(__tflink->__prev, __tllink->__next);
            __node_connect(__plink->__prev, __tflink);
            __node_connect(__tllink, __plink);
            this->__size += __dist;
            __con.__size -= __dist;
          }
        }
        void splice(const_iterator __pos, list&& __con)
        { this->splice(__pos, __con);}
        void splice(const_iterator __pos, list&& __con, const_iterator __it)
        { this->splice(__pos, __con, __it);}
        void splice(const_iterator __pos, list&& __con,
          const_iterator __first, const_iterator __last)
        { this->splice(__pos, __con, __first, __last);}


      public:
        void remove(const value_type& __val)
        {
          __link_type __dlink = this->__base->__next;
          __link_type __tlink = this->__base->__next->__next;
          for(;__dlink != __base;)
          {
            if(*(__dlink->__data) == __val)
            {
              __node_connect(__dlink->__prev, __dlink->__next);
              __dlink->__prev = __dlink->__next = nullptr;
              allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
              --(this->__size);
            }
            __dlink = __tlink;
            __tlink = __tlink->__next;
          }
        }
        template<typename _UnaryPredicate>
        void remove(_UnaryPredicate __pred)
        {
          __link_type __dlink = this->__base->__next;
          __link_type __tlink = this->__base->__next->__next;
          for(;__dlink != __base;)
          {
            if(__pred(static_cast<const value_type&>(*(__dlink->__data))))
            {
              __node_connect(__dlink->__prev, __dlink->__next);
              __dlink->__prev = __dlink->__next = nullptr;
              allocator_traits_type::deallocate(this->__allocator, __dlink->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __dlink);
              --(this->__size);
            }
            __dlink = __tlink;
            __tlink = __tlink->__next;
          }
        }

      public:
        inline void merge(list& __other)
        { this->merge(__other, utility::algorithm::less<value_type>());}
        inline void merge(list&& __other)
        { this->merge(__other, utility::algorithm::less<value_type>());}
        template<typename _Compare>
        void merge(list& __other, _Compare __compare)
        {
          if(&__other != this)
          {
            __link_type __tlink = this->__base;
            for(iterator __it = __other.begin(); __it != __other.end();)
            {
              __tlink = __tlink->__next;
              if(__tlink == this->__base)
              {
                this->splice(this->end(), __other);
                return;
              }
              __link_type __ulink = __it.__ptr;
              if(__compare(*(__ulink->__data), *(__tlink->__data)))
              {
                ++__it;
                __node_insert(__ulink, __tlink);
              }
            }
            this->__size += __other.__size;
            __other.__size = 0U;
          }
        }
        template<typename _Compare>
        void merge(list&& __other, _Compare __compare)
        { this->merge(__other, __compare);}

      public:
        inline void sort()
        {
          __sort(
            this->__base->__next, this->__base->__prev,
            this->__size, utility::algorithm::less<value_type>()
          );
        }
        template<typename _Compare>
        inline void sort(_Compare __compare)
        {
          __sort(
            this->__base->__next, this->__base->__prev,
            this->__size, __compare
          );
        }

      public:
        inline void unique()
        { this->unique(::utility::algorithm::equal_to<value_type>());}
        template<typename _BinaryPredicate>
        void unique(_BinaryPredicate __binarypred)
        {
          for(iterator __it = this->begin(), __eit = this->end(); __it != __eit;)
          {
            iterator __tit = utility::iterator::next(__it);
            for(;__tit != __eit && __binarypred(*__it, *__tit); ++__tit);
            if(++__it != __tit)
            { __it = this->erase(__it, __tit);}
          }
        }
      private:
        // Only used whem the list is deallocated
        UTILITY_ALWAYS_INLINE
        inline void force_clear() noexcept
        {
          this->clear();
          __base->__prev = __base->__next = nullptr;
          __node_allocator_traits_type::deallocate(this->__node_allocator, __base);
        }
        UTILITY_ALWAYS_INLINE
        template<typename... _Args>
        inline __link_type __allocate_node(_Args&&... __args)
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__node_allocator)
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__allocator)
          );
          allocator_traits_type::construct(
            this->__allocator, __valc.get(),
            utility::algorithm::move(__args)...
          );
          __link_type __link = __node.release();
          __link->__data = __valc.release();
          return __link;
        }
        UTILITY_ALWAYS_INLINE
        inline utility::container::pair<__link_type, __link_type>
        __allocate_node_chain(size_type __count, const value_type& __val)
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__node_allocator)
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__allocator)
          );
          allocator_traits_type::construct(
            this->__allocator, __valc.get(), __val
          );
          __link_type __epos = __node.release();
          __epos->__data = __valc.release();
          __epos->__next = nullptr;
          size_type __now = 1U;
          __link_type __bpos = __epos;
          __UTILITY_TRY_BEGIN
            for(; __now != __count; ++__now)
            {
              __node.reset(
                __node_allocator_traits_type::allocate(this->__node_allocator)
              );
              __valc.reset(
                allocator_traits_type::allocate(this->__allocator)
              );
              allocator_traits_type::construct(
                this->__allocator, __valc.get(), __val
              );
              __node_connect(__epos, __node.release());
              __epos = __epos->__next;
              __epos->__next = nullptr;
              __epos->__data = __valc.release();
            }
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(; __bpos != nullptr; __bpos = __epos)
            {
              __epos = __bpos->__next;
              allocator_traits_type::deallocate(this->__allocator, __bpos->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __bpos);
            }
          );
          return utility::container::pair<__link_type, __link_type>(
            __bpos, __epos
          );
        }
        template<typename _Inputiterator,
          typename
          utility::trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
          bool>::type = true
        >
        utility::container::pair<__link_type, __link_type> __allocate_node_chain(
          _Inputiterator __first, _Inputiterator __last
        )
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__node_allocator)
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__allocator)
          );
          allocator_traits_type::construct(
            this->__allocator, __valc.get(), *__first
          );
          ++__first;
          __link_type __epos = __node.release();
          __epos->__data = __valc.release();
          __epos->__next = nullptr;
          __link_type __bpos = __epos;
          __UTILITY_TRY_BEGIN
            for(; __first != __last; ++__first)
            {
              __node.reset(
                __node_allocator_traits_type::allocate(this->__node_allocator)
              );
              __valc.reset(
                allocator_traits_type::allocate(this->__allocator)
              );
              allocator_traits_type::construct(
                this->__allocator, __valc.get(), *__first
              );
              __node_connect(__epos, __node.release());
              __epos = __epos->__next;
              __epos->__next = nullptr;
              __epos->__data = __valc.release();
            }
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(; __bpos != nullptr; __bpos = __epos)
            {
              __epos = __bpos->__next;
              allocator_traits_type::deallocate(this->__allocator, __bpos->__data);
              __node_allocator_traits_type::deallocate(this->__node_allocator, __bpos);
            }
          );
          return utility::container::pair<__link_type, __link_type>(
            __bpos, __epos
          );
        }
      private:
        // forward insert
        UTILITY_ALWAYS_INLINE
        static inline void __node_insert(__link_type __inserter,
          __link_type __pos) noexcept
        {
          __inserter->__prev = __pos->__prev;
          __inserter->__next = __pos;
          __pos->__prev = (__pos->__prev->__next = __inserter);
        }
        UTILITY_ALWAYS_INLINE
        static inline void __node_connect(
          __link_type __before, __link_type __after
        ) noexcept
        {
          __before->__next = __after;
          __after->__prev = __before;
        }
        UTILITY_ALWAYS_INLINE
        static inline __link_type __node_next(
          __link_type __link, size_type __length
        ) noexcept
        {
          for(difference_type __i = 0; __i < __length; ++__i)
          { __link = __link->__next;}
          return __link;
        }

      private:
        template<typename _Compare>
        static __link_type __sort(
          __link_type __first, __link_type __last,
          size_type __tsize, _Compare __compare
        )
        {
          if(__tsize < 2)
          { return __first;}
          if(__tsize == 2)
          {
            if(__compare(*(__last->__data), *(__first->__data)))
            { utility::algorithm::swap(__first->__data, __last->__data);}
            return __first;
          }
          size_type __len = __tsize / 2;
          __link_type __mid = __node_next(__first, __len);
          __first = __sort(__first, __mid->__prev, __len, __compare);
          __mid = __sort(__mid, __last, __tsize - __len, __compare);
          __last = __node_next(__mid, __tsize - __len - 1);
          return __merge(
            __first, __mid, __last, __compare
          );
        }

        template<typename _Compare>
        UTILITY_ALWAYS_INLINE
        static inline __link_type __merge(
          __link_type __first, __link_type __mid, __link_type __last,
          _Compare __compare
        )
        {
          if(__compare(*(__mid->__prev->__data), *(__mid->__data)))
          { return __first;}
          __node_connect(__mid->__prev, __last->__next);
          __link_type __res = __first;
          __link_type __elink = __last->__next;
          __link_type __tlink = __mid->__next;
          for(; __first != __elink && __mid != __elink;)
          {
            if(!__compare(*(__mid->__data), *(__first->__data)))
            { __first = __first->__next;}
            else
            {
              __node_connect(__first->__prev, __mid);
              __node_connect(__mid, __first);
              __mid = __tlink;
              __tlink = __tlink->__next;
              if(__first == __res)
              { __res = __res->__prev;}
            }
          }
          if(__mid != __elink)
          {
            __node_connect(__elink->__prev, __mid);
            __node_connect(__last, __elink);
          }
          return __res;
        }
    };

    template<typename _T, typename _Alloc>
    inline bool operator==(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    {
      return __x.size() == __y.size() &&
        utility::algorithm::equal(__x.begin(), __x.end(), __y.begin());
    }
    template<typename _T, typename _Alloc>
    inline bool operator!=(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    { return !(__x == __y);}
    template<typename _T, typename _Alloc>
    inline bool operator<(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    {
      return utility::algorithm::lexicographical_compare(
        __x.begin(), __x.end(), __y.begin(), __y.end()
      );
    }
    template<typename _T, typename _Alloc>
    inline bool operator>(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    { return __y < __x;}
    template<typename _T, typename _Alloc>
    inline bool operator<=(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    { return !(__y < __x);}
    template<typename _T, typename _Alloc>
    inline bool operator>=(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<typename _T, typename _Alloc>
    inline void swap(
      ::utility::container::list<_T, _Alloc>& __x,
      ::utility::container::list<_T, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_LIST__
