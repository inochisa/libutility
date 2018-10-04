
#ifndef ___UTILITY__CONFIG__TYPES__PREDEFINED___
#define ___UTILITY__CONFIG__TYPES__PREDEFINED___

#define ___UTILITY_SYSTEM_BITS  64
#define ___UTILITY_BITS         8

#ifndef __CHAR_UNSIGNED__
#define ___UTILITY_CHAR_SIGNED  1
#else
#define ___UTILITY_CHAR_SIGNED  0
#endif

#define ___UTILITY_BIG_ENDIAN   0
#define ___UTILITY_LITTLE_ENDIAN   1

#define ___UTILITY_CHAR_WIDTH     1
#define ___UTILITY_SHORT_WIDTH    2
#define ___UTILITY_INT_WIDTH      4
#define ___UTILITY_LONG_WIDTH     8
#define ___UTILITY_LLONG_WIDTH    8
#define ___UTILITY_FLOAT_WIDTH    4
#define ___UTILITY_DOUBLE_WIDTH   8
#define ___UTILITY_LDOUBLE_WIDTH  16
#define ___UTILITY_PTR_WIDTH      8

#define ___UTILITY_CHAR_BITS      8
#define ___UTILITY_SHORT_BITS     16
#define ___UTILITY_INT_BITS       32
#define ___UTILITY_LONG_BITS      64
#define ___UTILITY_LLONG_BITS     64
#define ___UTILITY_FLOAT_BITS     32
#define ___UTILITY_DOUBLE_BITS    64
#define ___UTILITY_LDOUBLE_BITS   128
#define ___UTILITY_PTR_BITS       64

// char settings
#if ___UTILITY_CHAR_BITS == 8
#define ___UTILITY_SCHAR_MAX      0x7f
#define ___UTILITY_SCHAR_MIN      (-0x7f-1)
#define ___UTILITY_UCHAR_MAX      0xffU
#define ___UTILITY_UCHAR_MIN      0x00U
#elif ___UTILITY_CHAR_BITS == 16
#define ___UTILITY_SCHAR_MAX      0x7fff
#define ___UTILITY_SCHAR_MIN      (-0x7fff-1)
#define ___UTILITY_UCHAR_MAX      0xffffU
#define ___UTILITY_UCHAR_MIN      0x0000U
#elif ___UTILITY_CHAR_BITS == 32
#define ___UTILITY_SCHAR_MAX      0x7fffff
#define ___UTILITY_SCHAR_MIN      (-0x7fffff-1)
#define ___UTILITY_UCHAR_MAX      0xffffffU
#define ___UTILITY_UCHAR_MIN      0x000000U
#elif ___UTILITY_CHAR_BITS == 64
#define ___UTILITY_SCHAR_MAX      0x7fffffff
#define ___UTILITY_SCHAR_MIN      (-0x7fffffff-1)
#define ___UTILITY_UCHAR_MAX      0xffffffffU
#define ___UTILITY_UCHAR_MIN      0x00000000U
#else
#error chars setting use extra support, the value may be incorrect, please edit it to get the correct value directly.
#define ___UTILITY_SCHAR_MAX      utility::config::interger_type_value<signed char, unsigned char>::max_value()
#define ___UTILITY_SCHAR_MIN      utility::config::interger_type_value<signed char, unsigned char>::min_value()
#define ___UTILITY_UCHAR_MAX      utility::config::interger_type_value<signed char, unsigned char>::umax_value()
#define ___UTILITY_UCHAR_MIN      utility::config::interger_type_value<signed char, unsigned char>::umin_value()
#endif

