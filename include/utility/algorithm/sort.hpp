
#ifndef __UTILITY_ALGORITHM_SORT__
#define __UTILITY_ALGORITHM_SORT__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/impl/sort/select_sort.hpp>
#include<utility/algorithm/impl/sort/bubble_sort.hpp>
#include<utility/algorithm/impl/sort/cocktail_shaker_sort.hpp>
#include<utility/algorithm/impl/sort/odd_even_sort.hpp>
#include<utility/algorithm/impl/sort/comb_sort.hpp>
#include<utility/algorithm/impl/sort/gnome_sort.hpp>
#include<utility/algorithm/impl/sort/insertion_sort.hpp>
#include<utility/algorithm/impl/sort/shell_sort.hpp>
#include<utility/algorithm/impl/sort/cycle_sort.hpp>
#include<utility/algorithm/impl/sort/heap_sort.hpp>
#include<utility/algorithm/impl/sort/quick_sort.hpp>
#include<utility/algorithm/impl/sort/introspective_sort.hpp>

#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/algorithm/algorithm_auxiliary.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Sort the elements in the range.
     *
     * Sorts the elements in the range. [\a __first, \a __last) in ascending order.
     * The order of equal elements is not guaranteed to be preserved.
     *
     * \tparam SortTag        the sort algorithm needed.(default is introspective sort)
     * \tparam _Iterator      the iterator type
     * \tparam _Compare       the comparison function object type
     * \param __first,__last  the range [\a __first, \a __last) to sort
     * \param __compare       comparison function object.<br/>
     *                        The signature of the comparison function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool cmp(const Type1&, const Type2&);
     *                        \endcode
     *
     * \warning the iterator must meet the requirements of \b ValueSwappable,
     *       but \b RandomAccessIterator is not necessary,
     *       the sort will check whether the iterator type request is satisfied.<br/>
     *       The type of dereferenced RandomIt must meet the requirements
     *       of \b MoveAssignable and \b MoveConstructible.<br/>
     *       the behavior is undefined if the comparison function object is invalid.
     * \note This are all the request and guarantee of the sort algorithm
     * <table>
     *   <tr>
     *     <th>algorithm</th>
     *     <th>tag</th>
     *     <th>request iterator</th>
     *     <th>average complexity</th>
     *     <th>best complexity</th>
     *     <th>worst complexity</th>
     *     <th>memory</th>
     *     <th>stable(only for implement)</th>
     *     <th>method</th>
     *   </tr>
     *   <tr>
     *     <td>select sort</td>
     *     <td>select_sort_tag</td>
     *     <td>BidirectionalIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>No</td>
     *     <td>Selection</td>
     *   </tr>
     *   <tr>
     *     <td>bubble sort</td>
     *     <td>bubble_sort_tag</td>
     *     <td>BidirectionalIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>Yes</td>
     *     <td>Exchanging</td>
     *   </tr>
     *   <tr>
     *     <td>cocktail shaker sort</td>
     *     <td>cocktail_shaker_sort_tag</td>
     *     <td>BidirectionalIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>Yes</td>
     *     <td>Exchanging</td>
     *   </tr>
     *   <tr>
     *     <td>odd-even sort</td>
     *     <td>odd_even_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>Yes</td>
     *     <td>Exchanging</td>
     *   </tr>
     *   <tr>
     *     <td>comb sort</td>
     *     <td>comb_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>No</td>
     *     <td>Exchanging</td>
     *   </tr>
     *   <tr>
     *     <td>gnome sort</td>
     *     <td>gnome_sort_tag</td>
     *     <td>BidirectionalIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>Yes</td>
     *     <td>Exchanging</td>
     *   </tr>
     *   <tr>
     *     <td>insertion sort</td>
     *     <td>insertion_sort_tag</td>
     *     <td>BidirectionalIterator</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>Yes</td>
     *     <td>Insertion</td>
     *   </tr>
     *   <tr>
     *     <td>shell sort</td>
     *     <td>shell_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$nlog^{2}n\f$</td>
     *     <td>at most \f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>No</td>
     *     <td>Insertion</td>
     *   </tr>
     *   <tr>
     *     <td>cycle sort</td>
     *     <td>cycle_sort_tag</td>
     *     <td>ForwardIterartor</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>No</td>
     *     <td>Insertion</td>
     *   </tr>
     *   <tr>
     *     <td>heap sort</td>
     *     <td>heap_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$1\f$</td>
     *     <td>No</td>
     *     <td>Selection</td>
     *   </tr>
     *   <tr>
     *     <td>quick sort</td>
     *     <td>quick_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>at most \f$nlogn\f$</td>
     *     <td>\f$n^{2}\f$</td>
     *     <td>at most \f$n\f$</td>
     *     <td>No</td>
     *     <td>Partitioning</td>
     *   </tr>
     *   <tr>
     *     <td>introspective sort</td>
     *     <td>introspective_sort_tag</td>
     *     <td>RandomAccessIterator</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$nlogn\f$</td>
     *     <td>\f$logn\f$</td>
     *     <td>No</td>
     *     <td>Partitioning & Selection</td>
     *   </tr>
     * </table>
     * the default sort tag is \a introspective_sort_tag.<br/>
     */
    template
    <
      typename SortTag = sort_tag::introspective_sort_tag,
      typename _Iterator,
      typename _Compare
    >
    inline void sort(_Iterator __first, _Iterator __last, _Compare __compare)
    {
      typedef typename
        trait::type::transform::add_lvalue_reference<_Compare>::type
        __comp_ref;

      algorithm::detail::__sort<_Iterator, __comp_ref>(
        __first, __last, __compare, SortTag()
      );
    }

    /**
     * \overload inline void sort(_Iterator __first, _Iterator __last)
     *
     * this verson will use operator< as comparison function object.
     *
     */
    template
    <
      typename SortTag = sort_tag::introspective_sort_tag,
      typename _Iterator
    >
    inline void sort(_Iterator __first, _Iterator __last)
    {
      typedef typename
        iterator::iterator_traits<_Iterator>::value_type
        __value_type;

      algorithm::sort(
        __first, __last,
        algorithm::less<__value_type>()
      );
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_SORT__
