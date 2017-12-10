
#ifndef __UTILITY_GCC_CONFIG__
#define __UTILITY_GCC_CONFIG__

# define UTILITY_GCC_VERSION \
  (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

# define UTILITY_ALWAYS_INLINE __attribute__ ((__always_inline__))
# define __utility_alignof(type) __alignof__(type)

#endif // ! __UTILITY_GCC_CONFIG__
