
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
        // Constant
        typedef __WINT_TYPE__ wint_t;
        constexpr wchar_t weof = WEOF;

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

        // Helper

        /**
         * \brief find the end of a string(help function)
         *
         * the wide character version of \c strend
         *
         * \see detail::sstd::charS::strend
         */
        inline wchar_t* wcsend(wchar_t* __wstr) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0';)
            { ++__wstr;}
          }
          return __wstr;
        }

        /*!
        * \overload inline const wchar_t* wcsend(const wchar_t* __wstr) noexcept
        *
        * const version of the \c wcsend
        *
        */
        inline const wchar_t* wcsend(const wchar_t* __wstr) noexcept
        {
          if(__wstr != nullptr)
          {
            for(;*__wstr != '\0';)
            { ++__wstr;}
          }
          return __wstr;
        }

        /**
         * \brief find the length of a string(help function)
         *
         * the wide character version of \c strlen
         *
         * \see detail::sstd::charS::strlen
         */
        inline ptrdiff_t wcslen(const wchar_t* __wstr) noexcept
        {
          return __wstr == nullptr ? -1 :
            detail::sstd::charS::wcsend(__wstr) - __wstr;
        }

        // Copying

        /**
         * \brief Copy string
         *
         * the wide character version of \c strcpy
         *
         * \see detail::sstd::charS::strcpy
         */
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
        /**
         * \brief Copy string
         *
         * the wide character version of \c stpcpy
         *
         * \see detail::sstd::charS::stpcpy
         */
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
        /**
         * \brief Copy characters from string
         *
         * the wide character version of \c strncpy
         *
         * \see detail::sstd::charS::strncpy
         */
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
        /**
         * \brief Copy characters from string
         *
         * the wide character version of \c stpncpy
         *
         * \see detail::sstd::charS::stpncpy
         */
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

        /**
         * \brief Concatenate strings
         *
         * the wide character version of \c stpcat
         *
         * \see detail::sstd::charS::stpcat
         */
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
        /**
         * \brief Concatenate strings
         *
         * the wide character version of \c strcat
         *
         * \see detail::sstd::charS::strcat
         */
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
        /**
         * \brief Append characters from string
         *
         * the wide character version of \c strncat
         *
         * \see detail::sstd::charS::strncat
         */
        inline wchar_t* wcsncat(wchar_t* __wdest, const wchar_t* __wsrc,
          size_t __size
        )
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
        /**
         * \brief Append characters from string
         *
         * the wide character version of \c stpncat
         *
         * \see detail::sstd::charS::stpncat
         */
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

        /**
         * \brief Compare characters of two strings
         *
         * the wide character version of \c strncmp
         *
         * \see detail::sstd::charS::strncmp
         */
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
        /**
         * \brief Compare two strings
         *
         * the wide character version of \c strcmp
         *
         * \see detail::sstd::charS::strcmp
         */
        inline int wcscmp(const wchar_t* __comp1, const wchar_t* __comp2)
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

        /**
         * \brief Locate first occurrence of character in string
         *
         * the wide character version of \c strchr
         *
         * \see detail::sstd::charS::strchr
         */
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
        /*!
        * \overload inline const wchar_t* wcschr(const wchar_t* __wstr, wchar_t __wchar) noexcept
        *
        * const version of the \c wcschr
        *
        */
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
        /**
         * \brief Locate last occurrence of character in string
         *
         * the wide character version of \c strrchr
         *
         * \see detail::sstd::charS::strrchr
         */
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
        /*!
        * \overload inline const wchar_t* wcsrchr(const wchar_t* __wstr, wchar_t __wchar) noexcept

        *
        * const version of the \c wcsrchr
        *
        */
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
        /**
         * \brief Get span until character in string
         *
         * the wide character version of \c strcspn
         *
         * \see detail::sstd::charS::strcspn
         */
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
        /**
         * \brief Locate characters in string
         *
         * the wide character version of \c strpbrk
         *
         * \see detail::sstd::charS::strpbrk
         */
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
        /*!
        * \overload inline const wchar_t* wcspbrk(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        *
        * const version of the \c wcspbrk
        *
        */
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
        /**
         * \brief Get span of character set in string
         *
         * the wide character version of \c strspn
         *
         * \see detail::sstd::charS::strspn
         */
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
        /**
         * \brief Locate substring
         *
         * the wide character version of \c strstr
         *
         * \see detail::sstd::charS::strstr
         */
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
        /*!
        * \overload inline const wchar_t* wcsstr(const wchar_t* __wsrc, const wchar_t* __wpat) noexcept
        *
        * const version of the \c wcsstr
        *
        */
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