// short settings
#if ___UTILITY_SHORT_BITS == 16
#define ___UTILITY_SHORT_MAX      0x7fff
#define ___UTILITY_SHORT_MIN      (-0x7fff-1)
#define ___UTILITY_USHORT_MAX     0xffffU
#define ___UTILITY_USHORT_MIN     0x0000U
#elif ___UTILITY_SHORT_BITS == 32
#define ___UTILITY_SHORT_MAX      0x7fffff
#define ___UTILITY_SHORT_MIN      (-0x7fffff-1)
#define ___UTILITY_USHORT_MAX     0xffffffU
#define ___UTILITY_USHORT_MIN     0x000000U
#elif ___UTILITY_SHORT_BITS == 64
#define ___UTILITY_SHORT_MAX      0x7fffffff
#define ___UTILITY_SHORT_MIN      (-0x7fffffff-1)
#define ___UTILITY_USHORT_MAX     0xffffffffU
#define ___UTILITY_USHORT_MIN     0x00000000U
#else
#error short setting use extra support, the value may be incorrect, please edit it to get the correct value directly.
#define ___UTILITY_SHORT_MAX      utility::config::interger_type_value<signed short, unsigned short>::max_value()
#define ___UTILITY_SHORT_MIN      utility::config::interger_type_value<signed short, unsigned short>::min_value()
#define ___UTILITY_USHORT_MAX     utility::config::interger_type_value<signed short, unsigned short>::umax_value()
#define ___UTILITY_USHORT_MIN     utility::config::interger_type_value<signed short, unsigned short>::umin_value()
#endif

// int settings
#if ___UTILITY_INT_BITS == 16
#define ___UTILITY_INT_MAX        0x7fff
#define ___UTILITY_INT_MIN        (-0x7fff-1)
#define ___UTILITY_UINT_MAX       0xffffU
#define ___UTILITY_UINT_MIN       0x0000U
#elif ___UTILITY_INT_BITS == 32
#define ___UTILITY_INT_MAX        0x7fffff
#define ___UTILITY_INT_MIN        (-0x7fffff-1)
#define ___UTILITY_UINT_MAX       0xffffffU
#define ___UTILITY_UINT_MIN       0x000000U
#elif ___UTILITY_INT_BITS == 64
#define ___UTILITY_INT_MAX        0x7fffffff
#define ___UTILITY_INT_MIN        (-0x7fffffff-1)
#define ___UTILITY_UINT_MAX       0xffffffffU
#define ___UTILITY_UINT_MIN       0x00000000U
#else
#error int setting use extra support, the value may be incorrect, please edit it to get the correct value directly.
#define ___UTILITY_INT_MAX        utility::config::interger_type_value<signed int, unsigned int>::max_value()
#define ___UTILITY_INT_MIN        utility::config::interger_type_value<signed int, unsigned int>::min_value()
#define ___UTILITY_UINT_MAX       utility::config::interger_type_value<signed int, unsigned int>::umax_value()
#define ___UTILITY_UINT_MIN       utility::config::interger_type_value<signed int, unsigned int>::umin_value()
#endif

// long settings
#if ___UTILITY_LONG_BITS == 32
#define ___UTILITY_LONG_MAX       0x7fffffL
#define ___UTILITY_LONG_MIN       (-0x7fffffL-1)
#define ___UTILITY_ULONG_MAX      0xffffffUL
#define ___UTILITY_ULONG_MIN      0x000000UL
#elif ___UTILITY_LONG_BITS == 64
#define ___UTILITY_LONG_MAX       0x7fffffffL
#define ___UTILITY_LONG_MIN       (-0x7fffffffL-1)
#define ___UTILITY_ULONG_MAX      0xffffffffUL
#define ___UTILITY_ULONG_MIN      0x00000000UL
#else
#error long setting use extra support, the value may be incorrect, please edit it to get the correct value directly.
#define ___UTILITY_LONG_MAX       utility::config::interger_type_value<signed long, unsigned long>::max_value()
#define ___UTILITY_LONG_MIN       utility::config::interger_type_value<signed long, unsigned long>::min_value()
#define ___UTILITY_ULONG_MAX      utility::config::interger_type_value<signed long, unsigned long>::umax_value()
#define ___UTILITY_ULONG_MIN      utility::config::interger_type_value<signed long, unsigned long>::umin_value()
#endif

