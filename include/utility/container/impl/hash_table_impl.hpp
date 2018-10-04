
#ifdef __UTILITY_CONTAINER_HASH_TABLE__

#ifndef __UTILITY_CONTAINER_IMPL_HASH_TABLE_IMPL__
#define __UTILITY_CONTAINER_IMPL_HASH_TABLE_IMPL__

namespace utility
{
  namespace container
  {
    template<
      typename _Key,
      typename _Value = _Key,
      typename _Key_Value_Container = container::pair<const _Key, _Value>,
      typename _Hash = algorithm::hash<_Key>,
      typename _Key_eq = algorithm::equal_to<void>,
      typename _Alloc = memory::allocator<_Key_Value_Container>
    >
    class hash_table;

    namespace __hash_length
    {
      const size_t __prime_list[28] =
      {
        53UL,         97UL,           193UL,          389UL,
        769UL,        1543UL,         3079UL,         6151UL,
        12289UL,      24593UL,        49157UL,        98317UL,
        196613UL,     393241UL,       786433UL,       1572869UL,
        3145739UL,    6291469UL,      12582917UL,     25165843UL,
        50331653UL,   100663319UL,    201326611UL,    402653189UL,
        805306457UL,  1610612741UL,   3221225473UL,   4294967291UL
      };

      inline size_t __next_prime(size_t __n) noexcept
      {
        const size_t* __pos =
          algorithm::lower_bound(
            __prime_list, __prime_list+28, __n
          );
        return __pos == __prime_list+28 ? 4294967291UL : *__pos;
      }
    }

    namespace __detail
    {
      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container
      >
      struct __hash_table_node
      {
        public:
          typedef _Key                 __key_type;
          typedef _Value               __mapped_type;
          typedef _Key_Value_Container __data_type;

        public:
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>
            __node_type;
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>*
            __link_type;

        __link_type   __next;
        __data_type* __data;
      };

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_const_iterator;

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_iterator
      {
        private:
          template<typename, typename, typename, typename, typename, typename>
          friend class container::hash_table;
          template<typename, typename, typename, typename>
          friend class __hash_table_const_iterator;

        public:
          typedef helper::forward_iterator_tag
            iterator_category;
          typedef _Key                   key_type;
          typedef _Value                 mapped_type;
          typedef _Key_Value_Container   value_type;
          typedef _Container             container_type;
          typedef value_type&            reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __hash_table_iterator<_Key, _Value, _Key_Value_Container, _Container> self;

        private:
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container> __node_type;
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>* __link_type;
          typedef _Container*    __container_link;

        private:
          __link_type      __ptr;
          __container_link __container_ptr;

        public:
          inline __hash_table_iterator() noexcept:
            __ptr{nullptr}, __container_ptr{nullptr}
          { }
          inline explicit __hash_table_iterator(__link_type __link, __container_link __con_link) noexcept:
            __ptr{__link}, __container_ptr{__con_link}
          { }

        public:
          self& operator=(const self& __oit)
          {
            if(&__oit != this)
            {
              this->__ptr = __oit.__ptr;
              this->__container_ptr = __oit.__container_ptr;
            }
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
            __link_type __old = this->__ptr;
            this->__ptr = this->__ptr->__next;
            if(this->__ptr == nullptr)
            {
              typename _Container::size_type __pos =
                this->__container_ptr->key_hash(get<0>(*(__old->__data)), this->__container_ptr->bucket_size())+1;
              for(;
                this->__ptr == nullptr &&
                  __pos < this->__container_ptr->bucket_size();
                ++__pos
              )
              { this->__ptr = this->__container_ptr->__bucket[__pos];}
            }
            return *this;
          }
          self operator++(int) noexcept
          {
            self __tmp(*this);
            this->operator++();
            return __tmp;
          }

        public:
          bool operator==(const self& __o) const noexcept
          {
            return this->__ptr == __o.__ptr &&
                    this->__container_ptr == __o.__container_ptr;
          }
          bool operator!=(const self& __o) const noexcept
          {
            return this->__ptr != __o.__ptr ||
                    this->__container_ptr != __o.__container_ptr;
          }
      };

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_const_iterator
      {
        private:
          template<typename, typename, typename, typename, typename, typename>
          friend class container::hash_table;

        public:
          typedef helper::forward_iterator_tag
            iterator_category;
          typedef _Key                          key_type;
          typedef _Value                        mapped_type;
          typedef _Key_Value_Container          non_const_value_type;
          typedef _Container                    container_type;
          typedef const _Key_Value_Container    value_type;
          typedef const _Key_Value_Container&   reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __hash_table_const_iterator<_Key, _Value, _Key_Value_Container, _Container> self;

        private:
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container> __node_type;
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>* __link_type;
          typedef _Container*    __container_link;

        private:
          __link_type      __ptr;
          __container_link __container_ptr;

        public:
          inline __hash_table_const_iterator() noexcept:
            __ptr{nullptr}, __container_ptr{nullptr}
          { }
          inline explicit __hash_table_const_iterator(
            __link_type __link, __container_link __con_link
          ) noexcept:
            __ptr{__link}, __container_ptr{__con_link}
          { }
          inline __hash_table_const_iterator(
            const __hash_table_iterator<_Key, _Value, _Key_Value_Container, _Container>& __it
          ) noexcept:
            __ptr{__it.__ptr}, __container_ptr{__it.__container_ptr}
          { }

        public:
          self& operator=(const self& __oit) noexcept
          {
            if(&__oit != this)
            {
              this->__ptr = __oit.__ptr;
              this->__container_ptr = __oit.__container_ptr;
            }
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
            __link_type __old = this->__ptr;
            this->__ptr = this->__ptr->__next;
            if(this->__ptr == nullptr)
            {
              typename _Container::size_type __pos =
                this->__container_ptr->key_hash(get<0>(*(__old->__data)), this->__container_ptr->bucket_size())+1;
              for(;
                this->__ptr == nullptr &&
                  __pos < this->__container_ptr->bucket_size();
                ++__pos
              )
              { this->__ptr = this->__container_ptr->__bucket[__pos];}
            }
            return *this;
          }
          self operator++(int) noexcept
          {
            self __tmp(*this);
            this->operator++();
            return __tmp;
          }

        public:
          bool operator==(const self& __o) const noexcept
          {
            return this->__ptr == __o.__ptr &&
                    this->__container_ptr == __o.__container_ptr;
          }
          bool operator!=(const self& __o) const noexcept
          {
            return this->__ptr != __o.__ptr ||
                    this->__container_ptr != __o.__container_ptr;
          }
      };

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_const_local_iterator;

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_local_iterator
      {
        private:
          template<typename, typename, typename, typename, typename, typename>
          friend class container::hash_table;
          template<typename, typename, typename, typename>
          friend class __hash_table_const_local_iterator;

        public:
          typedef helper::forward_iterator_tag
            iterator_category;
          typedef _Key                             key_type;
          typedef _Value                           mapped_type;
          typedef _Key_Value_Container             value_type;
          typedef _Container                       container_type;
          typedef typename _Container::size_type   size_type;
          typedef value_type&                      reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __hash_table_local_iterator<_Key, _Value, _Key_Value_Container, _Container> self;

        private:
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container> __node_type;
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>* __link_type;
          typedef _Container*    __container_link;

        private:
          __link_type      __ptr;
          size_type        __bucket_num;
          __container_link __container_ptr;

        public:
          inline __hash_table_local_iterator() noexcept:
            __ptr{nullptr}
          { }
          inline explicit __hash_table_local_iterator(
            __link_type __link, size_type __num,
            __container_link __con_link
          ) noexcept:
            __ptr(__link), __bucket_num(__num),
            __container_ptr(__con_link)
          { }

        public:
          self& operator=(const self& __oit) noexcept
          {
            if(&__oit != this)
            {
              this->__ptr = __oit.__ptr;
              this->__bucket_num = __oit.__bucket_num;
              this->__container_ptr = __oit.__container_ptr;
            }
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
            self __tmp(*this);
            this->operator++();
            return __tmp;
          }

        public:
          bool operator==(const self& __o) const noexcept
          {
            return this->__ptr == __o.__ptr &&
                    this->__bucket_num == __o.__bucket_num &&
                    this->__container_ptr == __o.__container_ptr;
          }
          bool operator!=(const self& __o) const noexcept
          {
            return this->__ptr != __o.__ptr ||
                    this->__bucket_num != __o.__bucket_num ||
                    this->__container_ptr != __o.__container_ptr;
          }

      };

