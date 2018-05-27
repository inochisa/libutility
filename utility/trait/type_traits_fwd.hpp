
#ifndef __UTILITY_TRAIT_TYPE_FWD__
#define __UTILITY_TRAIT_TYPE_FWD__

namespace utility
{
  namespace trait
  {
    template<typename Type, Type val>
    struct integral_constant;

    namespace type
    {
      namespace categories
      {
        // is_void
        template<typename _T>
        struct is_void;

        // is_null_pointer && is_nullptr_t
        template<typename _T>
        struct is_null_pointer;
        template<typename _T>
        struct is_nullptr_t;

        // is_integral
        template<typename _T>
        struct is_integral;

        // is_floating_point
        template<typename _T>
        struct is_floating_point;

        // is_array
        template<typename _T>
        struct is_array;

        // is_enum
        template<typename _T>
        struct is_enum;

        // is_union
        template<typename _T>
        struct is_union;

        // is_class
        template<typename _T>
        struct is_class;

        // is_function
        template<typename _T>
        struct is_function;

        // is_pointer
        template<typename _T>
        struct is_pointer;

        // is_lvalue_reference
        template<typename _T>
        struct is_lvalue_reference;

        // is_rvalue_reference
        template<typename _T>
        struct is_rvalue_reference;

        // is_member_object_pointer
        template<typename _T>
        struct is_member_object_pointer;

        // is_member_function_pointer
        template<typename _T>
        struct is_member_function_pointer;

        // is_fundamental
        template<typename _T>
        struct is_fundamental;

        // is_arithmetic
        template<typename _T>
        struct is_arithmetic;

        // is_scalar
        template<typename _T>
        struct is_scalar;

        // is_object
        template<typename _T>
        struct is_object;

        // is_compound
        template<typename _T>
        struct is_compound;

        // is_reference
        template<typename _T>
        struct is_reference;

        // is_member_pointer
        template<typename _T>
        struct is_member_pointer;

      }

      namespace property
      {
        // is_const
        template<typename _T>
        struct is_const;

        // is_volatile
        template<typename _T>
        struct is_volatile;

        // is_trivial
        template<typename _T>
        struct is_trivial;

        // is_trivially_copyable
        template<typename _T>
        struct is_trivially_copyable;

        // is_standard_layout
        template<typename _T>
        struct is_standard_layout;

        // is_pod
        template<typename _T>
        struct is_pod;

        // is_literal_type
        template<typename _T>
        struct is_literal_type;

        // has_unique_object_representations
        template<typename _T>
        struct has_unique_object_representations;

        // is_empty
        template<typename _T>
        struct is_empty;

        // is_polymorphic
        template<typename _T>
        struct is_polymorphic;

        // is_abstract
        template<typename _T>
        struct is_abstract;

#ifndef __UTILITY_NO_CPP14__
        // is_final
        template<typename _T>
        struct is_final;
#endif // ! __UTILITY_NO_CPP14__

        // is_aggregate
        template<typename _T>
        struct is_aggregate;

        // is_signed
        template<typename _T>
        struct is_signed;

        // is_unsigned
        template<typename _T>
        struct is_unsigned;

      }

      namespace property_query
      {
        // extent
        template<typename _T, unsigned int I = 0>
        struct extent;

        // rank
        template<typename _T>
        struct rank;

        // alignment_of
        template<typename _T>
        struct alignment_of;

      }

      namespace features
      {
        // is_constructible
        template<class _T, class... Args>
        struct is_constructible;

        // is_trivially_constructible
        template<class _T, class... Args>
        struct is_trivially_constructible;

        // is_nothrow_constructible
        template<class _T, class... Args>
        struct is_nothrow_constructible;

        // is_default_constructible
        template<typename _T>
        struct is_default_constructible;

        // is_trivially_default_constructible
        template<typename _T>
        struct is_trivially_default_constructible;

        // is_nothrow_default_constructible
        template<typename _T>
        struct is_nothrow_default_constructible;

        // is_copy_constructible
        template<typename _T>
        struct is_copy_constructible;

        // is_trivially_copy_constructible
        template<typename _T>
        struct is_trivially_copy_constructible;

        // is_nothrow_copy_constructible
        template<typename _T>
        struct is_nothrow_copy_constructible;

        // is_move_constructible
        template<typename _T>
        struct is_move_constructible;

        // is_trivially_move_constructible
        template<typename _T>
        struct is_trivially_move_constructible;

