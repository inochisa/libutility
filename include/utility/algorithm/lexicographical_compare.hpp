
#ifndef __UTILITY_ALGORITHM_LEXICOGRAPGICAL_COMPARE__
#define __UTILITY_ALGORITHM_LEXICOGRAPGICAL_COMPARE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _InputIterator1, typename _InputIterator2,
      typename _Compare>
    bool lexicographical_compare(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _Compare __compare
    )
    {
      for(;__first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
      {
        if(__compare(*__first1, *__first2))
        { return true;}
        if(__compare(*__first2, *__first1))
        { return false;}
      }
      return __first1 == __last1 && __first2 != __last2;
    }
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool lexicographical_compare(
      _InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2
    )
    {
      return lexicographical_compare(
        __first1, __last1, __first2, __last2,
        algorithm::less<void>()
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_LEXICOGRAPGICAL_COMPARE__
