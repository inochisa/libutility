
#ifndef __UTILITY_CRYPTO_MD5__
#define __UTILITY_CRYPTO_MD5__

#include<utility/config/utility_config.hpp>
#include<utility/sstd/cstring.hpp>

#define __F(x, y, z) ((x & y) | (~x & z))
#define __G(x, y, z) ((x & z) | (y & ~z))
#define __H(x, y, z) (x ^ y ^ z)
#define __I(x, y, z) (y ^ ( x | ~z))
#define __LEFTROTATE(x, c) ((x << c) | (x >> (32-c)))

#define __R1(a, b, c, d, m, k, s) \
  { a += __F(b, c, d) + m + k ; a &= 0xffffffffUL; \
    a = b + __LEFTROTATE(a, s); a &= 0xffffffffUL;}
#define __R2(a, b, c, d, m, k, s) \
  { a += __G(b, c, d) + m + k ; a &= 0xffffffffUL; \
    a = b + __LEFTROTATE(a, s); a &= 0xffffffffUL;}
#define __R3(a, b, c, d, m, k, s) \
  { a += __H(b, c, d) + m + k ; a &= 0xffffffffUL; \
    a = b + __LEFTROTATE(a, s); a &= 0xffffffffUL;}
#define __R4(a, b, c, d, m, k, s) \
  { a += __I(b, c, d) + m + k ; a &= 0xffffffffUL; \
    a = b + __LEFTROTATE(a, s); a &= 0xffffffffUL;}