        // is_nothrow_move_constructible
        template<typename _T>
        struct is_nothrow_move_constructible;

        // is_assignable
        template<typename _T, typename U>
        struct is_assignable;

        // is_trivially_assignable
        template<typename _T, typename U>
        struct is_trivially_assignable;

        // is_nothrow_assignable
        template<typename _T, typename U>
        struct is_nothrow_assignable;

        // is_copy_assignable
        template<typename _T>
        struct is_copy_assignable;

        // is_trivially_copy_assignable
        template<typename _T>
        struct is_trivially_copy_assignable;

        // is_nothrow_copy_assignable
        template<typename _T>
        struct is_nothrow_copy_assignable;

        // is_move_assignable
        template<typename _T>
        struct is_move_assignable;

        // is_trivially_move_assignable
        template<typename _T>
        struct is_trivially_move_assignable;

        // is_nothrow_move_assignable
        template<typename _T>
        struct is_nothrow_move_assignable;

        // is_destructible
        template<typename _T>
        struct is_destructible;

        // is_trivially_destructible
        template<typename _T>
        struct is_trivially_destructible;

        // is_nothrow_destructible
        template<typename _T>
        struct is_nothrow_destructible;

        // has_virtual_destructor
        template<typename _T>
        struct has_virtual_destructor;

        // is_swappable_with
        template<typename _T, typename U>
        struct is_swappable_with;

        // is_swappable
        template<typename _T, typename U>
        struct is_swappable;

        // is_nothrow_swappable_with
        template<typename _T, typename U>
        struct is_nothrow_swappable_with;

        // is_nothrow_swappable
        template<typename _T, typename U>
        struct is_nothrow_swappable;

      }

      namespace releations
      {
        // is_same
        template<typename _T1, typename _T2>
        struct is_same;

        // is_convertible
        template<typename _T1, typename _T2>
        struct is_convertible;

        // is_base_of
        template<typename _T1, typename _T2>
        struct is_base_of;

        // is_invocable
        template<class Fn, class... ArgTypes>
        struct is_invocable;

        // is_invocable_r
        template<class R, class Fn, class... ArgTypes>
        struct is_invocable_r;

        // is_nothrow_invocable
        template<class Fn, class... ArgTypes>
        struct is_nothrow_invocable;

        // is_nothrow_invocable_r
        template<class R, class Fn, class... ArgTypes>
        struct is_nothrow_invocable_r;

      }


      namespace transform
      {
        // remove_const
        template<typename _T>
        struct remove_const;

        // remove_volatile
        template<typename _T>
        struct remove_volatile;

        // remove_cv
        template<typename _T>
        struct remove_cv;

        // add_const
        template<typename _T>
        struct add_const;

        // add_volatile
        template<typename _T>
        struct add_volatile;

        // add_cv
        template<typename _T>
        struct add_cv;

        // remove_reference
        template<typename _T>
        struct remove_reference;

        // add_lvalue_reference
        template<typename _T>
        struct add_lvalue_reference;

        // add_rvalue_reference
        template<typename _T>
        struct add_rvalue_reference;

        // remove_pointer
        template<typename _T>
        struct remove_pointer;

        // add_pointer
        template<typename _T>
        struct add_pointer;

        // remove_extent
        template<typename _T>
        struct remove_extent;

        // remove_all_extents
        template<typename _T>
        struct remove_all_extents;

        // decay
        template<typename _T>
        struct decay;

      }

      namespace operations
      {
        // conjunction
        template<class... B>
        struct conjunction;

        // disjunction
        template<class... B>
        struct disjunction;

        // negation
        template<class B>
        struct negation;
      }

      namespace miscellaneous
      {
        // make_signed
        template<typename _T>
        struct make_signed;

        // make_unsigned
        template<typename _T>
        struct make_unsigned;

        // aligned_storage
        template<size_t  Len, size_t Align>
        struct aligned_storage;

        // aligned_union
        template<size_t  Len, typename... Ts>
        struct aligned_union;

        // enable_if
        template<bool B, typename _T = void>
        struct enable_if;

        // conditional
        template<bool B, typename _T, typename F>
        struct conditional;

        // common_type
        template<typename... Ts>
        struct common_type;

        // underlying_type
        template<typename _T>
        struct underlying_type;

        // result_of
        template<class F, typename... ArgTypes>
        class result_of;

        // invoke_result
        template<class F, typename... ArgTypes>
        class invoke_result;

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FWD__
