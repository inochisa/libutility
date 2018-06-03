
#ifndef ___UTILITY__CONTROL__CONFIG___
#define ___UTILITY__CONTROL__CONFIG___

#if (defined(UTILITY_USE_STD) || defined(UTILITY_WITH_STD)) && \
    !defined(___UTILITY__CHECK__USE__STD___)
# define ___UTILITY__CHECK__USE__STD___
#endif

#if (defined(UTILITY_COMPATIBLE_WITH_STD) || \
    defined(___UTILITY__CHECK__USE__STD___)) && \
    !defined(___UTILITY__COMPATIBLE__WITH__STD__)
#define ___UTILITY__COMPATIBLE__WITH__STD__
#endif

#endif // ! ___UTILITY__CONTROL__CONFIG___
