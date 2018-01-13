
#ifndef __UTILITY_CONTAINER_WHITE_BLACK_TREE__
#define __UTILITY_CONTAINER_WHITE_BLACK_TREE__

/**
 * \file white_black_tree.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/equal.hpp>
#include<utility/algorithm/lexicographical_compare.hpp>
#include<utility/container/container_helper.hpp>
#include<utility/container/impl/pair_value.hpp>
#include<utility/container/pair.hpp>
#include<utility/container/compressed_pair.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/type/features/is_default_constructible.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/unique_ptr.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _Key,
      typename _Value,
      typename _Compare = utility::algorithm::less<_Key>,
      typename _Key_Value_Container = utility::container::pair<const _Key, _Value>,
      typename _Alloc = utility::memory::allocator<_Key_Value_Container>
    >
    class white_black_tree
    {
      private:
        template
        <
          typename __Key,
          typename __Value,
          typename __Key_Value_Container
        >
        struct __white_black_tree_node
        {
          public:
            typedef __Key                 __key_type;
            typedef __Value               __mapped_type;
            typedef __Key_Value_Container __data_type;

          public:
            typedef
              __white_black_tree_node<__Key, __Value, __Key_Value_Container>
              __self;
            typedef
              __white_black_tree_node<__Key, __Value, __Key_Value_Container>*
              __node_link;

          public:
            typedef bool __color_type;

          public:
            __node_link   __parent;
            __node_link   __left;
            __node_link   __right;
            __data_type*  __data;
            __color_type  __color;

          public:
            UTILITY_ALWAYS_INLINE
            static inline __node_link __minimum(__node_link __link)
            {
              while(__link->__left != nullptr)
              { __link = __link->__left;}
              return __link;
            }
            UTILITY_ALWAYS_INLINE
            static inline __node_link __maxmum(__node_link __link)
            {
              while(__link->__left != nullptr)
              { __link = __link->__left;}
              return __link;
            }
            UTILITY_ALWAYS_INLINE
            static inline __node_link __link_next(__node_link __link)
            {
              if(__link->__right != nullptr)
              { return __minimum(__link->__right);}
              __node_link __tmp = __link->__parent;
              while(__link == __tmp->__right)
              { __link = __tmp; __tmp = __tmp->__parent;}
              if(__link->__right != __tmp)
              { __link = __tmp;}
              return __link;
            }
            UTILITY_ALWAYS_INLINE
            static inline __node_link __link_prev(__node_link __link)
            {
              if(!__link->__color && __link->__parent->__parent == __link)
              { return __link->__right;}
              if(__link->__left != nullptr)
              { return __maxmum(__link->__left);}
              while(__link == __link->__parent->__left)
              { __link = __link->__parent;}
              return __link->__parent;
            }

        };

        template
        <
          typename __Key,
          typename __Value,
          typename __Key_Value_Container
        >
        class __white_black_tree_iterator
        {
          private:
            template<typename, typename, typename, typename, typename>
            friend class white_black_tree;
            template<typename, typename, typename>
            friend class __white_black_tree_const_iterator;

          public:
            typedef utility::iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Key                   key_type;
            typedef __Value                 mapped_type;
            typedef __Key_Value_Container   value_type;
            typedef value_type&             reference;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<value_type*>::pointer
              pointer;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<value_type*>::difference_type
              difference_type;

          public:
            typedef __white_black_tree_iterator<__Key, _Value, _Key_Value_Container> self;

          private:
            typedef __white_black_tree_node<__Key, __Value, __Key_Value_Container> __node_type;
            typedef __white_black_tree_node<__Key, __Value, __Key_Value_Container>* __link_type;

          private:
            __link_type __ptr;

          public:
            inline __white_black_tree_iterator() noexcept:
              __ptr(nullptr)
            { }
            inline explicit __white_black_tree_iterator(__link_type __link) noexcept:
              __ptr(__link)
            { }

          public:
            self& operator=(const self& __oit)
            {
              if(&__oit != this)
              { this->__ptr = __oit.__ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__ptr->__data);}
            pointer operator->() const
            { return this->__ptr->__data;}

          public:
            self& operator++() noexcept
            {
              this->__ptr = __node_type::__link_next(this->__ptr);
              return *this;
            }
            self operator++(int) noexcept
            {
              self __tmp(*this);
              this->__ptr = __node_type::__link_next(this->__ptr);
              return __tmp;
            }
            self& operator--() noexcept
            {
              this->__ptr = __node_type::__link_prev(this->__ptr);
              return *this;
            }
            self operator--(int) noexcept
            {
              self __tmp(*this);
              this->__ptr = __node_type::__link_prev(this->__ptr);
              return __tmp;
            }

          public:
            inline bool operator==(const self& __o) const noexcept
            { return this->__ptr == __o.__ptr;}
            inline bool operator!=(const self& __o) const noexcept
            { return this->__ptr != __o.__ptr;}
        };

        template
        <
          typename __Key,
          typename __Value,
          typename __Key_Value_Container
        >
        class __white_black_tree_const_iterator
        {
          private:
            template<typename, typename, typename, typename, typename>
            friend class white_black_tree;

          public:
            typedef utility::iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Key                   key_type;
            typedef __Value                 mapped_type;
            typedef __Key_Value_Container   value_type;
            typedef const value_type        const_value_type;
            typedef const value_type&       reference;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<const_value_type*>::pointer
              pointer;
            typedef typename
              utility::trait::miscellaneous::pointer_traits<const_value_type*>::difference_type
              difference_type;

          public:
            typedef __white_black_tree_const_iterator<__Key, _Value, _Key_Value_Container> self;

          private:
            typedef __white_black_tree_node<__Key, __Value, __Key_Value_Container> __node_type;
            typedef __white_black_tree_node<__Key, __Value, __Key_Value_Container>* __link_type;

          private:
            __link_type __ptr;

          public:
            inline __white_black_tree_const_iterator() noexcept:
              __ptr(nullptr)
            { }
            inline explicit __white_black_tree_const_iterator(__link_type __link) noexcept:
              __ptr(__link)
            { }
            inline __white_black_tree_const_iterator(
              const __white_black_tree_iterator<__Key, __Value, __Key_Value_Container>& __it
            ) noexcept:
              __ptr(__it.__ptr)
            { }

          public:
            self& operator=(const self& __oit)
            {
              if(&__oit != this)
              { this->__ptr = __oit.__ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__ptr->__data);}
            pointer operator->() const
            { return this->__ptr->__data;}

          public:
            self& operator++() noexcept
            {
              this->__ptr = __node_type::__link_next(this->__ptr);
              return *this;
            }
            self operator++(int) noexcept
            {
              self __tmp(*this);
              this->__ptr = __node_type::__link_next(this->__ptr);
              return __tmp;
            }
            self& operator--() noexcept
            {
              this->__ptr = __node_type::__link_prev(this->__ptr);
              return *this;
            }
            self operator--(int) noexcept
            {
              self __tmp(*this);
              this->__ptr = __node_type::__link_prev(this->__ptr);
              return __tmp;
            }

          public:
            bool operator==(const self& __o) const noexcept
            { return this->__ptr == __o.__ptr;}
            bool operator!=(const self& __o) const noexcept
            { return this->__ptr != __o.__ptr;}
        };

      private:
        constexpr static bool __white = true;
        constexpr static bool __black = false;

      private:
        typedef __white_black_tree_node<_Key, _Value, _Key_Value_Container> __node_type;
        typedef __node_type* __link_type;
        typedef utility::memory::allocator<__node_type>
          __node_allocator_type;
        typedef utility::memory::allocator_traits<__node_allocator_type>
          __node_allocator_traits_type;

      public:
        typedef _Key                  key_type;
        typedef _Value                mapped_type;
        typedef _Key_Value_Container  value_type;
        typedef _Compare              key_compare;
        typedef utility::size_t     size_type;
        typedef utility::ptrdiff_t  difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;
        typedef _Alloc                allocator_type;

      private:
        typedef utility::memory::unique_ptr<value_type>
          __value_container;
        typedef utility::memory::unique_ptr<__node_type>
          __node_container;

      public:
        typedef utility::memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef __white_black_tree_iterator<key_type, mapped_type, value_type>
          iterator;
        typedef __white_black_tree_const_iterator<key_type, mapped_type, value_type>
          const_iterator;
        typedef
          utility::iterator::reverse_iterator<iterator> reverse_iterator;
        typedef
          utility::iterator::reverse_iterator<const_iterator> const_reverse_iterator;

      public: // assert:
        static_assert(::utility::trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        __link_type             __head;
        size_type               __size;
        key_compare             __compare;
        allocator_type          __allocator;
        __node_allocator_type   __node_allocator;

      public:
        template<typename _Comp = _Compare,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        explicit white_black_tree():
          __size(0), __compare(), __allocator(), __node_allocator()
        { this->__init();}

        template<typename _Comp = _Compare,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_copy_constructible<_Comp>::value,
          bool
          >::type = true
        >
        explicit white_black_tree(
          const key_compare& __comp,
          const allocator_type& __alloc = allocator_type()
        ): __size(0), __compare(__comp),
           __allocator(__alloc), __node_allocator()
        { this->__init();}

        template<typename _Comp = _Compare,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(const allocator_type& __alloc):
          __size(0), __compare(),
          __allocator(__alloc), __node_allocator()
        { this->__init();}

        template<typename _InputIterator, typename _Comp = _Compare,
        typename
        utility::trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_copy_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(
          _InputIterator __first, _InputIterator __last,
          const key_compare& __comp = key_compare(),
          const allocator_type& __alloc = allocator_type()
        ): __size(0), __compare(__comp),
           __allocator(__alloc), __node_allocator()
        {
          this->__init();
          for(; __first != __last;)
          { this->insert_equal(*__first++);}
        }
        template<typename _Comp = _Compare, typename _InputIterator,
        typename
        utility::trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        utility::trait::type::miscellaneous::enable_if<
          utility::trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(
          _InputIterator __first, _InputIterator __last,
          const allocator_type& __alloc
        ): __size(0), __compare(),
           __allocator(__alloc), __node_allocator()
        {
          this->__init();
          for(; __first != __last;)
          { this->insert_equal(*__first++);}
        }


        white_black_tree(const white_black_tree& __o):
          __size(__o.__size), __compare(__o.__compare),
          __allocator(__o.__allocator), __node_allocator()
        {
          this->__init();
          this->__wb_tree_copy(
            this->__head->__parent, (__o.__head)->__parent
          );
          this->__head->__parent->__parent = this->__head;
          this->__head->__left =
            __node_type::__minimum(this->__head->__parent);
          this->__head->__right =
            __node_type::__maxmum(this->__head->__parent);
        }
        white_black_tree(
          const white_black_tree& __o,
          const allocator_type& __alloc
        ): __size(__o.__size), __compare(__o.__compare),
           __allocator(__alloc), __node_allocator()
        {
          this->__init();
          this->__wb_tree_copy(
            this->__head->__parent, (__o.__head)->__parent
          );
          this->__head->__parent->__parent = this->__head;
          this->__head->__left =
            __node_type::__minimum(this->__head->__parent);
          this->__head->__right =
            __node_type::__maxmum(this->__head->__parent);
        }

        white_black_tree(white_black_tree&& __o):
          __head(__o.__head),
          __size(__o.__size),
          __compare(::utility::algorithm::move(__o.__compare)),
          __allocator(::utility::algorithm::move(__o.__allocator)),
          __node_allocator()
        { __o.__head = nullptr;}
        white_black_tree(
          white_black_tree&& __o,
          const allocator_type& __alloc
        ): __head(__o.__head),
           __size(__o.__size),
           __compare(::utility::algorithm::move(__o.__compare)),
           __allocator(__alloc),
           __node_allocator()
        { __o.__head = nullptr;}

        white_black_tree(
          utility::container::initializer_list<value_type> __init,
          const key_compare& __comp = key_compare(),
          const allocator_type& __alloc = allocator_type()
        ):  __size(0), __compare(__comp),
           __allocator(__alloc), __node_allocator()
        {
          typedef typename
            utility::container::initializer_list<value_type>::iterator
            __iterator;
          this->__init();
          for(__iterator __it = __init.begin(), __end = __init.end(); __it != __end;)
          { this->insert_equal(*__it++);}
        }

        ~white_black_tree()
        {
          if(this->__head != nullptr)
          { this->force_clear();}
        }

      public:
        white_black_tree& operator=(const white_black_tree& __o)
        {
          if(this != &__o)
          {
            this->__allocator = __o.__allocator;
            this->__node_allocator = __o.__node_allocator;
            this->__size = __o.__size;
            this->__compare = __o.__compare;
            if(this->__head == nullptr)
            { this->__init();}
            else
            { this->clear();}
            this->__wb_tree_copy(
              this->__head->__parent, (__o.__head)->__parent
            );
            this->__head->__parent->__parent = this->__head;
            this->__head->__left =
              __node_type::__minimum(this->__head->__parent);
            this->__head->__right =
              __node_type::__maxmum(this->__head->__parent);
          }
          return *this;
        }

        white_black_tree& operator=(white_black_tree&& __o)
        {
          if(this != &__o)
          {
            this->__allocator =
              utility::algorithm::move(__o.__allocator);
            this->__node_allocator =
              utility::algorithm::move(__o.__node_allocator);
            this->__size = __o.__size;
            this->__compare =
              utility::algorithm::move(__o.__compare);
            if(this->__head != nullptr)
            { this->force_clear();}
            this->__head = __o.__head;
            __o.__head = nullptr;
          }
          return *this;
        }
        white_black_tree& operator=(
          utility::container::initializer_list<value_type> __init
        )
        {
          typedef typename
            utility::container::initializer_list<value_type>::iterator
            __iterator;
          this->__size = 0U;
          if(this->__head == nullptr)
          { this->__init();}
          else
          { this->clear();}
          for(__iterator __it = __init.begin(), __end = __init.end(); __it != __end;)
          { this->insert_equal(*__it++);}

          return *this;
        }

      public:
        iterator begin() noexcept
        { return iterator(this->__head->__left);}
        const_iterator begin() const noexcept
        { return const_iterator(this->__head->__left);}
        const_iterator cbegin() const noexcept
        { return const_iterator(this->__head->__left);}
        iterator end() noexcept
        { return iterator(this->__head);}
        const_iterator end() const noexcept
        { return const_iterator(this->__head);}
        const_iterator cend() const noexcept
        { return const_iterator(this->__head);}

      public:
        bool empty() const noexcept
        { return this->__head->__parent == nullptr;}
        size_type size() const noexcept
        { return this->__size;}

      public:
        reference minmum()
        {
          return const_cast<reference>(
            __get_value(*(this->__head->__left->__data))
          );
        }
        const_reference minmum() const
        { return __get_value(*(this->__head->__left->__data));}
        reference maxmum()
        {
          return const_cast<reference>(
            __get_value(*(this->__head->__right->__data))
          );
        }
        const_reference maxmum() const
        { return __get_value(*(this->__head->__right->__data));}


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
        utility::container::pair<iterator, bool>
        insert_unique(const value_type& __val)
        { return __insert_unique(__allocate_node(this, __val), this);}
        utility::container::pair<iterator, bool>
        insert_unique(value_type&& __val)
        {
          return __insert_unique(
            __allocate_node(this, utility::algorithm::move(__val)), this
          );
        }
        iterator insert_unique(
          const_iterator __hint, const value_type& __val
        )
        {
          return __insert_unique(
            __hint.__ptr ,__allocate_node(this, __val), this
          );
        }
        iterator insert_unique(const_iterator __hint, value_type&& __val)
        {
          return __insert_unique(
            __hint.__ptr,
            __allocate_node(this, utility::algorithm::move(__val)), this
          );
        }
        iterator insert_equal(const value_type& __val)
        { return __insert_equal(__allocate_node(this, __val), this);}
        iterator insert_equal(value_type&& __val)
        {
          return __insert_equal(
            __allocate_node(this, utility::algorithm::move(__val)), this
          );
        }
        iterator insert_equal(
          const_iterator __hint, const value_type& __val
        )
        {
          return __insert_equal(
            __hint.__ptr ,__allocate_node(this, __val), this
          );
        }
        iterator insert_equal(const_iterator __hint, value_type&& __val)
        {
          return __insert_equal(
            __hint.__ptr,
            __allocate_node(this, utility::algorithm::move(__val)), this
          );
        }

      public:
        template<typename... _Args>
        utility::container::pair<iterator, bool>
        emplace_unique(_Args&&... __args)
        {
          return __insert_unique(
            __allocate_node(
              this, utility::algorithm::forward<_Args>(__args)...
            ), this
          );
        }
        template<typename... _Args>
        iterator emplace_equal(_Args&&... __args)
        {
          return __insert_equal(
            __allocate_node(
              this, utility::algorithm::forward<_Args>(__args)...
            ), this
          );
        }
        template<typename... _Args>
        iterator emplace_unique_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          return __insert_unique(
            __hint.__ptr,
            __allocate_node(
              this, utility::algorithm::forward<_Args>(__args)...
            ), this
          );
        }
        template<typename... _Args>
        iterator emplace_equal_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          return __insert_equal(
            __hint.__ptr,
            __allocate_node(
              this, utility::algorithm::forward<_Args>(__args)...
            ), this
          );
        }

      public:
        size_type count(const key_type& __key) const noexcept
        {
          return utility::iterator::distance(
            this->lower_bound(__key),
            this->upper_bound(__key)
          );
        }

      public:
        inline iterator find(const key_type& __key) noexcept
        {
          iterator __res(const_cast<__link_type>(__lower_bound(this, __key)));
          return (__res == this->end() || this->__compare(__key, __get_key(*(__res.__ptr->__data)))) ?
            this->end() : __res;
        }
        inline const_iterator find(const key_type& __key) const noexcept
        {
          const_iterator __res(const_cast<__link_type>(__lower_bound(this, __key)));
          return (__res == this->end() || this->__compare(__key, __get_key(*(__res.__ptr->__data)))) ?
            this->end() : __res;
        }

      public:
        inline iterator lower_bound(const key_type& __key) noexcept
        { return iterator(const_cast<__link_type>(__lower_bound(this, __key)));}
        inline const_iterator lower_bound(const key_type& __key) const noexcept
        { return const_iterator(const_cast<__link_type>(__lower_bound(this, __key)));}
        inline iterator upper_bound(const key_type& __key) noexcept
        { return iterator(const_cast<__link_type>(__upper_bound(this, __key)));}
        inline const_iterator upper_bound(const key_type& __key) const noexcept
        { return const_iterator(const_cast<__link_type>(__upper_bound(this, __key)));}
        inline utility::container::pair<iterator, iterator>
        equal_range(const key_type& __key) noexcept
        {
          return utility::container::pair<iterator, iterator>(
            this->lower_bound(__key), this->upper_bound(__key)
          );
        }
        inline utility::container::pair<const_iterator, const_iterator>
        equal_range(const key_type& __key) const noexcept
        {
          return utility::container::pair<const_iterator, const_iterator>(
            this->lower_bound(__key), this->upper_bound(__key)
          );
        }

      public:
        inline void erase(const_iterator __pos)
        {
          __link_type __del = __erase_rebalance(
            __pos.__ptr, this->__head->__parent,
            this->__head->__left, this->__head->__right
          );
          __deallocate_node(__del, this);
          --(this->__size);
          return;
        }
        inline void erase(const_iterator __first, const_iterator __last)
        {
          if(__first == this->begin() && __last == this->end())
          { this->clear();}
          else
          {
            for(;__first != __last;)
            { this->erase(__first++);}
          }
        }
        inline void erase(const key_type& __key)
        {
          utility::container::pair<const_iterator, const_iterator>  __tmp =
            this->equal_range(__key);
          this->erase(__tmp.first, __tmp.second);
        }

      public:
        void clear()
        {
          if(!this->empty())
          {
            this->__node_clear(this->__head->__parent);
            this->__size = 0U;
            this->__head->__parent = nullptr;
            this->__head->__left = this->__head->__right = this->__head;
            this->__head->__color = __white;
          }
        }

      public:
        template<
          typename _Key_Compare = key_compare,
          typename utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_swappable<_Key_Compare>::value,
          bool>::type = true
        >
        void swap(white_black_tree& __other) noexcept(
          utility::trait::type::features::is_nothrow_swappable<key_compare>::value
        )
        {
          using utility::algorithm::swap;
          swap(this->__head, __other.__head);
          swap(this->__size, __other.__size);
          swap(this->__compare, __other.__compare);
          return;
        }
        template<
          typename _Key_Compare = key_compare, typename __Alloc = allocator_type,
          typename utility::trait::type::miscellaneous::enable_if<
            utility::trait::type::features::is_possible_swappable<_Key_Compare>::value &&
            utility::trait::type::features::is_possible_swappable<__Alloc>::value,
          bool>::type = true
        >
        void possible_swap(white_black_tree& __other) noexcept(
          utility::trait::type::features::is_nothrow_possible_swappable<key_compare>::value
        )
        {
          using utility::algorithm::possible_swap;
          possible_swap(this->__allocator, __other.__allocator);
          possible_swap(this->__head,      __other.__head     );
          possible_swap(this->__size,      __other.__size     );
          possible_swap(this->__compare,   __other.__compare  );
          return;
        }

      private:
        void force_clear()
        {
          this->clear();
          this->__head->__left = this->__head->__right = nullptr;
          __node_allocator_traits_type::deallocate(
            this->__node_allocator, this->__head
          );
          this->__head = nullptr;
        }

      private:
        void __init()
        {
          this->__head =
            __node_allocator_traits_type::allocate(
              this->__node_allocator
            );
          this->__head->__parent = nullptr;
          this->__head->__color = __white;
          this->__head->__left = this->__head->__right = this->__head;
        }
        void __node_clear(__link_type __root)
        {
          allocator_traits_type::deallocate(
            this->__allocator, __root->__data
          );
          if(__root->__left != nullptr)
          { this->__node_clear(__root->__left);}
          if(__root->__right != nullptr)
          { this->__node_clear(__root->__right);}
          __root->__left = __root->__right = __root->__parent = nullptr;
          __node_allocator_traits_type::deallocate(
            this->__node_allocator, __root
          );
          return;
        }
        void __wb_tree_copy(__link_type& __root, const __node_type* __o)
        {
          __root = __allocate_node(this, *(__o->__data));
          __root->__color   = __o->__color;
          __root->__left    = nullptr;
          __root->__right   = nullptr;
          if(__o->__left != nullptr)
          {
            this->__wb_tree_copy(__root->__left,  __o->__left);
            __root->__left->__parent = __root;
          }
          if(__o->__right != nullptr)
          {
            this->__wb_tree_copy(__root->__right, __o->__right);
            __root->__right->__parent = __root;
          }
          return;
        }

      private:
        static inline const __node_type* __lower_bound(
          const white_black_tree* __this, const key_type& __key
        )
        {
          const __node_type* __header = __this->__head;
          const __node_type* __pos = __this->__head->__parent;

          for(; __pos != nullptr;)
          {
            if(!__this->__compare(
              __get_key(*(__pos->__data)), __key
            ))
            { __header = __pos, __pos = __pos->__left;}
            else
            { __pos = __pos->__right;}
          }
          return __header;
        }
        static inline const __node_type* __upper_bound(
          const white_black_tree* __this, const key_type& __key
        )
        {
          const __node_type* __header = __this->__head;
          const __node_type* __pos = __this->__head->__parent;

          for(; __pos != nullptr;)
          {
            if(__this->__compare(
              __key, __get_key(*(__pos->__data))
            ))
            { __header = __pos, __pos = __pos->__left;}
            else
            { __pos = __pos->__right;}
          }
          return __header;
        }

      private:
        static utility::container::pair<iterator, bool>
        __insert_unique(
          __link_type __ins, white_black_tree* __this
        ) noexcept
        {
          __link_type __header = __this->__head;
          __link_type __pos = __this->__head->__parent;
          bool __comp = true;

          for(;__pos != nullptr;)
          {
            __header = __pos;
            __comp = __this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__pos->__data))
            );
            __pos = __comp ? __pos->__left : __pos->__right;
          }

          iterator __tmp(__header);
          if(__comp)
          {
            if(__tmp == __this->begin())
            {
              return utility::container::pair<iterator, bool>(
                __insert(__pos, __header, __ins, __this), true
              );
            }
            else
            { --__tmp;}
          }
          if(__this->__compare(
            __get_key(*(__tmp.__ptr->__data)), __get_key(*(__ins->__data))
          ))
          {
            return utility::container::pair<iterator, bool>(
              __insert(__pos, __header, __ins, __this), true
            );
          }
          __deallocate_node(__ins, __this);
          return utility::container::pair<iterator, bool>(__tmp, false);
        }
        static iterator __insert_unique(
          __link_type __pos, __link_type __ins,
          white_black_tree* __this
        ) noexcept
        {
          // The first node.
          if(__pos == __this->__head->__left)
          {
            if(__this->__size > 0 && __this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__pos->__data))
            ))
            { return __insert(__pos, __pos, __ins, __this);}
            return __insert_unique(__ins, __this).first;
          }
          // The last node.
          if(__pos == __this->__head)
          {
            if(__this->__compare(
              __get_key(*(__this->__head->__right->__data)), __get_key(*(__ins->__data))
            ))
            { return __insert(nullptr, __this->__head->__right, __ins, __this);}
            return __insert_unique(__ins, __this).first;
          }

          __link_type __before = __node_type::__link_prev(__pos);
          if(__this->__compare(__get_key(*(__before->__data)), __get_key(*(__ins->__data))) &&
             __this->__compare(__get_key(*(__ins->__data)), __get_key(*(__pos->__data))))
          {
            if(__before->__right == nullptr)
            { return __insert(nullptr, __before, __ins, __this);}
            return __insert(__pos, __pos, __ins, __this);
          }
          return __insert_unique(__ins, __this).first;
        }

        static iterator __insert_equal(
          __link_type __ins, white_black_tree* __this
        ) noexcept
        {
          __link_type __header = __this->__head;
          __link_type __pos = __this->__head->__parent;
          for(; __pos != nullptr;)
          {
            __header = __pos;
            __pos = __this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__pos->__data))
            ) ? __pos->__left : __pos->__right;
          }
          return __insert(__pos, __header, __ins, __this);
        }
        static iterator __insert_equal(
          __link_type __pos, __link_type __ins,
          white_black_tree* __this
        ) noexcept
        {
          // The first node.
          if(__pos == __this->__head->__left)
          {
            if(__this->__size > 0 && !(__this->__compare(
              __get_key(*(__pos->__data)), __get_key(*(__ins->__data))
            )))
            { return __insert(__pos, __pos, __ins, __this);}
            return __insert_equal(__ins, __this);
          }
          // The last node.
          if(__pos == __this->__head)
          {
            if(!(__this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__this->__head->__right->__data))
            )))
            { return __insert(nullptr, __this->__head->__right, __ins, __this);}
            return __insert_equal(__ins, __this);
          }

          __link_type __before = __node_type::__link_prev(__pos);
          if(!(__this->__compare(__get_key(*(__ins->__data)), __get_key(*(__before->__data)))) &&
             !(__this->__compare(__get_key(*(__pos->__data)), __get_key(*(__ins->__data)))))
          {
            if(__before->__right == nullptr)
            { return __insert(nullptr, __before, __ins, __this);}
            return __insert(__pos, __pos, __ins, __this);
          }
          return __insert_equal(__ins, __this);
        }


        static inline iterator __insert(
          __link_type __x, __link_type __y,
          __link_type __z, white_black_tree* __this
        ) noexcept
        {
          if(__y == __this->__head || __x != nullptr ||
            __this->__compare(
              __get_key(*(__z->__data)), __get_key(*(__y->__data))
            )
          )
          {
            __y->__left = __z;
            if(__y == __this->__head)
            {
              __this->__head->__parent = __z;
              __this->__head->__right = __z;
            }
            else if(__y == __this->__head->__left)
            { __this->__head->__left = __z;}
          }
          else
          {
            __y->__right = __z;
            if(__y == __this->__head->__right)
            { __this->__head->__right = __z;}
          }
          __z->__parent = __y;
          __z->__right = __z->__left = nullptr;
          __insert_rebalance(__z, __this->__head->__parent);
          ++(__this->__size);
          return iterator(__z);
        }

      private:
        template<typename... _Args>
        static inline __link_type __allocate_node(
          white_black_tree* __this, _Args&&... __args
        )
        {
          __value_container __value_holder(
            allocator_traits_type::allocate(__this->__allocator)
          );
          allocator_traits_type::construct(
            __this->__allocator, __value_holder.get(),
            utility::algorithm::forward<_Args>(__args)...
          );
          __node_container __node_holder(
            __node_allocator_traits_type::allocate(__this->__node_allocator)
          );
          __node_holder->__data = __value_holder.release();
          return __node_holder.release();
        }
        static inline void __deallocate_node(
          __link_type __pos, white_black_tree* __this
        )
        {
          if(__pos->__data != nullptr)
          {
            allocator_traits_type::deallocate(
              __this->__allocator, __pos->__data
            );
          }
          __node_allocator_traits_type::deallocate(
            __this->__node_allocator, __pos
          );
        }

      private:
        static inline void __rotate_left(
          __link_type __x, __link_type& __root
        )
        {
          // Get right node __y
          __link_type __y = __x->__right;
          __x->__right = __y->__left;

          // set __y's left child parent
          if(__y->__left != nullptr)
          { __y->__left->__parent = __x;}
          __y->__parent = __x->__parent;

          // set __y's position
          if(__x == __root)
          { __root = __y;}
          else if(__x == __x->__parent->__left)
          { __x->__parent->__left = __y;}
          else
          { __x->__parent->__right = __y;}

          // link __x and __y
          __y->__left = __x;
          __x->__parent = __y;
        }
        static inline void __rotate_right(
          __link_type __x, __link_type& __root
        )
        {
          __link_type __y = __x->__left;
          __x->__left = __y->__right;

          if(__y->__right != nullptr)
          { __y->__right->__parent = __x;}
          __y->__parent = __x->__parent;

          if(__x == __root)
          { __root = __y;}
          else if(__x == __x->__parent->__right)
          { __x->__parent->__right = __y;}
          else
          { __x->__parent->__left = __y;}

          __y->__right = __x;
          __x->__parent = __y;
        }

        static void __insert_rebalance(
          __link_type __x, __link_type& __root
        )
        {
          __x->__color = __white;
          for(;__x != __root && __x->__parent->__color == __white;)
          {
            if(__x->__parent == __x->__parent->__parent->__left)
            {
              __link_type __y = __x->__parent->__parent->__right;
              if(__y != nullptr && __y->__color == __white)
              {
                __x->__parent->__color = __black;
                __y->__color = __black;
                __x->__parent->__parent->__color = __white;
                __x = __x->__parent->__parent;
              }
              else
              {
                if(__x == __x->__parent->__right)
                {
                  __x = __x->__parent;
                  __rotate_left(__x, __root);
                }
                __x->__parent->__color = __black;
                __x->__parent->__parent->__color = __white;
                __rotate_right(__x->__parent->__parent, __root);
              }
            }
            else
            {
              __link_type __y = __x->__parent->__parent->__left;
              if(__y != nullptr && __y->__color == __white)
              {
                __x->__parent->__color = __black;
                __y->__color = __black;
                __x->__parent->__parent->__color = __white;
                __x = __x->__parent->__parent;
              }
              else
              {
                if(__x == __x->__parent->__left)
                {
                  __x = __x->__parent;
                  __rotate_right(__x, __root);
                }
                __x->__parent->__color = __black;
                __x->__parent->__parent->__color = __white;
                __rotate_left(__x->__parent->__parent, __root);
              }
            }
          }
          __root->__color = __black;
        }
        static __link_type __erase_rebalance(
          __link_type __z,         __link_type& __root,
          __link_type& __leftmost, __link_type& __rightmost
        )
        {
          __link_type __y = __z;
          __link_type __x = nullptr;
          __link_type __x_par = nullptr;

          if(__y->__left == nullptr)
          { __x = __y->__right;}
          else
          {
            if(__y->__right == nullptr)
            { __x = __y->__left;}
            else
            {
              __y = __y->__right;
              for(;__y->__left != nullptr;)
              { __y = __y->__left;}
              __x = __y->__right;
            }
          }

          if(__y != __z)
          {
            __z->__left->__parent = __y;
            __y->__left = __z->__left;
            if(__y != __z->__right)
            {
              __x_par = __y->__parent;
              if(__x != nullptr)
              { __x->__parent = __y->__parent;}
              __y->__parent->__left = __x;
              __y->__right = __z->__right;
              __z->__right->__parent = __y;
            }
            else
            { __x_par = __y;}

            if(__root == __z)
            { __root = __y;}
            else if(__z->__parent->__left == __z)
            { __z->__parent->__left = __y;}
            else
            { __z->__parent->__right = __y;}

            __y->__parent = __z->__parent;
            utility::algorithm::swap(__y->__color, __z->__color);
            __y = __z;
          }
          else
          {
            __x_par = __y->__parent;
            if(__x != nullptr)
            { __x->__parent= __y->__parent;}

            if(__root == __z)
            { __root = __x;}
            else if(__z->__parent->__left == __z)
            { __z->__parent->__left = __x;}
            else
            { __z->__parent->__right = __x;}

            if(__leftmost == __z)
            {
              if(__z->__right == nullptr)
              { __leftmost = __z->__parent;}
              else
              { __leftmost = __node_type::__minimum(__x);}
            }
            if(__rightmost == __z)
            {
              if(__z->__left == nullptr)
              { __rightmost = __z->__parent;}
              else
              { __rightmost = __node_type::__maxmum(__x);}
            }
          }

          if(__y->__color != __white)
          {
            for(; __x != __root && (__x == nullptr || __x->__color == __black);)
            {
              if(__x == __x_par->__left)
              {
                __link_type __w = __x_par->__right;
                if(__w->__color == __white)
                {
                  __w->__color = __black;
                  __x_par->__color = __white;
                  __rotate_left(__x_par, __root);
                  __w = __x_par->__right;
                }

                if((__w->__left == nullptr ||
                    __w->__left->__color == __black) &&
                   (__w->__right == nullptr ||
                    __w->__right->__color == __black)
                )
                {
                  __w->__color = __white;
                  __x = __x_par;
                  __x_par = __x_par->__parent;
                }
                else
                {
                  if(__w->__right == nullptr ||
                     __w->__right->__color == __black)
                  {
                    if(__w->__left != nullptr)
                    { __w->__left->__color = __black;}
                    __w->__color = __white;
                    __rotate_right(__w, __root);
                    __w = __x_par->__right;
                  }
                  __w->__color = __x_par->__color;
                  __x_par->__color = __black;
                  if(__w->__right != nullptr)
                  { __w->__right->__color = __black;}
                  __rotate_left(__x_par, __root);
                  break;
                }
              }
              else
              {
                __link_type __w = __x_par->__left;
                if(__w->__color == __white)
                {
                  __w->__color = __black;
                  __x_par->__color = __white;
                  __rotate_right(__x_par, __root);
                  __w = __x_par->__left;
                }

                if((__w->__right == nullptr ||
                    __w->__right->__color == __black) &&
                   (__w->__left == nullptr ||
                    __w->__left->__color == __black)
                )
                {
                  __w->__color = __white;
                  __x = __x_par;
                  __x_par = __x_par->__parent;
                }
                else
                {
                  if(__w->__left == nullptr ||
                     __w->__left->__color == __black
                  )
                  {
                    if(__w->__right != nullptr)
                    { __w->__right->__color = __black;}
                    __w->__color = __white;
                    __rotate_left(__w, __root);
                    __w = __x_par->__left;
                  }
                  __w->__color = __x_par->__color;
                  __x_par->__color = __black;
                  if(__w->__left != nullptr)
                  { __w->__left->__color = __black;}
                  __rotate_right(__x_par, __root);
                  break;
                }
              }
            }
            if(__x != nullptr)
            { __x->__color = __black;}
          }
          return __y;
        }

      private:
        UTILITY_ALWAYS_INLINE
        static inline const key_type& __get_key(const value_type& __con)
        {
          using utility::container::get_key;
          return get_key(__con);
        }
        UTILITY_ALWAYS_INLINE
        static inline const key_type& __get_value(const value_type& __con)
        {
          using utility::container::get_key;
          return get_value(__con);
        }
    };

    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator==(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    {
      return __x.size() == __y.size() &&
        utility::algorithm::equal(__x.begin(), __x.end(), __y.begin());
    }
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator!=(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    { return !(__x == __y);}
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator<(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    {
      return utility::algorithm::lexicographical_compare(
        __x.begin(), __x.end(), __y.begin(), __y.end()
      );
    }
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator>(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    { return __y < __x;}
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator<=(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    { return !(__y < __x);}
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc
    >
    inline bool operator>=(
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      const white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    )
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc,
      typename utility::trait::type::miscellaneous::enable_if<
        utility::trait::type::features::is_swappable<_Compare>::value,
      bool>::type = true
    >
    void swap(
      ::utility::container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      ::utility::container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc,
      typename utility::trait::type::miscellaneous::enable_if<
        utility::trait::type::features::is_possible_swappable<_Compare>::value &&
        utility::trait::type::features::is_possible_swappable<_Alloc>::value,
      bool>::type = true
    >
    void possible_swap(
      ::utility::container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      ::utility::container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_WHITE_BLACK_TREE__
