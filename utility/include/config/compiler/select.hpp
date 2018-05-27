
// GNU-xml Complier
#if defined(__GCCXML__)
# define __UTILITY_USE_GCC_XML__

// clang complier
#elif defined(__clang__)
#define __UTILITY_USE_CLANG__

#include<utility/config/compiler/clang.hpp>

// GNU Complier
#elif defined(__GNUC__)
#define __UTILITY_USE_GCC__

# include<utility/config/compiler/gcc.hpp>

// MSVC Complier
#elif defiend(_MSC_VER)
#define __UTILITY_USE_MSVC__

#include<utility/config/compiler/MSVC.hpp>

#else
#error Now the utility library does not support this compiler

#endif
