
#ifndef ___UTILITY__DEBUG__CONFIG___
#define ___UTILITY__DEBUG__CONFIG___

#ifdef UTILITY_DEBUG

#define __utility_private public
#define __UTILITY_ASSGIN(__TYPE, __TYPENAME, __ASS) \
          __type __TYPENAME = __ASS

#define UTILITY_ALGORITHM_NEED_EXTRA true
#define UTILITY_CONTAINER_NEED_EXTRA true
#define UTILITY_ITERATOR_HAS_EXTRA true
#define UTILITY_MATH_HAS_EXTRA true
#define UTILITY_MEMORY_HAS_EXTRA true
#define UTILITY_TRAIT_HAS_EXTRA true

#else

#define __utility_private private
#define __UTILITY_ASSGIN(__TYPE, __TYPENAME, __ASS)

#endif // ! __UTILITY_DEBUG


#endif // ! ___UTILITY__DEBUG__CONFIG___
