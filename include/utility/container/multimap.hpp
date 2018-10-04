
#ifndef __UTILITY_CONTAINER_MULTIMAP__
#define __UTILITY_CONTAINER_MULTIMAP__

/**
 * \file multimap.hpp
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

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

#include<utility/iterator/iterator_traits.hpp>

#include<utility/memory/addressof.hpp>
#include<utility/memory/allocator_traits.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _Key,
      typename _Value,
      typename _Compare = algorithm::less<void>,
      typename _Alloc = memory::allocator<container::pair<const _Key, _Value>>
    >
    class multimap
    {
      public:
        class value_compare
        {
          protected:
            _Compare __compare;

          protected:
            value_compare(const _Compare& __comp):
              __compare(__comp)
            { }

          public:
            bool operator()(
              container::pair<const _Key, _Value>& __x,
              container::pair<const _Key, _Value>& __y
            ) const
            { return this->__compare(__get_key(__x), __get_key(__y));}
        };

      private:
        typedef typename memory::allocator_traits<_Alloc>::template
          rebind_alloc<container::pair<const _Key, _Value>>
          __allocator;
        typedef container::white_black_tree<
          _Key, _Value, _Compare,
          container::pair<const _Key, _Value>, __allocator>
          __tree_type;

      public:
        typedef _Key                                          key_type;
        typedef _Value                                        multimapped_type;
        typedef container::pair<const _Key, _Value>  value_type;

        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;
        typedef _Compare            key_compare;
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
        typedef typename __tree_type::iterator        iterator;
        typedef typename __tree_type::const_iterator  const_iterator;
        typedef typename __tree_type::reverse_iterator
          reverse_iterator;
        typedef typename __tree_type::const_reverse_iterator
          const_reverse_iterator;

      private:
        __tree_type __tree;

      public:
        multimap(): multimap(key_compare())
        { }
        explicit multimap(
          const key_compare& __comp,
          const allocator_type& __alloc = allocator_type()
        ):__tree(__comp, __alloc)
        { }
        explicit multimap(const allocator_type& __alloc):
          __tree(__alloc)
        { }

        template<typename _InputIterator,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        multimap(
          _InputIterator __first, _InputIterator __last,
          const _Compare& __comp = _Compare(),
          const allocator_type __alloc = allocator_type()
        ): __tree(__first, __last, __comp, __alloc)
        { }
        template<typename _InputIterator,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true
        >
        multimap(
          _InputIterator __first, _InputIterator __last,
          const allocator_type __alloc
        ): __tree(__first, __last, __alloc)
        { }

        multimap(const multimap& __other):
          __tree(__other.__tree)
        { }
        multimap(
          const multimap& __other, const allocator_type __alloc
        ):__tree(__other.__tree, __alloc)
        { }
        multimap(multimap&& __other):
          __tree(algorithm::move(__other.__tree))
        { }
        multimap(
          multimap&& __other, const allocator_type __alloc
        ):__tree(algorithm::move(__other.__tree), __alloc)
        { }

        multimap(
          initializer_list<value_type> __initlist,
          const _Compare __comp = _Compare(),
          const allocator_type __alloc = allocator_type()
        ): __tree(__initlist, __comp, __alloc)
        { }
        multimap(
          initializer_list<value_type> __initlist,
          const allocator_type __alloc
        ): __tree(__initlist, __alloc)
        { }

      public:
        multimap& operator=(const multimap& __other)
        {
          if(&__other != this)
          { this->__tree = __other.__tree;}
          return *this;
        }
        multimap& operator=(multimap&& __other)
        {
          if(&__other != this)
          { this->__tree = algorithm::move(__other.__tree);}
          return *this;
        }
        multimap& operator=(initializer_list<value_type> __initlist)
        {
          this->__tree = __initlist;
          return *this;
        }

      public:
        allocator_type get_allocator() const
        { return allocator_type{};}

      public:
        key_compare key_comp() const
        { return key_compare{};}
        value_compare value_comp() const
        { return value_compare{key_compare{}};}

      public:
        iterator begin() noexcept
        { return this->__tree.begin();}
        const_iterator begin() const noexcept
        { return this->__tree.begin();}
        const_iterator cbegin() const noexcept
        { return this->__tree.cbegin();}
        iterator end() noexcept
        { return this->__tree.end();}
        const_iterator end() const noexcept
        { return this->__tree.end();}
        const_iterator cend() const noexcept
        { return this->__tree.cend();}

      public:
        reverse_iterator rbegin() noexcept
        { return this->__tree.rbegin();}
        const_reverse_iterator rbegin() const noexcept
        { return this->__tree.rbegin();}
        const_reverse_iterator crbegin() const noexcept
        { return this->__tree.crbegin();}
        reverse_iterator rend() noexcept
        { return this->__tree.rend();}
        const_reverse_iterator rend() const noexcept
        { return this->__tree.rend();}
        const_reverse_iterator crend() const noexcept
        { return this->__tree.crend();}

      public:
        bool empty() const noexcept
        { return this->__tree.empty();}
        size_type size() const noexcept
        { return this->__tree.size();}

      public:
        container::pair<iterator, bool>
        insert(const value_type& __val)
        { return this->__tree.insert_unique(__val);}
        container::pair<iterator, bool>
        insert(value_type&& __val)
        {
          return this->__tree.insert_unique(
            algorithm::move(__val)
          );
        }
        iterator insert(
          const_iterator __hint, const value_type& __val
        )
        { return this->__tree.insert_unique(__hint, __val);}
        iterator insert(
          const_iterator __hint, value_type&& __val
        )
        {
          return this->__tree.insert_unique(
            __hint, algorithm::move(__val)
          );
        }

      public:
        template<typename... _Args>
        container::pair<iterator, bool>
        emplace(_Args&&... __args)
        {
          return this->__tree.emplace_unique(
            algorithm::move(__args)...
          );
        }
        template<typename... _Args>
        iterator emplace_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          return this->__tree.emplace_unique(
            __hint, algorithm::move(__args)...
          );
        }

      public:
        inline size_type count(const key_type& __key) const noexcept
        { return this->__tree.count(__key);}

      public:
        inline iterator lower_bound(const key_type& __key) noexcept
        { return this->__tree.lower_bound(__key);}
        inline const_iterator lower_bound(const key_type& __key) const noexcept
        { return this->__tree.lower_bound(__key);}
        inline iterator upper_bound(const key_type& __key) noexcept
        { return this->__tree.upper_bound(__key);}
        inline const_iterator upper_bound(const key_type& __key) const noexcept
        { return this->__tree.upper_bound(__key);}
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
        { return this->__tree.find(__key);}
        inline iterator find(const key_type& __key) const noexcept
        { return this->__tree.find(__key);}

      public:
        inline iterator erase(const_iterator __pos)
        { return this->__tree.erase(__pos);}
        inline iterator erase(
          const_iterator __first, const_iterator __last
        )
        { return this->__tree.erase(__first, __last);}
        inline size_type erase(const key_type& __key)
        { return this->__tree.erase(__key);}

      public:
        void clear()
        { this->__tree.clear();}

      public:
        void swap(multimap& __other) noexcept(
          noexcept(__tree.swap(__other.__tree))
        )
        { this->__tree.swap(__other.__tree);}
        void possible_swap(multimap& __other) noexcept(
          noexcept(__tree.possible_swap(__other.__tree))
        )
        { this->__tree.possible_swap(__other.__tree);}

      public:
        bool operator==(const multimap& __y) const
        { return this->__tree == __y.__tree;}
        bool operator<(const multimap& __y) const
        { return this->__tree < __y.__tree;}

    };

    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    bool operator!=(
      const multimap<_Key, _Value, _Compare, _Alloc>& __x,
      const multimap<_Key, _Value, _Compare, _Alloc>& __y
    )
    { return !(__x == __y);}
    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    bool operator>(
      const multimap<_Key, _Value, _Compare, _Alloc>& __x,
      const multimap<_Key, _Value, _Compare, _Alloc>& __y
    )
    { return __y < __x;}
    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    bool operator<=(
      const multimap<_Key, _Value, _Compare, _Alloc>& __x,
      const multimap<_Key, _Value, _Compare, _Alloc>& __y
    )
    { return !(__y < __x);}
    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    bool operator>=(
      const multimap<_Key, _Value, _Compare, _Alloc>& __x,
      const multimap<_Key, _Value, _Compare, _Alloc>& __y
    )
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    void swap(
      container::multimap<_Key, _Value, _Compare, _Alloc>& __x,
      container::multimap<_Key, _Value, _Compare, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<
      typename _Key, typename _Value,
      typename _Compare, typename _Alloc
    >
    void possible_swap(
      container::multimap<_Key, _Value, _Compare, _Alloc>& __x,
      container::multimap<_Key, _Value, _Compare, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_MULTIMAP__
