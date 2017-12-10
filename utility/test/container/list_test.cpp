#define UTILITY_DEBUG

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<utility/container/list.hpp>
#include<utility/algorithm/is_sorted.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/miscellaneous/ignore_unused.hpp>

using namespace utility::container;


inline void test_attribute()
{
  using utility::trait::type::releations::is_same;
  using utility::memory::allocator;
  using utility::memory::allocator_traits;
  using utility::iterator::bidirectional_iterator_tag;
  typedef typename list<int>::iterator iterator;
  typedef typename list<int>::const_iterator const_iterator;

  static_assert(is_same<typename list<int>::value_type, int>::value, "value_type");
  static_assert(is_same<typename list<int>::allocator_type, allocator<int>>::value, "allocator_type");
  static_assert(is_same<typename list<int>::size_type, decltype(sizeof(0))>::value, "size_type");
  static_assert(is_same<typename list<int>::difference_type, decltype(0L)>::value, "difference_type");
  static_assert(is_same<typename list<int>::reference, int&>::value, "reference");
  static_assert(is_same<typename list<int>::const_reference, const int&>::value, "const_reference");
  static_assert(is_same<typename list<int>::allocator_traits_type, allocator_traits<allocator<int>>>::value, "allocator_traits_type");
  static_assert(is_same<typename list<int>::pointer, int*>::value, "pointer");
  static_assert(is_same<typename list<int>::const_pointer, const int*>::value, "const_pointer");

  static_assert(is_same<typename iterator::iterator_category, bidirectional_iterator_tag>::value, "iterator::iterator_category");
  static_assert(is_same<typename iterator::value_type, int>::value, "iterator::value_type");
  static_assert(is_same<typename iterator::reference, int&>::value, "iterator::reference");
  static_assert(is_same<typename iterator::pointer, int*>::value, "iterator::pointer");
  static_assert(is_same<typename iterator::difference_type, decltype(0L)>::value, "iterator::difference_type");
  static_assert(is_same<typename iterator::self, iterator>::value, "iterator::difference_type");

  static_assert(is_same<typename const_iterator::iterator_category, bidirectional_iterator_tag>::value, "const_iterator::iterator_category");
  static_assert(is_same<typename const_iterator::value_type, int>::value, "const_iterator::value_type");
  static_assert(is_same<typename const_iterator::const_value_type, const int>::value, "const_iterator::const_value_type");
  static_assert(is_same<typename const_iterator::reference, const int&>::value, "const_iterator::reference");
  static_assert(is_same<typename const_iterator::pointer, const int*>::value, "const_iterator::pointer");
  static_assert(is_same<typename const_iterator::difference_type, decltype(0L)>::value, "const_iterator::difference_type");
  static_assert(is_same<typename const_iterator::self, const_iterator>::value, "const_iterator::self");

  return;
}

