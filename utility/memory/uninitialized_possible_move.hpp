

#ifndef __UTILITY_MEMORY_POSSIBLE_MOVE__
#define __UTILITY_MEMORY_POSSIBLE_MOVE__

#include<utility/config/utility_config.hpp>
#include<utility/memory/uninitialized_copy.hpp>
#include<utility/memory/uninitialized_move.hpp>

#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace memory
  {
    namespace detail
    {
      template<typename _InputIterator, typename _ForwardIterator>
      inline
      _ForwardIterator
      __uninitialized_possible_move(
        _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
        trait::true_type
      )
      { return uninitialized_move(__first, __last, __result);}
      template<typename _InputIterator, typename _ForwardIterator>
      inline
      _ForwardIterator
      __uninitialized_possible_move(
        _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
        trait::false_type
      )
      { return uninitialized_copy(__first, __last, __result);}

      template<typename _InputIterator, typename _ForwardIterator>
      inline
      _ForwardIterator
      __uninitialized_possible_move_backward(
        _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
        trait::true_type
      )
      { return uninitialized_move_backward(__first, __last, __result);}
      template<typename _InputIterator, typename _ForwardIterator>
      inline
      _ForwardIterator
      __uninitialized_possible_move_backward(
        _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
        trait::false_type
      )
      { return uninitialized_copy_backward(__first, __last, __result);}

    }


    template<typename _InputIterator, typename _ForwardIterator>
    inline
    _ForwardIterator
    uninitialized_possible_move(
      _InputIterator __first, _InputIterator __last, _ForwardIterator __result
    )
    {
      typedef trait::type::features::is_nothrow_move_constructible<
        typename iterator::iterator_traits<_InputIterator>::value_type>
        __identify;

      return detail::__uninitialized_possible_move(
        __first, __last, __result, __identify{}
      );
    }
    template<typename _InputIterator, typename _ForwardIterator>
    inline
    _ForwardIterator
    uninitialized_possible_move_backward(
      _InputIterator __first, _InputIterator __last, _ForwardIterator __result
    )
    {
      typedef trait::type::features::is_nothrow_move_constructible<
        typename iterator::iterator_traits<_InputIterator>::value_type>
        __identify;

      return detail::__uninitialized_possible_move_backward(
        __first, __last, __result, __identify{}
      );
    }

  }
}

#endif // ! __UTILITY_MEMORY_POSSIBLE_MOVE__