namespace utility
{
  namespace crypto
  {
    struct md5_block
    {
      unsigned char data[64];
      unsigned long hash[4];
      unsigned long dlength;
      unsigned long long bits;
    };
    namespace detail
    {
      void __md5_block_transform(md5_block& __block)
      {
        unsigned long __a, __b, __c, __d;
        unsigned long __data[16];

        for(unsigned int __i = 0, __j = 0; __i < 16; ++__i, __j+=4)
        {
          __data[__i] =
            __block.data[__j] +
            (__block.data[__j+1] << 8UL) +
            (__block.data[__j+2] << 16UL) +
            (__block.data[__j+3] << 24UL);
          __data[__i] &= 0xffffffffUL;
        }

        __a = __block.hash[0];
        __b = __block.hash[1];
        __c = __block.hash[2];
        __d = __block.hash[3];

        __R1(__a, __b, __c, __d,  __data[0], 0xd76aa478U,   7);
        __R1(__d, __a, __b, __c,  __data[1], 0xe8c7b756U,  12);
        __R1(__c, __d, __a, __b,  __data[2], 0x242070dbU,  17);
        __R1(__b, __c, __d, __a,  __data[3], 0xc1bdceeeU,  22);
        __R1(__a, __b, __c, __d,  __data[4], 0xf57c0fafU,   7);
        __R1(__d, __a, __b, __c,  __data[5], 0x4787c62aU,  12);
        __R1(__c, __d, __a, __b,  __data[6], 0xa8304613U,  17);
        __R1(__b, __c, __d, __a,  __data[7], 0xfd469501U,  22);
        __R1(__a, __b, __c, __d,  __data[8], 0x698098d8U,   7);
        __R1(__d, __a, __b, __c,  __data[9], 0x8b44f7afU,  12);
        __R1(__c, __d, __a, __b, __data[10], 0xffff5bb1U,  17);
        __R1(__b, __c, __d, __a, __data[11], 0x895cd7beU,  22);
        __R1(__a, __b, __c, __d, __data[12], 0x6b901122U,   7);
        __R1(__d, __a, __b, __c, __data[13], 0xfd987193U,  12);
        __R1(__c, __d, __a, __b, __data[14], 0xa679438eU,  17);
        __R1(__b, __c, __d, __a, __data[15], 0x49b40821U,  22);

        __R2(__a, __b, __c, __d,  __data[1], 0xf61e2562U,   5);
        __R2(__d, __a, __b, __c,  __data[6], 0xc040b340U,   9);
        __R2(__c, __d, __a, __b, __data[11], 0x265e5a51U,  14);
        __R2(__b, __c, __d, __a,  __data[0], 0xe9b6c7aaU,  20);
        __R2(__a, __b, __c, __d,  __data[5], 0xd62f105dU,   5);
        __R2(__d, __a, __b, __c, __data[10], 0x02441453U,   9);
        __R2(__c, __d, __a, __b, __data[15], 0xd8a1e681U,  14);
        __R2(__b, __c, __d, __a,  __data[4], 0xe7d3fbc8U,  20);
        __R2(__a, __b, __c, __d,  __data[9], 0x21e1cde6U,   5);
        __R2(__d, __a, __b, __c, __data[14], 0xc33707d6U,   9);
        __R2(__c, __d, __a, __b,  __data[3], 0xf4d50d87U,  14);
        __R2(__b, __c, __d, __a,  __data[8], 0x455a14edU,  20);
        __R2(__a, __b, __c, __d, __data[13], 0xa9e3e905U,   5);
        __R2(__d, __a, __b, __c,  __data[2], 0xfcefa3f8U,   9);
        __R2(__c, __d, __a, __b,  __data[7], 0x676f02d9U,  14);
        __R2(__b, __c, __d, __a, __data[12], 0x8d2a4c8aU,  20);

        __R3(__a, __b, __c, __d,  __data[5], 0xfffa3942U,   4);
        __R3(__d, __a, __b, __c,  __data[8], 0x8771f681U,  11);
        __R3(__c, __d, __a, __b, __data[11], 0x6d9d6122U,  16);
        __R3(__b, __c, __d, __a, __data[14], 0xfde5380cU,  23);
        __R3(__a, __b, __c, __d,  __data[1], 0xa4beea44U,   4);
        __R3(__d, __a, __b, __c,  __data[4], 0x4bdecfa9U,  11);
        __R3(__c, __d, __a, __b,  __data[7], 0xf6bb4b60U,  16);
        __R3(__b, __c, __d, __a, __data[10], 0xbebfbc70U,  23);
        __R3(__a, __b, __c, __d, __data[13], 0x289b7ec6U,   4);
        __R3(__d, __a, __b, __c,  __data[0], 0xeaa127faU,  11);
        __R3(__c, __d, __a, __b,  __data[3], 0xd4ef3085U,  16);
        __R3(__b, __c, __d, __a,  __data[6], 0x04881d05U,  23);
        __R3(__a, __b, __c, __d,  __data[9], 0xd9d4d039U,   4);
        __R3(__d, __a, __b, __c, __data[12], 0xe6db99e5U,  11);
        __R3(__c, __d, __a, __b, __data[15], 0x1fa27cf8U,  16);
        __R3(__b, __c, __d, __a,  __data[2], 0xc4ac5665U,  23);

        __R4(__a, __b, __c, __d,  __data[0], 0xf4292244U,   6);
        __R4(__d, __a, __b, __c,  __data[7], 0x432aff97U,  10);
        __R4(__c, __d, __a, __b, __data[14], 0xab9423a7U,  15);
        __R4(__b, __c, __d, __a,  __data[5], 0xfc93a039U,  21);
        __R4(__a, __b, __c, __d, __data[12], 0x655b59c3U,   6);
        __R4(__d, __a, __b, __c,  __data[3], 0x8f0ccc92U,  10);
        __R4(__c, __d, __a, __b, __data[10], 0xffeff47dU,  15);
        __R4(__b, __c, __d, __a,  __data[1], 0x85845dd1U,  21);
        __R4(__a, __b, __c, __d,  __data[8], 0x6fa87e4fU,   6);
        __R4(__d, __a, __b, __c, __data[15], 0xfe2ce6e0U,  10);
        __R4(__c, __d, __a, __b,  __data[6], 0xa3014314U,  15);
        __R4(__b, __c, __d, __a, __data[13], 0x4e0811a1U,  21);
        __R4(__a, __b, __c, __d,  __data[4], 0xf7537e82U,   6);
        __R4(__d, __a, __b, __c, __data[11], 0xbd3af235U,  10);
        __R4(__c, __d, __a, __b,  __data[2], 0x2ad7d2bbU,  15);
        __R4(__b, __c, __d, __a,  __data[9], 0xeb86d391U,  21);

        __block.hash[0] += __a;
        __block.hash[1] += __b;
        __block.hash[2] += __c;
        __block.hash[3] += __d;
      }