// long long settings
#if ___UTILITY_LLONG_BITS == 64
#define ___UTILITY_LLONG_MAX      0x7fffffffLL
#define ___UTILITY_LLONG_MIN      (-0x7fffffffLL-1)
#define ___UTILITY_ULLONG_MAX     0xffffffffULL
#define ___UTILITY_ULLONG_MIN     0x00000000ULL
#elif ___UTILITY_LLONG_BITS == 128
#define ___UTILITY_LLONG_MAX      0x7fffffffffffffffLL
#define ___UTILITY_LLONG_MIN      (-0x7fffffffffffffffLL-1)
#define ___UTILITY_ULLONG_MAX     0xffffffffffffffffULL
#define ___UTILITY_ULLONG_MIN     0x0000000000000000ULL
#else
#error long long setting use extra support, the value may be incorrect, please edit it to get the correct value directly.
#define ___UTILITY_LLONG_MAX      utility::config::interger_type_value<signed long long, unsigned long long>::max_value()
#define ___UTILITY_LLONG_MIN      utility::config::interger_type_value<signed long long, unsigned long long>::min_value()
#define ___UTILITY_ULLONG_MAX     utility::config::interger_type_value<signed long long, unsigned long long>::umax_value()
#define ___UTILITY_ULLONG_MIN     utility::config::interger_type_value<signed long long, unsigned long long>::umin_value()
#endif

#if ___UTILITY_CHAR_SIGNED == 1
#define ___UTILITY_CHAR_MAX       ___UTILITY_SCHAR_MAX
#define ___UTILITY_CHAR_MIN       ___UTILITY_SCHAR_MIN
#else
#define ___UTILITY_CHAR_MAX       ___UTILITY_UCHAR_MAX
#define ___UTILITY_CHAR_MIN       ___UTILITY_UCHAR_MIN
#endif


#if ___UTILITY_CHAR_BITS == 8
#define ___UTILITY_INT8_T       signed char
#define ___UTILITY_UINT8_T      unsigned char
#define ___UTILITY_INT8_MAX     ___UTILITY_SCHAR_MAX
#define ___UTILITY_INT8_MIN     ___UTILITY_SCHAR_MIN
#define ___UTILITY_UINT8_MAX    ___UTILITY_UCHAR_MAX
#define ___UTILITY_UINT8_MIN    ___UTILITY_UCHAR_MIN
#define ___UTILITY_INT8_d      "hhd"
#define ___UTILITY_INT8_i      "hhi"
#define ___UTILITY_INT8_u      "hhu"
#define ___UTILITY_INT8_o      "hho"
#define ___UTILITY_INT8_x      "hhx"
#define ___UTILITY_INT8_X      "hhX"
#else
#error Unsupport 8 bit intergers ! please edit this to fix or disable.
#endif


#if ___UTILITY_SHORT_BITS == 16
#define ___UTILITY_INT16_T      signed short
#define ___UTILITY_UINT16_T     unsigned short
#define ___UTILITY_INT16_MAX    ___UTILITY_SHORT_MAX
#define ___UTILITY_INT16_MIN    ___UTILITY_SHORT_MIN
#define ___UTILITY_UINT16_MAX   ___UTILITY_USHORT_MAX
#define ___UTILITY_UINT16_MIN   ___UTILITY_USHORT_MIN
#define ___UTILITY_INT16_d      "hd"
#define ___UTILITY_INT16_i      "hi"
#define ___UTILITY_INT16_u      "hu"
#define ___UTILITY_INT16_o      "ho"
#define ___UTILITY_INT16_x      "hx"
#define ___UTILITY_INT16_X      "hX"
#elif ___UTILITY_INT_BITS == 16
#define ___UTILITY_INT16_T      signed int
#define ___UTILITY_UINT16_T     unsigned int
#define ___UTILITY_INT16_MAX    ___UTILITY_INT_MAX
#define ___UTILITY_INT16_MIN    ___UTILITY_INT_MIN
#define ___UTILITY_UINT16_MAX   ___UTILITY_UINT_MAX
#define ___UTILITY_UINT16_MIN   ___UTILITY_UINT_MIN
#define ___UTILITY_INT16_d      "d"
#define ___UTILITY_INT16_i      "i"
#define ___UTILITY_INT16_u      "u"
#define ___UTILITY_INT16_o      "o"
#define ___UTILITY_INT16_x      "x"
#define ___UTILITY_INT16_X      "X"
#else
#error Unsupport 16 bit intergers ! please edit this to fix or disable.
#endif


