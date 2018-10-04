

#ifndef ___UTILITY__TYPE__DECLARARTION___
#define ___UTILITY__TYPE__DECLARARTION___

namespace utility
{
  using size_t = decltype(sizeof(char));  ///< size type
  using nullptr_t = decltype(nullptr);    ///< nullptr type
  using ptrdiff_t = decltype(reinterpret_cast<char*>(0)-reinterpret_cast<char*>(0));         ///< pointer storage type
}

#endif // ! ___UTILITY__TYPE__DECLARARTION___
