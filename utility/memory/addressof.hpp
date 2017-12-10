
#ifndef __UTILITY_MEMORY_ADDRESSOF__
#define __UTILITY_MEMORY_ADDRESSOF__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace memory
  {
    /*!
    * \brief Get the pointer of the reference
    *
    * Get the pointer of a reference, even if the
    * operator& is overloaded
    *
    * \param __ref a reference
    * \return the pointer of the referenece
    * \note the rvalue version is deleted;
    */
    template<typename _T>
    __UTILITY_CPP14_CONSTEXPR__
    inline _T* addressof(_T& __ref) noexcept
    {
      return reinterpret_cast<_T*>(
        const_cast<char*>(&reinterpret_cast<const volatile char&>(__ref)));
    }
    /*!
    * \overload const _T* addressof(const _T&&)
    *
    * This function is deleted because the address of an rvalue is not
    * vaild.
    *
    */
    template<typename _T>
    const _T* addressof(const _T&&) = delete;
  }
}

#endif // ! __UTILITY_MEMORY_ADDRESSOF__