#if ___UTILITY_INT_BITS == 32
#define ___UTILITY_INT32_T      signed int
#define ___UTILITY_UINT32_T     unsigned int
#define ___UTILITY_INT32_MAX    ___UTILITY_INT_MAX
#define ___UTILITY_INT32_MIN    ___UTILITY_INT_MIN
#define ___UTILITY_UINT32_MAX   ___UTILITY_UINT_MAX
#define ___UTILITY_UINT32_MIN   ___UTILITY_UINT_MIN
#define ___UTILITY_INT32_d      "d"
#define ___UTILITY_INT32_i      "i"
#define ___UTILITY_INT32_u      "u"
#define ___UTILITY_INT32_o      "o"
#define ___UTILITY_INT32_x      "x"
#define ___UTILITY_INT32_X      "X"
#elif ___UTILITY_LONG_BITS == 32
#define ___UTILITY_INT32_T      signed long
#define ___UTILITY_UINT32_T     unsigned long
#define ___UTILITY_INT32_MAX    ___UTILITY_LONG_MAX
#define ___UTILITY_INT32_MIN    ___UTILITY_LONG_MIN
#define ___UTILITY_UINT32_MAX   ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT32_MIN   ___UTILITY_ULONG_MIN
#define ___UTILITY_INT32_d      "ld"
#define ___UTILITY_INT32_i      "li"
#define ___UTILITY_INT32_u      "lu"
#define ___UTILITY_INT32_o      "lo"
#define ___UTILITY_INT32_x      "lx"
#define ___UTILITY_INT32_X      "lX"
#else
#error Unsupport 32 bit intergers ! please edit this to fix or disable.
#endif

#if ___UTILITY_LONG_BITS == 64
#define ___UTILITY_INT64_T      signed long
#define ___UTILITY_UINT64_T     unsigned long
#define ___UTILITY_INT64_MAX    ___UTILITY_LONG_MAX
#define ___UTILITY_INT64_MIN    ___UTILITY_LONG_MIN
#define ___UTILITY_UINT64_MAX   ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT64_MIN   ___UTILITY_ULONG_MIN
#define ___UTILITY_INT64_d      "ld"
#define ___UTILITY_INT64_i      "li"
#define ___UTILITY_INT64_u      "lu"
#define ___UTILITY_INT64_o      "lo"
#define ___UTILITY_INT64_x      "lx"
#define ___UTILITY_INT64_X      "lX"
#elif ___UTILITY_LLONG_BITS == 64
#define ___UTILITY_INT64_T      signed long long
#define ___UTILITY_UINT64_T     unsigned long long
#define ___UTILITY_INT64_MAX    ___UTILITY_LLONG_MAX
#define ___UTILITY_INT64_MIN    ___UTILITY_LLONG_MIN
#define ___UTILITY_UINT64_MAX   ___UTILITY_ULLONG_MAX
#define ___UTILITY_UINT64_MIN   ___UTILITY_ULLONG_MIN
#define ___UTILITY_INT64_d      "lld"
#define ___UTILITY_INT64_i      "lli"
#define ___UTILITY_INT64_u      "llu"
#define ___UTILITY_INT64_o      "llo"
#define ___UTILITY_INT64_x      "llx"
#define ___UTILITY_INT64_X      "llX"
#else
#error Unsupport 64 bit intergers ! please edit this to fix or disable.
#endif

