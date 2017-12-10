
#ifndef ___UTILITY__TRAIT__CONFIG___
#define ___UTILITY__TRAIT__CONFIG___

#ifdef __GNUC__
# include<utility/trait/config/gcc_config.hpp>
#endif // ! __GNUC__

#ifdef _MSC_VER
# include<utility/trait/config/msvc_config.hpp>
#endif // ! _MSC_VER

#ifdef __clang__
# include<utility/trait/config/clang_config.hpp>
#endif // ! __clang__

#ifndef __utility_support_compile_extension
#define __utility_support_compile_extension 0
#define __utility_has_has_trivial_destructor 0
#define __utility_has_has_virtual_destructor 0
#define __utility_has_is_abstract 0
#define __utility_has_is_aggregate 0
#define __utility_has_is_assignable 0
#define __utility_has_is_base_of 0
#define __utility_has_is_class 0
#define __utility_has_is_constructible 0
#define __utility_has_is_empty 0
#define __utility_has_is_enum 0
#define __utility_has_is_literal 0
#define __utility_has_is_pod 0
#define __utility_has_is_polymorphic 0
#define __utility_has_is_standard_layout 0
#define __utility_has_is_trivial 0
#define __utility_has_is_trivially_assignable 0
#define __utility_has_is_trivially_constructible 0
#define __utility_has_is_trivially_copyable 0
#define __utility_has_is_union 0
#define __utility_has_underlying_type 0
#endif // __utility_support_compile_extension


#ifndef __UTILITY_NO_CPP14__
# include<utility/trait/config/trait_cpp14_config.hpp>
#endif // ! __UNILITY_NO_CPP14__

#ifdef __UTILITY_TYPE_TRAIT_DEBUG
# include<utility/trait/config/trait_undef.hpp>
# define __utility_support_compile_extension 0
# define __utility_has_has_trivial_destructor 0
# define __utility_has_has_virtual_destructor 0
# define __utility_has_is_abstract 0
# define __utility_has_is_aggregate 0
# define __utility_has_is_assignable 0
# define __utility_has_is_base_of 0
# define __utility_has_is_class 0
# define __utility_has_is_constructible 0
# define __utility_has_is_empty 0
# define __utility_has_is_enum 0
# define __utility_has_is_literal 0
# define __utility_has_is_pod 0
# define __utility_has_is_polymorphic 0
# define __utility_has_is_standard_layout 0
# define __utility_has_is_trivial 0
# define __utility_has_is_trivially_assignable 0
# define __utility_has_is_trivially_constructible 0
# define __utility_has_is_trivially_copyable 0
# define __utility_has_is_union 0
# define __utility_has_underlying_type 0
#endif // ! __UTILITY_TYPE_TRAIT_DEBUG

#endif // ! ___UTILITY__TRAIT__CONFIG___
