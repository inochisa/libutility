
#ifndef __UTILITY_CONTAINER_FORWARD_LIST__
#define __UTILITY_CONTAINER_FORWARD_LIST__

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      _T,
      _Alloc = utility::memory::allocator
    >
    class forward_list
    {
      private:
        template<typename __Value>
        struct __list_node
        {
          typedef __list_node*  __node_link;
          typedef __Value       __value_type;

          __node_link     __next;
          __value_type*   __data;
          __list_node() = default;
          __list_node(__node_link __n):
            __next(__n)
          { };

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
            typedef utility::iterator::forward_iterator_tag
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
            __link_type __inner_ptr;

          public:
            inline __list_iterator() noexcept:
              __inner_ptr(nullptr)
            { }
            inline explicit __list_iterator(__link_type __link) noexcept:
              __inner_ptr(__link)
            { }
            ~__list_iterator()
            { }

          public:
            self& operator=(const self& __other)
            {
              if(this != &__other)
              { this->__inner_ptr = __other.__inner_ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__inner_ptr->__data);}
            pointer operator->() const
            { return this->__inner_ptr->__data;}

          public:
            self& operator++()
            {
              this->__inner_ptr = this->__inner_ptr->__next;
              return *this;
            }
            self operator++(int)
            {
              self __it = *this;
              this->__inner_ptr = this->__inner_ptr->__next;
              return __it;
            }

          public:
            bool operator==(const self& __o) const
            { return this->__inner_ptr == __o.__inner_ptr;}
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
            typedef utility::iterator::forward_iterator_tag
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
            __link_type __inner_ptr;

          public:
            inline __list_const_iterator() noexcept:
              __inner_ptr(nullptr)
            { }
            inline explicit __list_const_iterator(__link_type __link) noexcept:
              __inner_ptr(__link)
            { }
            inline __list_const_iterator(const __list_iterator<__Value>& __it) noexcept:
              __inner_ptr(__it.__inner_ptr)
            { }

            inline
            ~__list_const_iterator()
            { }

          public:
            self& operator=(const self& __other)
            {
              if(this != &__other)
              { this->__inner_ptr = __other.__inner_ptr;}
              return *this;
            }

          public:
            reference operator*() const
            { return *(this->__inner_ptr->__data);}
            pointer operator->() const
            { return this->__inner_ptr->__data;}

          public:
            self& operator++()
            {
              this->__inner_ptr = this->__inner_ptr->__next;
              return *this;
            }
            self operator++(int)
            {
              self __it = *this;
              this->__inner_ptr = this->__inner_ptr->__next;
              return __it;
            }

          public:
            bool operator==(const self& __o) const
            { return this->__inner_ptr == __o.__inner_ptr;}
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
        typedef __list_const_iterator<value_type> const_iterator;

      public: // assert
        static_assert(utility::trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        __link_type __base;
        __link_type __ebase;
#ifdef __UTILITY_FORWARD_LIST_HAS_SIZE__
        size_type __size;
#endif // ! __UTILITY_FORWARD_LIST_HAS_SIZE__
        allocator_type __allocator;
        __node_allocator_type __node_allocator;

      public:
        forward_list(): forward_list(allocator_type())
        { }
        explicit forward_list(const allocator_type& __alloc):
          __node_allocator(__node_allocator_type()),
          __allocator(__alloc)
        {
          this->__base =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          this->__ebase =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          this->__base->__next = this->__ebase;
#ifdef __UTILITY_FORWARD_LIST_HAS_SIZE__
          this->__size = 0;
#endif // ! __UTILITY_FORWARD_LIST_HAS_SIZE__
        }

      public:
        forward_list& operator=(const forward_list& __other) = delete;

        forward_list& operator=(forward_list&& __other) = delete;

      public:

      public:
        allocator_type get_allocator() const
        { return this->__allocator;}
        void change_allocator(const allocator_type& __alloc)
        { this->__allocator = __alloc;}

      public:
        reference front()
        { return *(this->__base->__next->__data);}
        const_reference front()
        { return *(this->__base->__next->__data);}

      public:
        iterator before_begin() noexcept
        { return iterator(this->__base);}
        const_iterator before_begin() const noexcept
        { return const_iterator(this->__base);}
        const_iterator cbefore_begin() const noexcept
        { return const_iterator(this->__base);}
        iterator begin() noexcept
        { return iterator(this->__base->__next);}
        const_iterator begin() const noexcept
        { return const_iterator(this->__base->__next);}
        const_iterator cbegin() const noexcept
        { return const_iterator(this->__base->__next);}
        iterator end() noexcept
        { return iterator(this->__ebase);}
        const_iterator end() const noexcept
        { return const_iterator(this->__ebase);}
        const_iterator cend() const noexcept
        { return const_iterator(this->__ebase);}

      public:
        bool empty()
        { return this->__base->__next == this->__ebase;}

      public:
        void push_front(const value_type& __val)
        {
          __link_type __ulink =
            __node_allocator_traits_type::allocate(this->__node_allocator);
          __ulink->__data =
            allocator_traits_type::allocate(this->__allocator);
          allocator_traits_type::construct(__ulink, __val);
          ;
        }

      private:
        UTILITY_ALWAYS_INLINE
        inline static void __node_insert_after(__link_type __inserter,
          __link_type __pos) noexcept
        {
          __inserter.__next = __pos.__next;
          __pos.__next = __inserter;

        }
    };
  }
}

#endif // ! __UTILITY_CONTAINER_FORWARD_LIST__
