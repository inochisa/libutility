
#ifndef __UTILITY_CRYPTO_SHA1__
#define __UTILITY_CRYPTO_SHA1__

#include<utility/config/utility_config.hpp>
#include<utility/crypto/impl/crypto_block.hpp>

#define ___I1(x, y, z) ((x & y) | ((~x) & z))
#define ___I2(x, y, z) (x ^ y ^ z)
#define ___I3(x, y, z) ((x & y) | (x & z) | (y & z))
#define ___LEFTROTATE(x, c) ((x << c) | (x >> (32-c)))

#define ___R1(a, b, c, d, e, m) \
  { e += ___I1(b, c, d) + m + 0x5a827999 + ___LEFTROTATE(a, 5); \
    e &= 0xffffffffUL; b = ___LEFTROTATE(b, 30); b &= 0xffffffffUL;}
#define ___R2(a, b, c, d, e, m) \
  { e += ___I2(b, c, d) + m + 0x6ed9eba1 + ___LEFTROTATE(a, 5); \
    e &= 0xffffffffUL; b = ___LEFTROTATE(b, 30); b &= 0xffffffffUL;}
#define ___R3(a, b, c, d, e, m) \
  { e += ___I3(b, c, d) + m + 0x8f1bbcdc + ___LEFTROTATE(a, 5); \
    e &= 0xffffffffUL; b = ___LEFTROTATE(b, 30); b &= 0xffffffffUL;}
#define ___R4(a, b, c, d, e, m) \
  { e += ___I2(b, c, d) + m + 0xca62c1d6 + ___LEFTROTATE(a, 5); \
    e &= 0xffffffffUL; b = ___LEFTROTATE(b, 30); b &= 0xffffffffUL;}

namespace utility
{
  namespace crypto
  {
    namespace detail
    {
      typedef __crypto_block<64, 5> sha1_block;

      void sha1_block_init(sha1_block& __block) noexcept
      {
        __block.bits = 0;
        __block.dlength = 0;
        __block.hash[0] = 0x67452301;
        __block.hash[1] = 0xEFCDAB89;
        __block.hash[2] = 0x98BADCFE;
        __block.hash[3] = 0x10325476;
        __block.hash[4] = 0xc3d2e1f0;

        return;
      }

