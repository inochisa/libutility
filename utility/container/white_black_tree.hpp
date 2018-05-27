
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
      typename _Compare = algorithm::less<_Key>,
      typename _Key_Value_Container = container::pair<const _Key, _Value>,
      typename _Alloc = memory::allocator<_Key_Value_Container>
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
            static inline __node_link __minimum(__node_link __link) noexcept
            {
              while(__link->__left != nullptr)
              { __link = __link->__left;}
              return __link;
            }
            UTILITY_ALWAYS_INLINE
            static inline __node_link __maxmum(__node_link __link) noexcept
            {
              while(__link->__left != nullptr)
              { __link = __link->__left;}
              return __link;
            }
            UTILITY_ALWAYS_INLINE
            static inline __node_link __link_next(__node_link __link) noexcept
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
            static inline __node_link __link_prev(__node_link __link) noexcept
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
            typedef iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Key                   key_type;
            typedef __Value                 mapped_type;
            typedef __Key_Value_Container   value_type;
            typedef value_type&             reference;
            typedef typename
              trait::miscellaneous::pointer_traits<value_type*>::pointer
              pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<value_type*>::difference_type
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
            self& operator=(const self& __oit) noexcept
            {
              if(&__oit != this)
              { this->__ptr = __oit.__ptr;}
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
            inline bool operator==(const self& __other) const noexcept
            { return this->__ptr == __other.__ptr;}
            inline bool operator!=(const self& __other) const noexcept
            { return this->__ptr != __other.__ptr;}
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
            typedef iterator::bidirectional_iterator_tag
              iterator_category;
            typedef __Key                   key_type;
            typedef __Value                 mapped_type;
            typedef __Key_Value_Container   value_type;
            typedef const value_type        const_value_type;
            typedef const value_type&       reference;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::pointer
              pointer;
            typedef typename
              trait::miscellaneous::pointer_traits<const_value_type*>::difference_type
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
            self& operator=(const self& __oit) noexcept
            {
              if(&__oit != this)
              { this->__ptr = __oit.__ptr;}
              return *this;
            }
            self& operator=(
               const __white_black_tree_iterator<__Key, __Value, __Key_Value_Container>& __oit
            ) noexcept
            {
              this->__ptr = __oit.__ptr;
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
            bool operator==(const self& __other) const noexcept
            { return this->__ptr == __other.__ptr;}
            bool operator!=(const self& __other) const noexcept
            { return this->__ptr != __other.__ptr;}
        };

      private:
        constexpr static bool __white = true;
        constexpr static bool __black = false;

      private:
        typedef __white_black_tree_node<_Key, _Value, _Key_Value_Container> __node_type;
        typedef __node_type* __link_type;
        typedef memory::allocator<__node_type>
          __node_allocator_type;
        typedef memory::allocator_traits<__node_allocator_type>
          __node_allocator_traits_type;

      public:
        typedef _Key                  key_type;
        typedef _Value                mapped_type;
        typedef _Key_Value_Container  value_type;
        typedef _Compare              key_compare;
        typedef size_t       size_type;
        typedef ptrdiff_t    difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;
        typedef _Alloc                allocator_type;

      private:
        typedef memory::unique_ptr<value_type>
          __value_container;
        typedef memory::unique_ptr<__node_type>
          __node_container;

      public:
        typedef memory::allocator_traits<allocator_type>
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
          iterator::reverse_iterator<iterator> reverse_iterator;
        typedef
          iterator::reverse_iterator<const_iterator> const_reverse_iterator;

      public: // assert:
        static_assert(trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        typedef container::compressed_pair<__link_type, __node_allocator_type>   __node_pair;
        typedef container::compressed_pair<size_type, allocator_type>  __mis_type;


      private:
        __node_pair     __base;
        __mis_type      __mis;
        key_compare     __compare;
        // __link_type             __head;
        // size_type               __size;
        // allocator_type          __allocator;
        // __node_allocator_type   __node_allocator;

      public:
        template<typename _Comp = _Compare,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        explicit white_black_tree():
          __base{nullptr, __node_allocator_type()},
          __mis{0U, allocator_type()},
          __compare{}
        { this->__init();}

        template<typename _Comp = _Compare,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Comp>::value,
          bool
          >::type = true
        >
        explicit white_black_tree(
          const key_compare& __comp,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{__comp}
        { this->__init();}

        template<typename _Comp = _Compare,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(const allocator_type& __alloc):
          __base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{}
        { this->__init();}

        template<typename _InputIterator, typename _Comp = _Compare,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(
          _InputIterator __first, _InputIterator __last,
          const key_compare& __comp = key_compare(),
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{__comp}
        {
          this->__init();
          for(; __first != __last;)
          { this->insert_equal(*__first++);}
        }
        template<typename _Comp = _Compare, typename _InputIterator,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_default_constructible<_Comp>::value,
          bool
          >::type = true
        >
        white_black_tree(
          _InputIterator __first, _InputIterator __last,
          const allocator_type& __alloc
        ):__base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{}
        {
          this->__init();
          for(; __first != __last;)
          { this->insert_equal(*__first++);}
        }


        white_black_tree(const white_black_tree& __other):
          __base{nullptr, __node_allocator_type()},
          __mis{__other.__mis.first(), __other.__mis.second()},
          __compare{__other.__compare}
        {
          this->__init();
          __link_type __head = this->__base.first();
          const __node_type* __ohead = __other.__base.first();
          this->__wb_tree_copy(
            __head->__parent, __ohead->__parent
          );
          __head->__parent->__parent = __head;
          __head->__left = __node_type::__minimum(__head->__parent);
          __head->__right = __node_type::__maxmum(__head->__parent);
        }
        white_black_tree(
          const white_black_tree& __other,
          const allocator_type& __alloc
        ):__base{nullptr, __node_allocator_type()},
          __mis{__other.__mis.first(), __alloc},
          __compare{__other.__compare}
        {
          this->__init();
          __link_type __head = this->__base.first();
          const __node_type* __ohead = __other.__base.first();
          this->__wb_tree_copy(
            __head->__parent, __ohead->__parent
          );
          __head->__parent->__parent = __head;
          __head->__left = __node_type::__minimum(__head->__parent);
          __head->__right = __node_type::__maxmum(__head->__parent);
        }

        white_black_tree(white_black_tree&& __other):
          __base{algorithm::move(__other.__base)},
          __mis{algorithm::move(__other.__mis)},
          __compare(algorithm::move(__other.__compare))
        { __other.__base.first() = nullptr;}
        white_black_tree(
          white_black_tree&& __other,
          const allocator_type& __alloc
        ):__base{algorithm::move(__other.__base)},
          __mis{__other.__mis.first(), __alloc},
          __compare(algorithm::move(__other.__compare))
        { __other.__base.first() = nullptr;}

        white_black_tree(
          container::initializer_list<value_type> __init,
          const key_compare& __comp,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{__comp}
        {
          typedef typename
            container::initializer_list<value_type>::iterator
            __iterator;
          this->__init();
          for(__iterator __it = __init.begin(), __end = __init.end(); __it != __end;)
          { this->insert_equal(*__it++);}
        }
        white_black_tree(
          container::initializer_list<value_type> __init,
          const allocator_type& __alloc = allocator_type()
        ):__base{nullptr, __node_allocator_type()},
          __mis{0U, __alloc},
          __compare{}
        {
          typedef typename
            container::initializer_list<value_type>::iterator
            __iterator;
          this->__init();
          for(__iterator __it = __init.begin(), __end = __init.end(); __it != __end;)
          { this->insert_equal(*__it++);}
        }

        ~white_black_tree()
        {
          if(this->__base.first() != nullptr)
          { this->force_clear();}
        }

      public:
        white_black_tree& operator=(const white_black_tree& __other)
        {
          if(this != &__other)
          {
            if(this->__base.first() != nullptr)
            { this->force_clear();}
            this->__base.second() = __other.__base.second();
            this->__mis = __other.__mis;
            this->__init();
            this->__compare = __other.__compare;
            __link_type __head = this->__base.first();
            this->__wb_tree_copy(
              __head->__parent, (__other.__base.first())->__parent
            );
            __head->__parent->__parent = __head;
            __head->__left = __node_type::__minimum(__head->__parent);
            __head->__right = __node_type::__maxmum(__head->__parent);
          }
          return *this;
        }

        white_black_tree& operator=(white_black_tree&& __other)
        {
          if(this != &__other)
          {
            if(this->__base.first() != nullptr)
            { this->force_clear();}
            this->__base = algorithm::move(__other.__base);
            this->__mis = algorithm::move(__other.__mis);
            this->__compare =
              algorithm::move(__other.__compare);
            __other.__base.first() = nullptr;
          }
          return *this;
        }
        white_black_tree& operator=(
          container::initializer_list<value_type> __init
        )
        {
          typedef typename
            container::initializer_list<value_type>::iterator
            __iterator;
          this->__mis.first() = 0U;
          if(this->__base.first() == nullptr)
          { this->__init();}
          else
          { this->clear();}
          for(__iterator __it = __init.begin(), __end = __init.end(); __it != __end;)
          { this->insert_equal(*__it++);}

          return *this;
        }

      public:
        allocator_type get_allocator() const
        { return this->__mis.second();}

      public:
        iterator begin() noexcept
        { return iterator(this->__base.first()->__left);}
        const_iterator begin() const noexcept
        { return const_iterator(this->__base.first()->__left);}
        const_iterator cbegin() const noexcept
        { return const_iterator(this->__base.first()->__left);}
        iterator end() noexcept
        { return iterator(this->__base.first());}
        const_iterator end() const noexcept
        { return const_iterator(this->__base.first());}
        const_iterator cend() const noexcept
        { return const_iterator(this->__base.first());}

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
        { return (this->__base.first())->__parent == nullptr;}
        size_type size() const noexcept
        { return this->__mis.first();}

      public:
        reference minmum()
        {
          return const_cast<reference>(
            __get_value(*(this->__base.first()->__left->__data))
          );
        }
        const_reference minmum() const
        { return __get_value(*(this->__base.first()->__left->__data));}
        reference maxmum()
        {
          return const_cast<reference>(
            __get_value(*(this->__base.first()->__right->__data))
          );
        }
        const_reference maxmum() const
        { return __get_value(*(this->__base.first()->__right->__data));}

      public:
        container::pair<iterator, bool>
        insert_unique(const value_type& __val)
        { return __insert_unique(this->__allocate_node(__val), this);}
        container::pair<iterator, bool>
        insert_unique(value_type&& __val)
        {
          return __insert_unique(
            this->__allocate_node(algorithm::move(__val)), this
          );
        }
        iterator insert_unique(
          const_iterator __hint, const value_type& __val
        )
        {
          return __insert_unique(
            __hint.__ptr, this->__allocate_node(__val), this
          );
        }
        iterator insert_unique(const_iterator __hint, value_type&& __val)
        {
          return __insert_unique(
            __hint.__ptr,
            this->__allocate_node(algorithm::move(__val)), this
          );
        }
        iterator insert_equal(const value_type& __val)
        { return __insert_equal(this->__allocate_node(__val), this);}
        iterator insert_equal(value_type&& __val)
        {
          return __insert_equal(
            this->__allocate_node(algorithm::move(__val)), this
          );
        }
        iterator insert_equal(
          const_iterator __hint, const value_type& __val
        )
        {
          return __insert_equal(
            __hint.__ptr, this->__allocate_node(__val), this
          );
        }
        iterator insert_equal(const_iterator __hint, value_type&& __val)
        {
          return __insert_equal(
            __hint.__ptr,
            this->__allocate_node(algorithm::move(__val)), this
          );
        }

        /**
         * \todo design policy for insert sequence<br/>
         * insert_unique(iterator __f, iterator __last)<br/>
         * insert_equal(iterator __f, iterator __last)<br/>
         */


      public:
        template<typename... _Args>
        container::pair<iterator, bool>
        emplace_unique(_Args&&... __args)
        {
          return __insert_unique(
            this->__allocate_node(
              algorithm::forward<_Args>(__args)...
            ), this
          );
        }
        template<typename... _Args>
        iterator emplace_equal(_Args&&... __args)
        {
          return __insert_equal(
            this->__allocate_node(
              algorithm::forward<_Args>(__args)...
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
            this->__allocate_node(
              algorithm::forward<_Args>(__args)...
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
            this->__allocate_node(
              algorithm::forward<_Args>(__args)...
            ), this
          );
        }

      public:
        size_type count(const key_type& __key) const noexcept
        {
          return iterator::distance(
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
        inline iterator erase(const_iterator __pos)
        {
          iterator __res(__pos.__ptr);
          ++__res;
          __link_type __head = this->__base.first();
          __link_type __del = __erase_rebalance(
            __pos.__ptr, __head->__parent,
            __head->__left, __head->__right
          );
          this->__deallocate_node(__del);
          --(this->__mis.first());
          return __res;
        }
        inline iterator erase(
          const_iterator __first, const_iterator __last
        )
        {
          if(__first == this->begin() && __last == this->end())
          {
            this->clear();
            return this->end();
          }
          else
          {
            for(;__first != __last;)
            { this->erase(__first++);}
          }
          return iterator(__last.__ptr);
        }
        inline size_type erase(const key_type& __key)
        {
          container::pair<const_iterator, const_iterator>  __tmp =
            this->equal_range(__key);
          size_type __res =
            iterator::distance(__tmp.first, __tmp.second);
          this->erase(__tmp.first, __tmp.second);
          return __res;
        }

      public:
        void clear()
        {
          if(!this->empty())
          {
            __link_type __head = this->__base.first();
            this->__tree_clear(__head->__parent);
            this->__mis.first() = 0U;
            __head->__parent = nullptr;
            __head->__left = __head->__right = __head;
            __head->__color = __white;
          }
        }

      public:
        template<
          typename _Key_Compare = key_compare,
          typename trait::type::miscellaneous::enable_if<
            trait::type::features::is_swappable<_Key_Compare>::value,
          bool>::type = true
        >
        void swap(white_black_tree& __other) noexcept(
          trait::type::features::is_nothrow_swappable<key_compare>::value &&
          trait::type::features::is_nothrow_swappable<allocator_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__base,    __other.__base);
          swap(this->__mis,     __other.__mis);
          swap(this->__compare, __other.__compare);
          return;
        }
        template<
          typename _Key_Compare = key_compare, typename __Alloc = allocator_type,
          typename trait::type::miscellaneous::enable_if<
            trait::type::features::is_possible_swappable<_Key_Compare>::value &&
            trait::type::features::is_possible_swappable<__Alloc>::value,
          bool>::type = true
        >
        void possible_swap(white_black_tree& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<key_compare>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__base,    __other.__base);
          possible_swap(this->__mis,     __other.__mis);
          possible_swap(this->__compare, __other.__compare);
          return;
        }

      private:
        void force_clear()
        {
          this->clear();
          __link_type __head = this->__base.first();
          __head->__left = __head->__right = nullptr;
          __head = nullptr;
          __node_allocator_traits_type::deallocate(
            this->__base.second(), this->__base.first()
          );
          this->__base.first() = nullptr;
        }

      private:
        void __init()
        {
          __link_type __tmp =
            __node_allocator_traits_type::allocate(
              this->__base.second()
            );
          __tmp->__parent = nullptr;
          __tmp->__color = __white;
          __tmp->__left = __tmp->__right = __tmp;
          this->__base.first() = __tmp;
        }
        void __tree_clear(__link_type __root)
        {
          if(__root->__left != nullptr)
          { this->__tree_clear(__root->__left);}
          if(__root->__right != nullptr)
          { this->__tree_clear(__root->__right);}
          __root->__left = __root->__right = __root->__parent = nullptr;
          this->__deallocate_node(__root);
          return;
        }
        void __wb_tree_copy(__link_type& __root, const __node_type* __other)
        {
          __root = this->__allocate_node(*(__other->__data));
          __root->__color   = __other->__color;
          __root->__left    = nullptr;
          __root->__right   = nullptr;
          if(__other->__left != nullptr)
          {
            this->__wb_tree_copy(__root->__left,  __other->__left);
            __root->__left->__parent = __root;
          }
          if(__other->__right != nullptr)
          {
            this->__wb_tree_copy(__root->__right, __other->__right);
            __root->__right->__parent = __root;
          }
          return;
        }

      private:
        static inline const __node_type* __lower_bound(
          const white_black_tree* __this, const key_type& __key
        )
        {
          const __node_type* __header = __this->__base.first();
          const __node_type* __pos = __header->__parent;

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
          const __node_type* __header = __this->__base.first();
          const __node_type* __pos = __header->__parent;

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
        static container::pair<iterator, bool>
        __insert_unique(
          __link_type __ins, white_black_tree* __this
        ) noexcept
        {
          __link_type __header = __this->__base.first();
          __link_type __pos = __header->__parent;
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
              return container::pair<iterator, bool>(
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
            return container::pair<iterator, bool>(
              __insert(__pos, __header, __ins, __this), true
            );
          }
          __this->__deallocate_node(__ins);
          return container::pair<iterator, bool>(__tmp, false);
        }
        static iterator __insert_unique(
          __link_type __pos, __link_type __ins,
          white_black_tree* __this
        ) noexcept
        {
          __link_type __head = __this->__base.first();
          // The first node.
          if(__pos == __head->__left)
          {
            if(__this->__mis.first() > 0 && __this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__pos->__data))
            ))
            { return __insert(__pos, __pos, __ins, __this);}
            return __insert_unique(__ins, __this).first;
          }
          // The last node.
          if(__pos == __head)
          {
            if(__this->__compare(
              __get_key(*(__head->__right->__data)), __get_key(*(__ins->__data))
            ))
            { return __insert(nullptr, __head->__right, __ins, __this);}
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
          __link_type __header = __this->__base.first();
          __link_type __pos = __header->__parent;
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
          __link_type __head = __this->__base.first();

          // The first node.
          if(__pos == __head->__left)
          {
            if(__this->__mis.first() > 0 && !(__this->__compare(
              __get_key(*(__pos->__data)), __get_key(*(__ins->__data))
            )))
            { return __insert(__pos, __pos, __ins, __this);}
            return __insert_equal(__ins, __this);
          }
          // The last node.
          if(__pos == __head)
          {
            if(!(__this->__compare(
              __get_key(*(__ins->__data)), __get_key(*(__head->__right->__data))
            )))
            { return __insert(nullptr, __head->__right, __ins, __this);}
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
          __link_type __head = __this->__base.first();

          if(__y == __head || __x != nullptr ||
            __this->__compare(
              __get_key(*(__z->__data)), __get_key(*(__y->__data))
            )
          )
          {
            __y->__left = __z;
            if(__y == __head)
            {
              __head->__parent = __z;
              __head->__right = __z;
            }
            else if(__y == __head->__left)
            { __head->__left = __z;}
          }
          else
          {
            __y->__right = __z;
            if(__y == __head->__right)
            { __head->__right = __z;}
          }
          __z->__parent = __y;
          __z->__right = __z->__left = nullptr;
          __insert_rebalance(__z, __head->__parent);
          ++(__this->__mis.first());
          return iterator(__z);
        }

      private:
        template<typename... _Args>
        inline __link_type __allocate_node(_Args&&... __args)
        {
          __value_container __value_holder(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __value_holder.get(),
            algorithm::forward<_Args>(__args)...
          );
          __node_container __node_holder(
            __node_allocator_traits_type::allocate(this->__base.second())
          );
          __node_holder->__data = __value_holder.release();
          return __node_holder.release();
        }
        inline void __deallocate_node(__link_type __pos)
        {
          if(__pos->__data != nullptr)
          {
            allocator_traits_type::destroy(
              this->__mis.second(), __pos->__data
            );
            allocator_traits_type::deallocate(
              this->__mis.second(), __pos->__data
            );
          }
          __node_allocator_traits_type::destroy(
            this->__base.second(), __pos
          );
          __node_allocator_traits_type::deallocate(
            this->__base.second(), __pos
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
            algorithm::swap(__y->__color, __z->__color);
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
          using container::get_key;
          return get_key(__con);
        }
        UTILITY_ALWAYS_INLINE
        static inline const key_type& __get_value(const value_type& __con)
        {
          using container::get_key;
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
        algorithm::equal(__x.begin(), __x.end(), __y.begin());
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
      return algorithm::lexicographical_compare(
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
      typename trait::type::miscellaneous::enable_if<
        trait::type::features::is_swappable<_Compare>::value,
      bool>::type = true
    >
    void swap(
      container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    {
      __x.swap(__y);
    }
    template<
      typename _Key, typename _Value, typename _Compare,
      typename _Key_Value_Container, typename _Alloc,
      typename trait::type::miscellaneous::enable_if<
        trait::type::features::is_possible_swappable<_Compare>::value &&
        trait::type::features::is_possible_swappable<_Alloc>::value,
      bool>::type = true
    >
    void possible_swap(
      container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __x,
      container::white_black_tree<_Key, _Value, _Compare, _Key_Value_Container, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    {
      __x.possible_swap(__y);
    }
  }
}

#endif // ! __UTILITY_CONTAINER_WHITE_BLACK_TREE__
