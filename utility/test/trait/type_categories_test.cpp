#include<utility/trait/type/type_categories.hpp>
#include<iostream>

namespace
{

  struct __test_struct
  {
    int __test_struct_val;
  };

  union __test_union
  {
    int x;
    double t;
  };

  class __test_class
  {
    public:
      void __test_class_func()
      { }
  };

  enum __test_enum
  { first, second, third};
  enum class __test_enum_class
  { alpha, beta, gamma};


  void __test_func(int)
  { }

  void(* __test_func_pointer)(int)  = __test_func;
  struct __test_fuc_struct
  {
    void operator()()
    { }
  };
  __test_fuc_struct __test_fuc_structer;

  int __test_array[2];

}
typedef decltype(nullptr) nullptr_t;

int main()
{
  using namespace utility::trait::type::categories;
  using std::cout;

  cout << "is_void" << "\n";
  cout << "int " << is_void<int>::value << "\n";
  cout << "nullptr_t " << is_void<nullptr_t>::value << "\n";
  cout << "void " << is_void<void>::value << "\n";
  cout << "\n";

  cout << "is_null_pointer && is_nullptr_t" << "\n";
  cout << "nullptr_t " << is_null_pointer<nullptr_t>::value << "\n";
  cout << "nullptr_t " << is_nullptr_t<nullptr_t>::value << "\n";
  cout << "int " << is_null_pointer<int>::value << "\n";
  cout << "int " << is_nullptr_t<int>::value << "\n";
  cout << "\n";

  cout << "is_integral" << "\n";
  cout << "bool " << is_integral<bool>::value << "\n";
  cout << "char " << is_integral<char>::value << "\n";
  cout << "signed char " << is_integral<signed char>::value << "\n";
  cout << "unsigned char " << is_integral<unsigned char>::value << "\n";
  cout << "signed short " << is_integral<signed short>::value << "\n";
  cout << "unsigned short " << is_integral<unsigned short>::value << "\n";
  cout << "int " << is_integral<int>::value << "\n";
  cout << "signed int " << is_integral<signed int>::value << "\n";
  cout << "unsigned int " << is_integral<unsigned int>::value << "\n";
  cout << "signed long " << is_integral<signed long>::value << "\n";
  cout << "unsigned long " << is_integral<unsigned long>::value << "\n";
  cout << "signed long long "
       << is_integral<signed long long>::value << "\n";
  cout << "unsigned long long " << is_integral<unsigned long long>::value << "\n";
  cout << "wchar_t " << is_integral<wchar_t>::value << "\n";
  cout << "float " << is_integral<float>::value << "\n";
  cout << "\n";

  cout << "is_floating_point" << "\n";
  cout << "float " << is_floating_point<float>::value << "\n";
  cout << "double " << is_floating_point<float>::value << "\n";
  cout << "long double " << is_floating_point<float>::value << "\n";
  cout << "\n";

  cout << "is_array" << "\n";
  cout << "__test_array "
       << is_array<decltype(__test_array)>::value << "\n";
  cout << "int[] " << is_array<int[]>::value << "\n";
  cout << "int[3] " << is_array<int[3]>::value << "\n";
  cout << "\n";

  cout << "is_enum" << "\n";
  cout << "__test_enum " << is_enum<__test_enum>::value << "\n";
  cout << "__test_enum_class "
       << is_enum<__test_enum_class>::value << "\n";
  cout << "\n";

  cout << "is_union" << "\n";
  cout << "__test_class " << is_union<__test_struct>::value << "\n";
  cout << "__test_union " << is_union<__test_union>::value << "\n";
  cout << "\n";

  cout << "is_class" << "\n";
  cout << "__test_class " << is_class<__test_struct>::value << "\n";
  cout << "__test_union " << is_class<__test_union>::value << "\n";
  cout << "\n";

  cout << "is_function" << "\n";
  cout << "__test_func "
       << is_function<decltype(__test_func)>::value << "\n";
  cout << "__test_func_pointer "
       << is_function<decltype(__test_func_pointer)>::value << "\n";
  cout << "__test_fuc_structer "
       << is_function<decltype(__test_fuc_structer)>::value << "\n";
  cout << "int(int) " << is_function<int(int)>::value << "\n";
  cout << "int(*)(int) " << is_function<int(*)(int)>::value << "\n";
  cout << "\n";

  cout << "is_pointer" << "\n";
  cout << "int " << is_pointer<int>::value << "\n";
  cout << "int* " << is_pointer<int*>::value << "\n";
  cout << "int& " << is_pointer<int&>::value << "\n";
  cout << "int&& " << is_pointer<int&&>::value << "\n";
  cout << "\n";

  cout << "is_reference" << "\n";
  cout << "int " << is_reference<int>::value << "\n";
  cout << "int* " << is_reference<int*>::value << "\n";
  cout << "int& " << is_reference<int&>::value << "\n";
  cout << "int&& " << is_reference<int&&>::value << "\n";
  cout << "\n";

  cout << "is_lvalue_reference" << "\n";
  cout << "int " << is_lvalue_reference<int>::value << "\n";
  cout << "int* " << is_lvalue_reference<int*>::value << "\n";
  cout << "int& " << is_lvalue_reference<int&>::value << "\n";
  cout << "int&& " << is_lvalue_reference<int&&>::value << "\n";
  cout << "\n";

  cout << "is_rvalue_reference" << "\n";
  cout << "int " << is_rvalue_reference<int>::value << "\n";
  cout << "int* " << is_rvalue_reference<int*>::value << "\n";
  cout << "int& " << is_rvalue_reference<int&>::value << "\n";
  cout << "int&& " << is_rvalue_reference<int&&>::value << "\n";
  cout << "\n";

  cout << "is_member_object_pointer" << "\n";
  cout << "__test_class::* "
       << is_member_object_pointer<int(__test_class::*)>::value << "\n";
  cout << "__test_class::*() "
       << is_member_object_pointer<int(__test_class::*)()>::value << "\n";
  cout << "\n";

  cout << "is_member_function_pointer" << "\n";
  cout << "__test_class::__test_class_func "
       << is_member_function_pointer<
          decltype(&__test_class::__test_class_func)>::value << "\n";
  cout << "\n";

  cout << "is_fundamental" << "\n";
  cout << "int " << is_fundamental<int>::value << "\n";
  cout << "short " << is_fundamental<short>::value << "\n";
  cout << "nullptr_t " << is_fundamental<nullptr_t>::value << "\n";
  cout << "char " << is_fundamental<char>::value << "\n";
  cout << "short " << is_fundamental<short>::value << "\n";
  cout << "float " << is_fundamental<float>::value << "\n";
  cout << "void " << is_fundamental<void>::value << "\n";
  cout << "__test_union " << is_fundamental<__test_union>::value << "\n";
  cout << "\n";

  cout << "is_arithmetic" << "\n";
  cout << "int " << is_arithmetic<int>::value << "\n";
  cout << "float " << is_arithmetic<float>::value << "\n";
  cout << "\n";

  cout << "is_scalar" << "\n";
  cout << "nullptr_t " << is_scalar<nullptr_t>::value << "\n";
  cout << "int " << is_scalar<int>::value << "\n";
  cout << "float " << is_scalar<float>::value << "\n";
  cout << "int* " << is_scalar<int*>::value << "\n";
  cout << "__test_class::* "
       << is_scalar<int(__test_class::*)>::value << "\n";
  cout << "__test_class::__test_class_func "
       << is_scalar<decltype(&__test_class::__test_class_func)>::value
       << "\n";
  cout << "__test_enum_class "
       << is_scalar<__test_enum_class>::value << "\n";
  cout << "\n";

  cout << "is_object" << "\n";
  cout << "nullptr_t " << is_object<nullptr_t>::value << "\n";
  cout << "int " << is_object<int>::value << "\n";
  cout << "float " << is_object<float>::value << "\n";
  cout << "int* " << is_object<int*>::value << "\n";
  cout << "__test_class::* "
       << is_object<int(__test_class::*)>::value << "\n";
  cout << "__test_class::__test_class_func "
       << is_object<decltype(&__test_class::__test_class_func)>::value
       << "\n";
  cout << "__test_enum_class "
       << is_object<__test_enum_class>::value << "\n";
  cout << "__test_class* " << is_object<__test_class*>::value << "\n";
  cout << "__test_class " << is_object<__test_class>::value << "\n";
  cout << "__test_union " << is_object<__test_union>::value << "\n";
  cout << "int[] " << is_object<int[]>::value << "\n";
  cout << "int[3] " << is_object<int[3]>::value << "\n";
  cout << "__test_array "
       << is_object<decltype(__test_array)>::value << "\n";
  cout << "\n";

  cout << "is_compound" << "\n";
  cout << "int " << is_compound<int>::value << "\n";
  cout << "short " << is_compound<short>::value << "\n";
  cout << "nullptr_t " << is_compound<nullptr_t>::value << "\n";
  cout << "char " << is_compound<char>::value << "\n";
  cout << "short " << is_compound<short>::value << "\n";
  cout << "float " << is_compound<float>::value << "\n";
  cout << "void " << is_compound<void>::value << "\n";
  cout << "__test_union " << is_compound<__test_union>::value << "\n";
  cout << "\n";

  cout << "is_member_pointer" << "\n";
  cout << "int __test_struct::* "
       << is_member_pointer<int __test_struct::*>::value << "\n";
  cout << "void(__test_struct::*)() "
       << is_member_pointer<void(__test_struct::*)()>::value << "\n";
  cout << "&__test_struct::__test_struct_val "
       << is_member_pointer<
          decltype(&__test_struct::__test_struct_val)>::value << "\n";
  cout << "\n";

  return 0;
}
