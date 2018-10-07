
#ifndef __UTILITY_CHARS_BASIC_STRING_VIEW__
#define __UTILITY_CHARS_BASIC_STRING_VIEW__

#include<utility/config/utility_config.hpp>
#include<utility/charS/impl/string_find.hpp>

#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/possible_swap.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/algorithm/min.hpp>

#include<utility/container/pair.hpp>

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/property/is_pod.hpp>

#include<utility/charS/char_traits.hpp>

#include<utility/iterator/reverse_iterator.hpp>
#include<utility/iterator/raw_pointer_iterator.hpp>
#include<utility/iterator/distance.hpp>

namespace utility
{
  namespace charS
  {
    namespace __detail
    {
      using namespace iterator;
      using trait::type::categories::is_array;
      using trait::type::property::is_pod;
      using trait::type::releations::is_same;
    }

    template<
      typename _CharT,
      typename _Traits = char_traits<_CharT>
    >
    class basic_string_view
    {
      public:
        typedef _CharT                value_type;
        typedef _CharT                char_type;
        typedef value_type&           reference;
        typedef const value_type      const_value_type;
        typedef const value_type&     const_reference;
        typedef _Traits               traits_type;
        typedef _CharT*               pointer;
        typedef const _CharT*         const_pointer;
        typedef size_t                size_type;
        typedef ptrdiff_t             difference_type;

      public:
        typedef __detail::raw_pointer_iterator<const value_type>  iterator;
        typedef __detail::raw_pointer_iterator<const value_type>  const_iterator;
        typedef __detail::reverse_iterator<iterator>        reverse_iterator;
        typedef __detail::reverse_iterator<const_iterator>  const_reverse_iterator;

      public:
        constexpr static size_type npos = /*static_cast<size_type>*/(-1);

      public:
        static_assert(
          !__detail::is_array<value_type>::value,
          "The char type of the basic_string_view can't be an array."
        );
        static_assert(
          __detail::is_pod<value_type>::value,
          "The char type of the basic_string_view must be pod."
        );
        static_assert(
          __detail::is_same<typename traits_type::char_type, value_type>::value,
          "The traits_type::char_type must be the same as value_type(_CharT)."
        );

      private:
        const_pointer   __ptr;
        size_type       __size;

      public:
        constexpr basic_string_view() noexcept:
          __ptr{}, __size{0U}
        { }

        constexpr basic_string_view(
          const char_type* _str, size_type _count
        ) noexcept:
          __ptr{_str}, __size{_count}
        { }

        __UTILITY_CPP14_CONSTEXPR__
        basic_string_view(const char_type* _str) noexcept:
          __ptr{_str}, __size{traits_type::length(_str)}
        { }
        constexpr basic_string_view(
          const basic_string_view&
        ) noexcept = default;

      public:
        basic_string_view& operator=(
          const basic_string_view&
        ) noexcept = default;

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const_reference operator[](size_type _pos) const
        { return __ptr[_pos];}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference at(size_type _pos) const
        {
#ifdef __UTILITY_USE_EXCEPTION
          if(_pos > __size)
          { }
#endif
          return __ptr[_pos];
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        bool empty() const noexcept
        { return __size == 0U;}
        __UTILITY_CPP14_CONSTEXPR__
        size_type size() const noexcept
        { return __size;}
        __UTILITY_CPP14_CONSTEXPR__
        size_type length() const noexcept
        { return __size;}
        __UTILITY_CPP14_CONSTEXPR__
        size_type max_size() const noexcept
        { return npos;}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const_reference front() const noexcept
        { return *__ptr;}
        __UTILITY_CPP14_CONSTEXPR__
        const_reference back() const noexcept
        { return __ptr[__size-1];}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const_pointer data() const noexcept
        { return __ptr;}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const_iterator begin() const noexcept
        { return const_iterator{__ptr};}
        __UTILITY_CPP14_CONSTEXPR__
        const_iterator cbegin() const noexcept
        { return const_iterator{__ptr};}
        __UTILITY_CPP14_CONSTEXPR__
        const_iterator end() const noexcept
        { return const_iterator{__ptr + __size};}
        __UTILITY_CPP14_CONSTEXPR__
        const_iterator cend() const noexcept
        { return const_iterator{__ptr + __size};}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator{end()};}
        __UTILITY_CPP14_CONSTEXPR__
        const_reverse_iterator crbegin() const noexcept
        { return const_reverse_iterator{end()};}
        __UTILITY_CPP14_CONSTEXPR__
        const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator{begin()};}
        __UTILITY_CPP14_CONSTEXPR__
        const_reverse_iterator crend() const noexcept
        { return const_reverse_iterator{begin()};}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        void remove_prefix(size_type _len) noexcept
        {
          __ptr += _len;
          __size -= _len;
        }
        __UTILITY_CPP14_CONSTEXPR__
        void remove_suffix(size_type _len) noexcept
        { __size -= _len;}

