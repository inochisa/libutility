
#ifndef __UTILITY_ALGORITHM_IMPL_FNV_HASH_1A__
#define __UTILITY_ALGORITHM_IMPL_FNV_HASH_1A__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace hash_detail
    {
      template<size_t = sizeof(size_t)>
      struct fnv_hash_1a;

      template<>
      struct fnv_hash_1a<4>
      {
        public:
          static inline size_t __aux(
            const void* __src, size_t __len,
            size_t __res = 2166136261UL
          ) noexcept
          {
            const unsigned char* __ptr =
              static_cast<const unsigned char*>(__src);
            for(; __len; --__len)
            {
              __res ^= static_cast<size_t>(*__ptr++);
              __res *= static_cast<size_t>(16777619UL);
            }
            return __res;
          }

        public:
          inline size_t operator()(
            const void* __src, size_t __len,
            size_t __res = 2166136261UL
          ) const noexcept
          {
            return algorithm::hash_detail::fnv_hash_1a<4>::__aux(
              __src, __len, __res
            );
          }
      };

      template<>
      struct fnv_hash_1a<8>
      {
        public:
          static inline size_t __aux(
            const void* __src, size_t __len,
            size_t __res = 14695981039346656037UL
          ) noexcept
          {
            const unsigned char* __ptr =
              static_cast<const unsigned char*>(__src);
            for(; __len; --__len)
            {
              __res ^= static_cast<size_t>(*__ptr++);
              __res *= static_cast<size_t>(1099511628211UL);
            }
            return __res;
          }

        public:
          inline size_t operator()(
            const void* __src, size_t __len,
            size_t __res = 14695981039346656037UL
          ) const noexcept
          {
            return algorithm::hash_detail::fnv_hash_1a<8>::__aux(
              __src, __len, __res
            );
          }
      };
    }
  }
}

// FNV_prime value
// 32 bit FNV_prime = 2^24 + 2^8 + 0x93 = 16777619
// 64 bit FNV_prime = 2^40 + 2^8 + 0xb3 = 1099511628211
// 128 bit FNV_prime = 2^88 + 2^8 + 0x3b = 309485009821345068724781371
// 256 bit FNV_prime = 2^168 + 2^8 + 0x63 =374144419156711147060143317175368453031918731002211
// 512 bit FNV_prime = 2^344 + 2^8 + 0x57 = 35835915874844867368919076489095108449946327955754392558399825615420669938882575
// 126094039892345713852759
// 1024 bit FNV_prime = 2^680 + 2^8 + 0x8d =
// 50164565101131186554345988110352789550307653454047907443030175238311120551081474
// 51509157692220295382716162651878526895249385292291816524375083746691371804094271
// 873160484737966720260389217684476157468082573

// FNV_offset value
// 32 bit offset_basis = 2166136261
// 64 bit offset_basis = 14695981039346656037
// 128 bit offset_basis = 144066263297769815596495629667062367629
// 256 bit offset_basis = 100029257958052580907070968620625704837092796014241193945225284501741471925557
// 512 bit offset_basis = 96593031294966694980094354007163104660904187456726378961083743294344626579945829
// 32197716438449813051892206539805784495328239340083876191928701583869517785
// 1024 bit offset_basis = 14197795064947621068722070641403218320880622795441933960878474914617582723252296
// 73230371772215086409652120235554936562817466910857181476047101507614802975596980
// 40773201576924585630032153049571501574036444603635505054127112859663616102678680
// 82893823963790439336411086884584107735010676915

#endif // ! __UTILITY_ALGORITHM_IMPL_FNV_HASH_1A__
