#undef ___UTILITY__TRAIT__CONFIG___

#undef __utility_has_has_trivial_destructor
#undef __utility_has_has_virtual_destructor
#undef __utility_has_is_abstract
#undef __utility_has_is_aggregate
#undef __utility_has_is_assignable
#undef __utility_has_is_base_of
#undef __utility_has_is_class
#undef __utility_has_is_constructible
#undef __utility_has_is_empty
#undef __utility_has_is_enum
#undef __utility_has_is_literal
#undef __utility_has_is_pod
#undef __utility_has_is_polymorphic
#undef __utility_has_is_standard_layout
#undef __utility_has_is_trivial
#undef __utility_has_is_trivially_assignable
#undef __utility_has_is_trivially_constructible
#undef __utility_has_is_trivially_copyable
#undef __utility_has_is_union
#undef __utility_has_underlying_type
#undef __utility_support_compile_extension

#ifdef __GNUC__
#undef __utility_has_trivial_destructor
#undef __utility_has_virtual_destructor
#undef __utility_is_abstract
#undef __utility_is_aggregate
#undef __utility_is_assignable
#undef __utility_is_base_of
#undef __utility_is_class
#undef __utility_is_constructible
#undef __utility_is_empty
#undef __utility_is_enum
#undef __utility_is_literal
#undef __utility_is_pod
#undef __utility_is_polymorphic
#undef __utility_is_standard_layout
#undef __utility_is_trivial
#undef __utility_is_trivially_assignable
#undef __utility_is_trivially_constructible
#undef __utility_is_trivially_copyable
#undef __utility_is_union
#undef __utility_underlying_type
#undef ___UTILITY__TRAIT__GNU__CONFIG___
#endif // ! __GNUC__

#ifdef _MSC_VER
#undef __utility_has_trivial_destructor
#undef __utility_has_virtual_destructor
#undef __utility_is_abstract
#undef __utility_is_aggregate
#undef __utility_is_assignable
#undef __utility_is_base_of
#undef __utility_is_class
#undef __utility_is_constructible
#undef __utility_is_empty
#undef __utility_is_enum
#undef __utility_is_pod
#undef __utility_is_polymorphic
#undef __utility_is_union
#undef ___UTILITY__TRAIT__MSVC__CONFIG___
#endif // ! _MSC_VER

#ifdef __clang__
#undef __utility_has_trivial_destructor
#undef __utility_has_virtual_destructor
#undef __utility_is_abstract
#undef __utility_is_aggregate
#undef __utility_is_assignable
#undef __utility_is_base_of
#undef __utility_is_class
#undef __utility_is_constructible
#undef __utility_is_empty
#undef __utility_is_enum
#undef __utility_is_literal
#undef __utility_is_pod
#undef __utility_is_polymorphic
#undef __utility_is_trivially_assignable
#undef __utility_is_trivially_constructible
#undef __utility_is_union
#undef __utility_underlying_type
#undef ___UTILITY__TRAIT__CLANG__CONFIG___
#endif // ! __clang__

#ifndef __UTILITY_NO_CPP14__
# undef __utility_support_compile_cpp14_extension
# undef __utility_has_is_final
# undef __utility_is_final
#endif // ! __UNILITY_NO_CPP14__