#define ___UTILITY_INTMAX_T     signed long long
#define ___UTILITY_UINTMAX_T    unsigned long long
#define ___UTILITY_INTMAX_MAX   ___UTILITY_LLONG_MAX
#define ___UTILITY_INTMAX_MIN   ___UTILITY_LLONG_MIN
#define ___UTILITY_UINTMAX_MAX  ___UTILITY_ULLONG_MAX
#define ___UTILITY_UINTMAX_MIN  ___UTILITY_ULLONG_MIN
#define ___UTILITY_INTMAX_d     "lld"
#define ___UTILITY_INTMAX_i     "lli"
#define ___UTILITY_INTMAX_u     "llu"
#define ___UTILITY_INTMAX_o     "llo"
#define ___UTILITY_INTMAX_x     "llx"
#define ___UTILITY_INTMAX_X     "llX"

#if ___UTILITY_CHAR_BITS >= 8
#define ___UTILITY_INT_LEAST8_T         signed char
#define ___UTILITY_UINT_LEAST8_T        unsigned char
#define ___UTILITY_INT_LEAST8_MAX       ___UTILITY_SCHAR_MAX
#define ___UTILITY_INT_LEAST8_MIN       ___UTILITY_SCHAR_MIN
#define ___UTILITY_UINT_LEAST8_MAX      ___UTILITY_UCHAR_MAX
#define ___UTILITY_UINT_LEAST8_MIN      ___UTILITY_UCHAR_MIN
#define ___UTILITY_INT_LEAST8_d         "hhd"
#define ___UTILITY_INT_LEAST8_i         "hhi"
#define ___UTILITY_INT_LEAST8_u         "hhu"
#define ___UTILITY_INT_LEAST8_o         "hho"
#define ___UTILITY_INT_LEAST8_x         "hhx"
#define ___UTILITY_INT_LEAST8_X         "hhX"
#else
#define ___UTILITY_INT_LEAST8_T         signed short
#define ___UTILITY_UINT_LEAST8_T        unsigned short
#define ___UTILITY_INT_LEAST8_MAX       ___UTILITY_SHORT_MAX
#define ___UTILITY_INT_LEAST8_MIN       ___UTILITY_SHORT_MIN
#define ___UTILITY_UINT_LEAST8_MAX      ___UTILITY_USHORT_MAX
#define ___UTILITY_UINT_LEAST8_MIN      ___UTILITY_USHORT_MIN
#define ___UTILITY_INT_LEAST8_d         "hd"
#define ___UTILITY_INT_LEAST8_i         "hi"
#define ___UTILITY_INT_LEAST8_u         "hu"
#define ___UTILITY_INT_LEAST8_o         "ho"
#define ___UTILITY_INT_LEAST8_x         "hx"
#define ___UTILITY_INT_LEAST8_X         "hX"
#endif

#define ___UTILITY_INT_LEAST16_T        signed short
#define ___UTILITY_UINT_LEAST16_T       unsigned short
#define ___UTILITY_INT_LEAST16_MAX      ___UTILITY_SHORT_MAX
#define ___UTILITY_INT_LEAST16_MIN      ___UTILITY_SHORT_MIN
#define ___UTILITY_UINT_LEAST16_MAX     ___UTILITY_USHORT_MAX
#define ___UTILITY_UINT_LEAST16_MIN     ___UTILITY_USHORT_MIN
#define ___UTILITY_INT_LEAST16_d        "hd"
#define ___UTILITY_INT_LEAST16_i        "hi"
#define ___UTILITY_INT_LEAST16_u        "hu"
#define ___UTILITY_INT_LEAST16_o        "ho"
#define ___UTILITY_INT_LEAST16_x        "hx"
#define ___UTILITY_INT_LEAST16_X        "hX"

