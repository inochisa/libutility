
// provide C++11 support error

#ifndef __UTILITY_CPP11_ERROR__

#if __cplusplus < 201103L
# error this file use C++11 standard , use the compiler that \
        supports C++11.
#endif

#endif // ! __UTILITY_CPP11_ERROR__
