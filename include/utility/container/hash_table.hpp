
#ifndef __UTILITY_CONTAINER_HASH_TABLE__
#define __UTILITY_CONTAINER_HASH_TABLE__

/**
 * \file hash_table.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/algorithm/hash.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/forward.hpp>
#include<utility/algorithm/max.hpp>
#include<utility/algorithm/lower_bound.hpp>
#include<utility/algorithm/is_permutation.hpp>

#include<utility/container/container_helper.hpp>
#include<utility/container/pair.hpp>
#include<utility/container/compressed_pair.hpp>
#include<utility/container/vector.hpp>

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>
#include<utility/trait/miscellaneous/pointer_traits.hpp>

#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/memory/unique_ptr.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/distance.hpp>

#include<utility/miscellaneous/ignore_unused.hpp>

#include<utility/container/impl/hash_table_impl.hpp>

namespace utility
{
  namespace container
  {
    template<
      typename _Key,                  typename _Value,
      typename _Key_Value_Container,  typename _Hash,
      typename _Key_eq,               typename _Alloc
    >
    class hash_table
    {
      private:
        template<typename, typename, typename, typename>
        friend class __detail::__hash_table_iterator;
        template<typename, typename, typename, typename>
        friend class __detail::__hash_table_const_iterator;

      public:
        typedef __detail::__hash_table_node<_Key, _Value, _Key_Value_Container>
          __node_type;
        typedef __node_type* __link_type;
        typedef memory::allocator<__node_type>
          __node_allocator_type;
        typedef memory::allocator_traits<__node_allocator_type>
          __node_allocator_traits_type;
        typedef
          hash_table<_Key, _Value, _Key_Value_Container, _Hash, _Key_eq, _Alloc>
          __self_type;

      public:
        typedef _Key                  key_type;
        typedef _Value                mapped_type;
        typedef _Key_Value_Container  value_type;
        typedef _Hash                 hasher;
        typedef _Key_eq               key_equal;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;
        typedef value_type&           reference;
        typedef const value_type&     const_reference;
        typedef _Alloc                allocator_type;

      private:
        typedef memory::unique_ptr<value_type>
          __value_container;
        typedef memory::unique_ptr<__node_type>
          __node_container;
        typedef container::vector<__link_type>
          __bucket_container;

      public:
        typedef memory::allocator_traits<allocator_type>
          allocator_traits_type;

      public:
        typedef typename allocator_traits_type::pointer pointer;
        typedef typename allocator_traits_type::const_pointer const_pointer;

      public:
        typedef
          __detail::__hash_table_iterator<key_type, mapped_type, value_type, __self_type>
          iterator;
        typedef
          __detail::__hash_table_const_iterator<key_type, mapped_type, value_type, __self_type>
          const_iterator;
        typedef
          __detail::__hash_table_local_iterator<key_type, mapped_type, value_type, __self_type>
          local_iterator;
        typedef
          __detail::__hash_table_const_local_iterator<key_type, mapped_type, value_type, __self_type>
          const_local_iterator;

      public: // assert:
        static_assert(trait::type::releations::is_same<
          value_type, typename allocator_type::value_type>::value,
          "the allocator's alloc type must be the same as value type");

      private:
        typedef container::compressed_pair<float, __node_allocator_type> __control_pair;
        typedef container::compressed_pair<size_type, allocator_type> __mis_type;

      private:
        __bucket_container        __bucket;
        __mis_type                __mis;
        __control_pair            __load_allocator;
        hasher                    __hasher;
        key_equal                 __key_eq;

      public:
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_default_constructible<_Key_Eq>::value &&
          trait::type::features::is_default_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        explicit hash_table():
          __bucket(97UL), __mis{0U, allocator_type{}},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{}, __key_eq{}
        { }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        explicit hash_table(
          size_type __count, const hasher& __ha,
          const key_equal& __equal,
          const allocator_type& __alloc = allocator_type()
        ):__bucket(__hash_length::__next_prime(__count)),
          __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{__ha}, __key_eq{__equal}
        { }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value,
          bool
          >::type = true
        >
        explicit hash_table(
          size_type __count, const hasher& __ha,
          const allocator_type& __alloc = allocator_type()
        ):__bucket(__hash_length::__next_prime(__count)),
          __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{__ha}, __key_eq{}
        { }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value &&
          trait::type::features::is_default_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        explicit hash_table(
          size_type __count,
          const allocator_type& __alloc = allocator_type()
        ):__bucket(__hash_length::__next_prime(__count)),
          __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{}, __key_eq{}
        { }

        explicit hash_table(const allocator_type& __alloc):
          __bucket(97UL), __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{}, __key_eq{}
        { }

        template<typename _InputIterator,
        typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        hash_table(
          _InputIterator __first, _InputIterator __last,
          size_type __count, const hasher& __ha,
          const key_equal& __equal,
          const allocator_type& __alloc = allocator_type()
        ):__bucket{}, __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{__ha}, __key_eq{__equal}
        {
          const size_type __bucket_size =
            algorithm::max<size_type>(
              __hash_length::__next_prime(
                helper::distance(__first, __last)
              ),
              __hash_length::__next_prime(__count)
            );
          this->__bucket.resize(__bucket_size);
          for(; __first != __last;)
          { __insert_equal(this->__allocate_node(*__first++), this);}
        }
        template<typename _InputIterator,
        typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value &&
          trait::type::features::is_default_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        hash_table(
          _InputIterator __first, _InputIterator __last,
          size_type __count = 97UL,
          const allocator_type& __alloc = allocator_type()
        ): hash_table(__first, __last, __count, hasher{}, key_equal{}, __alloc)
        { }
        template<typename _InputIterator,
        typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
            is_iterator<_InputIterator>::value,
            bool
          >::type = true,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value,
          bool
          >::type = true
        >
        hash_table(
          _InputIterator __first, _InputIterator __last,
          size_type __count, const hasher& __ha,
          const allocator_type& __alloc = allocator_type()
        ): hash_table(__first, __last, __count, __ha, key_equal{}, __alloc)
        { }


        hash_table(const hash_table& __other):
          __bucket(__other.__bucket.size()),
          __mis{__other.__mis},
          __load_allocator{__other.__load_allocator},
          __hasher{__other.__hasher},
          __key_eq{__other.__key_eq}
        {
          const size_type __bucket_size = __other.__bucket.size();

          for(size_type __i = 0; __i < __bucket_size; ++__i)
          {
            if(__other.__bucket[__i] != nullptr)
            {
              this->__bucket[__i] = this->__allocate_node_chain(
                __other.begin(__i), __other.end(__i)
              ).first;
            }
          }
        }
        hash_table(
          const hash_table& __other, const allocator_type& __alloc
        ):__bucket(__other.__bucket.size()),
          __mis{__other.__mis.first(), __alloc},
          __load_allocator{__other.__load_allocator},
          __hasher{__other.__hasher},
          __key_eq{__other.__key_eq}
        {
          const size_type __bucket_size = __other.__bucket.size();

          for(size_type __i = 0; __i < __bucket_size; ++__i)
          {
            if(__other.__bucket[__i] != nullptr)
            {
              this->__bucket[__i] = this->__allocate_node_chain(
                __other.begin(__i), __other.end(__i)
              ).first;
            }
          }
        }
        hash_table(hash_table&& __other):
          __bucket{algorithm::move(__other.__bucket)},
          __mis{algorithm::move(__other.__mis)},
          __load_allocator{algorithm::move(__other.__load_allocator)},
          __hasher{algorithm::move(__other.__hasher)},
          __key_eq{algorithm::move(__other.__key_eq)}
        { }
        hash_table(
          hash_table&& __other, const allocator_type& __alloc
        ):__bucket{algorithm::move(__other.__bucket)},
          __mis{__other.__mis.first(), __alloc},
          __load_allocator{algorithm::move(__other.__load_allocator)},
          __hasher{algorithm::move(__other.__hasher)},
          __key_eq{algorithm::move(__other.__key_eq)}
        { }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        hash_table(
          initializer_list<value_type> __initlist,
          size_type __count, const hasher& __ha,
          const key_equal __equal,
          const allocator_type& __alloc = allocator_type()
        ):__bucket{}, __mis{0U, __alloc},
          __load_allocator{1.0f, __node_allocator_type{}},
          __hasher{__ha}, __key_eq{__equal}
        {
          typedef typename initializer_list<value_type>::const_iterator
            __iterator;
          const size_type __bucket_size =
            algorithm::max<size_type>(
              __hash_length::__next_prime(__initlist.size()),
              __hash_length::__next_prime(__count)
            );
          this->__bucket.resize(__bucket_size);
          for(__iterator __first = __initlist.begin(),
            __last = __initlist.end(); __first != __last;)
          { __insert_equal(this->__allocate_node(*__first++), this);}
        }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value &&
          trait::type::features::is_default_constructible<_Hasher>::value,
          bool
          >::type = true
        >
        hash_table(
          initializer_list<value_type> __initlist,
          size_type __count = 97UL,
          const allocator_type& __alloc = allocator_type()
        ):hash_table(
          __initlist, __count, hasher{}, key_equal{}, __alloc
        )
        { }
        template<typename _Key_Eq = _Key_eq, typename _Hasher = _Hash,
        typename
        trait::type::miscellaneous::enable_if<
          trait::type::features::is_copy_constructible<_Key_Eq>::value &&
          trait::type::features::is_copy_constructible<_Hasher>::value &&
          trait::type::features::is_default_constructible<_Key_Eq>::value,
          bool
          >::type = true
        >
        hash_table(
          initializer_list<value_type> __initlist,
          size_type __count, const hasher& __ha,
          const allocator_type& __alloc = allocator_type()
        ):hash_table(
          __initlist, __count, __ha, key_equal{}, __alloc
        )
        { }

        ~hash_table()
        {
          this->clear();
        }

      public:
        hash_table& operator=(const hash_table& __other)
        {
          if(&__other != this)
          {
            this->__load_allocator = __other.__load_allocator;
            this->__hasher = __other.__hasher;
            this->__key_eq = __other.__key_eq;

            const size_type __bucket_size = __other.__bucket.size();
            __bucket_container __tmp(__bucket_size);

            __UTILITY_TRY_BEGIN
              for(size_type __i = 0; __i < __bucket_size; ++__i)
              {
                if(__other.__bucket[__i] != nullptr)
                {
                  __tmp[__i] = this->__allocate_node_chain(
                    __other.begin(__i), __other.end(__i)
                  ).first;
                }
              }
              this->clear();
              this->__bucket.swap(__tmp);
              this->__mis.first() = __other.__mis.first();
            __UTILITY_TRY_END
            __UTILITY_CATCH(...)
            __UTILITY_CATCH_UNWIND(
              for(size_type __now = 0; __now < __tmp.size(); ++__now)
              {
                if(__tmp[__now] != nullptr)
                {
                  __link_type __use = __tmp[__now];
                  __tmp[__now] = nullptr;
                  this->__deallocate_node_chain(__use);
                }
              }
            );
          }
          return *this;
        }
        hash_table& operator=(hash_table&& __other)
        {
          if(&__other != this)
          {
            this->__load_allocator = __other.__load_allocator;
            this->__bucket.swap(__other.__bucket);
            this->__mis = algorithm::move(__other.__mis);
            this->__hasher =
              algorithm::move(__other.__hasher);
            this->__key_eq =
              algorithm::move(__other.__key_eq);
          }
          return *this;
        }
        hash_table& operator=(initializer_list<value_type> __initlist)
        {
          typedef typename initializer_list<value_type>::const_iterator
            __iterator;
          const size_type __bucket_size =
            algorithm::max<size_type>(
              __hash_length::__next_prime(__initlist.size()),
              __hash_length::__next_prime(this->bucket_size())
            );
          __bucket_container __tmp(__bucket_size);
          __link_type __ins;
          __UTILITY_TRY_BEGIN
            for(__iterator __first = __initlist.begin(),
              __last = __initlist.end(); __first != __last; ++__first)
            {
              __ins = this->__allocate_node(*__first);
              const size_type __pos =
                this->key_hash(__get_key(*(__ins->__data)), __bucket_size);
              __link_type __link = __tmp[__pos];
              for(__link_type __i = __link; __i != nullptr; __i = __i->__next)
              {
                if(this->__key_eq(
                  __get_key(*(__i->__data)), __get_key(*(__ins->__data))
                ))
                {
                  __ins->__next = __i->__next;
                  __i->__next = __ins;
                  goto __next_value;
                }
              }
              __ins->__next = __link;
              __tmp[__pos] = __ins;
              __next_value:;
            }
            this->clear();
            this->__bucket.swap(__tmp);
            this->__mis.first() = __initlist.size();
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(size_type __now = 0; __now < __tmp.size(); ++__now)
            {
              if(__tmp[__now] != nullptr)
              {
                __link_type __use = __tmp[__now];
                __tmp[__now] = nullptr;
                this->__deallocate_node_chain(__use);
              }
            }
          );
          return *this;
        }

      public:
        allocator_type get_allocator() const
        { return this->__mis.second();}

      public:
        inline size_type size() const noexcept
        { return this->__mis.first();}
        inline size_type bucket_size() const noexcept
        { return this->__bucket.size();}

      public:
        inline iterator begin() noexcept
        {
          for(
            typename __bucket_container::iterator __it = this->__bucket.begin(),
            __end = this->__bucket.end(); __it != __end; ++__it
          )
          {
            if(*__it != nullptr)
            { return iterator(*__it, this);}
          }
          return iterator(nullptr, this);
        }
        inline const_iterator begin() const noexcept
        {
          for(
            typename __bucket_container::const_iterator __it = this->__bucket.begin(),
            __end = this->__bucket.end(); __it != __end; ++__it
          )
          {
            if(*__it != nullptr)
            {
              return const_iterator(
                const_cast<__link_type>(*__it),
                const_cast<__self_type*>(this)
              );
            }
          }
          return const_iterator(nullptr, const_cast<__self_type*>(this));
        }
        inline const_iterator cbegin() const noexcept
        {
          for(
            typename __bucket_container::const_iterator __it = this->__bucket.begin(),
            __end = this->__bucket.end(); __it != __end; ++__it
          )
          {
            if(*__it != nullptr)
            {
              return const_iterator(
                const_cast<__link_type>(*__it),
                const_cast<__self_type*>(this)
              );
            }
          }
          return const_iterator(nullptr, const_cast<__self_type*>(this));
        }
        inline iterator end() noexcept
        { return iterator(nullptr, this);}
        inline const_iterator end() const noexcept
        { return iterator(nullptr, const_cast<__self_type*>(this));}
        inline const_iterator cend() const noexcept
        { return iterator(nullptr, const_cast<__self_type*>(this));}

      public:
        inline local_iterator begin(size_type __pos) noexcept
        { return local_iterator(this->__bucket[__pos], __pos, this);}
        inline const_local_iterator begin(size_type __pos) const noexcept
        {
          return const_local_iterator(
            this->__bucket[__pos], __pos, const_cast<__self_type*>(this)
          );
        }
        inline const_local_iterator cbegin(size_type __pos) const noexcept
        {
          return const_local_iterator(
            this->__bucket[__pos], __pos, const_cast<__self_type*>(this)
          );
        }
        inline local_iterator end(size_type __pos) noexcept
        { return local_iterator(nullptr, __pos, this);}
        inline const_local_iterator end(size_type __pos) const noexcept
        {
          return const_local_iterator(
            nullptr, __pos, const_cast<__self_type*>(this)
          );
        }
        inline const_local_iterator cend(size_type __pos) const noexcept
        {
          return const_local_iterator(
            nullptr, __pos, const_cast<__self_type*>(this)
          );
        }
        inline size_type bucket(const key_type& __key) const
        { return this->key_hash(__key, this->bucket_size());}

      public:
        inline container::pair<iterator, bool>
        insert_unique(const value_type& __val)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(this->__allocate_node(__val), this);
        }
        inline container::pair<iterator, bool>
        insert_unique(value_type&& __val)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(
            this->__allocate_node(algorithm::move(__val)), this
          );
        }
        inline iterator insert_equal(const value_type& __val)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(this->__allocate_node(__val), this);
        }
        inline iterator insert_equal(value_type&& __val)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(
            this->__allocate_node(algorithm::move(__val)), this
          );
        }
        iterator insert_unique(
          const_iterator __hint, const value_type& __val
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(this->__allocate_node(__val), this).first;
        }
        iterator insert_unique(
          const_iterator __hint, value_type&& __val
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(
            this->__allocate_node(algorithm::move(__val)), this
          ).first;
        }
        inline iterator insert_equal(
          const_iterator __hint, const value_type& __val
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(this->__allocate_node(__val), this);
        }
        inline iterator insert_equal(
          const_iterator __hint, value_type&& __val
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(
            this->__allocate_node(algorithm::move(__val)), this
          );
        }

        /**
         * \todo design policy for insert sequence<br/>
         * insert_unique(iterator __f, iterator __last)<br/>
         * insert_equal(iterator __f, iterator __last)<br/>
         */
        template<typename _InputIterator>
        inline size_type insert_unique(
          _InputIterator __first, _InputIterator __last
        )
        {
          if(__first == __last)
          { return 0U;}
          if(this->is_overload(helper::distance(__first, __last)))
          { this->resize(helper::distance(__first, __last));}
          size_type __success = 0;
          for(; __first != __last; ++__first)
          {
            if(__insert_unique(this->__allocate_node(*__first), this).second)
            { ++__success;}
          }
          return __success;
        }
        template<typename _InputIterator>
        inline void insert_equal(
          _InputIterator __first, _InputIterator __last
        )
        {
          if(__first == __last)
          { return;}
          if(this->is_overload(helper::distance(__first, __last)))
          { this->resize(helper::distance(__first, __last));}
          for(; __first != __last; ++__first)
          { __insert_equal(this->__allocate_node(*__first), this);}
        }

      public:
        template<typename... _Args>
        inline container::pair<iterator, bool>
        emplace_unique(_Args&&... __args)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(
            this->__allocate_node(algorithm::forward<_Args>(__args)...),
            this
          );
        }
        template<typename... _Args>
        inline iterator emplace_equal(_Args&&... __args)
        {
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(
            this->__allocate_node(algorithm::forward<_Args>(__args)...),
            this
          );
        }
        template<typename... _Args>
        inline iterator emplace_unique_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_unique(
            this->__allocate_node(algorithm::forward<_Args>(__args)...),
            this
          ).first;
        }
        template<typename... _Args>
        inline iterator emplace_equal_hint(
          const_iterator __hint, _Args&&... __args
        )
        {
          miscellaneous::ignore_unused(__hint);
          if(this->is_overload(1U))
          { this->resize(this->size() + 1);}
          return __insert_equal(
            this->__allocate_node(algorithm::forward<_Args>(__args)...),
            this
          );
        }

      public:
        iterator find(const key_type& __key)
        {
          const size_type __num = this->key_hash(__key, this->bucket_size());
          __link_type __pos = this->__bucket[__num];
          for(; __pos != nullptr; __pos = __pos->__next)
          {
            if(this->__key_eq(__get_key(*(__pos->__data)), __key))
            { return iterator(__pos, this);}
          }
          return iterator(nullptr, this);
        }
        const_iterator find(const key_type& __key) const
        {
          const size_type __num = this->key_hash(__key, this->bucket_size());
          const __node_type* __pos = this->__bucket[__num];
          for(; __pos != nullptr; __pos = __pos->__next)
          {
            if(this->__key_eq(__get_key(*(__pos->__data)), __key))
            { return const_iterator(__pos, this);}
          }
          return const_iterator(nullptr, this);
        }
        size_type count(const key_type& __key) const
        {
          const size_type __num = this->key_hash(__key, this->bucket_size());
          const __node_type* __pos = this->__bucket[__num];
          size_type __count = 0U;
          for(; __pos != nullptr; __pos = __pos->__next)
          {
            if(this->__key_eq(__get_key(*(__pos->__data)), __key))
            { break;}
          }
          for(; __pos != nullptr; __pos = __pos->__next)
          {
            if(!this->__key_eq(__get_key(*(__pos->__data)), __key))
            { break;}
            ++__count;
          }
          return __count;
        }
        container::pair<iterator, iterator>
        equal_range(const key_type& __key)
        {
          typedef container::pair<iterator, iterator>
            __result_container;
          const size_type __num = this->key_hash(__key, this->bucket_size());
          for(
            __link_type __bpos = this->__bucket[__num];
            __bpos != nullptr; __bpos = __bpos->__next
          )
          {
            if(this->__key_eq(__get_key(*(__bpos->__data)), __key))
            {
              for(
                __link_type __epos = __bpos->__next;
                __epos != nullptr; __epos = __epos->__next
              )
              {
                if(!(this->__key_eq(__get_key(*(__epos->__data)), __key)))
                {
                  return __result_container(
                    iterator(__bpos, this), iterator(__epos, this)
                  );
                }
              }
              for(
                size_type __i = __num +1 ; __i < this->__bucket.size(); ++__i
              )
              {
                if(this->__bucket[__i] != nullptr)
                {
                  return __result_container(
                    iterator(__bpos, this),
                    iterator(this->__bucket[__i], this)
                  );
                }
              }
              return __result_container(
                iterator(__bpos, this), iterator(nullptr, this)
              );
            }
          }
          return __result_container(
            iterator(nullptr, this), iterator(nullptr, this)
          );
        }
        container::pair<const_iterator, const_iterator>
        equal_range(const key_type& __key) const
        {
          typedef container::pair<const_iterator, const_iterator>
            __result_container;
          const size_type __num = this->key_hash(__key, this->bucket_size());
          for(
            const __node_type* __bpos = this->__bucket[__num];
            __bpos != nullptr; __bpos = __bpos->__next
          )
          {
            if(this->__key_eq(__get_key(*(__bpos->__data)), __key))
            {
              for(
                const __node_type* __epos = __bpos->__next;
                __epos != nullptr; __epos = __epos->__next
              )
              {
                if(!(this->__key_eq(__get_key(*(__epos->__data)), __key)))
                {
                  return __result_container(
                    iterator(__bpos, this), iterator(__epos, this)
                  );
                }
              }
              for(
                size_type __i = __num +1 ; __i < this->__bucket.size(); ++__i
              )
              {
                if(this->__bucket[__i] != nullptr)
                {
                  return __result_container(
                    iterator(__bpos, this),
                    iterator(this->__bucket[__i], this)
                  );
                }
              }
              return __result_container(
                iterator(__bpos, this), iterator(nullptr, this)
              );
            }
          }
          return __result_container(
            iterator(nullptr, this), iterator(nullptr, this)
          );
        }

      public:
        size_type erase(const key_type& __key)
        {
          const size_type __num = this->key_hash(__key, this->size());
          __link_type __pos = this->__bucket[__num];
          size_type __erased = 0U;
          if(__pos != nullptr)
          {
            __link_type __bpos = __pos;
            __link_type __epos = __pos->__next;
            for(; __epos != nullptr; __epos = __bpos->__next)
            {
              if(this->__key_eq(__get_key(*(__epos->__data)), __key))
              {
                __bpos->__next = __epos->__next;
                this->__deallocate_node(__epos);
                ++__erased;
                --(this->__mis.first());
              }
              else
              { __bpos = __epos;}
            }
            if(this->__key_eq(__get_key(*(__pos->__data)), __key))
            {
              this->__bucket[__num] = __pos->__next;
              this->__deallocate_node(__pos);
              ++__erased;
              --(this->__mis.first());
            }
          }
          return __erased;
        }
        iterator erase(const_iterator __pos)
        {
          if(__pos.__ptr == nullptr)
          { return iterator(nullptr, this);}
          __link_type __tpos = __pos.__ptr;
          const size_type __num =
            this->key_hash(__get_key(*(__tpos->__data)), this->bucket_size());
          __link_type __spos = this->__bucket[__num];

          if(__spos == __tpos)
          {
            this->__bucket[__num] = __spos->__next;
            __tpos = __tpos->__next;
            this->__deallocate_node(__spos);
            --(this->__mis.first());
            return iterator(__tpos, this);
          }

          for(; __spos->__next != __tpos; __spos = __spos->__next)
          { }
          __spos->__next = __tpos->__next;
          this->__deallocate_node(__tpos);
          return iterator(__spos, this).operator++();
        }
        iterator erase(const_iterator __first, const_iterator __last)
        {
          if(__first == __last)
          { return iterator(__last.__ptr, __last.__container_ptr);}
          if(__last.__ptr == nullptr)
          { return this->erase_from(__first);}
          __link_type __bpos = __first.__ptr;
          __link_type __epos = __last.__ptr;
          const size_type __bnum =
            this->key_hash(__get_key(*(__bpos->__data)), this->bucket_size());
          const size_type __enum =
            this->key_hash(__get_key(*(__epos->__data)), this->bucket_size());
          __link_type __pos = this->__bucket[__bnum];
          if(__bnum == __enum)
          {
            if(__bpos == __pos)
            { this->__bucket[__bnum] = __epos;}
            this->__erase_node_chain(__bpos, __epos);
          }
          else
          {
            if(__bpos == __pos)
            { this->__bucket[__bnum] = nullptr;}
            else
            {
              for(; __pos->__next != __bpos; __pos = __pos->__next)
              { }
              __pos->__next = nullptr;
            }
            this->__erase_node_chain(__bpos, nullptr);
            for(size_type __i = __bnum + 1; __i < __enum; ++__i)
            {
              if(this->__bucket[__i] != nullptr)
              {
                this->__erase_node_chain(this->__bucket[__i], nullptr);
                this->__bucket[__i] = nullptr;
              }
            }
            this->__erase_node_chain(this->__bucket[__enum], __epos);
            this->__bucket[__enum] = __epos;
          }
          return iterator(__epos, this);
        }

      public:
        inline hasher hash_function() const
        { return this->__hasher;}
        inline key_equal key_eq() const
        { return this->__key_eq;}

      public:
        inline bool empty() const noexcept
        { return this->size() == 0UL;}
        void clear()
        {
          for(
            typename __bucket_container::iterator __it = this->__bucket.begin(),
              __eit = this->__bucket.end(); __it != __eit; ++__it
          )
          {
            if((*__it) != nullptr)
            {
              this->__deallocate_node_chain(*__it);
              *__it = nullptr;
            }
          }
          this->__mis.first() = 0U;
          return;
        }

      public:
        void swap(hash_table& __o) noexcept(
          trait::type::features::is_nothrow_swappable<hasher>::value &&
          trait::type::features::is_nothrow_swappable<key_equal>::value &&
          trait::type::features::is_nothrow_swappable<allocator_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__load_allocator,  __o.__load_allocator);
          swap(this->__mis,             __o.__mis);
          swap(this->__key_eq,          __o.__key_eq);
          swap(this->__hasher,          __o.__hasher);
          swap(this->__bucket,          __o.__bucket);
        }
        void possible_swap(hash_table& __o) noexcept(
          trait::type::features::is_nothrow_possible_swappable<hasher>::value &&
          trait::type::features::is_nothrow_possible_swappable<key_equal>::value &&
          trait::type::features::is_nothrow_possible_swappable<allocator_type>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__load_allocator,  __o.__load_allocator);
          possible_swap(this->__mis,             __o.__mis);
          possible_swap(this->__key_eq,          __o.__key_eq);
          possible_swap(this->__hasher,          __o.__hasher);
          possible_swap(this->__bucket,          __o.__bucket);
        }

      public:
        float max_load_factor() const noexcept
        { return this->__load_allocator.first();}
        void max_load_factor(float __fac) noexcept
        { this->__load_allocator.first() = __fac;}
        float load_factor() const noexcept
        {
          return static_cast<double>(this->size()) / this->__bucket.size();
        }

      __utility_private:
        UTILITY_ALWAYS_INLINE
        inline size_type key_hash(const key_type& __key, size_type __s) const
        { return (this->__hasher)(__key) % __s;}
        iterator erase_from(const_iterator __pos)
        {
          __link_type __tpos = __pos.__ptr;
          const size_type __num =
            this->key_hash(__get_key(*(__tpos->__data)), this->bucket_size());
          __link_type __link = this->__bucket[__num];
          const size_type __bsize = this->bucket_size();
          if(__link == __tpos)
          {
            this->__erase_node_chain(__tpos, nullptr);
            this->__bucket[__num] = nullptr;
          }
          else
          {
            for(; __link->__next != __tpos; __link = __link->__next)
            { }
            __link->__next = nullptr;
            this->__erase_node_chain(__tpos, nullptr);
          }
          for(size_type __i = __num+1; __i != __bsize; ++__i)
          {
            if(this->__bucket[__i] != nullptr)
            {
              this->__erase_node_chain(this->__bucket[__i], nullptr);
              this->__bucket[__i] = nullptr;
            }
          }
          return iterator(nullptr, this);
        }

      private:
        bool is_overload(size_type __add)
        {
          return ((static_cast<double>(this->size() + __add) / this->__bucket.size()) > this->__load_allocator.first());
        }
        void resize(size_type __need_size)
        {
          const size_type __old_size = this->__bucket.size();
          const size_type __new_size =
            __hash_length::__next_prime(__need_size);
          __bucket_container __tmp(
            __new_size, nullptr, this->__bucket.get_allocator()
          );
          __UTILITY_TRY_BEGIN
            for(size_type __now = 0U; __now < __old_size; ++__now)
            {
              __link_type __link = this->__bucket[__now];
              for(;__link != nullptr;)
              {
                size_type __pos =
                  this->key_hash(__get_key(*(__link->__data)), __new_size);
                this->__bucket[__now] = __link->__next;
                __link->__next = __tmp[__pos];
                __tmp[__pos] = __link;
                __link = this->__bucket[__now];
              }
            }
            this->__bucket.swap(__tmp);
          __UTILITY_TRY_END
          __UTILITY_CATCH(...)
          __UTILITY_CATCH_UNWIND(
            for(size_type __now = 0; __now < __tmp.size(); ++__now)
            {
              if(__tmp[__now] != nullptr)
              {
                __link_type __use = __tmp[__now];
                __tmp[__now] = nullptr;
                this->__deallocate_node_chain(__use);
              }
            }
          );
        }

      private:
        static container::pair<iterator, bool>
        __insert_unique(
          __link_type __ins, hash_table* __this
        )
        {
          const size_type __pos =
            __this->key_hash(__get_key(*(__ins->__data)), __this->bucket_size());
          __link_type __link = __this->__bucket[__pos];

          // Search whether the key *(__ins->__data) exists.
          for(__link_type __i = __link; __i != nullptr; __i = __i->__next)
          {
            if(__this->__key_eq(
              __get_key(*(__i->__data)), __get_key(*(__ins->__data))
            ))
            {
              __this->__deallocate_node(__ins);
              return container::pair<iterator, bool>(
                iterator(__i, __this), false
              );
            }
          }

          // The chain has no node which key is *(__ins->__data),
          // insert the node at the begin of the bucket
          __ins->__next = __link;
          __this->__bucket[__pos] = __ins;
          ++(__this->__mis.first());

          return container::pair<iterator, bool>(
            iterator(__ins, __this), true
          );
        }


        static iterator __insert_equal(
          __link_type __ins, hash_table* __this
        )
        {
          const size_type __pos =
            __this->key_hash(__get_key(*(__ins->__data)), __this->bucket_size());
          __link_type __link = __this->__bucket[__pos];

          // Search the insert pos
          for(__link_type __i = __link; __i != nullptr; __i = __i->__next)
          {
            if(__this->__key_eq(
              __get_key(*(__i->__data)), __get_key(*(__ins->__data))
            ))
            {
              __ins->__next = __i->__next;
              __i->__next = __ins;
              ++(__this->__mis.first());
              return iterator(__ins, __this);
            }
          }

          // The chain has no node which key is *(__ins->__data)
          // insert the node at the begin of the bucket
          __ins->__next = __link;
          __this->__bucket[__pos] = __ins;
          ++(__this->__mis.first());

          return iterator(__ins, __this);
        }

      private:
        template<typename... _Args>
        inline __link_type __allocate_node(_Args&&... __args)
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__load_allocator.second())
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __valc.get(),
            algorithm::forward<_Args>(__args)...
          );
          __link_type __link = __node.release();
          __link->__data = __valc.release();
          return __link;
        }
        template<typename _InputIterator>
        container::pair<__link_type, __link_type>
        __allocate_node_chain(
          _InputIterator __first, _InputIterator __last
        )
        {
          __node_container __node(
            __node_allocator_traits_type::allocate(this->__load_allocator.second())
          );
          __value_container __valc(
            allocator_traits_type::allocate(this->__mis.second())
          );
          allocator_traits_type::construct(
            this->__mis.second(), __valc.get(), *__first++
          );
          __link_type __epos = __node.release();
          __epos->__data = __valc.release();
          __epos->__next = nullptr;
          __link_type __bpos = __epos;
          __UTILITY_TRY_BEGIN
            for(; __first != __last;)
            {
              __node.reset(
                __node_allocator_traits_type::allocate(this->__load_allocator.second())
              );
              __valc.reset(
                allocator_traits_type::allocate(this->__mis.second())
              );
              allocator_traits_type::construct(
                this->__mis.second(), __valc.get(), *__first++
              );
              __epos->__next = __node.release();
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
        inline void __deallocate_node(__link_type __root)
        {
          if(__root->__data != nullptr)
          {
            allocator_traits_type::destroy(
              this->__mis.second(), __root->__data
            );
            allocator_traits_type::deallocate(
              this->__mis.second(), __root->__data, 1
            );
          }
          __node_allocator_traits_type::destroy(
            this->__load_allocator.second(), __root
          );
          __node_allocator_traits_type::deallocate(
            this->__load_allocator.second(), __root, 1
          );
          return;
        }
        inline void __deallocate_node_chain(__link_type __tmp)
        {
          if(__tmp->__next != nullptr)
          { this->__deallocate_node_chain(__tmp->__next);}
          this->__deallocate_node(__tmp);
          return;
        }
        inline void __erase_node_chain(
          __link_type __bpos, __link_type __epos
        ) // erase_chain
        {
          __link_type __pos = __bpos;
          for(; __pos != __epos;)
          {
            __pos = __bpos->__next;
            this->__deallocate_node(__bpos);
            --(this->__mis.first());
            __bpos = __pos;
          }
        }

      private:
        UTILITY_ALWAYS_INLINE
        static inline const key_type& __get_key(const value_type& __con)
        {
          using container::get;
          return get<0>(__con);
        }
        UTILITY_ALWAYS_INLINE
        static inline const mapped_type& __get_value(const value_type& __con)
        {
          using container::get;
          return get<1>(__con);
        }
    };

    template<
      typename _Key, typename _Value,
      typename _Key_Value_Container, typename _Hash,
      typename _Key_eq,typename _Alloc
    >
    bool operator==(
      const hash_table<_Key, _Value, _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __x,
      const hash_table<_Key, _Value, _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __y
    )
    {
      return algorithm::is_permutation(
        __x.begin(), __x.end(), __y.begin(), __y.end()
      );
    }
    template<
      typename _Key, typename _Value,
      typename _Key_Value_Container, typename _Hash,
      typename _Key_eq,typename _Alloc
    >
    bool operator!=(
      const hash_table<_Key, _Value, _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __x,
      const hash_table<_Key, _Value, _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __y
    )
    { return !(__x == __y);}
  }

  namespace algorithm
  {
    template<
      typename _Key,
      typename _Value,
      typename _Key_Value_Container,
      typename _Hash,
      typename _Key_eq,
      typename _Alloc
    >
    void swap(
      container::hash_table<_Key, _Value,
        _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __x,
      container::hash_table<_Key, _Value,
        _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y);}
    template<
      typename _Key,
      typename _Value,
      typename _Key_Value_Container,
      typename _Hash,
      typename _Key_eq,
      typename _Alloc
    >
    void possible_swap(
      container::hash_table<_Key, _Value,
        _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __x,
      container::hash_table<_Key, _Value,
        _Key_Value_Container, _Hash, _Key_eq, _Alloc>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    { __x.possible_swap(__y);}

  }
}

#endif // ! __UTILITY_CONTAINER_HASH_TABLE__
