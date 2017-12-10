
// provide C++14 support error

#ifndef __UTILITY_CPP14_WARNING__

#if __cplusplus < 201402L
# error this file use C++14 standard , use the compiler that \
        supports C++14.
#endif

#endif // ! __UTILITY_CPP14_WARNING__
