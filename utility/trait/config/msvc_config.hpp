
#ifndef ___UTILITY__TRAIT__MSVC__CONFIG___
#define ___UTILITY__TRAIT__MSVC__CONFIG___

#define __utility_support_compile_extension 1
#define __utility_has_has_trivial_destructor 1
#define __utility_has_has_virtual_destructor 1
#define __utility_has_is_abstract 1
#define __utility_has_is_aggregate 1
#define __utility_has_is_assignable 1
#define __utility_has_is_base_of 1
#define __utility_has_is_class 1
#define __utility_has_is_constructible 1
#define __utility_has_is_empty 1
#define __utility_has_is_enum 1
#define __utility_has_is_literal 0
#define __utility_has_is_pod 1
#define __utility_has_is_polymorphic 1
#define __utility_has_is_standard_layout 0
#define __utility_has_is_trivial 0
#define __utility_has_is_trivially_assignable 0
#define __utility_has_is_trivially_constructible 0
#define __utility_has_is_trivially_copyable 0
#define __utility_has_is_union 1
#define __utility_has_underlying_type 0

#define __utility_has_trivial_destructor(type) __has_trivial_destructor(type)
#define __utility_has_virtual_destructor(type) __has_virtual_destructor(type)
#define __utility_is_abstract(type) __is_abstract(type)
#define __utility_is_aggregate(type) __is_aggregate(type)
#define __utility_is_assignable(type1, type2) __is_assignable(type1, type2)
#define __utility_is_base_of(type1, type2) __is_base_of(type1, type2)
#define __utility_is_class(type) __is_class(type)
#define __utility_is_constructible(...) __is_constructible(__VA_ARGS__)
#define __utility_is_empty(type) __is_empty(type)
#define __utility_is_enum(type) __is_enum(type)
#define __utility_is_pod(type) __is_pod(type)
#define __utility_is_polymorphic(type) __is_polymorphic(type)
#define __utility_is_union(type) __is_union(type)

#endif // ! ___UTILITY__TRAIT__MSVC__CONFIG___
