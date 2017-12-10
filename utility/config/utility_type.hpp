

#ifndef ___UTILITY__TYPE__DECLARARTION___
#define ___UTILITY__TYPE__DECLARARTION___

#ifdef __CHAR_BIT__
# define __UTILITY_CHAR_BIT__ __CHAR_BIT__
#else
# define __UTILITY_CHAR_BIT__ 1
#endif // ! __CHAR_BIT__

namespace utility
{
  using size_t = decltype(sizeof(char));  ///< size type
  using nullptr_t = decltype(nullptr);    ///< nullptr type
  using ptrdiff_t = decltype(0L);         ///< pointer storage type
}

#endif // ! ___UTILITY__TYPE__DECLARARTION___
