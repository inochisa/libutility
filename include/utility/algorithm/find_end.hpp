
#ifndef __UTILITY_ALGORITHM_FIND_END__
#define __UTILITY_ALGORITHM_FIND_END__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/search.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace detail
    {
      template<
        typename _ForwardIterator1,
        typename _ForwardIterator2,
        typename _BinaryPredicate
      >
      _ForwardIterator1 __find_end(
        _ForwardIterator1 _first, _ForwardIterator1 _last,
        _ForwardIterator2 _ffirst, _ForwardIterator2 _flast,
        _BinaryPredicate _pred,
        iterator::forward_iterator_tag, iterator::forward_iterator_tag
      )
      {
        if(_ffirst == _flast)
        { return _last;}
        _ForwardIterator1 __it;
        for(;;)
        {
          _ForwardIterator1 __tit =
            search(_first, _last, _ffirst, _flast, __pred);
          if(__tit == _last)
          { return __it;}
          _first = __it = __tit;
          ++_first;
        }
      }
      template<
        typename _BidirectionalIterator1,
        typename _BidirectionalIterator2,
        typename _BinaryPredicate
      >
      _BidirectionalIterator1 __find_end(
        _BidirectionalIterator1 _first, _BidirectionalIterator1 _last,
        _BidirectionalIterator2 _ffirst, _BidirectionalIterator2 _flast,
        _BinaryPredicate _pred,
        iterator::bidirectional_iterator_tag,
        iterator::bidirectional_iterator_tag
      )
      {
        if(_ffirst == _flast)
        { return _last;}

        _BidirectionalIterator1 __end1 = _last;
        _BidirectionalIterator2 __end2 = _flast;
        --__end2;
        for(;;)
        {
          for(;;)
          {
            if(_first == __end1)
            { return _last;}
            if(_pred(*--__end1, *__end2))
            { break;}
          }

          _BidirectionalIterator1 __pos1 = __end1;
          _BidirectionalIterator2 __pos2 = __end2;

          for(;;)
          {
            if(__pos2 == _ffirst)
            { return __pos1;}
            if(__pos1 == _first)
            { return _last;}
            if(!_pred(*--__pos1, *--__pos2))
            { break;}
          }
        }
      }
      template<
        typename _RandomAccessIterator1,
        typename _RandomAccessIterator2,
        typename _BinaryPredicate
      >
      _RandomAccessIterator1 __find_end(
        _RandomAccessIterator1 _first, _RandomAccessIterator1 _last,
        _RandomAccessIterator2 _ffirst, _RandomAccessIterator2 _flast,
        _BinaryPredicate _pred,
        iterator::random_access_iterator_tag,
        iterator::random_access_iterator_tag
      )
      {
        using iterator::iterator_traits;
        typedef typename iterator_traits<_RandomAccessIterator1>::difference_type
          __diff_type1;
        typedef typename iterator_traits<_RandomAccessIterator2>::difference_type
          __diff_type2;

        if(_ffirst == _flast)
        { return _last;}
        __diff_type1 __len1 = _last-_first;
        __diff_type2 __len2 = _flast-_ffirst;

        if(__len1 < __len2)
        { return _last;}

        const _RandomAccessIterator1 __end = _first+(__len2-1);
        _RandomAccessIterator1 __end1 = _last;
        _RandomAccessIterator2 __end2 = _flast;
        --__end2;
        for(;;)
        {
          for(;;)
          {
            if(__end1 == __end)
            { return _last;}
            if(_pred(*--__end1, *__end2))
            { break;}
          }

          _RandomAccessIterator1 __pos1 = __end1;
          _RandomAccessIterator1 __pos2 = __end2;

          for(;;)
          {
            if(__pos2 == _ffirst)
            { return __pos1;}
            if(!_pred(*--__pos1, *--__pos2))
            { break;}
          }
        }
      }
    }
    /**
     * \brief Find last subsequence in range
     *
     * Searches for the last subsequence of elements [\a _ffirst, \a _flast)
     * in the range [\a _first, \a _last) satisfied the \a __pred.
     *
     * \tparam _ForwardIterator1,_ForwardIterator2 the iterator type
     * \tparam _BinaryPredicate the predicate type
     * \param _first,_last    the range of elements to examine
     * \param _ffirst,_flast 	the range of elements to search for
     * \param __pred            binary predicate which returns ​\b true
     *                          if the elements should be treated as equal.<br/>
     *                          The signature of the predicate function
     *                          should be logically equivalent to the following:
     *                          \code{.cpp}
     *                            bool pred(const Type1&, const Type2&);
     *                          \endcode
     * \return Iterator to the beginning of last subsequence
     *         [\a _ffirst, \a _flast) in range [first, last).<br/>
     *         If [\a _ffirst, \a _flast) is empty or
     *         if no such subsequence is found, \a _last is returned.
     *
     * @{
     */
    template<
      typename _ForwardIterator1,
      typename _ForwardIterator2,
      typename _BinaryPredicate
    >
    _ForwardIterator1 find_end(
      _ForwardIterator1 _first, _ForwardIterator1 _last,
      _ForwardIterator2 _ffirst, _ForwardIterator2 _flast,
      _BinaryPredicate _pred
    )
    {
      using trait::type::transform::add_lvalue_reference;
      using iterator::iterator_traits;
      typedef typename iterator_traits<_ForwardIterator1>::iterator_category
        __category1;
      typedef typename iterator_traits<_ForwardIterator1>::iterator_category
        __category2;

      return detail::__find_end<_ForwardIterator1, _ForwardIterator2,
        typename add_lvalue_reference<_BinaryPredicate>::type>(
          _first, _last, _ffirst, _flast, _pred,
          __category1{}, __category2{}
        )
    }

    template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline _ForwardIterator1 find_end(
      _ForwardIterator1 _first, _ForwardIterator1 _last,
      _ForwardIterator2 _ffirst, _ForwardIterator2 _flast
    )
    {
      using iterator::iterator_traits;
      return find_end(
        _first, _last, _ffirst, _flast,
        equal_to<void>{}
      );
    }
    /** @}*/
  }
}

#endif // ! __UTILITY_ALGORITHM_FIND_END__
