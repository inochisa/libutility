#define UTILITY_DEBUG

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<utility/container/vector.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/miscellaneous/ignore_unused.hpp>

using namespace utility::container;


inline void vector_attribute()
{
  using utility::trait::type::releations::is_same;
  using utility::memory::allocator;
  using utility::memory::allocator_traits;
  using utility::iterator::contiguous_iterator_tag;
  typedef typename vector<int>::iterator iterator;
  typedef typename vector<int>::const_iterator const_iterator;

  static_assert(is_same<typename vector<int>::value_type, int>::value, "value_type");
  static_assert(is_same<typename vector<int>::allocator_type, allocator<int>>::value, "allocator_type");
  static_assert(is_same<typename vector<int>::size_type, decltype(sizeof(0))>::value, "size_type");
  static_assert(is_same<typename vector<int>::difference_type, decltype(0L)>::value, "difference_type");
  static_assert(is_same<typename vector<int>::reference, int&>::value, "reference");
  static_assert(is_same<typename vector<int>::const_reference, const int&>::value, "const_reference");
  static_assert(is_same<typename vector<int>::allocator_traits_type, allocator_traits<allocator<int>>>::value, "allocator_traits_type");
  static_assert(is_same<typename vector<int>::pointer, int*>::value, "pointer");
  static_assert(is_same<typename vector<int>::const_pointer, const int*>::value, "const_pointer");

  static_assert(is_same<typename iterator::iterator_category, contiguous_iterator_tag>::value, "iterator::iterator_category");
  static_assert(is_same<typename iterator::value_type, int>::value, "iterator::value_type");
  static_assert(is_same<typename iterator::reference, int&>::value, "iterator::reference");
  static_assert(is_same<typename iterator::pointer, int*>::value, "iterator::pointer");
  static_assert(is_same<typename iterator::difference_type, decltype(0L)>::value, "iterator::difference_type");
  static_assert(is_same<typename iterator::self, iterator>::value, "iterator::difference_type");

  static_assert(is_same<typename const_iterator::iterator_category, contiguous_iterator_tag>::value, "const_iterator::iterator_category");
  static_assert(is_same<typename const_iterator::value_type, const int>::value, "const_iterator::value_type");
  static_assert(is_same<typename const_iterator::non_const_value_type, int>::value, "const_iterator::const_value_type");
  static_assert(is_same<typename const_iterator::reference, const int&>::value, "const_iterator::reference");
  static_assert(is_same<typename const_iterator::pointer, const int*>::value, "const_iterator::pointer");
  static_assert(is_same<typename const_iterator::difference_type, decltype(0L)>::value, "const_iterator::difference_type");
  static_assert(is_same<typename const_iterator::self, const_iterator>::value, "const_iterator::self");

  return;
}

