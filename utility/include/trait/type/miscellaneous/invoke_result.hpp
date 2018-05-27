
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/type_trait_special.hpp>
#include<utility/trait/type/categories/is_member_function_pointer.hpp>
#include<utility/trait/type/categories/is_member_object_pointer.hpp>
#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/transform/remove_cv_ref.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/releations/is_base_of.hpp>
#include<utility/trait/type/miscellaneous/conditional.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        namespace __invoke_related
        {
          using trait::__impl_helper::__wrapper;
          using trait::good_type;
          using trait::__impl_helper::__empty;
          using trait::__type_or__;
          template<typename _T>
          using __decay = trait::type::transform::decay<_T>;
          template<typename _T>
          using __remove_cv_ref =
            trait::type::transform::remove_cv_reference<_T>;

          // invoke tags
          struct __invoke_member_function_unpacked;
          struct __invoke_member_function_packed;
          struct __invoke_member_object_unpacked;
          struct __invoke_member_object_packed;
          struct __invoke_operators;
          struct __invoke_failed;

          struct __invoke_member_function_unpacked
          { };
          struct __invoke_member_function_packed
          { };
          struct __invoke_member_object_unpacked
          { };
          struct __invoke_member_object_packed
          { };
          struct __invoke_operators
          { };
          struct __invoke_failed
          { };

          template<typename _T, typename _Invoke_Tag>
          struct __invoke_process
          {
            typedef _T type;
            typedef _Invoke_Tag invoke_tag;
          };

          template<typename _Fn, typename _Arg, typename... _Args>
          struct __invoke_member_function_unpacked_helper
          {
            private:
              template<typename __Fn, typename __Arg, typename... __Args>
              static __invoke_process<good_type<decltype(((trait::type::special::declval<__Arg>()).*trait::type::special::declval<__Fn>())(trait::type::special::declval<__Args>()...))>, __invoke_member_function_unpacked> __test(int);
              template<typename __Fn, typename __Arg, typename... __Args>
              static __invoke_process<__empty, __invoke_failed> __test(...);

            public:
              typedef decltype(__test<_Fn, _Arg, _Args...>(0)) type;
          };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __invoke_member_function_packed_helper
          {
            private:
              template<typename __Fn, typename __Arg, typename... __Args>
              static __invoke_process<good_type<decltype(((*trait::type::special::declval<__Arg>()).*trait::type::special::declval<__Fn>())(trait::type::special::declval<__Args>()...))>, __invoke_member_function_packed> __test(int);
              template<typename __Fn, typename __Arg, typename... __Args>
              static __invoke_process<__empty, __invoke_failed> __test(...);

            public:
              typedef decltype(__test<_Fn, _Arg, _Args...>(0)) type;
          };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __invoke_member_function_helper
          { typedef __invoke_process<__empty, __invoke_failed> type;};
          template<typename _Res, typename _Class, typename _Arg, typename... _Args>
          struct __invoke_member_function_helper<_Res _Class::*, _Arg, _Args...>
          {
            private:
              typedef typename __remove_cv_ref<_Arg>::type _Argval;
              typedef _Res _Class::* _Fn;

            public:
              typedef typename trait::type::miscellaneous::conditional<
                __type_or__<
                  trait::type::releations::is_same<_Argval, _Class>,trait::type::releations::is_base_of<_Class, _Argval>
                >::value,
                __invoke_member_function_unpacked_helper<_Fn, _Arg, _Args...>,
                __invoke_member_function_packed_helper<_Fn, _Arg, _Args...>
              >::type::type type;
          };

          template<typename _Fn, typename _Arg>
          struct __invoke_member_object_unpacked_helper
          {
            private:
              template<typename __Fn, typename __Arg>
              static __invoke_process<good_type<decltype(trait::type::special::declval<__Arg>().*trait::type::special::declval<__Fn>())>, __invoke_member_object_unpacked> __test(int);
              template<typename __Fn, typename __Arg>
              static __invoke_process<__empty, __invoke_failed> __test(...);

            public:
              typedef decltype(__test<_Fn, _Arg>(0)) type;
          };
          template<typename _Fn, typename _Arg>
          struct __invoke_member_object_packed_helper
          {
            private:
              template<typename __Fn, typename __Arg>
              static __invoke_process<good_type<decltype((*trait::type::special::declval<__Arg>()).*trait::type::special::declval<__Fn>())>, __invoke_member_object_packed> __test(int);
              template<typename __Fn, typename __Arg>
              static __invoke_process<__empty, __invoke_failed> __test(...);

            public:
              typedef decltype(__test<_Fn, _Arg>(0)) type;
          };
          template<typename _Fn, typename _Arg>
          struct __invoke_member_object_helper
          { typedef __invoke_process<__empty, __invoke_failed> type;};
          template<typename _Res, typename _Class, typename _Arg>
          struct __invoke_member_object_helper<_Res _Class::*, _Arg>
          {
            private:
              typedef typename __remove_cv_ref<_Arg>::type _Argval;
              typedef _Res _Class::* _Fn;

            public:
              typedef typename trait::type::miscellaneous::conditional<
                __type_or__<
                  trait::type::releations::is_same<_Argval, _Class>,trait::type::releations::is_base_of<_Class, _Argval>
                >::value,
                __invoke_member_object_unpacked_helper<_Fn, _Arg>,
                __invoke_member_object_packed_helper<_Fn, _Arg>
              >::type::type type;
          };

          template<typename _Fn, typename... _Args>
          struct __invoke_operators_helper
          {
            private:
              template<typename __Fn, typename... __Args>
              static __invoke_process<good_type<decltype(trait::type::special::declval<__Fn>()(trait::type::special::declval<__Args>()...))>, __invoke_operators> __test(int);
              template<typename __Fn, typename... __Args>
              static __invoke_process<__empty, __invoke_failed> __test(...);

            public:
              typedef decltype(__test<_Fn, _Args...>(0)) type;
          };


          template<bool/*member_function*/, bool/*member_object*/,
            typename _Fn, typename... _Args>
          struct __invoke_result_helper :
            public __invoke_process<__empty, __invoke_failed>
          { };

          template<typename _Fn, typename... _Args>
          struct __invoke_result_helper<true, false, _Fn, _Args...> :
            public __invoke_process<__empty, __invoke_failed>
          { };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __invoke_result_helper<true, false, _Fn, _Arg, _Args...>:
            public __invoke_member_function_helper<
              typename __decay<_Fn>::type,
              typename __wrapper<_Arg, typename __decay<_Arg>::type>::type,
              _Args...>::type
          { };

          template<typename _Fn, typename... _Args>
          struct __invoke_result_helper<false, true, _Fn, _Args...> :
            public __invoke_process<__empty, __invoke_failed>
          { };
          template<typename _Fn, typename _Arg, typename... _Args>
          struct __invoke_result_helper<false, true, _Fn, _Arg, _Args...>:
            public __invoke_member_object_helper<
              typename __decay<_Fn>::type,
              typename __wrapper<_Arg, typename __decay<_Arg>::type>::type
              >::type
          { };

          template<typename _Fn, typename... _Args>
          struct __invoke_result_helper<false, false, _Fn, _Args...> :
            public __invoke_operators_helper<_Fn, _Args...>::type
          { };

          template<typename _Fn, typename... _Args>
          struct __invoke_result : public __invoke_result_helper<
            trait::type::categories::is_member_function_pointer<_Fn>::value,
            trait::type::categories::is_member_object_pointer<_Fn>::value,
            _Fn, _Args...>
          { };

        }
        // result_of
        template<typename _Fn, typename... _ArgTypes>
        struct result_of;
        template<typename _Fn, typename... _ArgTypes>
        struct result_of<_Fn(_ArgTypes...)> :
          public __invoke_related::__invoke_result<_Fn, _ArgTypes...>::type
        { };

        // invoke_result
        template<typename _Fn, typename... _ArgTypes>
        struct invoke_result :
          public __invoke_related::__invoke_result<_Fn, _ArgTypes...>::type
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__
