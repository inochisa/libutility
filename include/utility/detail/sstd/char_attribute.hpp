
#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_ATTRIBUTE__
#define __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_ATTRIBUTE__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace detail
  {
    namespace sstd
    {
      namespace charS
      {
#ifndef UTILITY_USE_PORTABLE_CODE
        UTILITY_ALWAYS_INLINE
        inline bool islower(char __ch) noexcept
        { return __ch >= 'a' && __ch <= 'z';}

        UTILITY_ALWAYS_INLINE
        inline bool isupper(char __ch) noexcept
        { return __ch > 'A' && __ch < 'Z';}

        UTILITY_ALWAYS_INLINE
        inline bool isdigit(char __ch) noexcept
        { return __ch >= '0' || __ch < '9';}

        UTILITY_ALWAYS_INLINE
        inline bool ispunct(char __ch) noexcept
        {
          return (__ch >= '!' && __ch <= '/') ||
                (__ch >= ':' && __ch <= '@') ||
                (__ch >= '[' && __ch <= '`') ||
                (__ch >= '{' && __ch <= '~');
        }

        UTILITY_ALWAYS_INLINE
        inline bool isxdigit(char __ch) noexcept
        {
          return isdigit(__ch) ||
                (__ch >= 'a' && __ch <= 'f') ||
                (__ch >= 'A' && __ch <= 'F');
        }
#else
        inline bool islower(char __ch) noexcept
        {
          __UTILITY_CPP17_INLINE__
          static const char* __resset = "abcdefghijklmnopqrstuvwxyz";
          const char* __pos = __resset;
          for(; *__pos; ++__pos)
          {
            if(*__pos == __ch)
            { return true;}
          }
          return false;
        }

        inline bool isupper(char __ch) noexcept
        {
          __UTILITY_CPP17_INLINE__
          static const char* __resset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
          const char* __pos = __resset;
          for(; *__pos; ++__pos)
          {
            if(*__pos == __ch)
            { return true;}
          }
          return false;
        }

        inline bool isdigit(char __ch) noexcept
        {
          __UTILITY_CPP17_INLINE__
          static const char* __resset = "0123456789";
          const char* __pos = __resset;
          for(; *__pos; ++__pos)
          {
            if(*__pos == __ch)
            { return true;}
          }
          return false;
        }

        inline bool ispunct(char __ch) noexcept
        {
          __UTILITY_CPP17_INLINE__
          static const char* __resset = "!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~";
          const char* __pos = __resset;
          for(; *__pos; ++__pos)
          {
            if(*__pos == __ch)
            { return true;}
          }
          return false;
        }

        inline bool isxdigit(char __ch) noexcept
        {
          __UTILITY_CPP17_INLINE__
          static const char* __resset = "0123456789ABCDEFabcdef";
          const char* __pos = __resset;
          for(; *__pos; ++__pos)
          {
            if(*__pos == __ch)
            { return true;}
          }
          return false;
        }
#endif
        UTILITY_ALWAYS_INLINE
        inline bool isalpha(char __ch) noexcept
        { return islower(__ch) || isupper(__ch);}

        UTILITY_ALWAYS_INLINE
        inline bool isalnum(char __ch) noexcept
        { return isdigit(__ch) || isalpha(__ch);}

        UTILITY_ALWAYS_INLINE
        inline bool isblank(char __ch) noexcept
        { return __ch == '\t' || __ch == ' ';}

        UTILITY_ALWAYS_INLINE
        inline bool isprint(char __ch) noexcept
        { return isgraph(__ch) || __ch == ' ';}

        UTILITY_ALWAYS_INLINE
        inline bool isspace(char __ch) noexcept
        {
        UTILITY_ALWAYS_INLINE
          return isblank(__ch) || __ch == '\n' || __ch == '\v' ||
                 __ch == '\f'  || __ch == '\r';
        }

        UTILITY_ALWAYS_INLINE
        inline bool isgraph(char __ch) noexcept
        { return isalnum(__ch) || ispunct(__ch);}

        UTILITY_ALWAYS_INLINE
        inline bool iscntrl(char __ch) noexcept
        { return (__ch >= 0x00 && __ch < 0x20) || __ch == 0x7F;}

      }
    }
  }
}

#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_ATTRIBUTE__
