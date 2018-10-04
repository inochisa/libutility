
#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_WCHAR_STRING__
#define __UTILITY_DETAIL_STANDARD_LIBRARY_WCHAR_STRING__

/**
 * \file wchar_string.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

#ifndef __WINT_TYPE__
# define __WINT_TYPE__ unsigned int
#endif // ! __WINT_TYPE__
#ifndef WEOF
# define WEOF (0xffffffffu)
#endif // ! WEOF

namespace utility
{
  namespace detail
  {
    namespace sstd
    {
      namespace charS
      {
        /** \addtogroup charS
         *  @{
         */
        /** \addtogroup Constant
         *  @{
         */
        // Constant
        typedef __WINT_TYPE__ wint_t;
        constexpr wchar_t weof = WEOF;
        /** @}*/

        /** \addtogroup Type
         *  @{
         */
        // Type
        struct mbstate_t
        {
          int __count;
          union
          {
            wint_t __wch;
            char __wchb[4];
          } __value;
        };
        /** @}*/



        /** \addtogroup Helper
         *  @{
         */
        /**
         * \brief find the end of a string(help function)
         *
         * the wide character version of \c strend
         */
        inline wchar_t* wcsend(wchar_t* __wstr) noexcept;
        /**
         * \overload inline const wchar_t* wcsend(const wchar_t* __wstr) noexcept
         */
        inline const wchar_t* wcsend(const wchar_t* __wstr) noexcept;
        /**
         * \brief find the length of a string(help function)
         *
         * the wide character version of \c strlen
         */
        inline ptrdiff_t wcslen(const wchar_t* __wstr) noexcept;
        /** @}*/

        /** \addtogroup Copying
         *  @{
         */
        /**
         * \brief Copy string
         *
         * the wide character version of \c strcpy
         */
        inline wchar_t* wcscpy(wchar_t* __wdest, const wchar_t* __wsrc) noexcept;
        /**
         * \brief Copy string
         *
         * the wide character version of \c stpcpy
         */
        inline wchar_t* wcpcpy(wchar_t* __wdest, const wchar_t* __wsrc) noexcept;
        /**
         * \brief Copy characters from string
         *
         * the wide character version of \c strncpy
         */
        inline wchar_t* wcsncpy(wchar_t* __wdest, const wchar_t* __wsrc, size_t __size) noexcept;
        /**
         * \brief Copy characters from string
         *
         * the wide character version of \c stpncpy
         */
        inline wchar_t* wcpncpy(wchar_t* __wdest, const wchar_t* __wsrc, size_t __size) noexcept;

        /** \addtogroup Concatenation
         *  @{
         */
        /**
         * \brief Concatenate strings
         *
         * the wide character version of \c stpcat
         */
        inline wchar_t* wcscat(wchar_t* __wdest, const wchar_t* __wsrc) noexcept;
        /**
         * \brief Concatenate strings
         *
         * the wide character version of \c strcat
         */
        inline wchar_t* wcpcat(wchar_t* __wdest, const wchar_t* __wsrc) noexcept;
        /**
         * \brief Append characters from string
         *
         * the wide character version of \c strncat
         */
        inline wchar_t* wcsncat(wchar_t* __wdest, const wchar_t* __wsrc, size_t __size) noexcept;
        /**
         * \brief Append characters from string
         *
         * the wide character version of \c stpncat
         */
        inline wchar_t* wcpncat(wchar_t* __wdest, const wchar_t* __wsrc, size_t __size) noexcept;
        /** @}*/

        /** \addtogroup Comparison
         *  @{
         */
        /**
         * \brief Compare characters of two strings
         *
         * the wide character version of \c strncmp
         */
        inline int wcsncmp(const wchar_t* __comp1, const wchar_t* __comp2, size_t __size) noexcept;
        /**
         * \brief Compare two strings
         *
         * the wide character version of \c strcmp
         */
        inline int wcscmp(const wchar_t* __comp1, const wchar_t* __comp2) noexcept;
        /** @}*/

        /** \addtogroup Searching
         *  @{
         */
        /**
         * \brief Locate first occurrence of character in string
         *
         * the wide character version of \c strchr
         */
        inline wchar_t* wcschr(wchar_t* __wstr, wchar_t __wchar) noexcept;
        /**
         * \overload inline const wchar_t* wcschr(const wchar_t* __wstr, wchar_t __wchar) noexcept
         */
        inline const wchar_t* wcschr(const wchar_t* __wstr, wchar_t __wchar) noexcept;
        /**
         * \brief Locate last occurrence of character in string
         *
         * the wide character version of \c strrchr
         */
        inline wchar_t* wcsrchr(wchar_t* __wstr, wchar_t __wchar) noexcept;
        /**
         * \overload inline const wchar_t* wcsrchr(const wchar_t* __wstr, wchar_t __wchar) noexcept
         */
        inline const wchar_t* wcsrchr(const wchar_t* __wstr, wchar_t __wchar) noexcept;
        /**
         * \brief Get span until character in string
         *
         * the wide character version of \c strcspn
         */
        inline size_t wcscspn(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /**
         * \brief Locate characters in string
         *
         * the wide character version of \c strpbrk
         */
        inline wchar_t* wcspbrk(wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /**
         * \overload inline const wchar_t* wcspbrk(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
         */
        inline const wchar_t* wcspbrk(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /**
         * \brief Get span of character set in string
         *
         * the wide character version of \c strspn
         */
        inline size_t wcsspn(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /**
         * \brief Locate substring
         *
         * the wide character version of \c strstr
         */
        inline wchar_t* wcsstr(wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /**
         * \overload inline const wchar_t* wcsstr(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
         */
        inline const wchar_t* wcsstr(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept;
        /** @}*/
        /** @}*/

      }
      namespace charS
      {
        // Helper
        inline wchar_t* wcsend(wchar_t* __wstr) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0';)
            { ++__wstr;}
          }
          return __wstr;
        }

        inline const wchar_t* wcsend(const wchar_t* __wstr) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0';)
            { ++__wstr;}
          }
          return __wstr;
        }

        inline ptrdiff_t wcslen(const wchar_t* __wstr) noexcept
        {
          return __wstr == nullptr ? -1 :
            detail::sstd::charS::wcsend(__wstr) - __wstr;
        }

        // Copying
        inline wchar_t* wcscpy(wchar_t* __wdest, const wchar_t* __wsrc) noexcept
        {
          if(__wdest != nullptr && __wsrc != nullptr)
          {
            wchar_t* __dest = __wdest;
            for(;*__wsrc != '\0';)
            { *__dest++ = *__wsrc++;}
            *__dest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcpcpy(wchar_t* __wdest, const wchar_t* __wsrc) noexcept
        {
          if(__wdest != nullptr && __wsrc != nullptr)
          {
            for(;*__wsrc != '\0';)
            { *__wdest++ = *__wsrc++;}
            *__wdest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcsncpy(wchar_t* __wdest, const wchar_t* __wsrc,
          size_t __size
        ) noexcept
        {
          if(__size && __wdest != nullptr && __wsrc != nullptr)
          {
            wchar_t* __dest = __wdest;
            for(;__size-- && *__wsrc != '\0';)
            { *__dest++ = *__wsrc++;}
            *__dest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcpncpy(wchar_t* __wdest, const wchar_t* __wsrc,
          size_t __size
        ) noexcept
        {
          if(__size && __wdest != nullptr && __wsrc != nullptr)
          {
            for(;*__wsrc != '\0' && __size--;)
            { *__wdest = *__wsrc++;}
            *__wdest = '\0';
          }
          return __wdest;
        }

        // Concatenation
        inline wchar_t* wcscat(wchar_t* __wdest, const wchar_t* __wsrc) noexcept
        {
          if(__wdest != nullptr && __wsrc != nullptr)
          {
            wchar_t* __dest =
              detail::sstd::charS::wcsend(__wdest);
            for(;*__wsrc != '\0';)
            { *__dest++ = *__wsrc++;}
            *__dest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcpcat(wchar_t* __wdest, const wchar_t* __wsrc) noexcept
        {
          if(__wdest != nullptr && __wsrc != nullptr)
          {
            __wdest =
              detail::sstd::charS::wcsend(__wdest);
            for(;*__wsrc != '\0';)
            { *__wdest++ = *__wsrc++;}
            *__wdest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcsncat(wchar_t* __wdest, const wchar_t* __wsrc,
          size_t __size
        ) noexcept
        {
          if(__size && __wdest != nullptr && __wsrc != nullptr)
          {
            wchar_t* __dest =
              detail::sstd::charS::wcsend(__wdest);
            for(;*__wsrc != '\0' && __size--;)
            { *__dest++ = *__wsrc++;}
            *__dest = '\0';
          }
          return __wdest;
        }
        inline wchar_t* wcpncat(wchar_t* __wdest, const wchar_t* __wsrc,
          size_t __size
        ) noexcept
        {
          if(__size && __wdest != nullptr && __wsrc != nullptr)
          {
            __wdest =
              detail::sstd::charS::wcsend(__wdest);
            for(;*__wsrc != '\0' && __size--;)
            { *__wdest = *__wsrc++;}
            *__wdest = '\0';
          }
          return __wdest;
        }

        // Comparison
        inline int wcsncmp(const wchar_t* __comp1, const wchar_t* __comp2,
          size_t __size
        ) noexcept
        {
          if(__size && __comp1 != nullptr && __comp2 != nullptr)
          {
            for(; __size && *__comp1 & *__comp2; ++__comp1, ++__comp2, --__size)
            {
              if(*__comp1 != *__comp2)
              { return
                static_cast<int>(*__comp1) - static_cast<int>(*__comp2);}
            }
          }
          return 0;
        }
        inline int wcscmp(const wchar_t* __comp1, const wchar_t* __comp2) noexcept
        {
          if(__comp1 != nullptr && __comp2 != nullptr)
          {
            ptrdiff_t __size1 =
              detail::sstd::charS::wcslen(__comp1);
            ptrdiff_t __size2 =
              detail::sstd::charS::wcslen(__comp2);
            ptrdiff_t __size = __size1 < __size2 ? __size1 : __size2;
            return detail::sstd::charS::wcsncmp(
              __comp1, __comp2, __size
            );
          }
          return 0;
        }

        // Searching

        inline wchar_t* wcschr(wchar_t* __wstr, wchar_t __wchar) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0'; ++__wstr)
            {
              if(*__wstr == __wchar)
              { return __wstr;}
            }
            if(*__wstr == __wchar)
            { return __wstr;}
          }
          return nullptr;
        }
        inline const wchar_t* wcschr(const wchar_t* __wstr, wchar_t __wchar) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0'; ++__wstr)
            {
              if(*__wstr == __wchar)
              { return __wstr;}
            }
            if(*__wstr == __wchar)
            { return __wstr;}
          }
          return nullptr;
        }

        inline wchar_t* wcsrchr(wchar_t* __wstr, wchar_t __wchar) noexcept
        {
          if(__wstr != nullptr)
          {
            wchar_t* __wend =
              detail::sstd::charS::wcsend(__wstr);
            for(;__wend >= __wstr; --__wend)
            {
              if(*__wend == __wchar)
              { return __wend;}
            }
          }
          return nullptr;
        }
        inline const wchar_t* wcsrchr(const wchar_t* __wstr, wchar_t __wchar) noexcept
        {
          if(__wstr != nullptr)
          {
            const wchar_t* __wend =
              detail::sstd::charS::wcsend(__wstr);
            for(;__wend >= __wstr; --__wend)
            {
              if(*__wend == __wchar)
              { return __wend;}
            }
          }
          return nullptr;
        }

        inline size_t wcscspn(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            const wchar_t* __src = __wsrc;
            while(*__src != '\0')
            {
              const wchar_t* __pat = __wpat;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__src)
                { return __src - __wsrc;}
              }
              ++__src;
            }
            return __src - __wsrc;
          }
          return 0;
        }

        inline wchar_t* wcspbrk(wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            while(*__wsrc != '\0')
            {
              const wchar_t* __pat = __wpat;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__wsrc)
                { return __wsrc;}
              }
              ++__wsrc;
            }
          }
          return nullptr;
        }
        inline const wchar_t* wcspbrk(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            while(*__wsrc != '\0')
            {
              const wchar_t* __pat = __wpat;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__wsrc)
                { return __wsrc;}
              }
              ++__wsrc;
            }
          }
          return nullptr;
        }

        inline size_t wcsspn(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          size_t __i = 0;
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            while(*__wsrc != '\0')
            {
              const wchar_t* __pat = __wpat;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__wsrc)
                { ++__i; break;}
              }
              ++__wsrc;
            }
          }
          return __i;
        }
        inline wchar_t* wcsstr(wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            ptrdiff_t __slen =
              detail::sstd::charS::wcslen(__wsrc);
            ptrdiff_t __plen =
              detail::sstd::charS::wcslen(__wpat);
            if(__slen < __plen)
            { return nullptr;}
            ptrdiff_t __len = __slen - __plen+1;
            while(__len--)
            {
              if((*__wsrc == * __wpat) &&
                    detail::sstd::charS::wcsncmp(
                      __wsrc, __wpat, __plen
                    ) == 0)
              { return __wsrc;}
              ++__wsrc;
            }
          }
          return nullptr;
        }
        inline const wchar_t* wcsstr(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        {
          if(__wsrc != nullptr && __wpat != nullptr)
          {
            size_t __slen =
              detail::sstd::charS::wcslen(__wsrc);
            size_t __plen =
              detail::sstd::charS::wcslen(__wpat);
            if(__slen < __plen)
            { return nullptr;}
            size_t __len = __slen - __plen+1;
            while(__len--)
            {
              if((*__wsrc == * __wpat) &&
                    detail::sstd::charS::wcsncmp(
                      __wsrc, __wpat, __plen
                    ) == 0)
              { return __wsrc;}
              ++__wsrc;
            }
          }
          return nullptr;
        }
      }
    }
  }
}

#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_WCHAR_STRING__