#if ___UTILITY_INT_BITS >= 32
#define ___UTILITY_INT_LEAST32_T        signed int
#define ___UTILITY_UINT_LEAST32_T       unsigned int
#define ___UTILITY_INT_LEAST32_MAX      ___UTILITY_INT_MAX
#define ___UTILITY_INT_LEAST32_MIN      ___UTILITY_INT_MIN
#define ___UTILITY_UINT_LEAST32_MAX     ___UTILITY_UINT_MAX
#define ___UTILITY_UINT_LEAST32_MIN     ___UTILITY_UINT_MIN
#define ___UTILITY_INT_LEAST32_d        "d"
#define ___UTILITY_INT_LEAST32_i        "i"
#define ___UTILITY_INT_LEAST32_u        "u"
#define ___UTILITY_INT_LEAST32_o        "o"
#define ___UTILITY_INT_LEAST32_x        "x"
#define ___UTILITY_INT_LEAST32_X        "X"
#else
#define ___UTILITY_INT_LEAST32_T        signed long
#define ___UTILITY_UINT_LEAST32_T       unsigned long
#define ___UTILITY_INT_LEAST32_MAX      ___UTILITY_LONG_MAX
#define ___UTILITY_INT_LEAST32_MIN      ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_LEAST32_MAX     ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_LEAST32_MIN     ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_LEAST32_d        "ld"
#define ___UTILITY_INT_LEAST32_i        "li"
#define ___UTILITY_INT_LEAST32_u        "lu"
#define ___UTILITY_INT_LEAST32_o        "lo"
#define ___UTILITY_INT_LEAST32_x        "lx"
#define ___UTILITY_INT_LEAST32_X        "lX"
#endif

#if ___UTILITY_LONG_BITS >= 64
#define ___UTILITY_INT_LEAST64_T        signed long
#define ___UTILITY_UINT_LEAST64_T       unsigned long
#define ___UTILITY_INT_LEAST64_MAX      ___UTILITY_LONG_MAX
#define ___UTILITY_INT_LEAST64_MIN      ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_LEAST64_MAX     ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_LEAST64_MIN     ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_LEAST64_d        "ld"
#define ___UTILITY_INT_LEAST64_i        "li"
#define ___UTILITY_INT_LEAST64_u        "lu"
#define ___UTILITY_INT_LEAST64_o        "lo"
#define ___UTILITY_INT_LEAST64_x        "lx"
#define ___UTILITY_INT_LEAST64_X        "lX"
#else
#define ___UTILITY_INT_LEAST64_T        signed long long
#define ___UTILITY_UINT_LEAST64_T       unsigned long long
#define ___UTILITY_INT_LEAST64_MAX      ___UTILITY_LLONG_MAX
#define ___UTILITY_INT_LEAST64_MIN      ___UTILITY_LLONG_MIN
#define ___UTILITY_UINT_LEAST64_MAX     ___UTILITY_ULLONG_MAX
#define ___UTILITY_UINT_LEAST64_MIN     ___UTILITY_ULLONG_MIN
#define ___UTILITY_INT_LEAST64_d        "lld"
#define ___UTILITY_INT_LEAST64_i        "lli"
#define ___UTILITY_INT_LEAST64_u        "llu"
#define ___UTILITY_INT_LEAST64_o        "llo"
#define ___UTILITY_INT_LEAST64_x        "llx"
#define ___UTILITY_INT_LEAST64_X        "llX"
#endif

#if ___UTILITY_SYSTEM_BITS == 64
#define ___UTILITY_INT_FAST8_T          signed long
#define ___UTILITY_UINT_FAST8_T         unsigned long
#define ___UTILITY_INT_FAST8_MAX        ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST8_MIN        ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST8_MAX       ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST8_MIN       ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST8_d          "ld"
#define ___UTILITY_INT_FAST8_i          "li"
#define ___UTILITY_INT_FAST8_u          "lu"
#define ___UTILITY_INT_FAST8_o          "lo"
#define ___UTILITY_INT_FAST8_x          "lx"
#define ___UTILITY_INT_FAST8_X          "lX"