      template<
        typename _Key,
        typename _Value,
        typename _Key_Value_Container,
        typename _Container
      >
      class __hash_table_const_local_iterator
      {
        private:
          template<typename, typename, typename, typename, typename, typename>
          friend class container::hash_table;

        public:
          typedef helper::forward_iterator_tag
            iterator_category;
          typedef _Key                              key_type;
          typedef _Value                            mapped_type;
          typedef _Key_Value_Container              non_const_value_type;
          typedef const _Key_Value_Container        value_type;
          typedef _Container                        container_type;
          typedef typename _Container::size_type    size_type;
          typedef const _Key_Value_Container&       reference;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::pointer
            pointer;
          typedef typename
            trait::miscellaneous::pointer_traits<value_type*>::difference_type
            difference_type;

        public:
          typedef __hash_table_const_local_iterator<_Key, _Value, _Key_Value_Container, _Container> self;

        private:
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container> __node_type;
          typedef __hash_table_node<_Key, _Value, _Key_Value_Container>* __link_type;
          typedef _Container*    __container_link;

        private:
          __link_type      __ptr;
          size_type        __bucket_num;
          __container_link __container_ptr;

        public:
          inline __hash_table_const_local_iterator() noexcept:
            __ptr{nullptr}
          { }
          inline explicit __hash_table_const_local_iterator(
            __link_type __link, size_type __num,
            __container_link __con_link
          ) noexcept:
            __ptr(__link), __bucket_num(__num),
            __container_ptr(__con_link)
          { }
          inline __hash_table_const_local_iterator(
            const __hash_table_local_iterator<_Key, _Value, _Key_Value_Container, _Container>& __it
          ) noexcept:
            __ptr(__it.__ptr), __bucket_num(__it.__bucket_num),
            __container_ptr(__it.__container_ptr)
          { }

        public:
          self& operator=(const self& __oit) noexcept
          {
            if(&__oit != this)
            {
              this->__ptr = __oit.__ptr;
              this->__bucket_num = __oit.__bucket_num;
              this->__container_ptr = __oit.__container_ptr;
            }
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
            self __tmp(*this);
            this->operator++();
            return __tmp;
          }

        public:
          bool operator==(const self& __o) const noexcept
          {
            return this->__ptr == __o.__ptr &&
                    this->__bucket_num == __o.__bucket_num &&
                    this->__container_ptr == __o.__container_ptr;
          }
          bool operator!=(const self& __o) const noexcept
          {
            return this->__ptr != __o.__ptr ||
                    this->__bucket_num != __o.__bucket_num ||
                    this->__container_ptr != __o.__container_ptr;
          }

      };
    }
  }
}


#endif // ! __UTILITY_CONTAINER_IMPL_HASH_TABLE_IMPL__

#endif // ! __UTILITY_CONTAINER_HASH_TABLE__
