
#ifndef ___UTILITY__STANDARD__LIBRARY__CSTDLIB___
#define ___UTILITY__STANDARD__LIBRARY__CSTDLIB___

#include<utility/config/utility_config.hpp>
#include<cstdlib>

namespace utility
{
  namespace sstd
  {
    using ::std::div_t;
    using ::std::ldiv_t;
    using ::std::lldiv_t;
    using utility::size_t;

    using ::std::abort;
    using ::std::exit;
    using ::std::quick_exit;
    using ::std::_Exit;
    using ::std::atexit;
    using ::std::at_quick_exit;
    using ::std::system;
    using ::std::getenv;

    using ::std::malloc;
    using ::std::calloc;
    using ::std::realloc;
    using ::std::free;

    using ::std::atof;

#ifndef __UTILITY_NO_CPP17__
    using ::std::aligned_alloc
#endif // ! __UTILITY_NO_CPP17__

  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__CSTDLIB___
