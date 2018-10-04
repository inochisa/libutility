
#ifdef __UTILITY_CONTAINER_LIST__

#ifndef __UTILITY_CONTAINER_IMPL_LIST_IMPL__
#define __UTILITY_CONTAINER_IMPL_LIST_IMPL__

namespace utility
{
  namespace container
  {
    template<
      typename _T,
      typename _Alloc = memory::allocator<_T>
    >
    class list;

    namespace __detail
    {
      template<typename _Vt>
      struct __list_node
      {
        typedef __list_node*  __node_link;
        typedef _Vt           __value_type;

        __node_link     __prev;
        __node_link     __next;
        __value_type*   __data;
        __list_node() = default;
        __list_node(__node_link _p, __node_link _n):
          __prev{_p}, __next{_n}, __data{nullptr}
        { }

        UTILITY_ALWAYS_INLINE
        inline void reverse()
        {
          using algorithm::swap;
          swap(__prev, __next);
        }
      };

      template<typename _Vt>
      class __list_const_iterator;

      template<typename _Vt>
      class __list_iterator
      {
        private:
          template<typename>
          friend class __list_const_iterator;
          template<typename, typename>
          friend class container::list;

        public:
          typedef helper::bidirectional_iterator_tag  iterator_category;
          typedef _Vt                                 value_type;
          typedef value_type&                         reference;
          typedef typename
            trait::miscellaneous::pointer_traits<_Vt*>::pointer pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<_Vt*>::difference_type difference_type;

        public:
          typedef __list_iterator<_Vt>  self;

        private:
          typedef __list_node<value_type>* __link_type;

        private:
          __link_type __ptr;

        public:
          inline __list_iterator() noexcept:
            __ptr{nullptr}
          { }
          inline explicit __list_iterator(__link_type __link) noexcept:
            __ptr{__link}
          { }

        public:
          self& operator=(const self& _other) noexcept
          {
            if(this != &_other)
            { this->__ptr = _other.__ptr;}
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
          bool operator==(const self& _other) const noexcept
          { return this->__ptr == _other.__ptr;}
          bool operator!=(const self& _other) const noexcept
          { return !(this->operator==(_other));}

      };

      template<typename _Vt>
      class __list_const_iterator
      {
        private:
          template<typename, typename>
          friend class container::list;

        public:
          typedef helper::bidirectional_iterator_tag iterator_category;
          typedef const _Vt               value_type;
          typedef _Vt                     non_const_value_type;
          typedef const _Vt&              reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __list_const_iterator<_Vt>  self;

        private:
          typedef __list_node<non_const_value_type>* __link_type;

        private:
          __link_type __ptr;

        public:
          inline __list_const_iterator() noexcept:
            __ptr{nullptr}
          { }
          inline explicit __list_const_iterator(__link_type __link) noexcept:
            __ptr{__link}
          { }
          inline __list_const_iterator(const __list_iterator<_Vt>& __it) noexcept:
            __ptr{__it.__ptr}
          { }

        public:
          self& operator=(const self& _other) noexcept
          {
            if(this != &_other)
            { this->__ptr = _other.__ptr;}
            return *this;
          }
          self& operator=(
            const __list_iterator<_Vt>& _other
          ) noexcept
          {
            this->__ptr = _other.__ptr;
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
          bool operator==(const self& _other) const noexcept
          { return this->__ptr == _other.__ptr;}
          bool operator!=(const self& _other) const noexcept
          { return !(this->operator==(_other));}
      };
    }
  }
}

#endif // ! __UTILITY_CONTAINER_IMPL_LIST_IMPL__

#endif // ! __UTILITY_CONTAINER_LIST__
