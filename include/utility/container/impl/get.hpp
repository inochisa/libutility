
#ifndef __UTILITY_CONTAINER_IMPL_GET__
#define __UTILITY_CONTAINER_IMPL_GET__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace container
  {
    template<size_t _Id, typename _T>
    _T& get(_T& _val)
    { return _val;}
    template<size_t _Id, typename _T>
    const _T& get(const _T& _val)
    { return _val;}
    template<size_t _Id, typename _T>
    _T&& get(_T&& _val)
    { return static_cast<_T&&>(_val);}
    template<size_t _Id, typename _T>
    const _T&& get(const _T&& _val)
    { return static_cast<const _T&&>(_val);}
  }
}

#endif // ! __UTILITY_CONTAINER_IMPL_GET__