#define ___UTILITY_INT_FAST16_T         signed long
#define ___UTILITY_UINT_FAST16_T        unsigned long
#define ___UTILITY_INT_FAST16_MAX       ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST16_MIN       ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST16_MAX      ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST16_MIN      ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST16_d         "ld"
#define ___UTILITY_INT_FAST16_i         "li"
#define ___UTILITY_INT_FAST16_u         "lu"
#define ___UTILITY_INT_FAST16_o         "lo"
#define ___UTILITY_INT_FAST16_x         "lx"
#define ___UTILITY_INT_FAST16_X         "lX"

#define ___UTILITY_INT_FAST32_T         signed long
#define ___UTILITY_UINT_FAST32_T        unsigned long
#define ___UTILITY_INT_FAST32_MAX       ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST32_MIN       ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST32_MAX      ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST32_MIN      ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST32_d         "ld"
#define ___UTILITY_INT_FAST32_i         "li"
#define ___UTILITY_INT_FAST32_u         "lu"
#define ___UTILITY_INT_FAST32_o         "lo"
#define ___UTILITY_INT_FAST32_x         "lx"
#define ___UTILITY_INT_FAST32_X         "lX"

#if ___UTILITY_LONG_BITS >= 64
#define ___UTILITY_INT_FAST64_T         signed long
#define ___UTILITY_UINT_FAST64_T        unsigned long
#define ___UTILITY_INT_FAST64_MAX       ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST64_MIN       ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST64_MAX      ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST64_MIN      ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST64_d         "ld"
#define ___UTILITY_INT_FAST64_i         "li"
#define ___UTILITY_INT_FAST64_u         "lu"
#define ___UTILITY_INT_FAST64_o         "lo"
#define ___UTILITY_INT_FAST64_x         "lx"
#define ___UTILITY_INT_FAST64_X         "lX"
#else
#define ___UTILITY_INT_FAST64_T         signed long long
#define ___UTILITY_UINT_FAST64_T        unsigned long long
#define ___UTILITY_INT_FAST64_MAX       ___UTILITY_LLONG_MAX
#define ___UTILITY_INT_FAST64_MIN       ___UTILITY_LLONG_MIN
#define ___UTILITY_UINT_FAST64_MAX      ___UTILITY_ULLONG_MAX
#define ___UTILITY_UINT_FAST64_MIN      ___UTILITY_ULLONG_MIN
#define ___UTILITY_INT_FAST64_d         "lld"
#define ___UTILITY_INT_FAST64_i         "lli"
#define ___UTILITY_INT_FAST64_u         "llu"
#define ___UTILITY_INT_FAST64_o         "llo"
#define ___UTILITY_INT_FAST64_x         "llx"
#define ___UTILITY_INT_FAST64_X         "llX"
#endif

#else

#define ___UTILITY_INT_FAST8_T          signed int
#define ___UTILITY_UINT_FAST8_T         unsigned int
#define ___UTILITY_INT_FAST8_MAX        ___UTILITY_INT_MAX
#define ___UTILITY_INT_FAST8_MIN        ___UTILITY_INT_MIN
#define ___UTILITY_UINT_FAST8_MAX       ___UTILITY_UINT_MAX
#define ___UTILITY_UINT_FAST8_MIN       ___UTILITY_UINT_MIN
#define ___UTILITY_INT_FAST8_d          "d"
#define ___UTILITY_INT_FAST8_i          "i"
#define ___UTILITY_INT_FAST8_u          "u"
#define ___UTILITY_INT_FAST8_o          "o"
#define ___UTILITY_INT_FAST8_x          "x"
#define ___UTILITY_INT_FAST8_X          "X"

#define ___UTILITY_INT_FAST16_T         signed int
#define ___UTILITY_UINT_FAST16_T        unsigned int
#define ___UTILITY_INT_FAST16_MAX       ___UTILITY_INT_MAX
#define ___UTILITY_INT_FAST16_MIN       ___UTILITY_INT_MIN
#define ___UTILITY_UINT_FAST16_MAX      ___UTILITY_UINT_MAX
#define ___UTILITY_UINT_FAST16_MIN      ___UTILITY_UINT_MIN
#define ___UTILITY_INT_FAST16_d         "d"
#define ___UTILITY_INT_FAST16_i         "i"
#define ___UTILITY_INT_FAST16_u         "u"
#define ___UTILITY_INT_FAST16_o         "o"
#define ___UTILITY_INT_FAST16_x         "x"
#define ___UTILITY_INT_FAST16_X         "X"

