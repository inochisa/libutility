
#ifndef ___UTILITY__STANDARD__LIBRARY__NEW___
#define ___UTILITY__STANDARD__LIBRARY__NEW___

#include<utility/config/utility_config.hpp>
#include<new>

namespace utility
{
  namespace sstd
  {
    using std::get_new_handler;
    using std::set_new_handler;

    using std::bad_alloc;
    using std::bad_array_new_length;
    using std::nothrow_t;

    using std::new_handler;

    using std::nothrow;

#ifndef __UTILITY_NO_CPP17__

    using std::launder;
    using std::align_val_t;
    // using std::hardware_destructive_interference_size;
    // using std::hardware_constructive_interference_size;

#endif
  }
}

#endif // ! ___UTILITY__STANDARD__LIBRARY__NEW___
