

#ifndef ___UTILITY__CONFIG___
#define ___UTILITY__CONFIG___

#ifndef __cplusplus
# error This is a C++ library , please use C++ compiler.
#endif
// add C++11 error
#if __cplusplus < 201103L
# include<utility/config/utility_cpp11_error.hpp>
#endif

#if __cplusplus < 201402L
# define __UTILITY_NO_CPP14__ true
#endif

#if __cplusplus < 201703L
# define __UTILITY_NO_CPP17__ true
#endif

#ifdef __cpp_concepts
#define __UTILITY_CPP_CONCEPTS__ __cpp_concepts
#endif

#ifndef __UTILITY_NO_CPP14__
# define __UTILITY_CPP14_CONSTEXPR__ constexpr
#else
# define __UTILITY_CPP14_CONSTEXPR__
#endif // ! __UTILITY_NO_CPP14__

#ifndef __UTILITY_NO_CPP17__
# define __UTILITY_CPP17_CONSTEXPR__ constexpr
# define __UTILITY_CPP17_INLINE__ inline
#else
# define __UTILITY_CPP17_CONSTEXPR__
# define __UTILITY_CPP17_INLINE__
#endif // ! __UTILITY_NO_CPP17__

#define UTILITY_INTERFACE       1L
#define UTILITY_INCREMENTAL     1L
#define UTILITY_RELEASE         0L
#define UTILITY_VERSION         10101L

// select the support compiler
#include<utility/config/compiler/select.hpp>

#include<utility/config/debug/utility_debug_config.hpp>

#if !defined(__EXCEPTIONS) || defined(__UTILITY_NO_EXCEPTION__)
# define __UTILITY_NO_EXCEPTION__ true
#endif

// utility exception config
#include<utility/config/utility_exception_config.hpp>

// utility endian config
#ifdef __BIG_ENDIAN__
#if __BIG_END_IAN__
#define __UTILITY_BIG_ENDIAN__    1
#define __UTILITY_LITTLE_ENDIAN__ 0
#endif // ! __BIG_ENDIAN__
#endif // ! __BIG_ENDIAN__
#ifdef __LITTLE_ENDIAN__
#if __LITTLE_ENDIAN__
#define __UTILITY_BIG_ENDIAN__    0
#define __UTILITY_LITTLE_ENDIAN__ 1
#endif // ! __LITTLE_ENDIAN__
#endif // ! __LITTLE_ENDIAN__
#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __UTILITY_BIG_ENDIAN__    0
#define __UTILITY_LITTLE_ENDIAN__ 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __UTILITY_BIG_ENDIAN__    1
#define __UTILITY_LITTLE_ENDIAN__ 0
#endif // __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#endif // __BYTE_ORDER__


// get std support config
#include<utility/config/utility_control_config.hpp>

#define utility_null nullptr
// #define Label(X)  laber_##X
// #define Jump(X)   goto laber_##X

// utility global type declaration
#include<utility/config/utility_type.hpp>

// utility extra config
#include<utility/config/extra/utility_algorithm_extra.hpp>
#include<utility/config/extra/utility_container_extra.hpp>
#include<utility/config/extra/utility_iterator_extra.hpp>
#include<utility/config/extra/utility_math_extra.hpp>
#include<utility/config/extra/utility_memory_extra.hpp>
#include<utility/config/extra/utility_trait_extra.hpp>

#endif // ! ___UTILITY__CONFIG__
