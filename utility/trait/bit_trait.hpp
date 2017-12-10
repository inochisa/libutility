
#ifndef __UTILITY_TRAIT_MATH_BIT__
#define __UTILITY_TRAIT_MATH_BIT__

#include<limits>
#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace math
    {
      constexpr unsigned int per_bit = ::std::numeric_limits<unsigned char>::digits / sizeof(unsigned char);
      template<typename Type>
      struct bit_trait
      {
        typedef Type type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = false;
        constexpr static int allbit = -1;
        constexpr static int nonebit = 0;
        constexpr static unsigned int bitlen = sizeof(Type)*per_bit;
      };
      // bool
      template<>
      struct bit_trait<bool>
      {
        typedef bool type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static bool allbit = true;
        constexpr static bool nonebit = false;
        constexpr static unsigned int bitlen = sizeof(bool)*per_bit;
      };
      // signed char & unsigned char
      template<>
      struct bit_trait<signed char>
      {
        typedef signed char type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static signed char allbit = -1;
        constexpr static signed char nonebit = 0x0;
        constexpr static unsigned int bitlen = sizeof(signed char)*per_bit;
      };
      template<>
      struct bit_trait<unsigned char>
      {
        typedef unsigned char type;
        constexpr static bool vaild = true;
        constexpr static bool bitoperation = true;
        constexpr static unsigned char allbit = static_cast<unsigned char>(-1);
        constexpr static unsigned char nonebit = 0x0;
        constexpr static unsigned int bitlen = sizeof(unsigned char)*per_bit;
      };
      // signed short & unsigned short
      template<>
      struct bit_trait<signed short>
      {
        typedef signed short type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static signed short allbit = -1;
        constexpr static signed short nonebit = 0x0;
        constexpr static unsigned int bitlen = sizeof(unsigned short)*per_bit;
      };
      template<>
      struct bit_trait<unsigned short>
      {
        typedef unsigned short type;
        constexpr static bool vaild = true;
        constexpr static bool bitoperation = true;
        constexpr static unsigned short allbit =  static_cast<unsigned short>(-1);
        constexpr static unsigned short nonebit = 0x0U;
        constexpr static unsigned int bitlen = sizeof(unsigned short)*per_bit;
      };
      // signed int & unsigned int
      template<>
      struct bit_trait<signed int>
      {
        typedef signed int type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static signed int allbit = -1;
        constexpr static signed int nonebit = 0x0;
        constexpr static unsigned int bitlen = sizeof(signed int)*per_bit;
      };
      template<>
      struct bit_trait<unsigned int>
      {
        typedef unsigned int type;
        constexpr static bool vaild = true;
        constexpr static bool bitoperation = true;
        constexpr static unsigned int allbit =  static_cast<unsigned int>(-1);
        constexpr static unsigned int nonebit = 0x0U;
        constexpr static unsigned int bitlen = sizeof(unsigned int)*per_bit;
      };

      // signed long & unsigned long
      template<>
      struct bit_trait<signed long>
      {
        typedef signed long type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static signed long allbit = -1L;
        constexpr static signed long nonebit = 0x0L;
        constexpr static unsigned int bitlen = sizeof(signed long)*per_bit;
      };
      template<>
      struct bit_trait<unsigned long>
      {
        typedef unsigned long type;
        constexpr static bool vaild = true;
        constexpr static bool bitoperation = true;
        constexpr static unsigned long allbit =  static_cast<unsigned long>(-1);
        constexpr static unsigned long nonebit = 0x0UL;
        constexpr static unsigned int bitlen = sizeof(unsigned long)*per_bit;
      };

      // signed long long & unsigned long long
      template<>
      struct bit_trait<signed long long>
      {
        typedef signed long long type;
        constexpr static bool vaild = false;
        constexpr static bool bitoperation = true;
        constexpr static signed long long allbit = -1LL;
        constexpr static signed long long nonebit = 0x0LL;
        constexpr static unsigned int bitlen = sizeof(signed long)*per_bit;
      };
      template<>
      struct bit_trait<unsigned long long>
      {
        typedef unsigned long long type;
        constexpr static bool vaild = true;
        constexpr static bool bitoperation = true;
        constexpr static unsigned long long allbit =  static_cast<unsigned long long>(-1);
        constexpr static unsigned long long nonebit = 0x0ULL;
        constexpr static unsigned int bitlen = sizeof(unsigned long)*per_bit;
      };
    }
    using ::utility::trait::math::bit_trait;
    using ::utility::trait::math::per_bit;
  }
}
namespace utility
{
  namespace math
  {
    using ::utility::trait::math::per_bit;
  }
}
#endif // ! __UTILITY_TRAIT_MATH_BIT__
