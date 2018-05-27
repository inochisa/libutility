
#ifndef __UTILITY_ALGORITHM_IMPL_MURMUR_HASH_2__
#define __UTILITY_ALGORITHM_IMPL_MURMUR_HASH_2__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    namespace hash_detail
    {
      namespace __detail
      {
        UTILITY_ALWAYS_INLINE
        inline void* __size_t_cpy_impl(
          void* __destination, const void* __source,
          size_t __size) noexcept
        {
          unsigned char* __dest =
            static_cast<unsigned char*>(__destination);
          const unsigned char* __src =
            static_cast<const unsigned char*>(__source);
          while(__size--)
          { *__dest++ = *__src++;}
          return __destination;
        }
        UTILITY_ALWAYS_INLINE
        inline size_t __get_size_t(const void* __src)
        {
          size_t __res;
          __size_t_cpy_impl(&__res, __src, sizeof(size_t));
          return __res;
        }

        UTILITY_ALWAYS_INLINE
        inline size_t load_bytes(
          const void* __src, size_t __size
        ) noexcept
        {
          const unsigned char* __ptr =
            static_cast<const unsigned char*>(__src);
          size_t __res = 0U;
          for(; __size; --__size)
          { __res = (__res << 8) & (*__ptr);}
          return __res;
        }
      }

      template<size_t = sizeof(size_t)>
      struct murmur_hash_2;

      template<>
      struct murmur_hash_2<4>
      {
        private:
          UTILITY_ALWAYS_INLINE
          static inline size_t shift(size_t __val) noexcept
          { return __val ^ (__val >> 24);}

        public:
          static inline size_t __aux(
            const void* __src, size_t __len,
            size_t __seed
          ) noexcept
          {
            const static size_t __m = 0x5bd1e995U;
            size_t __res = __seed ^ __len;

            const unsigned char* __ptr =
              static_cast<const unsigned char*>(__src);

            const unsigned char* __end = __ptr + (__len & (~0x3U));

            for(; __ptr != __end; __ptr += 4)
            {
              __res *= __m;
              __res ^= shift(__detail::__get_size_t(__ptr) * __m) * __m;
            }
            if((__len & 0x3U) != 0)
            {
              __res ^= __detail::load_bytes(__end, __len & 0x3U);
              __res *= __m;
            }
            __res ^= __res >> 13U;
            __res *= __m;
            __res ^= __res >> 15U;
            return __res;
          }

        public:
          inline size_t operator()(
            const void* __src, size_t __len,
            size_t __seed
          ) const noexcept
          {
            return algorithm::hash_detail::murmur_hash_2<4>::__aux(
              __src, __len, __seed
            );
          }
      };

      template<>
      struct murmur_hash_2<8>
      {
        private:
          UTILITY_ALWAYS_INLINE
          static inline size_t shift(size_t __val) noexcept
          { return __val ^ (__val >> 47);}

        public:
          static inline size_t __aux(
            const void* __src, size_t __len,
            size_t __seed
          ) noexcept
          {
            const static size_t __m =
              (static_cast<size_t>(0xc6a4a793UL) << 32UL)
  			      + static_cast<size_t>(0x5bd1e995UL);
            const unsigned char* __ptr =
              static_cast<const unsigned char*>(__src);

            const unsigned char* __end = __ptr + (__len & (~0x7U));
            size_t __res = (__seed ^ __len) * __m;

            for(; __ptr != __end; __ptr += 8)
            {
              __res ^= shift(__detail::__get_size_t(__ptr)* __m) * __m;
              __res *= __m;
            }
            if((__len & 0x7U) != 0)
            {
              __res ^= __detail::load_bytes(__end, __len & 0x7U);
              __res *= __m;
            }
            __res = shift(__res) * __m;
            __res = shift(__res);
            return __res;
          }

        public:
          inline size_t operator()(
            const void* __src, size_t __len,
            size_t __seed
          ) const noexcept
          {
            return algorithm::hash_detail::murmur_hash_2<8>::__aux(
              __src, __len, __seed
            );
          }
      };

    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IMPL_MURMUR_HASH_2__
