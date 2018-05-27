
#ifndef ___UTILITY__DEBUG__CONFIG___
#define ___UTILITY__DEBUG__CONFIG___

#ifdef UTILITY_DEBUG

#define __utility_private public
#define __utility_debug   public
#define __UTILITY_ASSGIN(__TYPE, __TYPENAME, __ASS) \
          __type __TYPENAME = __ASS

#define UTILITY_ALGORITHM_NEED_EXTRA true
#define UTILITY_CONTAINER_NEED_EXTRA true
#define UTILITY_ITERATOR_HAS_EXTRA true
#define UTILITY_MATH_HAS_EXTRA true
#define UTILITY_MEMORY_HAS_EXTRA true
#define UTILITY_TRAIT_HAS_EXTRA true

#ifndef UTILITY_NO_EXTRA_CHECK

#else

#endif // ! UTILITY_NO_EXTRA_CHECK

#else

#define __utility_private private
#define __utility_debug   private
#define __UTILITY_ASSGIN(__TYPE, __TYPENAME, __ASS)

#endif // ! __UTILITY_DEBUG

#ifndef UTILITY_NOEXTRA
# define __utility_extra   public
#else
# define __utility_extra   private
#endif

#endif // ! ___UTILITY__DEBUG__CONFIG___
