
#ifndef __UTILITY_ITERATOR_REVERSE_ITERATOR__
#define __UTILITY_ITERATOR_REVERSE_ITERATOR__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/iterator/iterator_traits.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>

namespace utility
{
  namespace iterator
  {

    template<typename __Iterator>
    class reverse_iterator
    {
      public:
        typedef typename
          iterator_traits<__Iterator>::iterator_category  iterator_category;
        typedef typename
          iterator_traits<__Iterator>::value_type       value_type;
        typedef typename
          iterator_traits<__Iterator>::difference_type  difference_type;
        typedef typename
          iterator_traits<__Iterator>::pointer          pointer;
        typedef typename
          iterator_traits<__Iterator>::reference        reference;
      public:
        typedef __Iterator                                iterator_type;

      protected:
        __Iterator current;

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator(): current()
        { }
        __UTILITY_CPP14_CONSTEXPR__
        inline explicit reverse_iterator(iterator_type __iit):
          current(__iit)
        { }
        template<typename _T>
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator(const reverse_iterator<_T>& __oit):
          current(__oit.base())
        { }

      public:
        template<typename _T>
        inline __UTILITY_CPP14_CONSTEXPR__
        reverse_iterator& operator= (const reverse_iterator<_T>& __oit)
        {
          this->current = __oit.base();
          return *this;
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline reference operator*() const
        {
          iterator_type __uit = this->current;
          return *--__uit;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline pointer operator->() const
        { return ::utility::memory::addressof(this->operator*());}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator& operator++()
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   bidirectional_iterator_tag>::value,
          //   "Need the iterator support backward.");
          --(this->current);
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator operator++(int) const
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   bidirectional_iterator_tag>::value,
          //   "Need the iterator support backward.");
          reverse_iterator __nit(this->current);
          --(this->current);
          return __nit;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator& operator--()
        {
          ++(this->current);
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator operator--(int) const
        {
          reverse_iterator __nit(this->current);
          ++(this->current);
          return __nit;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator operator+(difference_type __len) const
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return reverse_iterator(this->current - __len);
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator operator-(difference_type __len) const
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return reverse_iterator(this->current + __len);
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator& operator+=(difference_type __len)
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          this->current -= __len;
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reverse_iterator& operator-=(difference_type __len)
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          this->current += __len;
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reference operator[](difference_type __len) const
        {
          // using ::utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return *(*this + __len);
        }

      public:
        iterator_type base() const
        { return this->current;}

    };

    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    { return __x.base() == __y.base();}
    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    { return __x.base() != __y.base();}

    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    {
      return __x.base() > __y.base();
    }
    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    {
      return __x.base() >= __y.base();
    }
    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    {
      return __x.base() < __y.base();
    }
    template<typename __Iterator1, typename __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(const reverse_iterator<__Iterator1>& __x,
      const reverse_iterator<__Iterator2>& __y)
    {
      return __x.base() <= __y.base();
    }

#ifdef UTILITY_ITERATOR_HAS_EXTRA_OPERATOR_ADD

    template<typename __Iterator>
    __UTILITY_CPP14_CONSTEXPR__
    inline reverse_iterator<__Iterator> operator+(
      typename reverse_iterator<__Iterator>::difference_type __len,
      const reverse_iterator<__Iterator>& __it)
    {
      return __it + __len;
    }

#endif // ! UTILITY_ITERATOR_HAS_EXTRA_OPERATOR_ADD

    template<typename __Iterator>
    __UTILITY_CPP14_CONSTEXPR__
    inline auto operator-(const reverse_iterator<__Iterator>& __x,
      const reverse_iterator<__Iterator>& __y)
      ->decltype(__y.base() - __x.base())
    {
      return __y.base() - __x.base();
    }

    template<typename __Iterator>
    __UTILITY_CPP17_CONSTEXPR__
    inline reverse_iterator<__Iterator> make_reverse_iterator(__Iterator __it)
    { return reverse_iterator<__Iterator>(__it);}
  }
}

#endif // ! __UTILITY_ITERATOR_REVERSE_ITERATOR__