void test_construct()
{
  using utility::memory::allocator;

  allocator<int> __u;

  list<int> test1;
  list<int> test2(10);
  list<int> test3(10, 1);
  list<int> test4(test3);
  list<int> test5({1,2,3,4,5});
  list<int> test6(__u);
  list<int> test7(10, __u);
  list<int> test8(10, 1,__u);
  list<int> test9(test3, __u);
  list<int> test10({1,2,3,4,5}, __u);
  assert(test1 == list<int>{});
  assert(test2 == list<int>({0,0,0,0,0,0,0,0,0,0}));
  assert(test3 == list<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(test4 == list<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(test5 == list<int>({1,2,3,4,5}));
  assert(test6 == list<int>{});
  assert(test7 == list<int>({0,0,0,0,0,0,0,0,0,0}));
  assert(test8 == list<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(test9 == list<int>({1,1,1,1,1,1,1,1,1,1}));
  assert(test10 == list<int>({1,2,3,4,5}));

  list<int> test11(::utility::algorithm::move(test5));
  list<int> test12(::utility::algorithm::move(test10), __u);
  assert(test11 == list<int>({1,2,3,4,5}));
  assert(test12 == list<int>({1,2,3,4,5}));

  list<int> test13 = test11;
  list<int> test14 = ::utility::algorithm::move(test11);
  assert(test13 == list<int>({1,2,3,4,5}));
  assert(test14 == list<int>({1,2,3,4,5}));

  printf("Test construct passes\n\n");

  return;
}

void test_insert()
{
  using std::rand;
  using std::printf;
  typedef typename list<int>::iterator iterator;
  typedef typename list<int>::const_iterator const_iterator;

  utility::miscellaneous::ignore_unused<iterator>();

  list<int> test;
  list<int> ins{14052,71205,74962,15453,13968,90023,98948,1256};
  test.push_back(12);
  test.push_back(11);
  test.push_back(10);
  test.emplace_back(1);
  test.emplace_back(6);
  assert(test == list<int>({12,11,10,1,6}));

  test.pop_back();
  test.pop_back();
  assert(test == list<int>({12,11,10}));

  const_iterator vit = test.begin();

  ++vit; ++vit;
  test.insert(vit, ins.begin(), ins.end());
  assert(test == list<int>({12,11,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = test.begin();
  ++vit; ++vit;
  test.insert(vit, 22);
  assert(test == list<int>({12,11,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = test.begin() ;
  ++vit; ++vit;
  test.insert(vit, 10, 20);
  assert(test == list<int>({12,11,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = test.begin();
  ++vit; ++vit;
  test.insert(vit, {54673,98812,61734,78474});
  assert(test == list<int>({12,11,54673,98812,61734,78474,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  vit = test.begin();
  ++vit; ++vit;
  test.emplace(vit, 100);
  assert(test == list<int>({12,11,100,54673,98812,61734,78474,20,20,20,20,20,20,20,20,20,20,22,14052,71205,74962,15453,13968,90023,98948,1256,10}));

  test.clear();
  assert(test == list<int>{});

  printf("Test insert, push_back, pop_back, emplace, emplace_back passes\n\n");

  return;
}

void test_push_front()
{
  using std::printf;

  list<int> test;

  test.push_front(10);
  test.push_front(9);
  test.emplace_front(8);
  assert(test == list<int>({8,9,10}));

  test.pop_front();
  assert(test == list<int>({9,10}));

  printf("Test push_front, emplace_front, pop_front passes\n\n");

  return;
}

void test_remove()
{
  using std::printf;

  list<int> test{10,12,11,14052,71205,74962,15453,13968,90023,98948,1256,10};

  test.remove(10);
  assert(test == list<int>({12,11,14052,71205,74962,15453,13968,90023,98948,1256}));

  test.remove([](const int&)->bool{ return true;});
  assert(test == list<int>{});

  printf("Test remove passes\n\n");

  return;
}

void test_front()
{
  using std::printf;

  list<int> test{14052,71205,74962,15453,13968,90023,98948,1256};

  int x = test.front();
  const int _x = test.front();
  assert(x == 14052);
  assert(_x == 14052);

  int y = test.back();
  const int _y = test.back();
  assert(y == 1256);
  assert(_y == 1256);

  printf("Test front and back passes\n\n");

  return;
}

void test_splice()
{
  using std::printf;
  typedef typename list<int>::const_iterator const_iterator;

  list<int> test{14052,71205,74962,15453,13968,90023,98948,1256};
  list<int> ins{73799,65703,30058,65677,83362,70219,36602,48771,17537,68428,40010,50204,82012,99793,7790,30558,99704,76616};

  const_iterator iit = ins.begin();
  const_iterator tit = test.begin();

  test.splice(tit, ins, ins.end().operator--().operator--());
  assert(test == list<int>({99704,14052,71205,74962,15453,13968,90023,98948,1256}));
  assert(ins == list<int>({73799,65703,30058,65677,83362,70219,36602,48771,17537,68428,40010,50204,82012,99793,7790,30558,76616}));

  test.splice(tit, ins, ins.end().operator--().operator--(), ins.end());
  assert(test == list<int>({99704,30558,76616,14052,71205,74962,15453,13968,90023,98948,1256}));
  assert(ins == list<int>({73799,65703,30058,65677,83362,70219,36602,48771,17537,68428,40010,50204,82012,99793,7790}));

  test.splice(tit, ins);
  assert(test == list<int>({99704,30558,76616,73799,65703,30058,65677,83362,70219,36602,48771,17537,68428,40010,50204,82012,99793,7790,14052,71205,74962,15453,13968,90023,98948,1256}));
  assert(ins == list<int>{});

  printf("Test splice passes\n\n");

  return;
}

void test_erase()
{
  list<int> test{14052,71205,74962,15453,13968,90023,98948,1256};
  assert(test == list<int>({14052,71205,74962,15453,13968,90023,98948,1256}));

  test.erase(test.begin());
  test.erase(test.begin());
  test.erase(test.begin());

  assert(test == list<int>({15453,13968,90023,98948,1256}));
  test.erase(test.begin(), test.end());
  assert(test == list<int>{});

  printf("Test erase passes\n\n");

  return;
}

void test_sort()
{
  using std::printf;
  using std::rand;
  using utility::algorithm::is_sorted;

  list<int> test;
  for(int i = 0; i < 1000; ++i)
  { test.push_back(rand() % 10000);}

  test.sort();
  assert(test.size() == 1000);
  assert(is_sorted(test.begin(), test.end()));

  printf("Test sort passes\n\n");

  return;
}

void test_size()
{
  list<int> test{14052,71205,74962,15453,13968,90023,98948,1256};
  assert(test == list<int>({14052,71205,74962,15453,13968,90023,98948,1256}));

  assert(test.size() == 8);

  test.clear();
  assert(test.size() == 0);

  list<int> tmp;
  tmp.assign(test.begin(), test.end());
  assert(tmp == list<int>{});

  tmp.assign(10, 20);
  assert(tmp == list<int>({20,20,20,20,20,20,20,20,20,20}));

  test.resize(10);
  assert(test.size() == 10);
  assert(test == list<int>({0,0,0,0,0,0,0,0,0,0}));

  test.resize(12, 1);
  assert(test.size() == 12);
  assert(test == list<int>({0,0,0,0,0,0,0,0,0,0,1,1}));

  printf("Test size passes\n\n");

  return;
}

int main()
{
  test_attribute();
  test_construct();
  test_insert();
  test_push_front();
  test_remove();
  test_splice();
  test_front();
  test_erase();
  test_size();
  test_sort();
}
