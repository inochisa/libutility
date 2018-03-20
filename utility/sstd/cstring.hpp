
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
    using utility::detail::sstd::charS::mbstate_t;
    using utility::detail::sstd::charS::wint_t;

    // Constant
    using utility::detail::sstd::charS::weof;

    // Memory
    // Copying
    using utility::detail::sstd::memory::memcpy;
    using utility::detail::sstd::memory::memccpy;
    using utility::detail::sstd::memory::mempcpy;
    using utility::detail::sstd::memory::memrcpy;
    using utility::detail::sstd::memory::memmove;
    // Search
    using utility::detail::sstd::memory::memchr;
    using utility::detail::sstd::memory::memrchr;
    using utility::detail::sstd::memory::memmem;
    // Comparison
    using utility::detail::sstd::memory::memcmp;
    // Fill
    using utility::detail::sstd::memory::memset;

    // CharS

    // Helper
    using utility::detail::sstd::charS::strend;
    using utility::detail::sstd::charS::strlen;
    using utility::detail::sstd::charS::wcsend;
    using utility::detail::sstd::charS::wcslen;
    // Copying
    using utility::detail::sstd::charS::strcpy;
    using utility::detail::sstd::charS::stpcpy;
    using utility::detail::sstd::charS::strncpy;
    using utility::detail::sstd::charS::stpncpy;
    using utility::detail::sstd::charS::wcscpy;
    using utility::detail::sstd::charS::wcpcpy;
    using utility::detail::sstd::charS::wcsncpy;
    using utility::detail::sstd::charS::wcpncpy;
    // Concatenation
    using utility::detail::sstd::charS::strcat;
    using utility::detail::sstd::charS::stpcat;
    using utility::detail::sstd::charS::strncat;
    using utility::detail::sstd::charS::stpncat;
    using utility::detail::sstd::charS::wcscat;
    using utility::detail::sstd::charS::wcpcat;
    using utility::detail::sstd::charS::wcsncat;
    using utility::detail::sstd::charS::wcpncat;
    // Comparison
    using utility::detail::sstd::charS::strcmp;
    using utility::detail::sstd::charS::strncmp;
    using utility::detail::sstd::charS::wcscmp;
    using utility::detail::sstd::charS::wcsncmp;
    // Searching
    using utility::detail::sstd::charS::strchr;
    using utility::detail::sstd::charS::strrchr;
    using utility::detail::sstd::charS::strcspn;
    using utility::detail::sstd::charS::strpbrk;
    using utility::detail::sstd::charS::strspn;
    using utility::detail::sstd::charS::strstr;
    using utility::detail::sstd::charS::wcschr;
    using utility::detail::sstd::charS::wcsrchr;
    using utility::detail::sstd::charS::wcscspn;
    using utility::detail::sstd::charS::wcspbrk;
    using utility::detail::sstd::charS::wcsspn;
    using utility::detail::sstd::charS::wcsstr;
  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__CSTDING___