void vector_construct()
{
  using utility::memory::allocator;

  allocator<int> __u;

  vector<int> vec1;
  vector<int> vec2(10);
  vector<int> vec3(10, 1);
  vector<int> vec4(vec3);
  vector<int> vec5({1,2,3,4,5});
  vector<int> vec6(__u);
  vector<int> vec7(10, __u);
  vector<int> vec8(10, 1,__u);
  vector<int> vec9(vec3, __u);
  vector<int> vec10({1,2,3,4,5}, __u);
  assert(vec1 == vector<int>{});
  assert(vec2 == vector<int>({0,0,0,0,0,0,0,0,0,0}));
  assert(vec3 == vector<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(vec4 == vector<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(vec5 == vector<int>({1,2,3,4,5}));
  assert(vec6 == vector<int>{});
  assert(vec7 == vector<int>({0,0,0,0,0,0,0,0,0,0}));
  assert(vec8 == vector<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(vec9 == vector<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(vec10 == vector<int>({1,2,3,4,5}));

  vector<int> vec11(utility::algorithm::move(vec5));
  vector<int> vec12(utility::algorithm::move(vec10), __u);
  assert(vec11 == vector<int>({1,2,3,4,5}));
  assert(vec12 == vector<int>({1,2,3,4,5}));

  vector<int> vec13 = vec11;
  vector<int> vec14 = utility::algorithm::move(vec11);
  assert(vec13 == vector<int>({1,2,3,4,5}));
  assert(vec14 == vector<int>({1,2,3,4,5}));

  printf("Vector construct test passes\n\n");

  return;
}

void vector_insert()
{
  using std::rand;
  using std::printf;
  typedef typename vector<int>::iterator iterator;
  typedef typename vector<int>::const_iterator const_iterator;

  utility::miscellaneous::ignore_unused<iterator>();

  vector<int> vec;
  vector<int> ins{14052,71205,74962,15453,13968,90023,98948,1256};
  vec.push_back(12);
  vec.push_back(11);
  vec.push_back(10);
  vec.emplace_back(1);
  vec.emplace_back(6);
  assert(vec == vector<int>({12,11,10,1,6}));

  vec.pop_back();
  vec.pop_back();
  assert(vec == vector<int>({12,11,10}));

  const_iterator vit = vec.begin();

  vit += 2;
  vec.insert(vit, ins.begin(), ins.end());
  assert(vec == vector<int>({12,11,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = vec.begin() + 2;
  vec.insert(vit, 22);
  assert(vec == vector<int>({12,11,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = vec.begin() + 2;
  vec.insert(vit, 10, 20);
  assert(vec == vector<int>({12,11,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = vec.begin() + 2;
  vec.insert(vit, {54673,98812,61734,78474});
  assert(vec == vector<int>({12,11,54673,98812,61734,78474,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = vec.begin() + 2;
  vec.emplace(vit, 100);
  assert(vec == vector<int>({12,11,100,54673,98812,61734,78474,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vec.clear();
  assert(vec == vector<int>{});

  printf("Vector insert, push_back, pop_back, emplace, emplace_back test passes\n\n");

  return;
}

void vector_front()
{
  using std::printf;

  vector<int> vec{14052,71205,74962,15453,13968,90023,98948,1256};

  int x = vec.front();
  const int _x = vec.front();
  assert(x == 14052);
  assert(_x == 14052);

  int y = vec.back();
  const int _y = vec.back();
  assert(y == 1256);
  assert(_y == 1256);

  printf("Vector front and back test passes\n\n");

  return;
}

void vector_erase()
{
  vector<int> vec{14052,71205,74962,15453,13968,90023,98948,1256};
  assert(vec == vector<int>({14052,71205,74962,15453,13968,90023,98948,1256}));

  vec.erase(vec.begin());
  vec.erase(vec.begin());
  vec.erase(vec.begin());

  assert(vec == vector<int>({15453,13968,90023,98948,1256}));
  vec.erase(vec.begin(), vec.end());
  assert(vec == vector<int>{});

  printf("Vector erase test passes\n\n");

  return;
}

void vector_size()
{
  vector<int> vec{14052,71205,74962,15453,13968,90023,98948,1256};
  assert(vec == vector<int>({14052,71205,74962,15453,13968,90023,98948,1256}));

  assert(vec.size() == 8);

  vec.shrink_to_fit();
  assert(vec.size() == vec.capacity());

  vec.clear();
  assert(vec.size() == 0);
  assert(vec.capacity() == 8);

  vector<int> tmp;
  tmp.assign(vec.begin(), vec.end());
  assert(tmp == vector<int>{});

  tmp.assign(10, 20);
  assert(tmp == vector<int>({20,20,20,20,20,20,20,20,20,20}));

  vec.reserve(200);
  assert(vec.capacity() == 200);

  vec.resize(10);
  assert(vec.size() == 10);
  assert(vec.capacity() == 200);
  assert(vec == vector<int>({0,0,0,0,0,0,0,0,0,0}));

  vec.resize(12, 1);
  assert(vec.size() == 12);
  assert(vec.capacity() == 200);
  assert(vec == vector<int>({0,0,0,0,0,0,0,0,0,0,1,1}));

  printf("Vector size test passes\n\n");
}

int main()
{
  vector_attribute();
  vector_construct();
  vector_insert();
  vector_front();
  vector_erase();
  vector_size();
}
