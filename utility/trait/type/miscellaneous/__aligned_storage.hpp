
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ALIGNED_STORAGE__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ALIGNED_STORAGE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_void.hpp>
#include<utility/trait/type/property_query/alignment_of.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // aligned_storage
        namespace __aligned_storage_impl
        {
          using ::utility::trait::__impl_helper::__type_pair;
          using ::utility::trait::__impl_helper::__none;
          template<typename _T>
          struct __align_type
          {
            constexpr static ::utility::trait::size_t value =
              ::utility::trait::type::property_query::alignment_of<_T>::value;
            typedef _T type;
          };
          struct __double_array
          { double __ld[4];};

          typedef
            __type_pair<__align_type<unsigned char>,
            __type_pair<__align_type<unsigned short>,
            __type_pair<__align_type<unsigned int>,
            __type_pair<__align_type<unsigned long>,
            __type_pair<__align_type<unsigned long long>,
            __type_pair<__align_type<double>,
            __type_pair<__align_type<long double>,
            __type_pair<__align_type<::utility::trait::__impl_helper::__ldouble>,
            __type_pair<__align_type<__double_array>,
            __type_pair<__align_type<int*>,
            __none>>>>>>>>>> __all;


          template<typename _T, ::utility::trait::size_t _align>
          struct __aligned_storage_helper;

          template<typename _F, ::utility::trait::size_t _align>
          struct __aligned_storage_helper<__type_pair<_F, __none>, _align>
          {
            typedef typename
              ::utility::trait::miscellaneous::conditional<
                _align == _F::value,
                typename _t::type,
                void
              >::type type;
          };
          template<typename _F, typename _S, ::utility::trait::size_t _align>
          struct __aligned_storage_helper<__type_pair<_F, _S>, _align>
          {
            typedef typename
              ::utility::trait::miscellaneous::conditional<
                _align == _F::value,
                typename _t::type,
                typename __aligned_storage_helper<_T, _align>::type
              >::type type;
          };

          template<::utility::trait::size_t _N, ::utility::trait::size_t _T1,
          ::utility::trait::size_t _T2>
          struct __select_type
          {
            private:
              constexpr static ::utility::trait::size_t __min =
                _T1 < _T2 ? _T1 : _T2;
              constexpr static ::utility::trait::size_t __max =
                _T1 > _T2 ? _T1 : _T2;
            public:
              constexpr ::utility::trait::size_t value =
                _N < __max ? __min : __max;
          };

          template<typename _T, ::utility::trait::size_t _N>
          struct __aligned_max_helper;
          template<typename _F, ::utility::trait::size_t _N>
          struct __aligned_max_helper<__type_pair<_F, __none>, _N> :
            public ::utility::trait::integral_constant<::utility::trait::size_t,
              _F::value>
          { };
          template<typename _F, typename _T, ::utility::trait::size_t _N>
          struct __aligned_max_helper<__type_pair<_F, _T>, _N> :
            public ::utility::trait::integral_constant<::utility::trait::size_t,
              __select_type<_N, _F::value, __aligned_max_helper<_T, _N
              >::value>::value>
          { };

        }
        template<::utility::trait::size_t _Len, ::utility::trait::size_t _Align =
          __aligned_storage_impl::__aligned_max_helper<
            __aligned_storage_impl::__all, _Len>::value>
        struct aligned_storage
        {
          typedef typename __aligned_storage_impl::__align_type<
            __aligned_storage_impl::__all, _Align>::type _Aligner;
          static_assert(!::utility::trait::type::categories::is_void<
            _Aligner>::value, "");
          union type
          {
            _Aligner __align;
            unsigned char __data[(_Len+_Align-1)/_Align*_Align];
          };
        };

#define aligned_storage_template(n) \
        template<::utility::trait::size_t _Len> \
        struct aligned_storage<_Len, n> \
        {\
          struct alignas(n) type \
          { unsigned char __data[(_Len+n-1)/n*n];};\
        }

        aligned_storage_template(0x1);
        aligned_storage_template(0x2);
        aligned_storage_template(0x4);
        aligned_storage_template(0x8);
        aligned_storage_template(0x10);
        aligned_storage_template(0x20);
        aligned_storage_template(0x40);
        aligned_storage_template(0x80);
        aligned_storage_template(0x100);
        aligned_storage_template(0x200);
        aligned_storage_template(0x400);
        aligned_storage_template(0x800);
        aligned_storage_template(0x1000);
        aligned_storage_template(0x2000);
        // aligned_storage_template(0x4000);

#undef aligned_storage_template
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ALIGNED_STORAGE__
