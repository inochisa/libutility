
/*!
* \file cstring.hpp
* \author Inochi Amaoto
* \date 2017-09-13
* \brief sstd cstring library
* a head file like cstring, but the dangerous functions are
* removed. All the function has null pointer check.
*/


#ifndef ___UTILITY__STANDARD__LIBRARY__CSTDING___
#define ___UTILITY__STANDARD__LIBRARY__CSTDING___

#include<utility/detail/sstd/memory.hpp>
#include<utility/detail/sstd/char_string.hpp>
#include<utility/detail/sstd/wchar_string.hpp>

namespace utility
{
  namespace sstd
  {
    // Type
    using detail::sstd::charS::mbstate_t;
    using detail::sstd::charS::wint_t;

    // Constant
    using detail::sstd::charS::weof;

    // Memory
    // Copying
    using detail::sstd::memory::memcpy;
    using detail::sstd::memory::memccpy;
    using detail::sstd::memory::mempcpy;
    using detail::sstd::memory::memrcpy;
    using detail::sstd::memory::memmove;
    // Search
    using detail::sstd::memory::memchr;
    using detail::sstd::memory::memrchr;
    using detail::sstd::memory::memmem;
    // Comparison
    using detail::sstd::memory::memcmp;
    // Fill
    using detail::sstd::memory::memset;

    // CharS

    // Helper
    using detail::sstd::charS::strend;
    using detail::sstd::charS::strlen;
    using detail::sstd::charS::wcsend;
    using detail::sstd::charS::wcslen;
    // Copying
    using detail::sstd::charS::strcpy;
    using detail::sstd::charS::stpcpy;
    using detail::sstd::charS::strncpy;
    using detail::sstd::charS::stpncpy;
    using detail::sstd::charS::wcscpy;
    using detail::sstd::charS::wcpcpy;
    using detail::sstd::charS::wcsncpy;
    using detail::sstd::charS::wcpncpy;
    // Concatenation
    using detail::sstd::charS::strcat;
    using detail::sstd::charS::stpcat;
    using detail::sstd::charS::strncat;
    using detail::sstd::charS::stpncat;
    using detail::sstd::charS::wcscat;
    using detail::sstd::charS::wcpcat;
    using detail::sstd::charS::wcsncat;
    using detail::sstd::charS::wcpncat;
    // Comparison
    using detail::sstd::charS::strcmp;
    using detail::sstd::charS::strncmp;
    using detail::sstd::charS::wcscmp;
    using detail::sstd::charS::wcsncmp;
    // Searching
    using detail::sstd::charS::strchr;
    using detail::sstd::charS::strrchr;
    using detail::sstd::charS::strcspn;
    using detail::sstd::charS::strpbrk;
    using detail::sstd::charS::strspn;
    using detail::sstd::charS::strstr;
    using detail::sstd::charS::wcschr;
    using detail::sstd::charS::wcsrchr;
    using detail::sstd::charS::wcscspn;
    using detail::sstd::charS::wcspbrk;
    using detail::sstd::charS::wcsspn;
    using detail::sstd::charS::wcsstr;
  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__CSTDING___
