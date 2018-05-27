
#ifndef __UTILITY_ALGORITHM_MOVE_FORWARD__
#define __UTILITY_ALGORITHM_MOVE_FORWARD__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/features/is_trivially_copy_assignable.hpp>
#include<utility/trait/type/features/is_trivially_move_assignable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>
#include<utility/sstd/cstring.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
    }

    /**
     * \todo the implement is not well prepared
     */
    template<typename _InputBidirectionalIterator, typename _OutputBidirectionalIterator>
    inline _OutputBidirectionalIterator move_forward(
      _InputBidirectionalIterator __first, _InputBidirectionalIterator __last,
      _OutputBidirectionalIterator __result
    )
    {
      for(;__first != __last;)
      { *(__result++) = algorithm::move(*(__first++));}
      return __result;
    }
    template<typename _T, typename _U>
    inline
    typename trait::type::miscellaneous::enable_if<
      trait::type::releations::is_same<
        typename
        trait::type::transform::remove_cv<_T>::type,
        _U>::value &&
      trait::type::features::is_trivially_copy_assignable<_U>::value,
      _U*>::type
    move_forward(_T* __first, _T* __last, _U* __result)
    {
      const size_t __len =
        static_cast<size_t>(__last-__first);
      if(__len > 0)
      {
        sstd::memmove(__result, __first, __len*sizeof(_U));
      }
      return __result + __len;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MOVE_BACKWARD__
