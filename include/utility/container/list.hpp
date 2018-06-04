
#ifndef __UTILITY_CONTAINER_LIST__
#define __UTILITY_CONTAINER_LIST__

/**
 * \file list.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#ifdef ___UTILITY__CHECK__USE__STD___

#include<list>

namespace utility
{
  namespace container
  {
    using std::list;
  }
}

#else // ___UTILITY__CHECK__USE__STD___

#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/equal.hpp>
#include<utility/algorithm/lexicographical_compare.hpp>

#include<utility/container/compressed_pair.hpp>
#include<utility/container/pair.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/unique_ptr.hpp>
#include<utility/memory/basic_deallocator.hpp>

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
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
      typename _Alloc = memory::allocator<_T>
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
          {
            using algorithm::swap;
            swap(__prev, __next);
          }
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
            typedef helper::bidirectional_iterator_tag
              iterator_category;
            typedef __Value value_type;
            typedef value_type& reference;
            typedef typename
              trait::miscellaneous::pointer_traits<__Value*>::pointer pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<__Value*>::difference_type difference_type;

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

          public:
            self& operator=(const self& __other) noexcept
            {
              if(this != &__other)
              { this->__ptr = __other.__ptr;}
              return *this;
            }

          public:
            reference operator*() const noexcept
            { return *(this->__ptr->__data);}
            pointer operator->() const noexcept
            { return this->__ptr->__data;}

          public:
            self& operator++() noexcept
            {
              this->__ptr = this->__ptr->__next;
              return *this;
            }
            self operator++(int) noexcept
            {
              self __it = *this;
              this->__ptr = this->__ptr->__next;
              return __it;
            }
            self& operator--() noexcept
            {
              this->__ptr = this->__ptr->__prev;
              return *this;
            }
            self operator--(int) noexcept
            {
              self __it = *this;
              this->__ptr = this->__ptr->__prev;
              return __it;
            }

          public:
            bool operator==(const self& __other) const noexcept
            { return this->__ptr == __other.__ptr;}
            bool operator!=(const self& __other) const noexcept
            { return !(this->operator==(__other));}

        };
        template<typename __Value>
        class __list_const_iterator
        {
          private:
            template<typename, typename>
            friend class list;
          public:
            typedef helper::bidirectional_iterator_tag
              iterator_category;
            typedef __Value value_type;
            typedef const value_type const_value_type;
            typedef const value_type& reference;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::pointer
              pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::difference_type
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

          public:
            self& operator=(const self& __other) noexcept
            {
              if(this != &__other)
              { this->__ptr = __other.__ptr;}
              return *this;
            }
            self& operator=(
              const __list_iterator<__Value>& __other
            ) noexcept
            {
              this->__ptr = __other.__ptr;
              return *this;
            }

          public:
            reference operator*() const noexcept
            { return *(this->__ptr->__data);}
            pointer operator->() const noexcept
            { return this->__ptr->__data;}

          public:
            self& operator++() noexcept
            {
              this->__ptr = this->__ptr->__next;
              return *this;
            }
            self operator++(int) noexcept
            {
              self __it = *this;
              this->__ptr = this->__ptr->__next;
              return __it;
            }
            self& operator--() noexcept
            {
              this->__ptr = this->__ptr->__prev;
              return *this;
            }
            self operator--(int) noexcept
            {
              self __it = *this;
              this->__ptr = this->__ptr->__prev;
              return __it;
            }

          public:
            bool operator==(const self& __other) const noexcept
            { return this->__ptr == __other.__ptr;}
            bool operator!=(const self& __other) const noexcept
            { return !(this->operator==(__other));}
        };

      private:
        typedef __list_node<_T>   __node_type;
        typedef __node_type*      __link_type;
        typedef memory::allocator<__node_type>
          __node_allocator_type;
        typedef memory::allocator_traits<__node_allocator_type>
          __node_allocator_traits_type;

      public:
        typedef _T                    value_type;
        typedef _Alloc                allocator_type;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;

      public:
        typedef memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef __list_iterator<value_type> iterator;
        typedef
          helper::reverse_iterator<iterator> reverse_iterator;
        typedef __list_const_iterator<value_type> const_iterator;
        typedef
          helper::reverse_iterator<const_iterator> const_reverse_iterator;

      public: // assert
        static_assert(trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        typedef memory::unique_ptr<value_type>
          __value_container;
        typedef memory::unique_ptr<__node_type>
          __node_container;

      private:
        typedef container::compressed_pair<__link_type, __node_allocator_type>   __node_pair;
        typedef container::compressed_pair<size_type, allocator_type>  __mis_type;

      private:
        __node_pair     __base;
        __mis_type      __mis;

      public:
        list(): list(allocator_type())
        { }
        explicit list(const allocator_type& __alloc):
          __base{nullptr, __node_allocator_type{}},
          __mis{0U, __alloc}
        { this->init_base();}

        explicit list(
          size_type __count,
          const value_type& __val,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type{}},
          __mis{0U, __alloc}
        {
          this->init_base();
          for(; __count > 0; --__count)
          { this->push_back(__val);}
        }

        explicit list(
          size_type __count,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type{}},
          __mis{0U, __alloc}
        {
          this->init_base();
          for(; __count > 0; --__count)
          { this->emplace_back();}
        }

        template<typename _Inputiterator,
          typename
          trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
            bool
          >::type = true
        >
        explicit list(_Inputiterator __first, _Inputiterator __last,
          const allocator_type __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type{}},
          __mis{0U, __alloc}
        {
          this->init_base();
          for(; __first != __last; ++__first)
          { this->push_back(*__first);}
        }

        list(const list& __other):
          __base{nullptr, __other.__base.second()},
          __mis{0, __other.__mis.second()}
        {
          this->init_base();
          for(const_iterator __it = __other.begin();
            __it != __other.end(); ++__it)
          { this->push_back(*__it);}
        }
        list(const list& __other, const allocator_type& __alloc):
          __base{nullptr, __other.__base.second()},
          __mis{0U, __alloc}
        {
          this->init_base();
          for(const_iterator __it = __other.begin();
            __it != __other.end(); ++__it)
          { this->push_back(*__it);}
        }

        list(list&& __other):
          __base{algorithm::move(__other.__base)},
          __mis{algorithm::move(__other.__mis)}
        { __other.__base.first() = nullptr;}
        list(list&& __other, const allocator_type& __alloc):
          __base{algorithm::move(__other.__base)},
          __mis{__other.__mis.first(), __alloc}
        { __other.__base.first() = nullptr;}

        list(initializer_list<value_type> __initlist,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type{}},
          __mis{0U, __alloc}
        {
          this->init_base();
          for(typename initializer_list<value_type>::iterator __it = __initlist.begin();
            __it != __initlist.end(); ++__it)
          { this->push_back(*__it);}
        }

        ~list()
        { this->force_clear();}

      //!< \todo this part is not well prepared
      public:
        list& operator=(const list& __other)
        {
          if(&__other != this)
          {
            this->__mis.second() = __other.__mis.second();
            this->__base.second() = __other.__base.second();
            if(this->__base.first() == nullptr)
            {
              this->__base.first() =
                __node_allocator_traits_type::allocate(this->__base.second());
              this->__mis.first() = 0U;
              this->__base.first()->__prev = this->__base.first();
              this->__base.first()->__next = this->__base.first();
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
            this->__mis =
              algorithm::move(__other.__mis);
            this->__base =
              algorithm::move(__other.__base);
            __other.__base.first() = nullptr;
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
        trait::type::miscellaneous::enable_if<
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
        { return this->__mis.second();}

      public:
        reference front() noexcept
        { return *(this->__base.first()->__next->__data);}
        const_reference front() const noexcept
        { return *(this->__base.first()->__next->__data);}
        reference back() noexcept
        { return *(this->__base.first()->__prev->__data);}
        const_reference back() const noexcept
        { return *(this->__base.first()->__prev->__data);}

      public:
        iterator begin() noexcept
        { return iterator{this->__base.first()->__next};}
        const_iterator begin() const noexcept
        { return const_iterator{this->__base.first()->__next};}
        const_iterator cbegin() const noexcept
        { return const_iterator{this->__base.first()->__next};}
        iterator end() noexcept
        { return iterator{this->__base.first()};}
        const_iterator end() const noexcept
        { return const_iterator{this->__base.first()};}
        const_iterator cend() const noexcept
        { return const_iterator{this->__base.first()};}

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
        bool empty() const noexcept
        { return this->__base.first() == this->__base.first()->__next;}
        size_type size() const noexcept
        { return this->__mis.first();}

      public:
        void push_front(const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, this->__base.first()->__next);
          ++(this->__mis.first());
        }
        void push_front(value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__val));
          __node_insert(__ulink, this->__base.first()->__next);
          ++(this->__mis.first());
        }
        void push_back(const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, this->__base.first());
          ++(this->__mis.first());
        }
        void push_back(value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__val));
          __node_insert(__ulink, this->__base.first());
          ++(this->__mis.first());
        }

      public:
        template<typename... _Args>
        iterator emplace(const_iterator __pos ,_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__args)...);
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__mis.first());
          return iterator(__pos.__ptr);
        }
        template<typename... _Args>
        reference emplace_front(_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__args)...);
          __node_insert(__ulink, this->__base.first()->__next);
          ++(this->__mis.first());
          return *(this->__base.first()->__next->__data);
        }
        template<typename... _Args>
        reference emplace_back(_Args&&... __args)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__args)...);
          __node_insert(__ulink, this->__base.first());
          ++(this->__mis.first());
          return *(this->__base.first()->__prev->__data);
        }

      public:
        void pop_front()
        {
          __link_type __dlink = this->__base.first()->__next;
          __node_connect(__dlink->__prev, __dlink->__next);
          this->__deallocate_node(__dlink);
          --(this->__mis.first());
        }
        void pop_back()
        {
          __link_type __dlink = this->__base.first()->__prev;
          __node_connect(__dlink->__prev, __dlink->__next);
          this->__deallocate_node(__dlink);
          --(this->__mis.first());
        }

      public:
        iterator insert(const_iterator __pos, const value_type& __val)
        {
          __link_type __ulink = this->__allocate_node(__val);
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__mis.first());
          return iterator(__ulink);
        }
        iterator insert(const_iterator __pos, value_type&& __val)
        {
          __link_type __ulink =
            this->__allocate_node(algorithm::move(__val));
          __node_insert(__ulink, __pos.__ptr);
          ++(this->__mis.first());
          return iterator(__ulink);
        }
        iterator insert(const_iterator __pos,
          size_type __count, const value_type& __val)
        {
          if(__count == 0)
          { return iterator(__pos.__ptr);}
          container::pair<__link_type, __link_type> __chain =
            this->__allocate_node_chain(__count, __val);
          __link_type __tpos =__pos.__ptr;
          __node_connect(__tpos->__prev, __chain.first);
          __node_connect(__chain.second, __tpos);
          this->__mis.first() += __count;
          return iterator(__chain.first);
        }

        template<typename _Inputiterator,
          typename trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
          bool>::type = true
        >
        iterator insert(const_iterator __pos,
          _Inputiterator __first, _Inputiterator __last)
        {
          if(__first == __last)
          { return iterator(__pos.__ptr);}
          container::pair<__link_type, __link_type> __chain =
            this->__allocate_node_chain(__first, __last);
          __link_type __tpos = __pos.__ptr;
          __node_connect(__tpos->__prev, __chain.first);
          __node_connect(__chain.second, __tpos);
          this->__mis.first() += helper::distance(__first, __last);
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
            __link_type __dbase = this->__base.first();
            __link_type __tmp = __dbase->__prev;
            __link_type __dtmp = __dbase->__prev->__prev;
            for(;__tmp != __dbase;)
            {
              __tmp->__next = __tmp->__prev = nullptr;
              this->__deallocate_node(__tmp);
              __tmp = __dtmp;
              __dtmp = __dtmp->__prev;
            }
            this->__mis.first() = 0U;
            __dbase->__prev = __dbase->__next = __dbase;
          }
        }
        void resize(size_type __count)
        {
          if(__count > this->__mis.first())
          {
            for(;__count != this->__mis.first();)
            { this->emplace_back();}
            return;
          }
          for(;__count != this->__mis.first();)
          { this->pop_back();}
        }
        void resize(size_type __count, const value_type& __val)
        {
          if(__count > this->__mis.first())
          {
            for(;__count != this->__mis.first();)
            { this->push_back(__val);}
            return;
          }
          for(;__count != this->__mis.first();)
          { this->pop_back();}
        }

      public:
        iterator erase(const_iterator __pos)
        {
          __link_type __dlink = __pos.__ptr;
          __link_type __elink = __dlink->__next;
          __node_connect(__dlink->__prev, __dlink->__next);
          this->__deallocate_node(__dlink);
          --(this->__mis.first());
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
              this->__deallocate_node(__dlink);
              __dlink = __tlink;
              __tlink = __tlink->__next;
              --(this->__mis.first());
            }
          }
          return iterator(__elink);
        }

      public:
        void swap(list& __other) noexcept(
          trait::type::features::is_nothrow_swappable<allocator_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__mis,   __other.__mis);
          swap(this->__base,  __other.__base);
        }
        void possible_swap(list& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<allocator_type>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__mis,  __other.__mis);
          possible_swap(this->__base, __other.__base);
        }

      public:
        void reverse() noexcept
        {
          __link_type __tlink = this->__base.first();
          __link_type __tbase = __tlink;
          __tlink->reverse();
          __tlink = __tlink->__prev;
          for(;__tlink != __tbase;)
          {
            __tlink->reverse();
            __tlink = __tlink->__prev;
          }
        }

      public:
        void splice(const_iterator __pos, list& __con) noexcept
        {
          if(!__con.empty() && (&__con != this))
          {
            __link_type __plink = __pos.__ptr;
            __link_type __pbase = __con.__base.first();
            __node_connect(__plink->__prev, __pbase->__next);
            __node_connect(__pbase->__prev, __plink);
            __pbase->__prev = __pbase->__next = __pbase;
            this->__mis.first() += __con.__mis.first();
            __con.__mis.first() = 0;
          }
        }
        void splice(const_iterator __pos, list& __con, const_iterator __it) noexcept
        {
          if((__pos != __it) && !__con.empty())
          {
            __link_type __plink = __pos.__ptr;
            __link_type __tlink = __it.__ptr;
            __node_connect(__tlink->__prev, __tlink->__next);
            __node_connect(__plink->__prev, __tlink);
            __node_connect(__tlink, __plink);
            ++(this->__mis.first());
            --(__con.__mis.first());
          }
        }
        void splice(const_iterator __pos, list& __con,
          const_iterator __first, const_iterator __last) noexcept
        {
          if(!__con.empty() && (__first != __last))
          {
            size_type __dist = helper::distance(__first, __last);
            __link_type __plink = __pos.__ptr;
            __link_type __tflink = __first.__ptr;
            __link_type __tllink = __last.__ptr->__prev;
            __node_connect(__tflink->__prev, __tllink->__next);
            __node_connect(__plink->__prev, __tflink);
            __node_connect(__tllink, __plink);
            this->__mis.first() += __dist;
            __con.__mis.first() -= __dist;
          }
        }
        void splice(const_iterator __pos, list&& __con) noexcept
        { this->splice(__pos, __con);}
        void splice(const_iterator __pos, list&& __con, const_iterator __it) noexcept
        { this->splice(__pos, __con, __it);}
        void splice(const_iterator __pos, list&& __con,
          const_iterator __first, const_iterator __last) noexcept
        { this->splice(__pos, __con, __first, __last);}


      public:
        void remove(const value_type& __val)
        {
          __link_type __dbase = this->__base.first();
          __link_type __dlink = __dbase->__next;
          __link_type __tlink = __dbase->__next->__next;
          for(;__dlink != __dbase;)
          {
            if(*(__dlink->__data) == __val)
            {
              __node_connect(__dlink->__prev, __dlink->__next);
              __dlink->__prev = __dlink->__next = nullptr;
              this->__deallocate_node(__dlink);
              --(this->__mis.first());
            }
            __dlink = __tlink;
            __tlink = __tlink->__next;
          }
        }
        template<typename _UnaryPredicate>
        void remove(_UnaryPredicate __pred)
        {
          __link_type __dbase = this->__base.first();
          __link_type __dlink = __dbase->__next;
          __link_type __tlink = __dbase->__next->__next;
          for(;__dlink != __dbase;)
          {
            if(__pred(static_cast<const value_type&>(*(__dlink->__data))))
            {
              __node_connect(__dlink->__prev, __dlink->__next);
              __dlink->__prev = __dlink->__next = nullptr;
              this->__deallocate_node(__dlink);
              --(this->__mis.first());
            }
            __dlink = __tlink;
            __tlink = __tlink->__next;
          }
        }

      public:
        inline void merge(list& __other)
        { this->merge(__other, algorithm::less<value_type>{});}
        inline void merge(list&& __other)
        { this->merge(__other, algorithm::less<value_type>{});}
        template<typename _Compare>
        void merge(list& __other, _Compare __compare)
        {
          if(&__other != this)
          {
            __link_type __tlink = this->__base.first();
            for(iterator __it = __other.begin(); __it != __other.end();)
            {
              __tlink = __tlink->__next;
              if(__tlink == this->__base.first())
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
            this->__mis.first() += __other.__size;
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
            this->__base.first()->__next, this->__base.first()->__prev,
            this->__mis.first(), algorithm::less<value_type>{}
          );
        }
        template<typename _Compare>
        inline void sort(_Compare __compare)
        {
          typedef typename
            trait::type::transform::add_lvalue_reference<_Compare>::type
            __comp_ref;
          __sort<__comp_ref>(
            this->__base.first()->__next, this->__base.first()->__prev,
            this->__mis.first(), __compare
          );
        }

      public:
        inline void unique()
        { this->unique(algorithm::equal_to<value_type>{});}
        template<typename _BinaryPredicate>
        void unique(_BinaryPredicate __binarypred)
        {
          for(iterator __it = this->begin(), __eit = this->end(); __it != __eit;)
          {
            iterator __tit = helper::next(__it);
            for(;__tit != __eit && __binarypred(*__it, *__tit); ++__tit);
            if(++__it != __tit)
            { __it = this->erase(__it, __tit);}
          }
        }
      private:
        UTILITY_ALWAYS_INLINE
        inline bool base_empty() const noexcept
        { return this->__base.first() == nullptr;}
        // Only used whem the list is deallocated
        UTILITY_ALWAYS_INLINE
        inline void force_clear() noexcept
        {
          if(!this->base_empty())
          {
            this->clear();

#ifndef UTILITY_DEALLOCATE_EMPTY
            this->__base.first()->__prev = this->__base.first()->__next = nullptr;
#endif // ! UTILITY_DEALLOCATE_EMPTY

            __node_allocator_traits_type::deallocate(
              this->__base.second(), this->__base.first()
            );

            this->__base.first() = nullptr;
          }
        }
        UTILITY_ALWAYS_INLINE
        inline void init_base()
        {
          __link_type __tmp =
            __node_allocator_traits_type::allocate(this->__base.second());
          __tmp->__prev = __tmp->__next = __tmp;
          this->__base.first() = __tmp;
        }

      private:
        template<typename... _Args>
        UTILITY_ALWAYS_INLINE
        inline __link_type __allocate_node(_Args&&... __args)
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__base.second())
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __valc.get(),
            algorithm::move(__args)...
          );
          __link_type __link = __node.release();
          __link->__data = __valc.release();
          return __link;
        }
        UTILITY_ALWAYS_INLINE
        inline void __deallocate_node(__link_type __link)
        {
#ifndef UTILITY_DEALLOCATE_EMPTY
          __link->__prev = __link->__next = nullptr;
#endif // ! UTILITY_DEALLOCATE_EMPTY

          if(__link->__data != nullptr)
          {
            allocator_traits_type::destroy(this->__mis.second(), __link->__data);
            allocator_traits_type::deallocate(this->__mis.second(), __link->__data);
          }
          __node_allocator_traits_type::destroy(this->__base.second(), __link);
          __node_allocator_traits_type::deallocate(this->__base.second(), __link);
        }
        UTILITY_ALWAYS_INLINE
        inline container::pair<__link_type, __link_type>
        __allocate_node_chain(size_type __count, const value_type& __val)
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__base.second())
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __valc.get(), __val
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
                __node_allocator_traits_type::allocate(this->__base.second())
              );
              __valc.reset(
                allocator_traits_type::allocate(this->__mis.second())
              );
              allocator_traits_type::construct(
                this->__mis.second(), __valc.get(), __val
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
              this->__deallocate_node(__bpos);
            }
          );
          return container::pair<__link_type, __link_type>(
            __bpos, __epos
          );
        }
        template<typename _Inputiterator,
          typename
          trait::type::miscellaneous::enable_if<
            is_iterator<_Inputiterator>::value,
          bool>::type = true
        >
        container::pair<__link_type, __link_type> __allocate_node_chain(
          _Inputiterator __first, _Inputiterator __last
        )
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__base.second())
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __valc.get(), *__first
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
                __node_allocator_traits_type::allocate(this->__base.second())
              );
              __valc.reset(
                allocator_traits_type::allocate(this->__mis.second())
              );
              allocator_traits_type::construct(
                this->__mis.second(), __valc.get(), *__first
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
              this->__deallocate_node(__bpos);
            }
          );
          return container::pair<__link_type, __link_type>(
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
          for(size_type __i = 0; __i < __length; ++__i)
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
          using algorithm::swap;
          if(__tsize < 2)
          { return __first;}
          if(__tsize == 2)
          {
            if(__compare(*(__last->__data), *(__first->__data)))
            { swap(__first->__data, __last->__data);}
            return __first;
          }
          size_type __len = __tsize / 2;
          __link_type __mid = __node_next(__first, __len);
          __first = __sort<_Compare>(__first, __mid->__prev, __len, __compare);
          __mid = __sort<_Compare>(__mid, __last, __tsize - __len, __compare);
          __last = __node_next(__mid, __tsize - __len - 1);
          return __merge<_Compare>(
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
        algorithm::equal(__x.begin(), __x.end(), __y.begin());
    }
    template<typename _T, typename _Alloc>
    inline bool operator!=(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    { return !(__x == __y);}
    template<typename _T, typename _Alloc>
    inline bool operator<(const list<_T, _Alloc>& __x, const list<_T, _Alloc>& __y)
    {
      return algorithm::lexicographical_compare(
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
      container::list<_T, _Alloc>& __x,
      container::list<_T, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<typename _T, typename _Alloc>
    inline void possible_swap(
      container::list<_T, _Alloc>& __x,
      container::list<_T, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! ___UTILITY__CHECK__USE__STD___

#endif // ! __UTILITY_CONTAINER_LIST__
