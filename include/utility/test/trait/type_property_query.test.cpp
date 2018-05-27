#include<utility/trait/type/type_property_query.hpp>
#include<iostream>

int main()
{
  using namespace utility::trait::type::property_query;
  using std::cout;

  cout << "extent" << "\n";
  cout << "int[][10][24](0th dimension) "
       << extent<int[][10][24], 0>::value << "\n";
  cout << "int[][10][24](1th dimension) "
       << extent<int[][10][24], 1>::value << "\n";
  cout << "int[][10][24](2th dimension) "
       << extent<int[][10][24], 2>::value << "\n";
  cout << "int[][10][24](3th dimension) "
       << extent<int[][10][24], 3>::value << "\n";
  cout << "\n";

  cout << "rank" << "\n";
  cout << "int[][10][10] " << rank<int[][10][10]>::value << "\n";
  cout << "int[][10] " << rank<int[][10]>::value << "\n";
  cout << "int[] " << rank<int[]>::value << "\n";
  cout << "int " << rank<int>::value << "\n";
  cout << "\n";

  cout << "alignment_of" << "\n";
  cout << "int " << alignment_of<int>::value << "\n";
  cout << "char " << alignment_of<char>::value << "\n";
  cout << "long long " << alignment_of<long long>::value << "\n";
  cout << "int[] " << alignment_of<int[]>::value << "\n";
  cout << "int[10] " << alignment_of<int[10]>::value << "\n";
  cout << "int* " << alignment_of<int*>::value << "\n";

  return 0;
}
