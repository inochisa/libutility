#include<utility/trait/type/type_relations.hpp>
#include<iostream>

struct __test_par
{ };
struct __test_child : public __test_par
{ };

int main()
{
  using namespace utility::trait::type::releations;
  using std::cout;

  cout << "is_same" << "\n";
  cout << "int, int "
       << is_same<int, int>::value
       << "\n";
  cout << "int, const int "
       << is_same<int, const int>::value
       << "\n";
  cout << "\n";

  cout << "is_base_of" << "\n";
  cout << "int, int "
       << is_base_of<int, int>::value
       << "\n";
  cout << "__test_child, __test_par "
       << is_base_of<__test_child, __test_par>::value
       << "\n";
  cout << "__test_par, __test_child "
       << is_base_of<__test_par, __test_child>::value
       << "\n";
  cout << "__test_par, const __test_child "
       << is_base_of<__test_par, const __test_child>::value
       << "\n";
  cout << "__test_par&, __test_child& "
       << is_base_of<__test_par&, __test_child&>::value
       << "\n";
  cout << "\n";

  cout << "is_convertible" << "\n";
  cout << "int -> int "
       << is_convertible<int, int>::value
       << "\n";
  cout << "const int& -> int "
       << is_convertible<const int&, int>::value
       << "\n";
  cout << "int[] -> int* "
       << is_convertible<int[], int*>::value
       << "\n";
  cout << "int* -> int[] "
       << is_convertible<int*, int[]>::value
       << "\n";
  cout << "int -> double "
       << is_convertible<int, double>::value
       << "\n";
  cout << "double -> int "
       << is_convertible<double, int>::value
       << "\n";
  cout << "__test_child -> __test_par "
       << is_convertible<__test_child, __test_par>::value
       << "\n";
  cout << "__test_par -> __test_child "
       << is_convertible<__test_par, __test_child>::value
       << "\n";

  return 0;
}
