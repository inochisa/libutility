
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ALIGNED_UNION__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ALIGNED_UNION__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/miscellaneous/aligned_storage.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // aligned_union
        namespace __aligned_union_impl
        {
          template<typename... _Ts>
          struct __aligned_union_helper
          {
            constexpr static size_t __size = 0;
            constexpr static size_t __align = 0;
          };
          template<typename _T, typename... _Ts>
          struct __aligned_union_helper<_T, _Ts...>
          {
            constexpr static size_t __size =
              sizeof(_T) > __aligned_union_helper<_Ts...>::__size ?
              sizeof(_T) : __aligned_union_helper<_Ts...>::__size;
            constexpr static size_t __align =
              alignof(_T) > __aligned_union_helper<_Ts...>::__align ?
              alignof(_T) : __aligned_union_helper<_Ts...>::__align;
        };
        }
        template<size_t _Len, typename... _Ts>
        struct aligned_union
        {
          private:
            static_assert(sizeof...(_Ts) != 0, "Need at least ont type");
            using __type =
              __aligned_union_impl::__aligned_union_helper<_Ts...>;
            constexpr static size_t __align =
              _Len > __type::__size ? _Len : __type::__size;
          public:
            constexpr static size_t alignment_value =
              __type::__align;
            typedef typename aligned_storage<__align, alignment_value>::type type;
        };

        template<size_t _Len, typename... _Ts>
        using aligned_union_t = typename aligned_union<_Len, _Ts...>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS__
