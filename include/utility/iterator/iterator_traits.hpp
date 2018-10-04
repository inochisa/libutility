
#ifndef __UTILITY_ITERATOR_ITERATOR_TRAITS__
#define __UTILITY_ITERATOR_ITERATOR_TRAITS__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/iterator/iterator_tag.hpp>

namespace utility
{
  namespace iterator
  {
    namespace __trait_impl
    {
      template<typename __Iterator>
      struct __has_iterator_category_tag
      {
        private:
          struct __two
          { char ___[2];};
          template<typename __T>
          static char __test(typename __T::iterator_category* = nullptr);
          template<typename __T>
          static __two __test(...);
        public:
          constexpr static bool value = sizeof(__test<__Iterator>(0)) == sizeof(char);
      };

      template<typename __Iterator, bool>
      struct __iterator_traits_helper
      { };
      template<typename __Iterator>
      struct __iterator_traits_helper<__Iterator, true>
      {
        typedef typename __Iterator::iterator_category  iterator_category;
        typedef typename __Iterator::value_type         value_type;
        typedef typename __Iterator::difference_type    difference_type;
        typedef typename __Iterator::pointer            pointer;
        typedef typename __Iterator::reference          reference;
      };
    }
    template<typename __Iterator>
    struct iterator_traits : public
      __trait_impl::__iterator_traits_helper<__Iterator,
        __trait_impl::__has_iterator_category_tag<__Iterator>::value>
    { };
    template<typename _T>
    struct iterator_traits<_T*>
    {
      typedef contiguous_iterator_tag iterator_category;
      typedef typename
        trait::type::transform::remove_const<_T>::type value_type;
      typedef ptrdiff_t difference_type;
      typedef _T* pointer;
      typedef _T& reference;
    };
    template<typename _T>
    struct iterator_traits<const _T*>
    {
      typedef contiguous_iterator_tag iterator_category;
      typedef typename
        trait::type::transform::remove_const<_T>::type value_type;
      typedef ptrdiff_t difference_type;
      typedef const _T* pointer;
      typedef const _T& reference;
    };

    /**
     * \brief Detect whether a type is an iterator type
     *
     * This is the \b iterator_traits implementation used.
     *
     * \tparam _T the type to detect whether is an iterator type
     * \see iterator::iterator_traits
     */
    template<typename _T>
    using is_iterator =
      trait::integral_constant<bool,
        iterator::__trait_impl::__has_iterator_category_tag<
          iterator::iterator_traits<_T>
        >::value
      >;

    /**
     * \brief Detect whether an iterator is an target iterator type
     *
     * \tparam _InputIterator    the input iterator type
     * \tparam _TargetIteratorTag   the request iterator type tag
     * \note   Use this when is_iterator is true_type, otherwise the
     *         behavior is undefined.
     * \see iterator::is_iterator
     */
    template<typename _InputIterator, typename _TargetIteratorTag>
    using is_vaild_iterator_type =
      trait::integral_constant<bool,
        trait::type::releations::is_convertible<
          typename
          iterator::iterator_traits<_InputIterator>::iterator_category,
          _TargetIteratorTag
        >::value
      >;

    /**
     * \brief Detect whether an iterator is a vaild iterator(CT)
     *
     * It's a simple using just for judging whether an iterator is
     * satisfy the request<br/>
     * It's means the \b is_vaild_iterator_type is true_type and
     * the \b value_type of the iterators is convertible.
     *
     * \tparam _InputIterator    the input iterator
     * \tparam _TargetIterator   the request iterator
     * \note   Use this when is_iterator is true_type, otherwise the
     *         behavior is undefined.
     * \see iterator::is_iterator
     * \see iterator::is_vaild_iterator_type
    */
    template<typename _InputIterator, typename _TargetIterator>
    using is_vaild_iterator =
      trait::integral_constant<bool,
        is_vaild_iterator_type<
          _InputIterator,
          typename
          iterator::iterator_traits<_TargetIterator>::iterator_category
        >::value &&
        trait::type::releations::is_convertible<
          typename
          iterator::iterator_traits<_InputIterator>::value_type, typename
          iterator::iterator_traits<_TargetIterator>::value_type
        >::value
      >;

    template<typename _Iterator>
    using is_input_iterator =
      is_vaild_iterator_type<_Iterator, input_iterator_tag>;
    template<typename _Iterator>
    using is_forward_iterator =
      is_vaild_iterator_type<_Iterator, forward_iterator_tag>;
    template<typename _Iterator>
    using is_bidirectional_iterator =
      is_vaild_iterator_type<_Iterator, bidirectional_iterator_tag>;
    template<typename _Iterator>
    using is_random_access_iterator =
      is_vaild_iterator_type<_Iterator, random_access_iterator_tag>;
    template<typename _Iterator>
    using is_contiguous_iterator =
      is_vaild_iterator_type<_Iterator, contiguous_iterator_tag>;
    template<typename _Iterator>
    using is_output_iterator =
      is_vaild_iterator_type<_Iterator, output_iterator_tag>;

  }
}

#endif // ! __UTILITY_ITERATOR_ITERATOR_TRAITS__
