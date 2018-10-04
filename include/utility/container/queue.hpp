
#ifndef __UTILITY_CONTAINER_QUEUE__
#define __UTILITY_CONTAINER_QUEUE__

/**
 * \file queue.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/container/container_helper.hpp>

#include<utility/algorithm/move.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>

#include<utility/container/list.hpp>

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_nothrow_default_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_swappable.hpp>
#include<utility/trait/type/features/is_nothrow_possible_swappable.hpp>

namespace utility
{
  namespace container
  {
    template
    <
      typename _T,
      typename _Container = container::list<_T>
    >
    class queue
    {
      public:
        typedef _Container                                container_type;
        typedef typename container_type::value_type       value_type;
        typedef typename container_type::reference        reference;
        typedef typename container_type::const_reference  const_reference;
        typedef typename container_type::size_type        size_type;

        static_assert(
          trait::type::releations::is_same<_T, value_type>::value,
          "the container's value type must epual to the queue use type."
        );

      protected:
        container_type __container;

      public:
        explicit queue() noexcept(
          trait::type::features::is_nothrow_default_constructible<container_type>::value
        ): __container()
        { }
        explicit queue(const container_type& __cont) noexcept(
          trait::type::features::is_nothrow_copy_constructible<container_type>::value
        ): __container(__cont)
        { }
        explicit queue(container_type&& __cont) noexcept(
          trait::type::features::is_nothrow_move_constructible<container_type>::value
        ): __container(algorithm::move(__cont))
        { }
        queue(const queue& __queue) noexcept(
          trait::type::features::is_nothrow_copy_constructible<container_type>::value
        ): __container(__queue.__container)
        { }
        queue(queue&& __queue) noexcept(
          trait::type::features::is_nothrow_move_constructible<container_type>::value
        ): __container(algorithm::move(__queue.__container))
        { }

      public:
        queue& operator=(const queue& __queue) noexcept(
          trait::type::features::is_nothrow_copy_assignable<container_type>::value
        )
        {
          if(&__queue != this)
          { this->__container = __queue.__container;}
          return *this;
        }
        queue& operator=(queue&& __queue) noexcept(
          trait::type::features::is_nothrow_move_assignable<container_type>::value
        )
        {
          if(&__queue != this)
          {
            this->__container =
              algorithm::move(__queue.__container);
          }
          return *this;
        }

      public:
        reference top()
        { return this->__container.front();}
        const_reference top() const
        { return this->__container.front();}

      public:
        bool empty() const noexcept
        { return this->__container.empty();}
        size_type size() const noexcept
        { return this->__container.size();}

      public:
        void push(const value_type& __val)
        { this->__container.push_back(__val);}
        void push(value_type&& __val)
        { this->__container.push_back(algorithm::move(__val));}
        template<typename... _Args>
        reference emplace(_Args&&... __args)
        {
          return this->__container.emplace_back(
            algorithm::move(__args)...
          );
        }

      public:
        void pop()
        { this->__container.pop_front();}

      public:
        void swap(queue& __other) noexcept(
          trait::type::features::is_nothrow_swappable<container_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__container, __other.__container);
        }
        void possible_swap(queue& __other) noexcept(
          trait::type::features::is_nothrow_possible_swappable<container_type>::value
        )
        {
          using algorithm::possible_swap;
          possible_swap(this->__container, __other.__container);
        }

      private:
        template<typename _U, typename _C>
        friend
        bool operator==(
          const queue<_U, _C>& __x, const queue<_U, _C>& __y
        );
        template<typename _U, typename _C>
        friend
        bool operator<(
          const queue<_U, _C>& __x, const queue<_U, _C>& __y
        );
    };

    template<typename _T, typename _C>
    bool operator==(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return __x.__container == __y.container;}
    template<typename _T, typename _C>
    bool operator!=(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return !(__x == __y);}
    template<typename _T, typename _C>
    bool operator<(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return __x.__container < __y.container;}
    template<typename _T, typename _C>
    bool operator<=(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return !(__y < __x);}
    template<typename _T, typename _C>
    bool operator>(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return __y < __x;}
    template<typename _T, typename _C>
    bool operator>=(
      const queue<_T, _C>& __x, const queue<_T, _C>& __y
    )
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<typename _T, typename _Container>
    void swap(
      container::queue<_T, _Container>& __x,
      container::queue<_T, _Container>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y);}
    template<typename _T, typename _Container>
    void possible_swap(
      container::queue<_T, _Container>& __x,
      container::queue<_T, _Container>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    { __x.possible_swap(__y);}
  }

}

#endif // ! __UTILITY_CONTAINER_QUEUE__
