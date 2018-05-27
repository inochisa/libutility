
#ifndef ___UTILITY__STANDARD__LIBRARY__CSTDINT___
#define ___UTILITY__STANDARD__LIBRARY__CSTDINT___

#include<utility/config/utility_config.hpp>

#if defined(__UTILITY_USE_GCC__) || defined(__UTILITY_USE_CLANG__)

namespace utility
{
  namespace sstd
  {
    __UTILITY_CPP17_INLINE__
    constexpr size_t char_bit  = __CHAR_BIT__;
    __UTILITY_CPP17_INLINE__
    constexpr size_t short_bit = char_bit* sizeof(short int);
    __UTILITY_CPP17_INLINE__
    constexpr size_t int_bit   = __CHAR_BIT__ * sizeof(int);
    __UTILITY_CPP17_INLINE__
    constexpr size_t long_bit  = __CHAR_BIT__ * sizeof(long);
    __UTILITY_CPP17_INLINE__
    constexpr size_t long_long_bit  =
      char_bit* sizeof(long long int);
    __UTILITY_CPP17_INLINE__
    constexpr size_t pointer_bit  =
      char_bit* sizeof(void*);

    __UTILITY_CPP17_INLINE__
    constexpr bool char_signed = char(-1) < 0;

#ifdef __INT8_TYPE__
    typedef __INT8_TYPE__   int8_t;
#endif
#ifdef __INT16_TYPE__
    typedef __INT16_TYPE__  int16_t;
#endif
#ifdef __INT32_TYPE__
    typedef __INT32_TYPE__  int32_t;
#endif
#ifdef __INT64_TYPE__
    typedef __INT64_TYPE__  int64_t;
#endif

#ifdef __INT_LEAST8_TYPE__
    typedef __INT_LEAST8_TYPE__     int_least8_t;
#endif
#ifdef __INT_LEAST16_TYPE__
    typedef __INT_LEAST16_TYPE__    int_least16_t;
#endif
#ifdef __INT_LEAST32_TYPE__
    typedef __INT_LEAST32_TYPE__    int_least32_t;
#endif
#ifdef __INT_LEAST64_TYPE__
    typedef __INT_LEAST64_TYPE__    int_least64_t;
#endif

#ifdef __INT_FAST8_TYPE__
    typedef __INT_FAST8_TYPE__  int_fast8_t;
#endif
#ifdef __INT_FAST16_TYPE__
    typedef __INT_FAST16_TYPE__ int_fast16_t;
#endif
#ifdef __INT_FAST32_TYPE__
    typedef __INT_FAST32_TYPE__ int_fast32_t;
#endif
#ifdef __INT_FAST64_TYPE__
    typedef __INT_FAST64_TYPE__ int_fast64_t;
#endif

#ifdef __UINT8_TYPE__
    typedef __UINT8_TYPE__  uint8_t;
#endif
#ifdef __UINT16_TYPE__
    typedef __UINT16_TYPE__ uint16_t;
#endif
#ifdef __UINT32_TYPE__
    typedef __UINT32_TYPE__ uint32_t;
#endif
#ifdef __UINT64_TYPE__
    typedef __UINT64_TYPE__ uint64_t;
#endif

#ifdef __UINT_LEAST8_TYPE__
    typedef __UINT_LEAST8_TYPE__   uint_least8_t;
#endif
#ifdef __UINT_LEAST16_TYPE__
    typedef __UINT_LEAST16_TYPE__  uint_least16_t;
#endif
#ifdef __UINT_LEAST32_TYPE__
    typedef __UINT_LEAST32_TYPE__  uint_least32_t;
#endif
#ifdef __UINT_LEAST64_TYPE__
    typedef __UINT_LEAST64_TYPE__  uint_least64_t;
#endif

#ifdef __UINT_FAST8_TYPE__
    typedef __UINT_FAST8_TYPE__  uint_fast8_t;
#endif
#ifdef __UINT_FAST16_TYPE__
    typedef __UINT_FAST16_TYPE__ uint_fast16_t;
#endif
#ifdef __UINT_FAST32_TYPE__
    typedef __UINT_FAST32_TYPE__ uint_fast32_t;
#endif
#ifdef __UINT_FAST64_TYPE__
    typedef __UINT_FAST64_TYPE__ uint_fast64_t;
#endif
  }
}

#else

#include<utility/detail/sstd/int_base.hpp>

namespace utility
{
  namespace sstd
  {

    __UTILITY_CPP17_INLINE__
    constexpr size_t char_bit  = ___CHAR_DIGITAL;
    __UTILITY_CPP17_INLINE__
    constexpr size_t short_bit = char_bit* sizeof(short int);
    __UTILITY_CPP17_INLINE__
    constexpr size_t int_bit   = ___WORD_DIGITAL;
    __UTILITY_CPP17_INLINE__
    constexpr size_t long_bit  = ___LONG_DIGITAL;
    __UTILITY_CPP17_INLINE__
    constexpr size_t long_long_bit  =
      char_bit* sizeof(long long int);
    __UTILITY_CPP17_INLINE__
    constexpr size_t pointer_bit  =
      char_bit* sizeof(void*);

    __UTILITY_CPP17_INLINE__
    constexpr bool char_signed = ___CHAR_IS_SIGNED;

#ifdef UTILITY_NEED_SPECIFIC_TYPES


#endif // ! UTILITY_NEED_SPECIFIC_TYPES

  }
}

#endif // !  // ! Known compilers

#endif // ! ___UTILITY__STANDARD__LIBRARY__CSTDINT___