      public:
        __UTILITY_CPP14_CONSTEXPR__
        void swap(basic_string_view& _other) noexcept
        {
          using algorithm::swap;
          swap(__ptr,   _other.__ptr);
          swap(__size,  _other.__size);
        }
        __UTILITY_CPP14_CONSTEXPR__
        void possible_swap(basic_string_view& _other) noexcept
        {
          using algorithm::swap;
          swap(__ptr,   _other.__ptr);
          swap(__size,  _other.__size);
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        basic_string_view substr(
          size_type _offset = 0, size_type _count = npos
        ) const
        {
#ifdef __UTILITY_USE_EXCEPTION
          if(_offset > __size)
          { }
#endif
          if(_offset + _count > __size || _count == npos)
          { _count = __size-_offset;}
          return basic_string_view{__ptr+_offset, _count};
        }

      public:
        __UTILITY_CPP14_CONSTEXPR__
        int compare(
          size_type _pos, size_type _count,
          const char_type* _str, size_type _clen
        ) const noexcept
        {
          using algorithm::min;
          container::pair<const char_type*, const char_type*> __sp =
            substr_ptr(_pos, _count);
          _count = static_cast<size_type>(__sp.second-__sp.first);
          size_type __len = min(_count, _clen);
          int __res = traits_type::compare(__sp.first, _str, __len);
          if(__res)
          { return __res;}
          return _count == _clen ? 0 : (_count < _clen ? -1 : 1);
        }
        __UTILITY_CPP14_CONSTEXPR__
        int compare(basic_string_view& _sv) const noexcept
        { return compare(0U, npos, _sv.__ptr, _sv.__size);}
        __UTILITY_CPP14_CONSTEXPR__
        int compare(
          size_type _pos, size_type _count,
          basic_string_view& _sv
        ) const noexcept
        { return compare(_pos, _count, _sv.__ptr, _sv.__size);}
        __UTILITY_CPP14_CONSTEXPR__
        int compare(
          size_type _pos, size_type _count,
          basic_string_view& _sv,
          size_type _idx, size_type _clen
        ) const noexcept
        {
          container::pair<const char_type*, const char_type*> __sp =
            _sv.substr_ptr(_idx, _clen);
          return compare(
            _pos, _count, __sp.first,
            static_cast<size_type>(__sp.second-__sp.first)
          );
        }
        int compare(const char_type* _str) const noexcept
        {
          size_type __clen = 0U;
          for(; *_str; ++_str, ++__clen)
          { }
          return compare(0U, npos, _str-__clen, __clen);
        }
        int compare(
          size_type _pos, size_type _count,
          const char_type* _str
        ) const noexcept
        {
          size_type __clen = 0U;
          for(; *_str; ++_str, ++__clen)
          { }
          return compare(_pos, _count, _str-__clen, __clen);
        }


      public:
        size_type copy(
          char_type* _dest, size_type _count = npos, size_type _pos = 0U
        ) const
        {
#ifdef __UTILITY_USE_EXCEPTION
          if(_count > __size)
          { }
#endif
          container::pair<const char_type*, const char_type*> __sp =
            substr_ptr(_pos, _count);
          size_type __ns = static_cast<size_type>(__sp.second-__sp.first);
          traits_type::assign(_dest, __sp.first, __ns);
          return __ns;
        }

      private:
        __UTILITY_CPP14_CONSTEXPR__
        container::pair<const char_type*, const char_type*>
        substr_ptr(size_type _idx, size_type _count = npos) const noexcept
        {
          typedef container::pair<const char_type*, const char_type*> __result;
          if(_idx >= __size)
          { return __result{__ptr+__size, __ptr+__size};}
          if(_idx+_count > __size || _count == npos)
          { _count = __size;}
          else
          { _count += _idx;}
          return __result{__ptr+_idx, __ptr+_count};
        }

      public:
        size_type find(
          const basic_string_view& _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type find(
          const char_type* _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type find(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__find<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type find(char_type _ch, size_type _pos = 0) const noexcept
        {
          return impl::__find<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }
        size_type rfind(
          const basic_string_view& _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__rfind<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type rfind(
          const char_type* _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__rfind<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type rfind(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__rfind<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type rfind(char_type _ch, size_type _pos = npos) const noexcept
        {
          return impl::__rfind<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }

      public:
        size_type find_first_of(
          const basic_string_view& _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find_first_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type find_first_of(
          const char_type* _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find_first_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type find_first_of(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__find_first_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type find_first_of(char_type _ch, size_type _pos = 0) const noexcept
        {
          return impl::__find_first_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }
        size_type find_last_of(
          const basic_string_view& _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__find_last_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type find_last_of(
          const char_type* _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__find_last_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type find_last_of(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__find_last_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type find_last_of(char_type _ch, size_type _pos = npos) const noexcept
        {
          return impl::__find_last_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }
        size_type find_first_not_of(
          const basic_string_view& _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find_first_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type find_first_not_of(
          const char_type* _str, size_type _pos = 0
        ) const noexcept
        {
          return impl::__find_first_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type find_first_not_of(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__find_first_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type find_first_not_of(char_type _ch, size_type _pos = 0) const noexcept
        {
          return impl::__find_first_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }
        size_type find_last_not_of(
          const basic_string_view& _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__find_last_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str.__ptr, _str.__size, _pos
          );
        }
        size_type find_last_not_of(
          const char_type* _str, size_type _pos = npos
        ) const noexcept
        {
          return impl::__find_last_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, traits_type::length(_str), _pos
          );
        }
        size_type find_last_not_of(
          const char_type* _str, size_type _pos, size_type _count
        ) const noexcept
        {
          return impl::__find_last_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _str, _count, _pos
          );
        }
        size_type find_last_not_of(
          char_type _ch, size_type _pos = npos
        ) const noexcept
        {
          return impl::__find_last_not_of<char_type, traits_type, size_type, npos>(
            __ptr, __size, _ch, _pos
          );
        }
    };

    template<typename _CharT, typename _Traits>
    constexpr typename basic_string_view<_CharT, _Traits>::size_type
      basic_string_view<_CharT, _Traits>::npos;

    template<typename _CharT, typename _Char_Traits>
    bool operator==(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) == 0;}
    template<typename _CharT, typename _Char_Traits>
    bool operator!=(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) != 0;}
    template<typename _CharT, typename _Char_Traits>
    bool operator<(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) < 0;}
    template<typename _CharT, typename _Char_Traits>
    bool operator>(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) > 0;}
    template<typename _CharT, typename _Char_Traits>
    bool operator<=(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) <= 0;}
    template<typename _CharT, typename _Char_Traits>
    bool operator>=(
      const basic_string_view<_CharT, _Char_Traits>& _x,
      const basic_string_view<_CharT, _Char_Traits>& _y
    ) noexcept
    { return _x.compare(_y) >= 0;}

    typedef basic_string_view<char>         string_view;
    typedef basic_string_view<wchar_t>      wstring_view;
    typedef basic_string_view<char16_t>     u16string_view;
    typedef basic_string_view<char32_t>     u32string_view;
  }
}

#endif // ! __UTILITY_CHARS_BASIC_STRING_VIEW__
