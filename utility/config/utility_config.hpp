

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
#else
# define __UTILITY_CPP17_CONSTEXPR__
#endif // ! __UTILITY_NO_CPP17__

#define UTILITY_INTERFACE       1L
#define UTILITY_INCREMENTAL     1L
#define UTILITY_RELEASE         0L
#define UTILITY_VERSION         10101L

// select the support compiler
#include<utility/config/compiler/select.hpp>

#include<utility/config/debug/utility_debug_config.hpp>

#if !defined(__EXCEPTIONS) || !defined(__UTILITY_NO_EXCEPTION__)
# define __UTILITY_NO_EXCEPTION__ true
#endif



// utility exception config
#include<utility/config/utility_exception_config.hpp>

#define utility_null nullptr
#define Label(X)  laber_##X
#define Jump(X)   goto laber_##X


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