      void __md5_last_block(md5_block& __block)
      {
        __block.bits += __block.dlength * 8ULL;

        if(__block.dlength > 55UL)
        {
          __block.data[__block.dlength++] = 0x80U;
          while(__block.dlength < 64UL)
          { __block.data[__block.dlength++] = 0x00U;}
          __md5_block_transform(__block);
          for(unsigned int __i = 0; __i < 56UL; ++__i)
          { __block.data[__i] = 0x00U;}
        }

        if(__block.dlength < 56UL)
        {
          __block.data[__block.dlength++] = 0x80U;
          while(__block.dlength < 56UL)
          { __block.data[__block.dlength++] = 0X00U;}
        }

        __block.data[56] = (__block.bits & 0xffU);
        __block.data[57] = ((__block.bits >>  8U) & 0xffU);
        __block.data[58] = ((__block.bits >> 16U) & 0xffU);
        __block.data[59] = ((__block.bits >> 24U) & 0xffU);
        __block.data[60] = ((__block.bits >> 32U) & 0xffU);
        __block.data[61] = ((__block.bits >> 40U) & 0xffU);
        __block.data[62] = ((__block.bits >> 48U) & 0xffU);
        __block.data[63] = ((__block.bits >> 56U) & 0xffU);

        __md5_block_transform(__block);
      }
    }
    void md5(
      unsigned char __res[16],
      const void* __mem, ::utility::size_t __len
    )
    {
      md5_block __block;
      __block.dlength = __block.bits = 0U;
      __block.hash[0] = 0x67452301UL;
      __block.hash[1] = 0xEFCDAB89UL;
      __block.hash[2] = 0x98BADCFEUL;
      __block.hash[3] = 0x10325476UL;
      ::utility::size_t __i;
      const unsigned char* __ptr =
        static_cast<const unsigned char*>(__mem);
      for(__i = 0; __i < __len; ++__i)
      {
        __block.data[__block.dlength++] = __ptr[__i];
        if(__block.dlength == 64U)
        {
          detail::__md5_block_transform(__block);
          __block.bits += 512U;
          __block.dlength = 0;
        }
      }
      detail::__md5_last_block(__block);

      __res[0] =  __block.hash[0] & 0xffU;
      __res[1] =  (__block.hash[0] >> 8) & 0xffU;
      __res[2] =  (__block.hash[0] >> 16) & 0xffU;
      __res[3] =  (__block.hash[0] >> 24) & 0xffU;
      __res[4] =  __block.hash[1] & 0xffU;
      __res[5] =  (__block.hash[1] >> 8) & 0xffU;
      __res[6] =  (__block.hash[1] >> 16) & 0xffU;
      __res[7] =  (__block.hash[1] >> 24) & 0xffU;
      __res[8] =  __block.hash[2] & 0xffU;
      __res[9] =  (__block.hash[2] >> 8) & 0xffU;
      __res[10] = (__block.hash[2] >> 16) & 0xffU;
      __res[11] = (__block.hash[2] >> 24) & 0xffU;
      __res[12] = __block.hash[3] & 0xffU;
      __res[13] = (__block.hash[3] >> 8) & 0xffU;
      __res[14] = (__block.hash[3] >> 16) & 0xffU;
      __res[15] = (__block.hash[3] >> 24) & 0xffU;
    }
  }
}

#undef __F
#undef __G
#undef __H
#undef __I
#undef __LEFTROTATE
#undef __R1
#undef __R2
#undef __R3
#undef __R4

#endif // ! __UTILITY_CRYPTO_MD5__

/*
 * md5 table
 *
  static unsigned int rec [] =
  {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
  };

  void run()
  {
    using std::floor;
    using std::abs;
    using std::sin;
    using std::printf;

    for(unsigned int i = 0; i < 64; ++i)
    {
      unsigned int x;
      if(i < 16)
      { x = i;}
      else if(i < 32)
      { x = (5U*i+1U)%0x10U;}
      else if(i < 48)
      { x = (3U*i+5U)%0x10U;}
      else if(i < 64)
      { x = (7U*i)%0x10U;}
      unsigned long long tmp =
        static_cast<unsigned long long>(floor((1ULL << 32) * abs(sin(i+1))));
      tmp &= 0xffffffffUL;
      printf("%2u  %2u  0x%08llx\n", x, rec[i], tmp);
    }
  }

  void printmd5()
  {
    using std::scanf;
    using std::printf;
    using ::utility::algorithm::rotate;

    char str[20];
    char need[4] = {'a', 'b', 'c', 'd'};
    unsigned int x, y;
    for(unsigned int i = 0; i < 16; ++i)
    {
      scanf("%u%u%s", &x, &y, str);
      printf("        ");
      printf("__R1(__%c, __%c, __%c, __%c, %s__data[%u], %sU, %3u);\n",
        need[0], need[1], need[2], need[3], x < 10U ? " " : "", x, str, y);
      rotate(need, need+3, need+4);
    }
    printf("\n");
    for(unsigned int i = 0; i < 16; ++i)
    {
      scanf("%u%u%s", &x, &y, str);
      printf("        ");
      printf("__R2(__%c, __%c, __%c, __%c, %s__data[%u], %sU, %3u);\n",
        need[0], need[1], need[2], need[3], x < 10U ? " " : "", x, str, y);
      rotate(need, need+3, need+4);
    }
    printf("\n");
    for(unsigned int i = 0; i < 16; ++i)
    {
      scanf("%u%u%s", &x, &y, str);
      printf("        ");
      printf("__R3(__%c, __%c, __%c, __%c, %s__data[%u], %sU, %3u);\n",
        need[0], need[1], need[2], need[3], x < 10U ? " " : "", x, str, y);
        rotate(need, need+3, need+4);
    }
    printf("\n");
    for(unsigned int i = 0; i < 16; ++i)
    {
      scanf("%u%u%s", &x, &y, str);
      printf("        ");
      printf("__R4(__%c, __%c, __%c, __%c, %s__data[%u], %sU, %3u);\n",
        need[0], need[1], need[2], need[3], x < 10U ? " " : "", x, str, y);
      rotate(need, need+3, need+4);
    }
    printf("\n");
  }
*/
/*
 * specal md5 value
 * "" = d41d8cd98f00b204e9800998ecf8427e
 * "The quick brown fox jumps over the lazy dog" = 9e107d9d372bb6826bd81d3542a419d6
 */
