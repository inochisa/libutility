
#ifndef __UTILITY_CRYPTO_CRC16__
#define __UTILITY_CRYPTO_CRC16__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace crypto
  {
    namespace CRC_table
    {
      constexpr const unsigned short CRC16_TABLE[16] =
      {
        0x0000U, 0xCC01U, 0xD801U, 0x1400U,
        0xF001U, 0x3C00U, 0x2800U, 0xE401U,
        0xA001U, 0x6C00U, 0x7800U, 0xB401U,
        0x5000U, 0x9C01U, 0x8801U, 0x4400U
      };

    }

    unsigned short CRC16(const void* __pos, utility::size_t __len) noexcept
    {
      unsigned short __res = 0U;
      unsigned short __table_value;
      const unsigned char* __ptr = static_cast<const unsigned char*>(__pos);
      for(utility::size_t __i = 0; __i < __len; ++__i, ++__ptr)
      {
        __table_value = CRC_table::CRC16_TABLE[__res & 0xfU];
        __res = (__res >> 4) & 0x0fffU;
        __res ^= __table_value;
        __res ^= CRC_table::CRC16_TABLE[(*__ptr)& 0xfU];

        __table_value = CRC_table::CRC16_TABLE[__res & 0xfU];
        __res = (__res >> 4) & 0x0fffU;
        __res ^= __table_value;
        __res ^= CRC_table::CRC16_TABLE[((*__ptr) >> 4)& 0xfU];
      }

      return __res;
    }

    unsigned short CRC16(
      unsigned short __pre_crc,
      const void* __pos, utility::size_t __len
    ) noexcept
    {
      unsigned short __table_value;
      const unsigned char* __ptr = static_cast<const unsigned char*>(__pos);
      for(utility::size_t __i = 0; __i < __len; ++__i, ++__ptr)
      {
        __table_value = CRC_table::CRC16_TABLE[__pre_crc & 0xfU];
        __pre_crc = (__pre_crc >> 4) & 0x0fffU;
        __pre_crc ^= __table_value;
        __pre_crc ^= CRC_table::CRC16_TABLE[(*__ptr)& 0xfU];

        __table_value = CRC_table::CRC16_TABLE[__pre_crc & 0xfU];
        __pre_crc = (__pre_crc >> 4) & 0x0fffU;
        __pre_crc ^= __table_value;
        __pre_crc ^= CRC_table::CRC16_TABLE[((*__ptr) >> 4)& 0xfU];
      }

      return __pre_crc;
    }

  }
}

#endif // ! __UTILITY_CRYPTO_CRC16__
