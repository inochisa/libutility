
/*!
* \file cstring.hpp
* \author Inochi Amaoto
* \date 2017-09-13
* \brief sstd cstring library
* a head file like cstring, but the dangerous functions are
* removed. All the function has null pointer check.
*/


#ifndef ___UTILITY__STANDARD__LIBRARY__CSTRING___
#define ___UTILITY__STANDARD__LIBRARY__CSTRING___

#include<utility/detail/sstd/memory.hpp>
#include<utility/detail/sstd/char_string.hpp>

namespace utility
{
  namespace sstd
  {
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

    // Char string
    // Helper
    using utility::detail::sstd::char_string::strend;
    using utility::detail::sstd::char_string::strlen;
    // Copying
    using utility::detail::sstd::char_string::strcpy;
    using utility::detail::sstd::char_string::stpcpy;
    using utility::detail::sstd::char_string::strncpy;
    using utility::detail::sstd::char_string::stpncpy;
    // Concatenation
    using utility::detail::sstd::char_string::strcat;
    using utility::detail::sstd::char_string::stpcat;
    using utility::detail::sstd::char_string::strncat;
    using utility::detail::sstd::char_string::stpncat;
    // Comparison
    using utility::detail::sstd::char_string::strcmp;
    // Searching
    using utility::detail::sstd::char_string::strchr;
    using utility::detail::sstd::char_string::strrchr;
    using utility::detail::sstd::char_string::strcspn;
    using utility::detail::sstd::char_string::strpbrk;
    using utility::detail::sstd::char_string::strspn;
    using utility::detail::sstd::char_string::strstr;
  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__CSTRING___
