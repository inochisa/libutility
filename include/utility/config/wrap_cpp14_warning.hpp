
#if defined(__UTILITY_NO_CPP14__) || \
  defined(__UTILITY_WRAP_CPP14_WARNING__)

#ifndef __UTILITY_WRAP_CPP14_WARNING__

#undef __UTILITY_NO_CPP14__
#define __UTILITY_WRAP_CPP14_WARNING__

#else

#undef __UTILITY_WRAP_CPP14_WARNING__
#define __UTILITY_NO_CPP14__ true

#endif // ! __UTILITY_WRAP_CPP14_WARNING__

#endif
