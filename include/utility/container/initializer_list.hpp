
#ifndef __UTILITY_CONTAINER_INITIALIZER_LIST__
#define __UTILITY_CONTAINER_INITIALIZER_LIST__

/**
 * \file initializer_list.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<initializer_list>

namespace utility
{
  namespace container
  {
    // template<typename _T>
    // class initializer_list
    // {
    //   private:
    //     const _T* __begin;
    //     size_t __size;
    //   public:
    //     __UTILITY_CPP14_CONSTEXPR__
    //     initializer_list(const _T* __st, size_t __s) noexcept :
    //       __begin(__st), __size(__s)
    //     { }
    //   public:
    //     typedef _T                value_type;
    //     typedef const _T&         reference;
    //     typedef const _T&         const_reference;
    //     typedef size_t size_type;

    //     typedef const _T*         iterator;
    //     typedef const _T*         const_iterator;

    //   public:
    //     /*!
    //     *
    //     */
    //     __UTILITY_CPP14_CONSTEXPR__
    //     initializer_list() noexcept :
    //       __begin(nullptr), __size(0)
    //     { }

    //   public:
    //     /*!
    //     * \brief get the size of the initializer_list
    //     * \return the initializer_list's size
    //     */
    //     __UTILITY_CPP14_CONSTEXPR__
    //     inline size_t size() const noexcept
    //     { return this->__size;}

    //     /*!
    //     * \brief get the first iterator of the initializer_list
    //     * \return the initializer_list's begin iterator
    //     */
    //     __UTILITY_CPP14_CONSTEXPR__
    //     inline const _T* begin() const noexcept
    //     { return this->__begin;}

    //     /*!
    //     * \brief get the last iterator of the initializer_list
    //     * \return the initializer_list's last iterator
    //     */
    //     __UTILITY_CPP14_CONSTEXPR__
    //     inline const _T* end() const noexcept
    //     { return this->__begin + this->__size;}
    // };

    // /*
    // * \see container::initializer_list::begin
    // */
    // template<typename _T>
    // __UTILITY_CPP14_CONSTEXPR__
    // inline const _T* begin(initializer_list<_T> __ilist) noexcept
    // { return __ilist.begin();}

    // /*
    // * \see container::initializer_list::end
    // */
    // template<typename _T>
    // __UTILITY_CPP14_CONSTEXPR__
    // inline const _T* end(initializer_list<_T> __ilist) noexcept
    // { return __ilist.end();}

    using std::initializer_list;
  }
}

#endif // ! __UTILITY_CONTAINER_INITIALIZER_LIST__
