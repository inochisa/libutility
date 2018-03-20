
#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_STRING__
#define __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_STRING__

/**
 * \file char_string.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

#ifndef EOF
# define EOF (-1)
#endif // ! EOF

namespace utility
{
  namespace detail
  {
    namespace sstd
    {
      namespace charS
      {
        // Helper
        /*!
        * \brief find the end of a string(help function)
        *
        * find the '\0' of a string
        *
        * \param[in] __str the string need to be found
        * \return a pointer to the '\0' of this string is returned
        */
        inline char* strend(char* __str) noexcept
        {
          if(__str != nullptr)
          {
            while(*__str != '\0')
            { ++__str;}
          }
          return __str;
        }
        /*!
        * \overload inline const char* strend(const char* __str) noexcept
        *
        * const version of the \c strend
        *
        */
        inline const char* strend(const char* __str) noexcept
        {
          if(__str != nullptr)
          {
            while(*__str != '\0')
            { ++__str;}
          }
          return __str;
        }

        /*!
        * \brief find the length of a string(help function)
        *
        * find the '\0' of a string
        *
        * \param[in] __str the string need to be found
        * \return a pointer to the '\0' of this string is returned
        */
        inline utility::ptrdiff_t strlen(const char* __str)
        {
          return
            __str == nullptr ? -1 :
            utility::detail::sstd::charS::strend(__str) - __str;
        }

        // Copying
        /*!
        * \brief Copy string
        *
        * Copies the C string pointed by \a __source into the array
        * pointed by \a __destination,
        * including the terminating null character (and stopping at that point).
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array
        *                      where the content is to be copied.
        * \param[in] __source      C string to be copied.
        * \return \a __destination is returned.
        * \see utility::detail::sstd::charS::stpcpy
        * \see utility::detail::sstd::charS::strncpy
        * \see utility::detail::sstd::charS::stpncpy
        */
        inline char* strcpy(char* __destination, const char* __source) noexcept
        {
          if(__destination != nullptr && __source != nullptr)
          {
            char* __dest = __destination;
            while(*__source != '\0')
            { *__dest++ = *__source++;}
            *__dest = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Copy string
        *
        * Copies the C string pointed by \a __source into the array
        * pointed by \a __destination,
        * including the terminating null character (and stopping at that point).
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array
        *                      where the content is to be copied.
        * \param[in] __source      C string to be copied.
        * \return the end of \a __destination is returned.
        * \see utility::detail::sstd::charS::strcpy
        * \see utility::detail::sstd::charS::strncpy
        * \see utility::detail::sstd::charS::stpncpy
        */
        inline char* stpcpy(char* __destination, const char* __source) noexcept
        {
          if(__destination != nullptr && __source != nullptr)
          {
            while(*__source != '\0')
            { *__destination++ = *__source++;}
            *__destination = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Copy characters from string
        *
        * Copies the first num characters of \a __source to \a __destination.
        * If the end of the \a __source C string
        * is found before num characters have been copied,
        * \a __destination is padded with zeros until a total
        * of num characters have been written to it.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination
        *                      array where the content is to be copied.
        * \param[in] __source      C string to be copied.
        * \param[in] __size        Maximum number of characters to be copied from source.
        * \return \a __destination is returned.
        * \see utility::detail::sstd::charS::strcpy
        * \see utility::detail::sstd::charS::stpcpy
        * \see utility::detail::sstd::charS::stpncpy
        */
        inline char* strncpy(char* __destination, const char* __source,
          utility::size_t __size
        ) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            char* __dest = __destination;
            while(__size-- && *__source != '\0')
            { *__dest++ = *__source++;}
            *__dest = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Copy characters from string
        *
        * Copies the first num characters of \a __source to \a __destination.
        * If the end of the \a __source C string
        * is found before num characters have been copied,
        * \a __destination is padded with zeros until a total
        * of num characters have been written to it.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination
        *                      array where the content is to be copied.
        * \param[in] __source      C string to be copied.
        * \param[in] __size        Maximum number of characters to be copied from source.
        * \return the end of \a __destination is returned.
        * \see utility::detail::sstd::charS::strcpy
        * \see utility::detail::sstd::charS::stpcpy
        * \see utility::detail::sstd::charS::strncpy
        */
        inline char* stpncpy(char* __destination, const char* __source,
          utility::size_t __size
        ) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            while(__size-- && *__source != '\0')
            { *__destination++ = *__source++;}
            *__destination = '\0';
          }
          return __destination;
        }

        // Concatenation

        /*!
        * \brief Concatenate strings
        *
        * Appends a copy of the \a __source string to
        * the \a __destination string.
        * The terminating null character in \a __destination is overwritten
        * by the first character of \a __source, and a null-character is included
        * at the end of the new string formed by
        * the concatenation of both in \a __destination.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array,
        *                      which should contain a C string, and be large enough
        *                      to contain the concatenated resulting string.
        * \param[in] __source      C string to be appended.
        * \return \a __destination is returned.
        * \see utility::detail::sstd::charS::stpcat
        * \see utility::detail::sstd::charS::strncat
        * \see utility::detail::sstd::charS::stpncat
        */
        inline char* strcat(char* __destination, const char* __source) noexcept
        {
          if(__destination != nullptr && __source != nullptr)
          {
            char* __dest =
              utility::detail::sstd::charS::strend(__destination);
            while(*__source != '\0')
            { *__dest++ = *__source++;}
            *__dest = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Concatenate strings
        *
        * Appends a copy of the \a __source string to
        * the \a __destination string.
        * The terminating null character in \a __destination is overwritten
        * by the first character of \a __source, and a null-character is included
        * at the end of the new string formed by
        * the concatenation of both in \a __destination.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array,
        *                      which should contain a C string, and be large enough
        *                      to contain the concatenated resulting string.
        * \param[in] __source      C string to be appended.
        * \return the end of \a __destination is returned.
        * \see utility::detail::sstd::charS::strcat
        * \see utility::detail::sstd::charS::strncat
        * \see utility::detail::sstd::charS::stpncat
        */
        inline char* stpcat(char* __destination, const char* __source) noexcept
        {
          if(__destination != nullptr && __source != nullptr)
          {
            __destination =
              utility::detail::sstd::charS::strend(__destination);
            while(*__source != '\0')
            { *__destination++ = *__source++;}
            *__destination = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Append characters from string
        *
        * Appends the first num characters of \a __source to \a __destination,
        * plus a terminating null-character.<br/>
        * If the length of the C string in \a __source is less than num,
        * only the content up to the terminating null-character is copied.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array,
        *                      which should contain a C string, and be large enough
        *                      to contain the concatenated resulting string.
        * \param[in] __source  C string to be appended.
        * \param[in] __size    Maximum number of characters to be appended.
        * \return \a __destination is returned.
        * \see utility::detail::sstd::charS::strcat
        * \see utility::detail::sstd::charS::stpcat
        * \see utility::detail::sstd::charS::stpncat
        */
        inline char* strncat(char* __destination, const char* __source,
          utility::size_t __size
        ) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            char* __dest =
              utility::detail::sstd::charS::strend(__destination);
            while(__size-- && *__source != '\0')
            { *__dest++ = *__source++;}
            *__dest = '\0';
          }
          return __destination;
        }

        /*!
        * \brief Append characters from string
        *
        * Appends the first num characters of \a __source to \a __destination,
        * plus a terminating null-character.<br/>
        * If the length of the C string in \a __source is less than num,
        * only the content up to the terminating null-character is copied.
        *
        * \warning this function doesn't check the overlapping.
        * \param[out] __destination Pointer to the destination array,
        *                      which should contain a C string, and be large enough
        *                      to contain the concatenated resulting string.
        * \param[in] __source  C string to be appended.
        * \param[in] __size    Maximum number of characters to be appended.
        * \return the end of \a __destination is returned.
        * \see utility::detail::sstd::charS::strcat
        * \see utility::detail::sstd::charS::stpcat
        * \see utility::detail::sstd::charS::strncat
        */
        inline char* stpncat(char* __destination, const char* __source,
          utility::size_t __size
        ) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            __destination =
              utility::detail::sstd::charS::strend(__destination);
            while(__size-- && *__source != '\0')
            { *__destination++ = *__source++;}
            *__destination = '\0';
          }
          return __destination;
        }

        // Comparison
        /**
        * \brief Compare characters of two strings
        *
        * Compares up to num characters of
        * the C string \a __comp1 to those of the C string \a __comp2.
        * This function starts comparing the first character of each string.
        * If they are equal to each other, it continues with the following pairs
        * until the characters differ, until a terminating null-character
        * is reached, or until num characters match in both strings,
        * whichever happens first.
        *
        * \param[in] __comp1 C string to be compared.
        * \param[in] __comp2 C string to be compared.
        * \param[in] __size  Maximum number of characters to compare.
        * \return Returns an integral value indicating the relationship
        * between the strings:
        * <table>
        *   <tr>
        *     <th>return value</th>
        *     <th>explanation</th>
        *   </tr>
        *   <tr>
        *     <td>\< 0</td>
        *     <td>the first character that does not match has a lower value
        *         in \a __comp1 than in \a __comp2</td>
        *   </tr>
        *   <tr>
        *     <td>0</td>
        *     <td>the contents of both strings are equal</td>
        *   </tr>
        *   <tr>
        *     <td>\> 0</td>
        *     <td>the first character that does not match has a greater value
        *         in \a __comp1 than in \a __comp2</td>
        *   </tr>
        * \see utility::detail::sstd::charS::strcmp
        */
        inline int strncmp(const char* __comp1, const char* __comp2,
          utility::size_t __size
        ) noexcept
        {
          if(__size && __comp1 != nullptr && __comp2 != nullptr)
          {
            for(; __size && *__comp1 && *__comp2; ++__comp1, ++__comp2, --__size)
            {
              if(*__comp1 != *__comp2)
              { return
                static_cast<int>(*__comp1) - static_cast<int>(*__comp2);}
            }
          }
          return 0;
        }

        /*!
        * \brief Compare two strings
        *
        * Compares the C string \a __comp1 to the C string \a __comp2.<br/>
        * This function starts comparing the first character of each string.
        * If they are equal to each other, it continues with the following pairs
        * until the characters differ or
        * until a terminating null-character is reached.
        *
        * \param[in] __comp1 C string to be compared.
        * \param[in] __comp2 C string to be compared.
        * \return Returns an integral value indicating the relationship
        *         between the strings:
        * <table>
        *   <tr>
        *     <th>return value</th>
        *     <th>explanation</th>
        *   </tr>
        *   <tr>
        *     <td>\< 0</td>
        *     <td>the first character that does not match has a lower value
        *         in \a __comp1 than in \a __comp2</td>
        *   </tr>
        *   <tr>
        *     <td>0</td>
        *     <td>the contents of both strings are equal</td>
        *   </tr>
        *   <tr>
        *     <td>\> 0</td>
        *     <td>the first character that does not match has a greater value
        *         in \a __comp1 than in \a __comp2</td>
        *   </tr>
        * \see utility::detail::sstd::charS::strncmp
        */
        inline int strcmp(const char* __comp1, const char* __comp2) noexcept
        {
          if(__comp1 != nullptr && __comp2 != nullptr)
          {
            utility::ptrdiff_t __size1 =
              utility::detail::sstd::charS::strlen(__comp1);
            utility::ptrdiff_t __size2 =
              utility::detail::sstd::charS::strlen(__comp2);
            utility::ptrdiff_t __size = __size1 < __size2 ? __size1 : __size2;
            return utility::detail::sstd::charS::strncmp(
              __comp1, __comp2, __size
            );
          }
          return 0;
        }

        // Searching
        /*!
        * \brief Locate first occurrence of character in string
        *
        * Returns a pointer to the first occurrence of \a __char
        * in the C string \a __str.<br/>
        * The terminating null-character is considered part of
        * the C string. Therefore, it can also be located in
        * order to retrieve a pointer to the end of a string.
        *
        * \param[in] __str  C string to locate.
        * \param[in] __char Character to be located.
        * \return A pointer to the first occurrence of character in \a __str.<br/>
        *         If the character is not found,
        *         the function returns a null pointer.
        * \see utility::detail::sstd::charS::strrchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strcspn
        * \see utility::detail::sstd::charS::strpbrk(
        *       char* __source, const char* __pattern)
        * \see utility::detail::sstd::charS::strspn
        * \see utility::detail::sstd::charS::strstr(
        *       const char* __source, const char* __pattern)
        */
        inline char* strchr(char* __str, char __char) noexcept
        {
          if(__str != nullptr)
          {
            while(*__str != '\0')
            {
              if(*__str++ == __char)
              { return __str-1;}
            }
            if(*__str == __char)
            { return __str;}
          }
          return nullptr;
        }
        /*!
        * \overload inline const char* strchr(const char* __str, char __char) noexcept
        *
        * const version
        *
        */
        inline const char* strchr(const char* __str, char __char) noexcept
        {
          if(__str != nullptr)
          {
            while(*__str != '\0')
            {
              if(*__str++ == __char)
              { return __str-1;}
            }
            if(*__str == __char)
            { return __str;}
          }
          return nullptr;
        }

        /*!
        * \brief Locate last occurrence of character in string
        *
        * Returns a pointer to the last occurrence of \a __char
        * in the C string \a __str.<br/>
        * The terminating null-character is considered part of
        * the C string. Therefore, it can also be located to
        * retrieve a pointer to the end of a string.
        *
        * \param[in] __str  C string to locate.
        * \param[in] __char Character to be located.
        * A pointer to the last occurrence of character in \a __str.<br/>
        * If the \a __char is not found,
        * the function returns a null pointer.<br/>
        * \see utility::detail::sstd::charS::strchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strcspn
        * \see utility::detail::sstd::charS::strpbrk(
        *       char* __source, const char* __pattern)
        * \see utility::detail::sstd::charS::strspn
        * \see utility::detail::sstd::charS::strstr(
        *       const char* __source, const char* __pattern)
        */
        inline char* strrchr(char* __str, char __char) noexcept
        {
          if(__str != nullptr)
          {
            char* __end =
              utility::detail::sstd::charS::strend(__str);
            while(__end >= __str)
            {
              if(*__end-- == __char)
              { return __end+1;}
            }
          }
          return nullptr;
        }
        /*!
        * \overload inline const char* strrchr(const char* __str, char __char) noexcept
        *
        * const version of strrchr
        *
        */
        inline const char* strrchr(const char* __str, char __char) noexcept
        {
          if(__str != nullptr)
          {
            const char* __end =
              utility::detail::sstd::charS::strend(__str);
            while(__end >= __str)
            {
              if(*__end-- == __char)
              { return __end+1;}
            }
          }
          return nullptr;
        }

        /*!
        * \brief Get span until character in string
        *
        * Scans \a __source for the first occurrence of
        * any of the characters that are part of \a __pattern,
        * returning the number of characters of \a __source read
        * before this first occurrence.<br/>
        * The search includes the terminating null-characters.
        * Therefore, the function will return
        * the length of \a __source if none of the characters of
        * \a __pattern are found in \a __source.
        *
        * \param[in] __source   C string to be scanned.
        * \param[in] __pattern  C string containing the characters to match.
        * \return The length of the initial part of \a __source
        *         not containing any of the characters that are part of
        *         \a __pattern.<br/>
        *         This is the length of \a __source if none of
        *         the characters in \a __pattern are found in \a __source.
        * \see utility::detail::sstd::charS::strchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strrchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strpbrk(
        *       char* __source, const char* __pattern)
        * \see utility::detail::sstd::charS::strspn
        * \see utility::detail::sstd::charS::strstr(
        *       const char* __source, const char* __pattern)
        */
        inline utility::size_t strcspn(const char* __source, const char* __pattern) noexcept
        {
          if(__source != nullptr && __pattern != nullptr)
          {
            const char* __src = __source;
            while(*__src != '\0')
            {
              const char* __pat = __pattern;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__src)
                { return __src - __source;}
              }
              ++__src;
            }
            return __src - __source;
          }
          return 0;
        }

        /*!
        * \brief Locate characters in string
        *
        * Returns a pointer to the first occurrence in \a __source
        * of any of the characters that are part of \a __pattern,
        * or a null pointer if there are no matches.<br/>
        * The search does not include the terminating null-characters
        * of either strings, but ends there.
        *
        * \param[in] __source   C string to be scanned.
        * \param[in] __pattern  C string containing the characters to match.
        * \return A pointer to the first occurrence in \a __source
        * of any of the characters that are part of \a __pattern,
        * or a null pointer if none of the characters of \a __pattern
        * is found in \a __source before the terminating null-character.<br/>
        * If none of the characters of \a __pattern is present
        * in \a __source, a null pointer is returned.
        * \see utility::detail::sstd::charS::strchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strrchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strcspn
        * \see utility::detail::sstd::charS::strspn
        * \see utility::detail::sstd::charS::strstr(
        *       const char* __source, const char* __pattern)
        */
        inline char* strpbrk(char* __source, const char* __pattern) noexcept
        {
          if(__source != nullptr && __pattern != nullptr)
          {
            while(*__source != '\0')
            {
              const char* __pat = __pattern;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__source)
                { return __source;}
              }
              ++__source;
            }
          }
          return nullptr;
        }
        /*!
        * \overload const char* strpbrk(const char* __source,
        *             const char* __pattern) noexcept
        *
        * const version of \c strpbrk
        *
        */
        inline const char* strpbrk(const char* __source, const char* __pattern) noexcept
        {
          if(__source != nullptr && __pattern != nullptr)
          {
            while(*__source != '\0')
            {
              const char* __pat = __pattern;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__source)
                { return __source;}
              }
              ++__source;
            }
          }
          return nullptr;
        }

        /*!
        * \brief Get span of character set in string
        *
        * Returns the length of the initial portion of \a __source
        * which consists only of characters that are part of \a __pattern.<br/>
        * The search does not include the terminating null-characters
        * of either strings, but ends there.
        *
        * \param __source   C string to be scanned.
        * \param __pattern  C string containing the characters to match.
        * \return The length of the initial portion of \a __source
        *         containing only characters that appear in \a __pattern.<br/>
        *         Therefore, if all of the characters in \a __source are in
        *         \a __pattern, the function returns the length of the entire
        *         \a __source string, and if the first character in
        *         \a __source is not in \a __pattern, the function returns zero.
        * \see utility::detail::sstd::charS::strchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strrchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strcspn
        * \see utility::detail::sstd::charS::strpbrk(
        *       char* __source, const char* __pattern)
        * \see utility::detail::sstd::charS::strstr(
        *       const char* __source, const char* __pattern)
        */
        inline utility::size_t strspn(const char* __source, const char* __pattern) noexcept
        {
          utility::size_t __i = 0;
          if(__source != nullptr && __pattern != nullptr)
          {
            while(*__source != '\0')
            {
              const char* __pat = __pattern;
              while(*__pat != '\0')
              {
                if(*__pat++ == *__source)
                { ++__i; break;}
              }
              ++__source;
            }
          }
          return __i;
        }

        /*!
        * \brief Locate substring
        *
        * Returns a pointer to the first occurrence of \a __pattern in
        * \a __source, or a null pointer if \a __pattern is not part
        * of \a __source.<br/>
        * The matching process does not include the terminating
        * null-characters, but it stops there.
        *
        * \param __source   C string to be scanned.
        * \param __pattern  C string containing the sequence of characters
        *                   to match.
        * \return A pointer to the first occurrence in \a __source
        *         of the entire sequence of characters specified in
        *         \a __pattern, or a null pointer if the sequence
        *         is not present in \a __source.
        * \see utility::detail::sstd::charS::strchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strrchr(
        *       char* __str, char __char)
        * \see utility::detail::sstd::charS::strcspn
        * \see utility::detail::sstd::charS::strpbrk(
        *       char* __source, const char* __pattern)
        * \see utility::detail::sstd::charS::strspn
        */
        inline char* strstr(char* __source, const char* __pattern) noexcept
        {
          if(__source != nullptr && __pattern != nullptr)
          {
            utility::ptrdiff_t __slen =
              utility::detail::sstd::charS::strlen(__source);
            utility::ptrdiff_t __plen =
              utility::detail::sstd::charS::strlen(__pattern);
            if(__slen < __plen)
            { return nullptr;}
            utility::ptrdiff_t __len = __slen - __plen+1;
            while(__len--)
            {
              if((*__source == * __pattern) &&
                    utility::detail::sstd::charS::strncmp(
                      __source, __pattern, __plen
                    ) == 0)
              { return __source;}
              ++__source;
            }
          }
          return nullptr;
        }
        /*!
        * \overload const char* strstr(const char* __source, const char*
        *             __pattern) noexcept
        *
        * const version
        *
        */
        inline const char* strstr(const char* __source, const char* __pattern) noexcept
        {
          if(__source != nullptr && __pattern != nullptr)
          {
            utility::size_t __slen =
              utility::detail::sstd::charS::strlen(__source);
            utility::size_t __plen =
              utility::detail::sstd::charS::strlen(__pattern);
            if(__slen < __plen)
            { return nullptr;}
            utility::size_t __len = __slen - __plen+1;
            while(__len--)
            {
              if((*__source == * __pattern) &&
                    utility::detail::sstd::charS::strncmp(
                      __source, __pattern, __plen
                    ) == 0)
              { return __source;}
              ++__source;
            }
          }
          return nullptr;
        }
      }
    }
  }
}

#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_CHAR_STRING__
