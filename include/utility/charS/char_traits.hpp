
#ifndef __UTILITY_CHARS_CHAR_TRAITS__
#define __UTILITY_CHARS_CHAR_TRAITS__

/**
 * \file char_traits.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/sstd/cstring.hpp>
#include<utility/sstd/cstdint.hpp>
#include<utility/stream/streamoff.hpp>
#include<utility/stream/fpos.hpp>

namespace utility
{
  namespace charS
  {
    template<typename _CharT>
    struct char_traits
    {
      typedef _CharT                          char_type;
      typedef int                             int_type;
      typedef stream::streamoff               off_type;
      typedef stream::streampos               pos_type;
      typedef sstd::mbstate_t                 state_type;

      __UTILITY_CPP14_CONSTEXPR__
      static inline void assign(char_type& __c, const char_type& __a) noexcept
      { __c = __a;}
      __UTILITY_CPP14_CONSTEXPR__
      static inline char_type* assign(
        char_type* __cptr, size_t __count,
        char_type __a
      ) noexcept
      {
        char_type* __tmp = __cptr;
        for(; __count; --__count)
        { assign(*__tmp++, __a);}
        return __tmp;
      }

      constexpr static inline bool eq(char_type __x, char_type __y) noexcept
      { return __x == __y;}
      constexpr static inline bool lt(char_type __x, char_type __y) noexcept
      { return __x < __y;}

      static inline char_type* move(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        if(__dest < __src)
        {
          for(; __count; --__count, ++__dest, ++__src)
          { assign(*__dest, *__src);}
        }
        else if(__src < __dest)
        {
          __dest += __count;
          __src += __count;
          for(; __count; --__count)
          { assign(*--__dest, *--__src);}
        }
        return __tmp;
      }

      static inline char_type* copy(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        for(;__count; --__count, ++__dest, ++__src)
        { assign(*__dest, *__src);}
        return __tmp;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline int compare(
        const char_type* __comp1, const char_type* __comp2,
        size_t __count
      ) noexcept
      {
        for(; __count; --__count, ++__comp1, ++__comp2)
        {
          if(lt(*__comp1, *__comp2))
          { return -1;}
          if(lt(*__comp2, *__comp1))
          { return 1;}
        }
        return 0;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline size_t length(const char_type* __str) noexcept
      {
        size_t __len = 0;
        for(; !eq(*__str, char_type(0)); ++__str, ++__len)
        { }
        return __len;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline const char_type* find(
        const char_type* __str, size_t __count,
        const char_type& __pat
      ) noexcept
      {
        for(; __count; --__count, ++__str)
        {
          if(eq(*__str, __pat))
          { return __str;}
        }
        return nullptr;
      }

      constexpr static inline char_type to_char_type(int_type __ch) noexcept
      { return static_cast<char_type>(__ch);}
      constexpr static inline int_type to_int_type(char_type __ch) noexcept
      { return static_cast<int_type>(__ch);}
      constexpr static inline bool eq_int_type(int_type __ch1, int_type __ch2) noexcept
      { return __ch1 == __ch2;}
      constexpr static inline int_type eof() noexcept
      { return static_cast<int_type>(EOF);}
      constexpr static inline int_type not_eof(int_type __ch) noexcept
      { return eq_int_type(__ch, eof()) ? ~eof() : __ch;}
    };

    template<>
    struct char_traits<char>
    {
      typedef char                            char_type;
      typedef int                             int_type;
      typedef stream::streamoff               off_type;
      typedef stream::streampos               pos_type;
      typedef sstd::mbstate_t                 state_type;

      __UTILITY_CPP14_CONSTEXPR__
      static inline void assign(char_type& __c, const char_type& __a) noexcept
      { __c = __a;}
      __UTILITY_CPP14_CONSTEXPR__
      static inline char_type* assign(
        char_type* __cptr, size_t __count,
        char_type __a
      ) noexcept
      {
        char_type* __tmp = __cptr;
        for(; __count; --__count, ++__tmp)
        { assign(*__tmp, __a);}
        return __tmp;
      }

      constexpr static inline bool eq(char_type __x, char_type __y) noexcept
      { return __x == __y;}
      constexpr static inline bool lt(char_type __x, char_type __y) noexcept
      { return __x < __y;}

      static inline char_type* move(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        if(__dest < __src)
        {
          for(;__count; --__count, ++__dest, ++__src)
          { assign(*__dest, *__src);}
        }
        else if(__src < __dest)
        {
          __dest += __count;
          __src += __count;
          for(; __count; --__count)
          { assign(*--__dest, *--__src);}
        }
        return __tmp;
      }

      static inline char_type* copy(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        for(;__count; --__count, ++__dest, ++__src)
        { assign(*__dest, *__src);}
        return __tmp;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline int compare(
        const char_type* __comp1, const char_type* __comp2,
        size_t __count
      ) noexcept
      {
        for(; __count; --__count, ++__comp1, ++__comp2)
        {
          if(lt(*__comp1, *__comp2))
          { return -1;}
          if(lt(*__comp2, *__comp1))
          { return 1;}
        }
        return 0;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline size_t length(const char_type* __str) noexcept
      {
        size_t __len = 0;
        for(; !eq(*__str, char_type(0)); ++__str, ++__len)
        { }
        return __len;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline const char_type* find(
        const char_type* __str, size_t __count,
        const char_type& __pat
      ) noexcept
      {
        for(; __count; --__count, ++__str)
        {
          if(eq(*__str, __pat))
          { return __str;}
        }
        return nullptr;
      }

      constexpr static inline char_type to_char_type(int_type __ch) noexcept
      { return static_cast<char_type>(__ch);}
      constexpr static inline int_type to_int_type(char_type __ch) noexcept
      { return static_cast<int_type>(__ch);}
      constexpr static inline bool eq_int_type(int_type __ch1, int_type __ch2) noexcept
      { return __ch1 == __ch2;}
      constexpr static inline int_type eof() noexcept
      { return static_cast<int_type>(EOF);}
      constexpr static inline int_type not_eof(int_type __ch) noexcept
      { return eq_int_type(__ch, eof()) ? ~eof() : __ch;}
    };


    template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t                         char_type;
      typedef sstd::wint_t                    int_type;
      typedef stream::streamoff               off_type;
      typedef stream::streampos               pos_type;
      typedef sstd::mbstate_t                 state_type;

      __UTILITY_CPP14_CONSTEXPR__
      static inline void assign(char_type& __c, const char_type& __a) noexcept
      { __c = __a;}
      __UTILITY_CPP14_CONSTEXPR__
      static inline char_type* assign(
        char_type* __cptr, size_t __count,
        char_type __a
      ) noexcept
      {
        char_type* __tmp = __cptr;
        for(; __count; --__count, ++__tmp)
        { assign(*__tmp, __a);}
        return __tmp;
      }

      constexpr static inline bool eq(char_type __x, char_type __y) noexcept
      { return __x == __y;}
      constexpr static inline bool lt(char_type __x, char_type __y) noexcept
      { return __x < __y;}

      static inline char_type* move(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        if(__dest < __src)
        {
          for(;__count; --__count, ++__dest, ++__src)
          { assign(*__dest, *__src);}
        }
        else if(__src < __dest)
        {
          __dest += __count;
          __src += __count;
          for(; __count; --__count)
          { assign(*--__dest, *--__src);}
        }
        return __tmp;
      }

      static inline char_type* copy(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        for(;__count; --__count, ++__dest, ++__src)
        { assign(*__dest, *__src);}
        return __tmp;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline int compare(
        const char_type* __comp1, const char_type* __comp2,
        size_t __count
      ) noexcept
      {
        for(; __count; --__count, ++__comp1, ++__comp2)
        {
          if(lt(*__comp1, *__comp2))
          { return -1;}
          if(lt(*__comp2, *__comp1))
          { return 1;}
        }
        return 0;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline size_t length(const char_type* __str) noexcept
      {
        size_t __len = 0;
        for(; !eq(*__str, char_type(0)); ++__str, ++__len)
        { }
        return __len;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline const char_type* find(
        const char_type* __str, size_t __count,
        const char_type& __pat
      ) noexcept
      {
        for(; __count; --__count, ++__str)
        {
          if(eq(*__str, __pat))
          { return __str;}
        }
        return nullptr;
      }

      constexpr static inline char_type to_char_type(int_type __ch) noexcept
      { return static_cast<char_type>(__ch);}
      constexpr static inline int_type to_int_type(char_type __ch) noexcept
      { return static_cast<int_type>(__ch);}
      constexpr static inline bool eq_int_type(int_type __ch1, int_type __ch2) noexcept
      { return __ch1 == __ch2;}
      constexpr static inline int_type eof() noexcept
      { return static_cast<int_type>(WEOF);}
      constexpr static inline int_type not_eof(int_type __ch) noexcept
      { return eq_int_type(__ch, eof()) ? ~eof() : __ch;}
    };


    template<>
    struct char_traits<char16_t>
    {
      typedef char16_t                        char_type;
      typedef sstd::uint_least16_t            int_type;
      typedef stream::streamoff               off_type;
      typedef stream::u16streampos            pos_type;
      typedef sstd::mbstate_t                 state_type;

      __UTILITY_CPP14_CONSTEXPR__
      static inline void assign(char_type& __c, const char_type& __a) noexcept
      { __c = __a;}
      __UTILITY_CPP14_CONSTEXPR__
      static inline char_type* assign(
        char_type* __cptr, size_t __count,
        char_type __a
      ) noexcept
      {
        char_type* __tmp = __cptr;
        for(; __count; --__count, ++__tmp)
        { assign(*__tmp, __a);}
        return __tmp;
      }

      constexpr static inline bool eq(char_type __x, char_type __y) noexcept
      { return __x == __y;}
      constexpr static inline bool lt(char_type __x, char_type __y) noexcept
      { return __x < __y;}

      static inline char_type* move(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        if(__dest < __src)
        {
          for(;__count; --__count, ++__dest, ++__src)
          { assign(*__dest, *__src);}
        }
        else if(__src < __dest)
        {
          __dest += __count;
          __src += __count;
          for(; __count; --__count)
          { assign(*--__dest, *--__src);}
        }
        return __tmp;
      }

      static inline char_type* copy(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        for(;__count; --__count, ++__dest, ++__src)
        { assign(*__dest, *__src);}
        return __tmp;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline int compare(
        const char_type* __comp1, const char_type* __comp2,
        size_t __count
      ) noexcept
      {
        for(; __count; --__count, ++__comp1, ++__comp2)
        {
          if(lt(*__comp1, *__comp2))
          { return -1;}
          if(lt(*__comp2, *__comp1))
          { return 1;}
        }
        return 0;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline size_t length(const char_type* __str) noexcept
      {
        size_t __len = 0;
        for(; !eq(*__str, char_type(0)); ++__str, ++__len)
        { }
        return __len;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline const char_type* find(
        const char_type* __str, size_t __count,
        const char_type& __pat
      ) noexcept
      {
        for(; __count; --__count, ++__str)
        {
          if(eq(*__str, __pat))
          { return __str;}
        }
        return nullptr;
      }

      constexpr static inline char_type to_char_type(int_type __ch) noexcept
      { return static_cast<char_type>(__ch);}
      constexpr static inline int_type to_int_type(char_type __ch) noexcept
      { return static_cast<int_type>(__ch);}
      constexpr static inline bool eq_int_type(int_type __ch1, int_type __ch2) noexcept
      { return __ch1 == __ch2;}
      constexpr static inline int_type eof() noexcept
      { return static_cast<int_type>(WEOF);}
      constexpr static inline int_type not_eof(int_type __ch) noexcept
      { return eq_int_type(__ch, eof()) ? static_cast<int_type>(~eof()) : __ch;}
    };

    template<>
    struct char_traits<char32_t>
    {
      typedef char32_t                        char_type;
      typedef sstd::uint_least32_t            int_type;
      typedef stream::streamoff               off_type;
      typedef stream::u32streampos            pos_type;
      typedef sstd::mbstate_t                 state_type;

      __UTILITY_CPP14_CONSTEXPR__
      static inline void assign(char_type& __c, const char_type& __a) noexcept
      { __c = __a;}
      __UTILITY_CPP14_CONSTEXPR__
      static inline char_type* assign(
        char_type* __cptr, size_t __count,
        char_type __a
      ) noexcept
      {
        char_type* __tmp = __cptr;
        for(; __count; --__count, ++__tmp)
        { assign(*__tmp, __a);}
        return __tmp;
      }

      constexpr static inline bool eq(char_type __x, char_type __y) noexcept
      { return __x == __y;}
      constexpr static inline bool lt(char_type __x, char_type __y) noexcept
      { return __x < __y;}

      static inline char_type* move(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        if(__dest < __src)
        {
          for(;__count; --__count, ++__dest, ++__src)
          { assign(*__dest, *__src);}
        }
        else if(__src < __dest)
        {
          __dest += __count;
          __src += __count;
          for(; __count; --__count)
          { assign(*--__dest, *--__src);}
        }
        return __tmp;
      }

      static inline char_type* copy(
        char_type* __dest, const char_type* __src,
        size_t __count
      ) noexcept
      {
        char_type* __tmp = __dest;
        for(;__count; --__count, ++__dest, ++__src)
        { assign(*__dest, *__src);}
        return __tmp;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline int compare(
        const char_type* __comp1, const char_type* __comp2,
        size_t __count
      ) noexcept
      {
        for(; __count; --__count, ++__comp1, ++__comp2)
        {
          if(lt(*__comp1, *__comp2))
          { return -1;}
          if(lt(*__comp2, *__comp1))
          { return 1;}
        }
        return 0;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline size_t length(const char_type* __str) noexcept
      {
        size_t __len = 0;
        for(; !eq(*__str, char_type(0)); ++__str, ++__len)
        { }
        return __len;
      }

      __UTILITY_CPP14_CONSTEXPR__
      static inline const char_type* find(
        const char_type* __str, size_t __count,
        const char_type& __pat
      ) noexcept
      {
        for(; __count; --__count, ++__str)
        {
          if(eq(*__str, __pat))
          { return __str;}
        }
        return nullptr;
      }

      constexpr static inline char_type to_char_type(int_type __ch) noexcept
      { return static_cast<char_type>(__ch);}
      constexpr static inline int_type to_int_type(char_type __ch) noexcept
      { return static_cast<int_type>(__ch);}
      constexpr static inline bool eq_int_type(int_type __ch1, int_type __ch2) noexcept
      { return __ch1 == __ch2;}
      constexpr static inline int_type eof() noexcept
      { return static_cast<int_type>(WEOF);}
      constexpr static inline int_type not_eof(int_type __ch) noexcept
      { return eq_int_type(__ch, eof()) ? ~eof() : __ch;}
    };

  }
}

#endif // ! __UTILITY_CHARS_CHAR_TRAITS__
