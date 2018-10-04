
#ifndef __UTILITY_CONTAINER_STACK__
#define __UTILITY_CONTAINER_STACK__

/**
 * \file stack.hpp
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
    class stack
    {
      public:
        typedef _Container                                container_type;
        typedef typename container_type::value_type       value_type;
        typedef typename container_type::reference        reference;
        typedef typename container_type::const_reference  const_reference;
        typedef typename container_type::size_type        size_type;

        static_assert(
          trait::type::releations::is_same<_T, value_type>::value,
          "the container's value type must epual to the stack use type."
        );

      protected:
        container_type __container;

      public:
        explicit stack() noexcept(
          trait::type::features::is_nothrow_default_constructible<container_type>::value
        ): __container()
        { }
        explicit stack(const container_type& __cont) noexcept(
          trait::type::features::is_nothrow_copy_constructible<container_type>::value
        ): __container(__cont)
        { }
        explicit stack(container_type&& __cont) noexcept(
          trait::type::features::is_nothrow_move_constructible<container_type>::value
        ): __container(algorithm::move(__cont))
        { }
        stack(const stack& __stack) noexcept(
          trait::type::features::is_nothrow_copy_constructible<container_type>::value
        ): __container(__stack.__container)
        { }
        stack(stack&& __stack) noexcept(
          trait::type::features::is_nothrow_move_constructible<container_type>::value
        ): __container(algorithm::move(__stack.__container))
        { }

      public:
        stack& operator=(const stack& __stack) noexcept(
          trait::type::features::is_nothrow_copy_assignable<container_type>::value
        )
        {
          if(&__stack != this)
          { this->__container = __stack.__container;}
          return *this;
        }
        stack& operator=(stack&& __stack) noexcept(
          trait::type::features::is_nothrow_move_assignable<container_type>::value
        )
        {
          if(&__stack != this)
          {
            this->__container =
              algorithm::move(__stack.__container);
          }
          return *this;
        }

      public:
        reference top()
        { return this->__container.back();}
        const_reference top() const
        { return this->__container.back();}

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
        { this->__container.pop_back();}

      public:
        void swap(stack& __other) noexcept(
          trait::type::features::is_nothrow_swappable<container_type>::value
        )
        {
          using algorithm::swap;
          swap(this->__container, __other.__container);
        }
        void possible_swap(stack& __other) noexcept(
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
          const stack<_U, _C>& __x, const stack<_U, _C>& __y
        );
        template<typename _U, typename _C>
        friend
        bool operator<(
          const stack<_U, _C>& __x, const stack<_U, _C>& __y
        );
    };

    template<typename _T, typename _C>
    bool operator==(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return __x.__container == __y.container;}
    template<typename _T, typename _C>
    bool operator!=(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return !(__x == __y);}
    template<typename _T, typename _C>
    bool operator<(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return __x.__container < __y.container;}
    template<typename _T, typename _C>
    bool operator<=(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return !(__y < __x);}
    template<typename _T, typename _C>
    bool operator>(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return __y < __x;}
    template<typename _T, typename _C>
    bool operator>=(
      const stack<_T, _C>& __x, const stack<_T, _C>& __y
    )
    { return !(__x < __y);}

  }

  namespace algorithm
  {
    template<typename _T, typename _Container>
    void swap(
      container::stack<_T, _Container>& __x,
      container::stack<_T, _Container>& __y
    ) noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y);}
    template<typename _T, typename _Container>
    void possible_swap(
      container::stack<_T, _Container>& __x,
      container::stack<_T, _Container>& __y
    ) noexcept(noexcept(__x.possible_swap(__y)))
    { __x.possible_swap(__y);}
  }
}

#endif // ! __UTILITY_CONTAINER_STACK__