#if ___UTILITY_INT_BITS >= 32
#define ___UTILITY_INT_FAST32_T         signed int
#define ___UTILITY_UINT_FAST32_T        unsigned int
#define ___UTILITY_INT_FAST32_MAX       ___UTILITY_INT_MAX
#define ___UTILITY_INT_FAST32_MIN       ___UTILITY_INT_MIN
#define ___UTILITY_UINT_FAST32_MAX      ___UTILITY_UINT_MAX
#define ___UTILITY_UINT_FAST32_MIN      ___UTILITY_UINT_MIN
#define ___UTILITY_INT_FAST32_d         "d"
#define ___UTILITY_INT_FAST32_i         "i"
#define ___UTILITY_INT_FAST32_u         "u"
#define ___UTILITY_INT_FAST32_o         "o"
#define ___UTILITY_INT_FAST32_x         "x"
#define ___UTILITY_INT_FAST32_X         "X"
#else
#define ___UTILITY_INT_FAST32_T         signed long
#define ___UTILITY_UINT_FAST32_T        unsigned long
#define ___UTILITY_INT_FAST32_MAX       ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST32_MIN       ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST32_MAX      ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST32_MIN      ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST32_d         "ld"
#define ___UTILITY_INT_FAST32_i         "li"
#define ___UTILITY_INT_FAST32_u         "lu"
#define ___UTILITY_INT_FAST32_o         "lo"
#define ___UTILITY_INT_FAST32_x         "lx"
#define ___UTILITY_INT_FAST32_X         "lX"
#endif

#if ___UTILITY_LONG_BITS >= 64
#define ___UTILITY_INT_FAST64_T         signed long
#define ___UTILITY_UINT_FAST64_T        unsigned long
#define ___UTILITY_INT_FAST64_MAX       ___UTILITY_LONG_MAX
#define ___UTILITY_INT_FAST64_MIN       ___UTILITY_LONG_MIN
#define ___UTILITY_UINT_FAST64_MAX      ___UTILITY_ULONG_MAX
#define ___UTILITY_UINT_FAST64_MIN      ___UTILITY_ULONG_MIN
#define ___UTILITY_INT_FAST64_d         "ld"
#define ___UTILITY_INT_FAST64_i         "li"
#define ___UTILITY_INT_FAST64_u         "lu"
#define ___UTILITY_INT_FAST64_o         "lo"
#define ___UTILITY_INT_FAST64_x         "lx"
#define ___UTILITY_INT_FAST64_X         "lX"
#else
#define ___UTILITY_INT_FAST64_T         signed long long
#define ___UTILITY_UINT_FAST64_T        unsigned long long
#define ___UTILITY_INT_FAST64_MAX       ___UTILITY_LLONG_MAX
#define ___UTILITY_INT_FAST64_MIN       ___UTILITY_LLONG_MIN
#define ___UTILITY_UINT_FAST64_MAX      ___UTILITY_ULLONG_MAX
#define ___UTILITY_UINT_FAST64_MIN      ___UTILITY_ULLONG_MIN
#define ___UTILITY_INT_FAST64_d         "lld"
#define ___UTILITY_INT_FAST64_i         "lli"
#define ___UTILITY_INT_FAST64_u         "llu"
#define ___UTILITY_INT_FAST64_o         "llo"
#define ___UTILITY_INT_FAST64_x         "llx"
#define ___UTILITY_INT_FAST64_X         "llX"
#endif
#endif

// TODO: ptrdiff_t size_t;

#endif // ! ___UTILITY__CONFIG__TYPES__PREDEFINED___
