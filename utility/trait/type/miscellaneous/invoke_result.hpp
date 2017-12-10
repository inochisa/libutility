
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/decay.hpp>
#include<utility/trait/type/transform/remove_cv.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>
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
        // invoke_result(C++17)
        namespace __invoke_result_impl
        {
        }
        /*!
        * \todo
        */
        template<typename _Fn, typename... _ArgTypes>
        class invoke_result;

        template<typename _Fn, typename... _ArgTypes>
        class invoke_result<_Fn(_ArgTypes...)>;

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_INVOKE_RESULT__

/*
      typedef typename
        conditional
          <
          __or_
            <
            is_same
              <
              _Argval, _Class
              >,
            is_base_of<_Class, _Argval>
            >::value,
        __result_of_memobj_ref<_MemPtr, _Arg>,
        __result_of_memobj_deref<_MemPtr, _Arg>
      >::type::type type;
*/
