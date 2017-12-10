#include<utility/trait/type/type_transform.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<iostream>

int main()
{
  using namespace utility::trait::type::transform;
  using utility::trait::type::releations::is_same;
  using std::cout;

  cout << "remove_const " << "\n";
  cout << "const int -> int "
       << is_same<remove_const<const int>::type, int>::value << "\n";
  cout << "const int* -> int* "
       << is_same<remove_const<const int*>::type, int*>::value << "\n";
  cout << "const int* -> const int* "
       << is_same<remove_const<const int*>::type, const int*>::value
       << "\n";
  cout << "int* const-> int* "
       << is_same<remove_const<int* const>::type, int*>::value << "\n";
  cout << "\n";

  cout << "remove_volatile" << "\n";
  cout << "volatile int -> int "
       << is_same<remove_volatile<volatile int>::type, int>::value
       << "\n";
  cout << "volatile int* -> int* "
       << is_same<remove_volatile<volatile int*>::type, int*>::value
       << "\n";
  cout << "volatile int* -> volatile int* "
       << is_same<remove_volatile<volatile int*>::type, volatile int*>::value
       << "\n";
  cout << "int* volatile-> int* "
       << is_same<remove_volatile<int* volatile>::type, int*>::value
       << "\n";
  cout << "\n";

  cout << "remove_cv" << "\n";
  cout << "const int -> int "
       << is_same<remove_cv<const int>::type, int>::value << "\n";
  cout << "const int* -> int* "
       << is_same<remove_cv<const int*>::type, int*>::value << "\n";
  cout << "const int* -> const int* "
       << is_same<remove_cv<const int*>::type, const int*>::value
       << "\n";
  cout << "int* const-> int* "
       << is_same<remove_cv<int* const>::type, int*>::value << "\n";
  cout << "volatile int -> int "
       << is_same<remove_cv<volatile int>::type, int>::value
       << "\n";
  cout << "volatile int* -> int* "
       << is_same<remove_cv<volatile int*>::type, int*>::value
       << "\n";
  cout << "volatile int* -> volatile int* "
       << is_same<remove_cv<volatile int*>::type, volatile int*>::value
       << "\n";
  cout << "int* volatile-> int* "
       << is_same<remove_cv<int* volatile>::type, int*>::value
       << "\n";
  cout << "const volatile int -> int "
       << is_same<remove_cv<const volatile int>::type, int>::value
       << "\n";
  cout << "const volatile int* -> int* "
       << is_same<remove_cv<const volatile int*>::type, int*>::value
       << "\n";
  cout << "const volatile int* -> const volatile int* "
       << is_same<remove_cv<const volatile int*>::type, const volatile int*>::value
       << "\n";
  cout << "int* const volatile -> int* "
       << is_same<remove_cv<int* const volatile>::type, int*>::value
       << "\n";
  cout << "\n";

  cout << "add_const" << "\n";
  cout << "int -> const int "
       << is_same<add_const<int>::type, const int>::value
       << "\n";
  cout << "int* -> const int* "
       << is_same<add_const<int*>::type, const int*>::value
       << "\n";
  cout << "int* -> int* const "
       << is_same<add_const<int*>::type, int* const>::value
       << "\n";
  cout << "const int -> const int "
       << is_same<add_const<const int>::type, const int>::value
       << "\n";
  cout << "const int* -> const int* "
       << is_same<add_const<const int*>::type, const int*>::value
       << "\n";
  cout << "const int* -> const int* const "
       << is_same<add_const<const int*>::type, const int* const>::value
       << "\n";
  cout << "int* const-> int* const "
       << is_same<add_const<int* const>::type, int* const>::value
       << "\n";
  cout << "\n";

  cout << "add_volatile" << "\n";
  cout << "int -> volatile int "
       << is_same<add_volatile<int>::type, volatile int>::value
       << "\n";
  cout << "int* -> volatile int* "
       << is_same<add_volatile<int*>::type, volatile int*>::value
       << "\n";
  cout << "int* -> int* volatile "
       << is_same<add_volatile<int*>::type, int* volatile>::value
       << "\n";
  cout << "volatile int -> volatile int "
       << is_same<add_volatile<volatile int>::type, volatile int>::value
       << "\n";
  cout << "volatile int* -> volatile int* "
       << is_same<add_volatile<volatile int*>::type, volatile int*>::value
       << "\n";
  cout << "volatile int* -> volatile int* volatile "
       << is_same<add_volatile<volatile int*>::type, volatile int* volatile>::value
       << "\n";
  cout << "int* volatile-> int* volatile "
       << is_same<add_volatile<int* volatile>::type, int* volatile>::value
       << "\n";
  cout << "\n";

  cout << "add_cv" << "\n";
  cout << "int -> const volatile int "
       << is_same<add_cv<int>::type, const volatile int>::value
       << "\n";
  cout << "int* -> const volatile int* "
       << is_same<add_cv<int*>::type, const volatile int*>::value
       << "\n";
  cout << "int* -> int* const volatile "
       << is_same<add_cv<int*>::type, int* const volatile>::value
       << "\n";
  cout << "const int* -> const int* const volatile "
       << is_same<add_cv<const int*>::type, const int* const volatile>::value
       << "\n";
  cout << "volatile int* -> volatile int* const volatile "
       << is_same<add_cv<volatile int*>::type, volatile int* const volatile>::value
       << "\n";
  cout << "const volatile int* -> const volatile int* const volatile "
       << is_same<add_cv<const volatile int*>::type, const volatile int* const volatile>::value
       << "\n";
  cout << "\n";

  cout << "remove_reference" << "\n";
  cout << "int -> int "
       << is_same<remove_reference<int>::type, int>::value
       << "\n";
  cout << "int& -> int "
       << is_same<remove_reference<int&>::type, int>::value
       << "\n";
  cout << "int&& -> int "
       << is_same<remove_reference<int&&>::type, int>::value
       << "\n";
  cout << "int(int) -> int(int) "
       << is_same<remove_reference<int(&&)(int)>::type, int(int)>::value
       << "\n";
  cout << "\n";

  cout << "add_lvalue_reference" << "\n";
  cout << "int -> int& "
       << is_same<add_lvalue_reference<int>::type, int&>::value
       << "\n";
  cout << "int& -> int& "
       << is_same<add_lvalue_reference<int&>::type, int&>::value
       << "\n";
  cout << "int&& -> int& "
       << is_same<add_lvalue_reference<int&&>::type, int&>::value
       << "\n";
  cout << "int(int) -> int(int) "
       << is_same<add_lvalue_reference<int(int)>::type, int(&)(int)>::value
       << "\n";
  cout << "int(int) -> int(int) "
       << is_same<add_lvalue_reference<int(*)(int)>::type, int(*&)(int)>::value
       << "\n";
  cout << "void -> void "
       << is_same<add_lvalue_reference<void>::type, void>::value
       << "\n";
  cout << "\n";

  cout << "add_rvalue_reference" << "\n";
  cout << "int -> int& "
       << is_same<add_rvalue_reference<int>::type, int&>::value
       << "\n";
  cout << "int& -> int& "
       << is_same<add_rvalue_reference<int&>::type, int&>::value
       << "\n";
  cout << "int&& -> int& "
       << is_same<add_rvalue_reference<int&&>::type, int&>::value
       << "\n";
  cout << "int(int) -> int(int) "
       << is_same<add_rvalue_reference<int(int)>::type, int(&&)(int)>::value
       << "\n";
  cout << "int(int) -> int(int) "
       << is_same<add_rvalue_reference<int(*)(int)>::type, int(*&&)(int)>::value
       << "\n";
  cout << "void -> void "
       << is_same<add_rvalue_reference<void>::type, void>::value
       << "\n";
  cout << "\n";

  cout << "remove_pointer" << "\n";
  cout << "int* -> int "
       << is_same<remove_pointer<int*>::type, int>::value
       << "\n";
  cout << "int** -> int* "
       << is_same<remove_pointer<int**>::type, int*>::value
       << "\n";
  cout << "const int* -> int "
       << is_same<remove_pointer<const int*>::type, const int>::value
       << "\n";
  cout << "int* const -> int "
       << is_same<remove_pointer<int* const>::type, int>::value
       << "\n";
  cout << "const int* const -> const int "
       << is_same<remove_pointer<const int* const>::type, const int>::value
       << "\n";
  cout << "const volatile int* const volatile -> const volatile int "
       << is_same<remove_pointer<const volatile int* const volatile>::type, const volatile int>::value
       << "\n";
  cout << "\n";

  cout << "add_pointer" << "\n";
  cout << "int -> int* "
       << is_same<add_pointer<int>::type, int*>::value
       << "\n";
  cout << "const int -> const int* "
       << is_same<add_pointer<const int>::type, const int*>::value
       << "\n";
  cout << "const int -> int* const"
       << is_same<add_pointer<const int>::type, int* const>::value
       << "\n";
  cout << "int& -> int* "
       << is_same<add_pointer<int&>::type, int*>::value
       << "\n";
  cout << "int&& -> int* "
       << is_same<add_pointer<int&&>::type, int*>::value
       << "\n";
  cout << "int(int) -> int(*)(int) "
       << is_same<add_pointer<int(int)>::type, int(*)(int)>::value
       << "\n";
  cout << "\n";

  cout << "remove_extent" << "\n";
  cout << "int[] -> int "
       << is_same<remove_extent<int[]>::type, int>::value
       << "\n";
  cout << "int[][1] -> int[1] "
       << is_same<remove_extent<int[][1]>::type, int[1]>::value
       << "\n";
  cout << "\n";

  cout << "remove_all_extents" << "\n";
  cout << "int[] -> int "
       << is_same<remove_all_extents<int[]>::type, int>::value
       << "\n";
  cout << "int[][] -> int "
       << is_same<remove_all_extents<int[][1]>::type, int>::value
       << "\n";
  cout << "\n";

  cout << "remove_all_pointer" << "\n";
  cout << "int* -> int "
       << is_same<remove_all_pointer<int*>::type, int>::value
       << "\n";
  cout << "const int* -> const int "
       << is_same<remove_all_pointer<const int*>::type, const int>::value
       << "\n";
  cout << "int* const -> int "
       << is_same<remove_all_pointer<int* const>::type, int>::value
       << "\n";
  cout << "const int* const -> const int "
       << is_same<remove_all_pointer<const int* const>::type, const int>::value
       << "\n";
  cout << "const volatile int* const volatile -> const volatile int "
       << is_same<remove_all_pointer<const volatile int* const volatile>::type, const volatile int>::value
       << "\n";
  cout << "int** -> int "
       << is_same<remove_all_pointer<int**>::type, int>::value
       << "\n";
  cout << "const int** -> int "
       << is_same<remove_all_pointer<const int**>::type, const int>::value
       << "\n";
  cout << "int* const* -> int "
       << is_same<remove_all_pointer<int* const*>::type, int>::value
       << "\n";
  cout << "const int* const* -> const int "
       << is_same<remove_all_pointer<const int* const*>::type, const int>::value
       << "\n";
  cout << "\n";

  cout << "remove_cv_reference" << "\n";
  cout << "const int -> int "
       << is_same<remove_cv_reference<const int>::type, int>::value
       << "\n";
  cout << "const int& -> int "
       << is_same<remove_cv_reference<const int&>::type, int>::value
       << "\n";
  cout << "const int&& -> int "
       << is_same<remove_cv_reference<const int&&>::type, int>::value
       << "\n";
  cout << "int(&)(int) -> int(int) "
       << is_same<remove_cv_reference<int(&)(int)>::type, int(int)>::value
       << "\n";
  cout << "\n";

  cout << "remove_all" << "\n";
  cout << "const int* const* volatile* const*[][50] -> int "
       << is_same<remove_all<const int* const* volatile* const*[][50]>::type, int>::value
       << "\n";
  cout << "int*& -> int "
       << is_same<remove_all<int*&>::type, int>::value
       << "\n";
  cout << "\n";

  cout << "decay" << "\n";
  cout << "int& -> int "
       << is_same<decay<int&>::type, int>::value
       << "\n";
  cout << "const int& -> int "
       << is_same<decay<const int&>::type, int>::value
       << "\n";
  cout << "int& -> int "
       << is_same<decay<int&>::type, int>::value
       << "\n";
  cout << "int(int) -> int "
       << is_same<decay<int(int)>::type, int(*)(int)>::value
       << "\n";

  return 0;
}
