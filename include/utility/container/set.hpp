
#ifndef __UTILITY_CONTAINER_SET__
#define __UTILITY_CONTAINER_SET__

/**
 * \file set.hpp
 * \author Inochi Amaoto
 *
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/container/pair.hpp>
#include<utility/container/compressed_pair.hpp>
#include<utility/container/white_black_tree.hpp>

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/opt/__empty__.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

#include<utility/iterator/iterator_traits.hpp>

#include<utility/memory/addressof.hpp>
#include<utility/memory/allocator_traits.hpp>

namespace utility
{
  namespace container
  {
    template<
      typename _Key,
      typename _Compare = algorithm::less<void>,
      typename _Alloc = memory::allocator<_Key>
    >
    class set
    {
      private:
        template<typename _Iterator>
        class __set_iterator
        {
          private:
            template<typename, typename, typename>
            friend class set;

          private:
            typedef _Iterator __iterator_type;

          public:
            typedef typename __iterator_type::iterator_category iterator_category;
            typedef typename __iterator_type::key_type key_type;
            typedef typename __iterator_type::key_type mapped_type;
            typedef typename __iterator_type::key_type value_type;
            typedef typename __iterator_type::reference reference;
            typedef typename __iterator_type::pointer pointer;
            typedef typename __iterator_type::difference_type difference_type;

          public:
            typedef __set_iterator<_Iterator> self;

          private:
            __iterator_type __it;

          public:
            inline __set_iterator() noexcept: __it()
            { }
            inline explicit __set_iterator(__iterator_type __t) noexcept:
              __it(__t)
            { }

          public:
            self& operator=(const self& __oit)
            {
              if(&__oit != this)
              { this->__it = __oit.__it;}
              return *this;
            }

          public:
            reference operator*() const
            {
              using container::get;
              return get<1>(*(this->__it));
            }
            pointer operator->() const
            {
              using container::get;
              return memory::addressof(get<1>(*(this->__it)));
            }

          public:
            self& operator++() noexcept
            {
              ++(this->__it);
              return *this;
            }
            self operator++(int) noexcept
            { return self((this->__it)++);}
            self& operator--() noexcept
            {
              --(this->__it);
              return *this;
            }
            self operator--(int) noexcept
            { return self((this->__it)--);}

          public:
            bool operator==(const self& __o) const noexcept
            { return this->__it == __o.__it;}
            bool operator!=(const self& __o) const noexcept
            { return !(this->__it == __o.__it);}
        };

      private:
        typedef typename memory::allocator_traits<_Alloc>::template
          rebind_alloc<container::compressed_pair<
            const _Key, trait::__opt__::__empty__
          >> __allocator;
        typedef container::white_black_tree<
          _Key, trait::__opt__::__empty__, _Compare,
          container::compressed_pair<
            const _Key, trait::__opt__::__empty__
          >, __allocator> __tree_type;

      public:
        typedef _Key                key_type;
        typedef _Key                value_type;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;
        typedef _Compare            key_compare;
        typedef _Compare            value_compare;
        typedef _Alloc              allocator_type;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;

      public:
        typedef memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef __set_iterator<typename __tree_type::const_iterator> iterator;
        typedef __set_iterator<typename __tree_type::const_iterator> const_iterator;
        typedef
          helper::reverse_iterator<iterator> reverse_iterator;
        typedef
          helper::reverse_iterator<const_iterator> const_reverse_iterator;

      private:
        __tree_type __tree;

      public:
        set():set(_Compare())
        { }
        explicit set(
          const _Compare& __comp,
          const allocator_type __alloc = allocator_type()
        ):__tree(__comp, __alloc)
        {}
        explicit set(const allocator_type& __alloc):
          __tree(__alloc)
        { }

        template<typename _InputIterator,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        set(
          _InputIterator __first, _InputIterator __last,
          const _Compare& __comp = _Compare(),
          const allocator_type __alloc = allocator_type()
        ): __tree(__comp, __alloc)
        {
          for(_InputIterator __i = __first; __i != __last; ++__i)
          {
            __tree.insert_unique(
              {*__i, trait::__opt__::__empty__{}}
            );
          }
        }
        template<typename _InputIterator,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        set(
          _InputIterator __first, _InputIterator __last,
          const allocator_type __alloc
        ): __tree(__alloc)
        {
          for(_InputIterator __i = __first; __i != __last; ++__i)
          {
            __tree.insert_unique(
              {*__i, trait::__opt__::__empty__{}}
            );
          }
        }

        set(const set& __other):
          __tree(__other.__tree)
        { }
        set(
          const set& __other, const allocator_type __alloc
        ):__tree(__other.__tree, __alloc)
        { }
        set(set&& __other):
          __tree(algorithm::move(__other.__tree))
        { }
        set(
          set&& __other, const allocator_type __alloc
        ):__tree(algorithm::move(__other.__tree), __alloc)
        { }

        set(
          initializer_list<value_type> __initlist,
          const _Compare __comp = _Compare(),
          const allocator_type __alloc = allocator_type()
        ): __tree(__comp, __alloc)
        {
          typedef typename
            initializer_list<value_type>::iterator
            __iterator;
          for(__iterator __i = __initlist.begin(); __i != __initlist.end(); ++__i)
          {
            __tree.insert_unique(
              {*__i, trait::__opt__::__empty__{}}
            );
          }
        }
        set(
          initializer_list<value_type> __initlist,
          const allocator_type __alloc
        ): __tree(__alloc)
        {
          typedef typename
            initializer_list<value_type>::iterator
            __iterator;
          for(__iterator __i = __initlist.begin(); __i != __initlist.end(); ++__i)
          {
            __tree.insert_unique(
              {*__i, trait::__opt__::__empty__{}}
            );
          }
        }

      public:
        set& operator=(const set& __other)
        {
          if(&__other != this)
          { this->__tree = __other.__tree;}
          return *this;
        }
        set& operator=(set&& __other)
        {
          if(&__other != this)
          { this->__tree = algorithm::move(__other.__tree);}
          return *this;
        }
        set& operator=(initializer_list<value_type> __initlist)
        {
          typedef typename
            initializer_list<value_type>::iterator
            __iterator;
          __tree.clear();
          for(__iterator __i = __initlist.begin(); __i != __initlist.end(); ++__i)
          {
            __tree.insert_unique(
              {*__i, trait::__opt__::__empty__{}}
            );
          }
          return *this;
        }

      public:
        allocator_type get_allocator() const
        { return allocator_type();}

      public:
        key_compare key_comp() const
        { return key_compare();}
        value_compare value_comp() const
        { return value_compare();}

      public:
        iterator begin() noexcept
        { return iterator(this->__tree.begin());}
        const_iterator begin() const noexcept
        { return const_iterator(this->__tree.begin());}
        const_iterator cbegin() const noexcept
        { return const_iterator(this->__tree.cbegin());}
        iterator end() noexcept
        { return iterator(this->__tree.end());}
        const_iterator end() const noexcept
        { return const_iterator(this->__tree.end());}
        const_iterator cend() const noexcept
        { return const_iterator(this->__tree.cend());}

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
        { return this->__tree.empty();}
        size_type size() const noexcept
        { return this->__tree.size();}

      public:
        container::pair<iterator, bool>
        insert(const value_type& __val)
        {
          typedef typename __tree_type::iterator __iterator;
          container::pair<__iterator, bool> __tmp =
            this->__tree.insert_unique(
              {__val, trait::__opt__::__empty__{}}
            );
          return container::pair<iterator, bool>{
            iterator{*(__tmp.first).first()}, __tmp.second
          };
        }
        container::pair<iterator, bool>
        insert(value_type&& __val)
        {
          typedef typename __tree_type::iterator __iterator;
          container::pair<__iterator, bool> __tmp =
            this->__tree.insert_unique({
              algorithm::move(__val),
              trait::__opt__::__empty__{}
            });
          return container::pair<iterator, bool>{
            iterator{*(__tmp.first).first()}, __tmp.second
          };
        }
        iterator insert(
          const_iterator __hint, const value_type& __val
        )
        {
          typedef typename __tree_type::iterator __iterator;
          __iterator __tmp = this->__tree.insert_unique(
            __hint.__it,
            {__val, trait::__opt__::__empty__{}}
          );
          return iterator{(*__tmp).first()};
        }
        iterator insert(
          const_iterator __hint, value_type&& __val
        )
        {
          typedef typename __tree_type::iterator __iterator;
          __iterator __tmp = this->__tree.insert_unique(
            __hint.__it,
            {algorithm::move(__val),
            trait::__opt__::__empty__{}}
          );
          return iterator{(*__tmp).first()};
        }

      public:
        template<typename... _Args>
        container::pair<iterator, bool>
        emplace(_Args&&... __args)
        {
          typedef typename __tree_type::iterator __iterator;
          container::pair<__iterator, bool> __tmp =
            this->__tree.emplace_unique(
              value_type{algorithm::move(__args)...},
              trait::__opt__::__empty__{}
            );
          return container::pair<iterator, bool>{
            iterator{*(__tmp.first).first()}, __tmp.second
          };
        }
        template<typename... _Args>
        iterator emplace_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          typedef typename __tree_type::iterator __iterator;
          __iterator __tmp = this->__tree.emplace_unique_hint(
            __hint.__it,
            value_type{algorithm::move(__args)...},
            trait::__opt__::__empty__{}
          );
          return iterator{(*__tmp).first()};
        }

      public:
        inline size_type count(const key_type& __key) const noexcept
        { return this->__tree.count(__key);}

      public:
        inline iterator lower_bound(const key_type& __key) noexcept
        { return iterator{this->__tree.lower_bound(__key)};}
        inline const_iterator lower_bound(const key_type& __key) const noexcept
        { return const_iterator{this->__tree.lower_bound(__key)};}
        inline iterator upper_bound(const key_type& __key) noexcept
        { return iterator{this->__tree.upper_bound(__key)};}
        inline const_iterator upper_bound(const key_type& __key) const noexcept
        { return const_iterator{this->__tree.upper_bound(__key)};}
        inline container::pair<iterator, iterator>
        equal_range(const key_type& __key) noexcept
        {
          return container::pair<iterator, iterator>{
            this->lower_bound(__key), this->upper_bound(__key)
          };
        }
        inline container::pair<const_iterator, const_iterator>
        equal_range(const key_type& __key) const noexcept
        {
          return container::pair<const_iterator, const_iterator>{
            this->lower_bound(__key), this->upper_bound(__key)
          };
        }

      public:
        inline iterator find(const key_type& __key) noexcept
        { return iterator{this->__tree.find(__key)};}
        inline iterator find(const key_type& __key) const noexcept
        { return iterator{this->__tree.find(__key)};}

      public:
        inline iterator erase(const_iterator __pos)
        { return iterator{this->__tree.erase(__pos.__it)};}
        inline iterator erase(
          const_iterator __first, const_iterator __last
        )
        { return iterator{this->__tree.erase(__first.__it, __last.__it)};}
        inline size_type erase(const key_type& __key)
        { return this->__tree.erase(__key);}


      public:
        void clear()
        { this->__tree.clear();}

      public:
        void swap(set& __other) noexcept(
          noexcept(__tree.swap(__other.__tree))
        )
        { this->__tree.swap(__other.__tree);}
        void possible_swap(set& __other) noexcept(
          noexcept(__tree.possible_swap(__other.__tree))
        )
        { this->__tree.possible_swap(__other.__tree);}

      public:
        bool operator==(const set& __y) const
        { return this->__tree == __y.__tree;}
        bool operator<(const set& __y) const
        { return this->__tree < __y.__tree;}

    };

    template<typename _Key, typename _Compare, typename _Alloc>
    bool operator!=(
      const set<_Key, _Compare, _Alloc>& __x,
      const set<_Key, _Compare, _Alloc>& __y
    )
    { return !(__x == __y);}
    template<typename _Key, typename _Compare, typename _Alloc>
    bool operator>(
      const set<_Key, _Compare, _Alloc>& __x,
      const set<_Key, _Compare, _Alloc>& __y
    )
    { return __y < __x;}
    template<typename _Key, typename _Compare, typename _Alloc>
    bool operator<=(
      const set<_Key, _Compare, _Alloc>& __x,
      const set<_Key, _Compare, _Alloc>& __y
    )
    { return !(__y < __x);}
    template<typename _Key, typename _Compare, typename _Alloc>
    bool operator>=(
      const set<_Key, _Compare, _Alloc>& __x,
      const set<_Key, _Compare, _Alloc>& __y
    )
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<typename _Key, typename _Compare, typename _Alloc>
    void swap(
      container::set<_Key, _Compare, _Alloc>& __x,
      container::set<_Key, _Compare, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    void possible_swap(
      container::set<_Key, _Compare, _Alloc>& __x,
      container::set<_Key, _Compare, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_SET__
