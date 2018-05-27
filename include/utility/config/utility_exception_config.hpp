
#ifndef ___UTILITY__EXCEPTION__CONFIG__
#define ___UTILITY__EXCEPTION__CONFIG__

#if defined(UTILITY_USE_EXCEPTION) || defined(__UTILITY_NO_EXCEPTION__)

# define __UTILITY_THROW(exception)
# define __UTILITY_NOEXCEPTION
# define __UTILITY_TRY_BEGIN
# define __UTILITY_TRY_END
# define __UTILITY_CATCH(exception)
# define __UTILITY_CATCH_DO(action)
# define __UTILITY_CATCH_UNWIND(action)

#else

# define __UTILITY_USE_EXCEPTION true
# define __UTILITY_THROW(exception) throw exception
# define __UTILITY_NOEXCEPTION noexcept
# define __UTILITY_TRY_BEGIN try {
# define __UTILITY_TRY_END }
# define __UTILITY_CATCH(exception) catch(exception)
# define __UTILITY_CATCH_DO(action) { action; }
# define __UTILITY_CATCH_UNWIND(action) { action; throw; }

#endif // UTILITY_USE_EXCEPTION || __UTILITY_NO_EXCEPTION__

#endif // ! ___UTILITY__EXCEPTION__CONFIG__