      void sha1_block_transform(sha1_block& __block) noexcept
      {
        unsigned long __a, __b, __c, __d, __e;
        unsigned long __data[80];

        for(unsigned int __i = 0, __j = 0; __i < 16; ++__i, __j+=4)
        {
          __data[__i] =
            (  __block.data[__j] << 24UL) +
            (__block.data[__j+1] << 16UL) +
            (__block.data[__j+2] << 8UL) +
            (__block.data[__j+3]);
          __data[__i] &= 0xffffffffUL;
        }
        for(unsigned int __i = 16; __i != 80; ++__i)
        {
          __data[__i] = __data[__i-3] ^ __data[__i-8] ^
                        __data[__i-14] ^ __data[__i-16];
          __data[__i] = (__data[__i] << 1) | (__data[__i] >> 31);
          __data[__i] &= 0xffffffffUL;
        }

        __a = __block.hash[0];
        __b = __block.hash[1];
        __c = __block.hash[2];
        __d = __block.hash[3];
        __e = __block.hash[4];

        ___R1(__a, __b, __c, __d, __e,  __data[0]);
        ___R1(__e, __a, __b, __c, __d,  __data[1]);
        ___R1(__d, __e, __a, __b, __c,  __data[2]);
        ___R1(__c, __d, __e, __a, __b,  __data[3]);
        ___R1(__b, __c, __d, __e, __a,  __data[4]);
        ___R1(__a, __b, __c, __d, __e,  __data[5]);
        ___R1(__e, __a, __b, __c, __d,  __data[6]);
        ___R1(__d, __e, __a, __b, __c,  __data[7]);
        ___R1(__c, __d, __e, __a, __b,  __data[8]);
        ___R1(__b, __c, __d, __e, __a,  __data[9]);
        ___R1(__a, __b, __c, __d, __e, __data[10]);
        ___R1(__e, __a, __b, __c, __d, __data[11]);
        ___R1(__d, __e, __a, __b, __c, __data[12]);
        ___R1(__c, __d, __e, __a, __b, __data[13]);
        ___R1(__b, __c, __d, __e, __a, __data[14]);
        ___R1(__a, __b, __c, __d, __e, __data[15]);
        ___R1(__e, __a, __b, __c, __d, __data[16]);
        ___R1(__d, __e, __a, __b, __c, __data[17]);
        ___R1(__c, __d, __e, __a, __b, __data[18]);
        ___R1(__b, __c, __d, __e, __a, __data[19]);

        ___R2(__a, __b, __c, __d, __e, __data[20]);
        ___R2(__e, __a, __b, __c, __d, __data[21]);
        ___R2(__d, __e, __a, __b, __c, __data[22]);
        ___R2(__c, __d, __e, __a, __b, __data[23]);
        ___R2(__b, __c, __d, __e, __a, __data[24]);
        ___R2(__a, __b, __c, __d, __e, __data[25]);
        ___R2(__e, __a, __b, __c, __d, __data[26]);
        ___R2(__d, __e, __a, __b, __c, __data[27]);
        ___R2(__c, __d, __e, __a, __b, __data[28]);
        ___R2(__b, __c, __d, __e, __a, __data[29]);
        ___R2(__a, __b, __c, __d, __e, __data[30]);
        ___R2(__e, __a, __b, __c, __d, __data[31]);
        ___R2(__d, __e, __a, __b, __c, __data[32]);
        ___R2(__c, __d, __e, __a, __b, __data[33]);
        ___R2(__b, __c, __d, __e, __a, __data[34]);
        ___R2(__a, __b, __c, __d, __e, __data[35]);
        ___R2(__e, __a, __b, __c, __d, __data[36]);
        ___R2(__d, __e, __a, __b, __c, __data[37]);
        ___R2(__c, __d, __e, __a, __b, __data[38]);
        ___R2(__b, __c, __d, __e, __a, __data[39]);

        ___R3(__a, __b, __c, __d, __e, __data[40]);
        ___R3(__e, __a, __b, __c, __d, __data[41]);
        ___R3(__d, __e, __a, __b, __c, __data[42]);
        ___R3(__c, __d, __e, __a, __b, __data[43]);
        ___R3(__b, __c, __d, __e, __a, __data[44]);
        ___R3(__a, __b, __c, __d, __e, __data[45]);
        ___R3(__e, __a, __b, __c, __d, __data[46]);
        ___R3(__d, __e, __a, __b, __c, __data[47]);
        ___R3(__c, __d, __e, __a, __b, __data[48]);
        ___R3(__b, __c, __d, __e, __a, __data[49]);
        ___R3(__a, __b, __c, __d, __e, __data[50]);
        ___R3(__e, __a, __b, __c, __d, __data[51]);
        ___R3(__d, __e, __a, __b, __c, __data[52]);
        ___R3(__c, __d, __e, __a, __b, __data[53]);
        ___R3(__b, __c, __d, __e, __a, __data[54]);
        ___R3(__a, __b, __c, __d, __e, __data[55]);
        ___R3(__e, __a, __b, __c, __d, __data[56]);
        ___R3(__d, __e, __a, __b, __c, __data[57]);
        ___R3(__c, __d, __e, __a, __b, __data[58]);
        ___R3(__b, __c, __d, __e, __a, __data[59]);

        ___R4(__a, __b, __c, __d, __e, __data[60]);
        ___R4(__e, __a, __b, __c, __d, __data[61]);
        ___R4(__d, __e, __a, __b, __c, __data[62]);
        ___R4(__c, __d, __e, __a, __b, __data[63]);
        ___R4(__b, __c, __d, __e, __a, __data[64]);
        ___R4(__a, __b, __c, __d, __e, __data[65]);
        ___R4(__e, __a, __b, __c, __d, __data[66]);
        ___R4(__d, __e, __a, __b, __c, __data[67]);
        ___R4(__c, __d, __e, __a, __b, __data[68]);
        ___R4(__b, __c, __d, __e, __a, __data[69]);
        ___R4(__a, __b, __c, __d, __e, __data[70]);
        ___R4(__e, __a, __b, __c, __d, __data[71]);
        ___R4(__d, __e, __a, __b, __c, __data[72]);
        ___R4(__c, __d, __e, __a, __b, __data[73]);
        ___R4(__b, __c, __d, __e, __a, __data[74]);
        ___R4(__a, __b, __c, __d, __e, __data[75]);
        ___R4(__e, __a, __b, __c, __d, __data[76]);
        ___R4(__d, __e, __a, __b, __c, __data[77]);
        ___R4(__c, __d, __e, __a, __b, __data[78]);
        ___R4(__b, __c, __d, __e, __a, __data[79]);

        // append the block hashes;
        __block.hash[0] += __a;
        __block.hash[1] += __b;
        __block.hash[2] += __c;
        __block.hash[3] += __d;
        __block.hash[4] += __e;

        __block.hash[0] &= 0xffffffffUL;
        __block.hash[1] &= 0xffffffffUL;
        __block.hash[2] &= 0xffffffffUL;
        __block.hash[3] &= 0xffffffffUL;
        __block.hash[4] &= 0xffffffffUL;

        // init the block data;
        __block.bits += 512U;
        __block.dlength = 0;

        return;
      }

