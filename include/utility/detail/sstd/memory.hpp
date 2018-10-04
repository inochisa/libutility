
#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_MEMORY__
#define __UTILITY_DETAIL_STANDARD_LIBRARY_MEMORY__

/*!
 * \file memory.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace detail
  {
    namespace sstd
    {
      namespace memory
      {
        /** \addtogroup memory
         *  @{
         */
        /** \addtogroup Copying
         *  @{
         */
        void* memcpy(void* __destination, const void* __source, size_t __size) noexcept;
        void* memrcpy(void* __destination, const void* __source, size_t __size) noexcept;
        void* memccpy(void* __destination, const void* __source, unsigned char __val, size_t __size) noexcept;
        void* mempcpy(void* __destination, const void* __source, size_t __size) noexcept;
        void* memmove(void* __destination, const void* __source, size_t __size) noexcept;
        /** @}*/

        /** \addtogroup Comparison
         *  @{
         */
        int memcmp(const void* __comp1, const void* __comp2, size_t __size) noexcept;
        /** @}*/

        /** \addtogroup Fill
         *  @{
         */
        void* memchr(void* __source, unsigned char __val, size_t __size) noexcept;
        const void* memchr(const void* __source, unsigned char __val, size_t __size) noexcept;
        void* memrchr(void* __source, unsigned char __val, size_t __size) noexcept;
        const void* memrchr(const void* __source, unsigned char __val, size_t __size) noexcept;
        void* memmem(void* __source, size_t __srclen, const void* __tag, size_t __taglen) noexcept;
        const void* memmem(const void* __source, size_t __srclen, const void* __tag, size_t __taglen) noexcept;
        /** @}*/

        /** \addtogroup Searching
         *  @{
         */
        void* memset(void* __ptr, unsigned char __val, size_t __size) noexcept;
        /** @}*/
        /** @}*/

      }
      namespace memory
      {

        // Copying
        /*!
        * \brief Copy block of memory
        *
        * Copies the values of \a __size bytes from the location pointed to
        * by \a __source directly to the memory block pointed to by \a __destination.
        *
        * \warning This function does not check whether the memory is overlapping.
        * \param[out] __destination  Pointer to the destination array where the content is
        *                            to be copied, type-casted to a pointer of type void*.
        * \param[in] __source        Pointer to the source of data to be copied, type-casted
        *                            to a pointer of type const void*.
        * \param[in] __size          Number of bytes to copy.
        * \return \a __destination is returned.
        * \see detail::sstd::memory::memrcpy
        * \see detail::sstd::memory::memccpy
        * \see detail::sstd::memory::mempcpy
        * \see detail::sstd::memory::memmove
        */
        void* memcpy(void* __destination, const void* __source,
          size_t __size) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            unsigned char* __dest =
              static_cast<unsigned char*>(__destination);
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source);
            while(__size--)
            { *__dest++ = *__src++;}
          }
          return __destination;
        }

        /*!
        * \brief Copy block of memory
        *
        * Copies the values of \a __size bytes from the location pointed to
        * by \a __source directly to the memory block pointed to by \a __destination.
        * The copy begins at the last byte.
        *
        * \warning This function does not check whether the memory is overlapping.
        * \param[out] __destination  Pointer to the destination array where the content is
        *                            to be copied, type-casted to a pointer of type void*.
        * \param[in] __source        Pointer to the source of data to be copied, type-casted
        *                            to a pointer of type const void*.
        * \param[in] __size          Number of bytes to copy.
        * \return \a __destination is returned.
        * \see detail::sstd::memory::memcpy
        * \see detail::sstd::memory::memccpy
        * \see detail::sstd::memory::mempcpy
        * \see detail::sstd::memory::memmove
        */
        void* memrcpy(void* __destination, const void* __source,
          size_t __size) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            unsigned char* __dest =
              static_cast<unsigned char*>(__destination)+__size-1;
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source)+__size-1;
            while(__size--)
            { *__dest-- = *__src--;}
          }
          return __destination;
        }

        /*!
        * \brief Copy block of memory until some value is found
        *
        * Copies the values of no more than \a __size bytes
        * from the location pointed to by \a __source directly to
        * the memory block pointed to by \a __destination.
        * Stop when the \a __val is found
        *
        * \warning This function does not check whether the memory is overlapping.
        * \param[out] __destination  Pointer to the destination array where the content is
        *                            to be copied, type-casted to a pointer of type void*.
        * \param[in] __source        Pointer to the source of data to be copied, type-casted
        *                            to a pointer of type const void*.
        * \param[in] __val           the stop value
        * \param[in] __size          Number of bytes to copy.
        * \return \a __destination is returned if the \a __val is not found,
        *         otherwise a pointer to the \a __val is returned.
        * \see detail::sstd::memory::memcpy
        * \see detail::sstd::memory::memrcpy
        * \see detail::sstd::memory::mempcpy
        * \see detail::sstd::memory::memmove
        */
        void* memccpy(void* __destination, const void* __source,
          unsigned char __val, size_t __size) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            unsigned char* __dest =
              static_cast<unsigned char*>(__destination);
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source);
            while(__size--)
            {
              if((*__dest++ = *__src++) == __val)
              { return __dest;}
            }
          }
          return nullptr;
        }

        /*!
        * \brief Copy block of memory
        *
        * Copies the values of \a __size bytes from the location pointed to
        * by \a __source directly to the memory block pointed to by \a __destination.
        *
        * \warning This function does not check whether the memory is overlapping.
        * \param[out] __destination  Pointer to the destination array where the content is
        *                            to be copied, type-casted to a pointer of type void*.
        * \param[in] __source        Pointer to the source of data to be copied, type-casted
        *                            to a pointer of type const void*.
        * \param[in] __size          Number of bytes to copy.
        * \return a pointer to the last written byte is returned.
        * \see detail::sstd::memory::memcpy
        * \see detail::sstd::memory::memrcpy
        * \see detail::sstd::memory::memccpy
        * \see detail::sstd::memory::memmove
        */
        void* mempcpy(void* __destination, const void* __source,
          size_t __size) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr)
          {
            unsigned char* __dest =
              static_cast<unsigned char*>(__destination);
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source);
            while(__size--)
            { *__dest++ = *__src++;}
            return __dest;
          }
          return __destination;
        }

        /*!
        * \brief Move block of memory
        *
        * Copy the values of \a __size bytes from the location
        * pointed by \a __source to the memory block pointed by \a __destination.
        * Copying takes place as if an intermediate buffer were used,
        * allowing the destination and source to overlap.<br/>
        * The underlying type of the objects pointed by both the source
        * and destination pointers are irrelevant for this function;
        * The result is a binary copy of the data.<br/>
        * This function check the pointer, if the pointer is a null pointer
        * The function will do nothing.
        *
        * \param[out] __destination  Pointer to the destination array where the content is
        *                            to be copied, type-casted to a pointer of type void*.
        * \param[in] __source        Pointer to the source of data to be copied, type-casted
        *                            to a pointer of type const void*.
        * \param[in] __size          Number of bytes to copy.
        * \return \a __destination is returned.
        * \see detail::sstd::memory::memcpy
        * \see detail::sstd::memory::memrcpy
        * \see detail::sstd::memory::memccpy
        * \see detail::sstd::memory::mempcpy
        */
        void* memmove(void* __destination, const void* __source,
          size_t __size) noexcept
        {
          if(__size && __destination != nullptr && __source != nullptr &&
            __destination != __source
          )
          {
            if(__destination > __source)
            {
              detail::sstd::memory::memrcpy(
                __destination, __source, __size
              );
            }
            else
            {
              detail::sstd::memory::memcpy(
                __destination, __source, __size
              );
            }
          }
          return __destination;
        }

        // Comparison
        /*!
        * \brief Compare two blocks of memory
        *
        * Compare the first num bytes of the block of memory
        * pointed by \a __comp1 to the first num bytes pointed by \a __comp2,
        * returning zero if they all match or
        * a value different from zero representing
        * which is greater if they do not.
        *
        * \param[in] __comp1  Pointer to block of memory.
        * \param[in] __comp2  Pointer to block of memory.
        * \param[in] __size   Number of bytes to compare.
        * \return return an integral value indicating the
        * relationship between the content of the memory blocks.<br/>
        * <table>
        *   <tr>
        *     <th>return value</th>
        *     <th>explanation</th>
        *   </tr>
        *   <tr>
        *     <td>\< 0</td>
        *     <td>the first byte that does not match in both memory blocks
        *         has a lower value in ptr1 than in ptr2</td>
        *   </tr>
        *   <tr>
        *     <td>0</td>
        *     <td>the contents of both memory blocks are equal</td>
        *   </tr>
        *   <tr>
        *     <td>\> 0</td>
        *     <td>the first byte that does not match in both memory blocks
        *         has a greater value in ptr1 than in ptr2</td>
        *   </tr>
        */
        int memcmp(const void* __comp1, const void* __comp2,
          size_t __size) noexcept
        {
          if(__size && __comp1 != nullptr && __comp2 != nullptr)
          {
            const char* __ptr1 = static_cast<const char*>(__comp1);
            const char* __ptr2 = static_cast<const char*>(__comp2);
            for(; __size--; ++__ptr1, ++__ptr2)
            {
              if(*__ptr1 != *__ptr2)
              { return *__ptr1 - *__ptr2;}
            }
          }
          return 0;
        }

        // Search
        /*!
        * \brief Locate character in block of memory
        *
        * Searches within the first num bytes of the block of memory
        * pointed by \a __source
        * for the first occurrence of value (interpreted as an unsigned char),
        * and return a pointer to it.
        *
        * \param[in] __source Pointer to the block of memory where the search is performed.
        * \param[in] __val    Value to be located. The value is passed as an unsigned char,
        *                     but the function performs a byte per byte search.
        *                     using the unsigned char conversion of this value.
        * \param[in] __size   Number of bytes to be analyzed.
        * \return A pointer to the first occurrence of value.
        *         in the block of memory pointed by \a __source.
        *         If the value is not found, the function returns a null pointer.
        * \see detail::sstd::memory::memrchr(void* __source,
        *       unsigned char __val, size_t __size)
        * \see detail::sstd::memory::memmem(
        *       const void* __source, size_t __srclen,
        *       const void* __tag, size_t __taglen)
        */
        void* memchr(void* __source, unsigned char __val,
          size_t __size) noexcept
        {
          if(__size && __source != nullptr)
          {
            unsigned char* __src = static_cast<unsigned char*>(__source);
            while(__size--)
            {
              if(*__src++ == __val)
              { return (__src-1);}
            }
          }
          return nullptr;
        }
        /*!
        * \overload const void* memchr(const void* __source, unsigned char __val,
        *             size_t __size) noexcept
        *
        * const version
        *
        */
        const void* memchr(const void* __source, unsigned char __val,
          size_t __size) noexcept
        {
          if(__size && __source != nullptr)
          {
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source);
            while(__size--)
            {
              if(*__src++ == __val)
              { return static_cast<const void*>(__src-1);}
            }
          }
          return nullptr;
        }

        /*!
        * \brief Locate character in block of memory
        *
        * Searches within the last num bytes of the block of memory
        * pointed by \a __source
        * for the first occurrence of value (interpreted as an unsigned char),
        * and return a pointer to it.
        *
        * \param[in] __source Pointer to the block of memory where the search is performed.
        * \param[in] __val    Value to be located. The value is passed as an unsigned char,
        *                     but the function performs a byte per byte search.
        *                     using the unsigned char conversion of this value.
        * \param[in] __size   Number of bytes to be analyzed.
        * \return A pointer to the last occurrence of value.
        *         in the block of memory pointed by \a __source.
        *         If the value is not found, the function returns a null pointer.
        * \see detail::sstd::memory::memchr(void* __source,
        *       unsigned char __val, size_t __size)
        * \see detail::sstd::memory::memmem(
        *       const void* __source, size_t __srclen,
        *       const void* __tag, size_t __taglen)
        */
        void* memrchr(void* __source, unsigned char __val,
          size_t __size) noexcept
        {
          if(__size && __source != nullptr)
          {
            unsigned char* __src =
              static_cast<unsigned char*>(__source)+__size-1;
            while(__size--)
            {
              if(*__src-- == __val)
              { return static_cast<void*>(__src+1);}
            }
          }
          return nullptr;
        }
        /*!
        * \overload const void* memrchr(const void* __source, unsigned char __val,
        *             size_t __size) noexcept
        *
        * const version
        *
        */
        const void* memrchr(const void* __source, unsigned char __val,
          size_t __size) noexcept
        {
          if(__size && __source != nullptr)
          {
            const unsigned char* __src =
              static_cast<const unsigned char*>(__source)+__size-1;
            while(__size--)
            {
              if(*__src-- == __val)
              { return static_cast<const void*>(__src+1);}
            }
          }
          return nullptr;
        }

        /*!
        * \brief Locate a block of memory in another block of memory
        *
        * Searches within the first num bytes of the block of memory pointed by \a __source
        * for the first occurrence of value (input as an unsigned char),
        * and returns a pointer to it.
        *
        * \param[in] __source Pointer to the block of memory where the search is performed.
        * \param[in] __srclen Number of bytes to be analyzed.
        * \param[in] __tag    Pointer to the block of memory to be located
        * \param[in] __taglen Number of bytes to be located.
        * \return A pointer to the first occurrence of pattern
        *         in the block of memory pointed by \a __source.
        *         If the value is not found, the function returns a null pointer.
        * \see detail::sstd::memory::memchr(void* __source,
        *       unsigned char __val, size_t __size)
        * \see detail::sstd::memory::memrchr(void* __source,
        *       unsigned char __val, size_t __size)
        */
        void* memmem(
          void* __source, size_t __srclen,
          const void* __tag, size_t __taglen
        ) noexcept
        {
          if(__source == nullptr || __tag == nullptr)
          { return nullptr;}
          if(__taglen == 0)
          { return __source;}
          if(__srclen < __taglen)
          { return nullptr;}
          const unsigned char* __mem_tag =
            static_cast<const unsigned char*>(__tag);
          unsigned char* __src = static_cast<unsigned char*>(__source);
          unsigned char* __endsrc = __src +(__srclen - __taglen) +1;
          if(__taglen == 1)
          { return detail::sstd::memory::memchr(__source, *__mem_tag, __srclen);}
          while(__src < __endsrc)
          {
            if((*__src == *__mem_tag) && (
              detail::sstd::memory::memcmp(__src, __mem_tag, __taglen) == 0))
            { return __src;}
            ++__src;
          }
          return nullptr;
        }
        /*!
        * \overload const void* memmem(
        *             const void* __source, size_t __srclen,
        *             const void* __tag, size_t __taglen)
        *
        * const version
        *
        */
        const void* memmem(
          const void* __source, size_t __srclen,
          const void* __tag, size_t __taglen
        ) noexcept
        {
          if(__source == nullptr || __tag == nullptr)
          { return nullptr;}
          if(__taglen == 0)
          { return __source;}
          if(__srclen < __taglen)
          { return nullptr;}
          const unsigned char* __mem_tag = static_cast<const unsigned char*>(__tag);
          const unsigned char* __src = static_cast<const unsigned char*>(__source);
          const unsigned char* __endsrc = __src +(__srclen - __taglen) +1;
          if(__taglen == 1)
          {
            return detail::sstd::memory::memchr(
                      __source, *__mem_tag, __srclen
                   );
          }
          while(__src < __endsrc)
          {
            if((*__src == *__mem_tag) && (
              detail::sstd::memory::memcmp(
                __src, __mem_tag, __taglen) == 0))
            { return __src;}
            ++__src;
          }
          return nullptr;
        }

        // Fill
        /*!
        * \brief Fill block of memory
        *
        * Sets the first num bytes of the block of memory pointed by \a __ptr
        * to the specified value (interpreted as an unsigned char).
        *
        * \param __ptr  Pointer to the block of memory to fill.
        * \param __val  Value to be set.
        * \param __size Number of bytes to be set to the value.
        * \return \a __ptr is returned.
        *
        */
        void* memset(void* __ptr, unsigned char __val,
          size_t __size) noexcept
        {
          if(__size && __ptr != nullptr)
          {
            unsigned char* __src = static_cast<unsigned char*>(__ptr);
            while(__size--)
            { *__src++ = __val;}
          }
          return __ptr;
        }

      }
    }
  }
}

#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_MEMORY__
