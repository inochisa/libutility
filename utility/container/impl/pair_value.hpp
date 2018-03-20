
#ifndef __UTILITY_CONTAINER_IMPL_PAIR_VALUE__
#define __UTILITY_CONTAINER_IMPL_PAIR_VALUE__

namespace utility
{
  namespace container
  {
    // template<typename _T>
    // inline
    // auto get_key(_T& __o) -> decltype(__o.first)&
    // { return __o.first;}
    template<typename _T>
    auto get_key(const _T& __o) -> const decltype(__o.first)&
    { return __o.first;}
    // template<typename _T>
    // auto get_key(_T&& __o)
    //   -> decltype(utility::algorithm::move(__o.first))
    // { return utility::algorithm::move(__o.first);}
    template<typename _T>
    inline auto get_value(_T& __o) -> decltype(__o.second)&
    { return __o.second;}
    template<typename _T>
    auto get_value(const _T& __o) -> const decltype(__o.second)&
    { return __o.second;}
    template<typename _T>
    void get_value(_T&& __o) = delete;

  }
}

#endif // ! __UTILITY_CONTAINER_IMPL_PAIR_VALUE__