      static void sha1_last_block(sha1_block& __block) noexcept
      {
        __block.bits += __block.dlength * 8ULL;

        if(__block.dlength > 55UL)
        {
          __block.data[__block.dlength++] = 0x80U;
          while(__block.dlength < 64UL)
          { __block.data[__block.dlength++] = 0x00U;}
          sha1_block_transform(__block);
          for(unsigned int __i = 0; __i < 56UL; ++__i)
          { __block.data[__i] = 0x00U;}
        }
        else
        {
          __block.data[__block.dlength++] = 0x80U;
          while(__block.dlength < 56UL)
          { __block.data[__block.dlength++] = 0X00U;}
        }

        __block.data[56] = ((__block.bits >> 56U) & 0xffU);
        __block.data[57] = ((__block.bits >> 48U) & 0xffU);
        __block.data[58] = ((__block.bits >> 40U) & 0xffU);
        __block.data[59] = ((__block.bits >> 32U) & 0xffU);
        __block.data[60] = ((__block.bits >> 24U) & 0xffU);
        __block.data[61] = ((__block.bits >> 16U) & 0xffU);
        __block.data[62] = ((__block.bits >>  8U) & 0xffU);
        __block.data[63] = ((__block.bits       ) & 0xffU);

        sha1_block_transform(__block);

        return;
      }

      static inline void sha1_result_transform(
        unsigned char __res[20], sha1_block& __block
      ) noexcept
      {
        __res[0]  =  (__block.hash[0] >> 24) & 0xffU;
        __res[1]  =  (__block.hash[0] >> 16) & 0xffU;
        __res[2]  =  (__block.hash[0] >> 8 ) & 0xffU;
        __res[3]  =  (__block.hash[0]      ) & 0xffU;
        __res[4]  =  (__block.hash[1] >> 24) & 0xffU;
        __res[5]  =  (__block.hash[1] >> 16) & 0xffU;
        __res[6]  =  (__block.hash[1] >> 8 ) & 0xffU;
        __res[7]  =  (__block.hash[1]      ) & 0xffU;
        __res[8]  =  (__block.hash[2] >> 24) & 0xffU;
        __res[9]  =  (__block.hash[2] >> 16) & 0xffU;
        __res[10] =  (__block.hash[2] >> 8 ) & 0xffU;
        __res[11] =  (__block.hash[2]      ) & 0xffU;
        __res[12] =  (__block.hash[3] >> 24) & 0xffU;
        __res[13] =  (__block.hash[3] >> 16) & 0xffU;
        __res[14] =  (__block.hash[3] >> 8 ) & 0xffU;
        __res[15] =  (__block.hash[3]      ) & 0xffU;
        __res[16] =  (__block.hash[4] >> 24) & 0xffU;
        __res[17] =  (__block.hash[4] >> 16) & 0xffU;
        __res[18] =  (__block.hash[4] >> 8 ) & 0xffU;
        __res[19] =  (__block.hash[4]      ) & 0xffU;

        return;
      }
    }
    void sha1(
      unsigned char __res[20],
      const void* __mem, size_t __len
    ) noexcept
    {
      detail::sha1_block __block;

      detail::sha1_block_init(__block);

      size_t __i;
      const unsigned char* __ptr =
        static_cast<const unsigned char*>(__mem);

      for(__i = 0; __i < __len; ++__i)
      {
        __block.data[__block.dlength++] = __ptr[__i];
        if(__block.dlength == 64U)
        { detail::sha1_block_transform(__block);}
      }
      // align the last 512 bits;
      detail::sha1_last_block(__block);
      // Get the result from the result block
      detail::sha1_result_transform(__res, __block);
    }
  }
}

#undef ___I1
#undef ___I2
#undef ___I3
#undef ___LEFTROTATE
#undef ___R1
#undef ___R2
#undef ___R3
#undef ___R4

#endif // ! __UTILITY_CRYPTO_SHA1__

/*
 *
    void printsha1()
    {
      using std::printf;
      using algorithm::rotate;

      char need[5] = {'a', 'b', 'c', 'd', 'e'};

      for(unsigned int i = 0; i < 20; ++i)
      {
        printf("        ");
        printf("___R1(__%c, __%c, __%c, __%c, __%c, %s__data[%u]);\n",
          need[0], need[1], need[2], need[3], need[4], i < 10U ? " ": "", i);
        rotate(need, need+4, need+5);
      }
      printf("\n");
      for(unsigned int i = 20; i < 40; ++i)
      {
        printf("        ");
        printf("___R2(__%c, __%c, __%c, __%c, __%c, %s__data[%u]);\n",
          need[0], need[1], need[2], need[3], need[4], i < 10U ? " ": "", i);
        rotate(need, need+4, need+5);
      }
      printf("\n");
      for(unsigned int i = 40; i < 60; ++i)
      {
        printf("        ");
        printf("___R3(__%c, __%c, __%c, __%c, __%c, %s__data[%u]);\n",
          need[0], need[1], need[2], need[3], need[4], i < 10U ? " ": "", i);
        rotate(need, need+4, need+5);
      }
      printf("\n");
      for(unsigned int i = 60; i < 80; ++i)
      {
        printf("        ");
        printf("___R4(__%c, __%c, __%c, __%c, __%c, %s__data[%u]);\n",
          need[0], need[1], need[2], need[3], need[4], i < 10U ? " ": "", i);
        rotate(need, need+4, need+5);
      }
      printf("\n");
    }
 *
 */
/**
 * Special sha1 values
 * "" = da39a3ee5e6b4b0d3255bfef95601890afd80709
 * "The quick brown fox jumps over the lazy dog" = 2fd4e1c67a2d28fced849ee1bb76e7391b93eb12
 *
 */
