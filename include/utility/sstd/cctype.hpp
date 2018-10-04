
#ifndef ___UTILITY__STANDARD__LIBRARY__CCTYPE___
#define ___UTILITY__STANDARD__LIBRARY__CCTYPE___

#include<utility/detail/sstd/char_attribute.hpp>

namespace utility
{
  namespace sstd
  {
    using detail::sstd::charS::isalnum;
    using detail::sstd::charS::isalpha;
    using detail::sstd::charS::islower;
    using detail::sstd::charS::isupper;
    using detail::sstd::charS::isdigit;
    using detail::sstd::charS::isxdigit;
    using detail::sstd::charS::isgraph;
    using detail::sstd::charS::isspace;
    using detail::sstd::charS::isblank;
    using detail::sstd::charS::isprint;
    using detail::sstd::charS::ispunct;
  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__CCTYPE___
