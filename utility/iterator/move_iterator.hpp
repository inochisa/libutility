
#ifndef __UTILITY_ITERATOR_MOVE_ITERATOR__
#define __UTILITY_ITERATOR_MOVE_ITERATOR__

#include<utility/config/utility_config.hpp>
#include<utility/memory/addressof.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/trait/type/categories/is_reference.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>

#include<utility/iterator/iterator_tag.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>

namespace utility
{
  namespace iterator
  {

    template<typename __Iterator>
    class move_iterator
    {
      private:
        typedef typename
          iterator_traits<__Iterator>::reference        original_reference;
      public:
        typedef typename
          iterator_traits<__Iterator>::iterator_category  iterator_category;
        typedef typename
          iterator_traits<__Iterator>::value_type       value_type;
        typedef typename
          iterator_traits<__Iterator>::difference_type  difference_type;
        typedef __Iterator                              pointer;
        typedef typename
          utility::trait::type::miscellaneous::conditional<
           utility::trait::type::categories::is_reference<original_reference>::value,
           typename utility::trait::transform::remove_reference<original_reference>::type&&,
           original_reference>::type                    reference;

      public:
        typedef __Iterator                              iterator_type;

      private:
        __Iterator current;

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator(): current()
        { }
        __UTILITY_CPP14_CONSTEXPR__
        inline explicit move_iterator(iterator_type __iit):
          current(__iit)
        { }
        template<typename _T>
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator(const move_iterator<_T>& __oit):
          current(__oit.base())
        { }

      public:
        template<typename _T>
        inline __UTILITY_CPP14_CONSTEXPR__
        move_iterator& operator= (const move_iterator<_T>& __oit)
        {
          this->current = __oit.base();
          return *this;
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline reference operator*() const
        {
          iterator_type __uit = this->current;
          return static_cast<reference>(*__uit);
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline pointer operator->() const
        { return this->current;}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator& operator++()
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   bidirectional_iterator_tag>::value,
          //   "Need the iterator support backward.");
          ++(this->current);
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator operator++(int) const
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   bidirectional_iterator_tag>::value,
          //   "Need the iterator support backward.");
          move_iterator __nit(this->current);
          ++(this->current);
          return __nit;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator& operator--()
        {
          --(this->current);
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator operator--(int) const
        {
          move_iterator __nit(this->current);
          --(this->current);
          return __nit;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator operator+(difference_type __len) const
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return move_iterator(this->current + __len);
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator operator-(difference_type __len) const
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return move_iterator(this->current - __len);
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator& operator+=(difference_type __len)
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          this->current += __len;
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline move_iterator& operator-=(difference_type __len)
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          this->current -= __len;
          return *this;
        }
        __UTILITY_CPP14_CONSTEXPR__
        inline reference operator[](difference_type __len) const
        {
          // using utility::trait::type::releations::is_convertible;
          // static_assert(is_convertible<iterator_category,
          //   random_access_iterator_tag>::value,
          //   "Need the iterator support random access.");
          return *(this->current + __len);
        }

      public:
        iterator_type base() const
        { return this->current;}

    };

    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator==(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    { return __x.base() == __y.base();}
    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator!=(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    { return __x.base() != __y.base();}

    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    {
      return __x.base() < __y.base();
    }
    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator<=(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    {
      return __x.base() <= __y.base();
    }
    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    {
      return __x.base() > __y.base();
    }
    template<typename __Iterator1, __Iterator2>
    __UTILITY_CPP14_CONSTEXPR__
    inline bool operator>=(const move_iterator<__Iterator1>& __x,
      const move_iterator<__Iterator1>& __y)
    {
      return __x.base() >= __y.base();
    }

    template<typename __Iterator>
    __UTILITY_CPP14_CONSTEXPR__
    inline move_iterator<__Iterator> operator+(
      typename move_iterator<__Iterator>::difference_type __len,
      const move_iterator<__Iterator>& __it)
    { return __it + __len;}

    template<typename __Iterator>
    __UTILITY_CPP14_CONSTEXPR__
    inline auto operator-(const move_iterator<__Iterator>& __x,
      const move_iterator<__Iterator>& __y)
      ->decltype(__x.base() - __y.base())
    {
      return __x.base() - __y.base();
    }

    template<typename __Iterator>
    __UTILITY_CPP17_CONSTEXPR__
    inline move_iterator<__Iterator> make_move_iterator(__Iterator __it)
    { return move_iterator<__Iterator>(__it);}
  }
}

#endif // ! __UTILITY_ITERATOR_MOVE_ITERATOR__
