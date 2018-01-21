
#ifndef __UTILITY_CRYPTO_IMPL_CRYPTO_BLOCKS__
#define __UTILITY_CRYPTO_IMPL_CRYPTO_BLOCKS__

namespace utility
{
  namespace crypto
  {
    namespace detail
    {
      template<unsigned long _data_length, unsigned long _hash_length>
      struct __crypto_block
      {
        unsigned char data[_data_length]; ///< the datas the transform need;
        unsigned long hash[_hash_length]; ///< the hash number(little endian);
        unsigned long dlength;            ///< the length this time process;
        unsigned long long bits;          ///< the true bits the block had transport;
      };
    }
  }
}

#endif // ! __UTILITY_CRYPTO_IMPL_CRYPTO_BLOCKS__
