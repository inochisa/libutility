#define UTILITY_DEBUG

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<utility/container/hash_table.hpp>
#include<utility/container/vector.hpp>
#include<utility/algorithm/all_of.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/memory/unique_ptr.hpp>
#include<utility/memory/allocator.hpp>
#include<utility/memory/allocator_traits.hpp>
#include<utility/iterator/iterator_tag.hpp>
#include<utility/miscellaneous/ignore_unused.hpp>

using namespace utility::container;

inline void test_attribute()
{
  using utility::trait::type::releations::is_same;
  using utility::memory::allocator;
  using utility::memory::allocator_traits;
  using utility::iterator::forward_iterator_tag;
  typedef hash_table<long, int>::iterator iterator;
  typedef hash_table<long, int>::const_iterator const_iterator;
  typedef hash_table<long, int>::local_iterator local_iterator;
  typedef hash_table<long, int>::const_local_iterator const_local_iterator;


  static_assert(is_same<typename hash_table<long, int>::key_type, long>::value, "key_type");
  static_assert(is_same<typename hash_table<long, int>::mapped_type, int>::value, "mapped_type");
  static_assert(is_same<typename hash_table<long, int>::value_type, utility::container::pair<const long, int>>::value, "value_type");
  static_assert(is_same<typename hash_table<long, int>::hasher, utility::algorithm::hash<long>>::value, "hasher");
  static_assert(is_same<typename hash_table<long, int>::key_equal, utility::algorithm::equal_to<void>>::value, "key_equal");
  static_assert(is_same<typename hash_table<long, int>::size_type, decltype(sizeof('0'))>::value, "size_type");
  static_assert(is_same<typename hash_table<long, int>::difference_type, long>::value, "difference_type");
  static_assert(is_same<typename hash_table<long, int>::reference, utility::container::pair<const long, int>&>::value, "reference");
  static_assert(is_same<typename hash_table<long, int>::const_reference, const utility::container::pair<const long, int>&>::value, "const_reference");
  static_assert(is_same<typename hash_table<long, int>::allocator_type, allocator<utility::container::pair<const long, int>>>::value, "allocator_type");
  static_assert(is_same<typename hash_table<long, int>::allocator_traits_type, allocator_traits<allocator<utility::container::pair<const long, int>>>>::value, "allocator_type");
  static_assert(is_same<typename hash_table<long, int>::pointer, utility::container::pair<const long, int>*>::value, "pointer");
  static_assert(is_same<typename hash_table<long, int>::const_pointer, const utility::container::pair<const long, int>*>::value, "const_pointer");

  static_assert(is_same<typename iterator::iterator_category, forward_iterator_tag>::value, "iterator::iterator_category");
  static_assert(is_same<typename iterator::key_type, long>::value, "iterator::key_type");
  static_assert(is_same<typename iterator::mapped_type, int>::value, "iterator::mapped_type");
  static_assert(is_same<typename iterator::value_type, utility::container::pair<const long, int>>::value, "iterator::value_type");
  static_assert(is_same<typename iterator::container_type, hash_table<long, int>>::value, "iterator::container_type");
  static_assert(is_same<typename iterator::reference,  utility::container::pair<const long, int>&>::value, "iterator::reference");
  static_assert(is_same<typename iterator::pointer, utility::container::pair<const long, int>*>::value, "iterator::pointer");
  static_assert(is_same<typename iterator::difference_type, decltype(0L)>::value, "iterator::difference_type");
  static_assert(is_same<typename iterator::self, iterator>::value, "iterator::self");

  static_assert(is_same<typename const_iterator::iterator_category, forward_iterator_tag>::value, "const_iterator::iterator_category");
  static_assert(is_same<typename const_iterator::key_type, long>::value, "const_iterator::key_type");
  static_assert(is_same<typename const_iterator::mapped_type, int>::value, "const_iterator::mapped_type");
  static_assert(is_same<typename const_iterator::non_const_value_type, utility::container::pair<const long, int>>::value, "const_iterator::non_const_value_type");
  static_assert(is_same<typename const_iterator::value_type, const utility::container::pair<const long, int>>::value, "const_iterator::value_type");
  static_assert(is_same<typename const_iterator::container_type, hash_table<long, int>>::value, "const_iterator::container_type");
  static_assert(is_same<typename const_iterator::reference, const utility::container::pair<const long, int>&>::value, "const_iterator::reference");
  static_assert(is_same<typename const_iterator::pointer, const utility::container::pair<const long, int>*>::value, "const_iterator::pointer");
  static_assert(is_same<typename const_iterator::difference_type, decltype(0L)>::value, "const_iterator::difference_type");
  static_assert(is_same<typename const_iterator::self, const_iterator>::value, "const_iterator::self");

  static_assert(is_same<typename local_iterator::iterator_category, forward_iterator_tag>::value, "local_iterator::iterator_category");
  static_assert(is_same<typename local_iterator::key_type, long>::value, "local_iterator::key_type");
  static_assert(is_same<typename local_iterator::mapped_type, int>::value, "local_iterator::mapped_type");
  static_assert(is_same<typename local_iterator::value_type, utility::container::pair<const long, int>>::value, "local_iterator::value_type");
  static_assert(is_same<typename local_iterator::container_type, hash_table<long, int>>::value, "local_iterator::container_type");
  static_assert(is_same<typename local_iterator::reference, utility::container::pair<const long, int>&>::value, "local_iterator::reference");
  static_assert(is_same<typename local_iterator::pointer, utility::container::pair<const long, int>*>::value, "local_iterator::pointer");
  static_assert(is_same<typename local_iterator::difference_type, decltype(0L)>::value, "local_iterator::difference_type");
  static_assert(is_same<typename local_iterator::self, local_iterator>::value, "local_iterator::self");

  static_assert(is_same<typename const_local_iterator::iterator_category, forward_iterator_tag>::value, "const_local_iterator::iterator_category");
  static_assert(is_same<typename const_local_iterator::key_type, long>::value, "const_local_iterator::key_type");
  static_assert(is_same<typename const_local_iterator::mapped_type, int>::value, "const_local_iterator::mapped_type");
  static_assert(is_same<typename const_local_iterator::non_const_value_type, utility::container::pair<const long, int>>::value, "const_local_iterator::non_const_value_type");
  static_assert(is_same<typename const_local_iterator::value_type, const utility::container::pair<const long, int>>::value, "const_local_iterator::value_type");
  static_assert(is_same<typename const_local_iterator::container_type, hash_table<long, int>>::value, "const_local_iterator::container_type");
  static_assert(is_same<typename const_local_iterator::reference, const utility::container::pair<const long, int>&>::value, "const_local_iterator::reference");
  static_assert(is_same<typename const_local_iterator::pointer, const utility::container::pair<const long, int>*>::value, "const_local_iterator::pointer");
  static_assert(is_same<typename const_local_iterator::difference_type, decltype(0L)>::value, "const_local_iterator::difference_type");
  static_assert(is_same<typename const_local_iterator::self, const_local_iterator>::value, "const_local_iterator::self");

  return;
}

void test_construct()
{
  using std::printf;
  using utility::memory::allocator;
  using utility::container::pair;
  using utility::algorithm::equal_to;
  using utility::algorithm::hash;
  using test_type = hash_table<long, int>;

  allocator<pair<const long, int>> __alloc;
  const vector<pair<const long, int>> __ins{{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{100,100}};

  test_type test1;
  assert(test1 == test_type{});
  assert(test1.size() == 0);
  assert(test1.bucket_size() == 97);
  test_type test2(97, __alloc);
  assert(test2 == test_type{});
  assert(test2.size() == 0);
  assert(test2.bucket_size() == 97);
  test_type test3(97, hash<long>());
  assert(test3 == test_type{});
  assert(test3.size() == 0);
  assert(test3.bucket_size() == 97);
  test_type test4(97, hash<long>(), equal_to<void>());
  assert(test4 == test_type{});
  assert(test4.size() == 0);
  assert(test4.bucket_size() == 97);

  test_type test5(__ins.begin(), __ins.end());
  assert(test5 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test5.size() == 7);
  assert(test5.bucket_size() == 97);
  test_type test6(__ins.begin(), __ins.end(),97, hash<long>(), equal_to<void>());
  assert(test6 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test6.size() == 7);
  assert(test6.bucket_size() == 97);
  test_type test7(__ins.begin(), __ins.end(),97, hash<long>());
  assert(test7 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test7.size() == 7);
  assert(test7.bucket_size() == 97);

  test_type test8(test5);
  assert(test8 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test8.size() == 7);
  assert(test8.bucket_size() == 97);
  test_type test9(test5, __alloc);
  assert(test9 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test9.size() == 7);
  assert(test9.bucket_size() == 97);

  test_type test10{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}};
  assert(test10 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test10.size() == 7);
  assert(test10.bucket_size() == 97);
  test_type test11({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}, 97, hash<long>(), equal_to<void>());
  assert(test11 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test11.size() == 7);
  assert(test11.bucket_size() == 97);
  test_type test12({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}, 97, hash<long>());
  assert(test12 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test12.size() == 7);
  assert(test12.bucket_size() == 97);

  test_type test13(utility::algorithm::move(test5));
  assert(test13 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test13.size() == 7);
  assert(test13.bucket_size() == 97);
  test_type test14(utility::algorithm::move(test6), __alloc);
  assert(test14 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test14.size() == 7);
  assert(test14.bucket_size() == 97);

  test1 = test7;
  assert(test1 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test1.size() == 7);
  assert(test1.bucket_size() == 97);
  test2 = utility::algorithm::move(test7);
  assert(test2 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test2.size() == 7);
  assert(test2.bucket_size() == 97);
  test3 = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}};
  assert(test3 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{100,100}}));
  assert(test3.size() == 7);
  assert(test3.bucket_size() == 97);

  printf("Test construct passes.\n");
  return;
}

void test_insert()
{
  using std::printf;
  using utility::memory::allocator;
  using utility::container::pair;
  using utility::algorithm::equal_to;
  using utility::algorithm::hash;
  using test_type = hash_table<long, int>;
  typedef hash_table<long, int>::iterator iterator;
  typedef hash_table<long, int>::const_iterator const_iterator;
  // typedef hash_table<long, int>::local_iterator local_iterator;
  // typedef hash_table<long, int>::const_local_iterator const_local_iterator;

  utility::miscellaneous::ignore_unused<iterator, const_iterator, test_type>();

  const vector<pair<const long, int>> __ins{{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{100,100}};

  test_type test;

  test.insert_unique({1,1});
  pair<iterator, bool> res = test.insert_unique({1,1});
  assert(!res.second);
  test.insert_unique({2,2});
  res = test.insert_unique({98,98});
  assert(res.second);
  assert(test == test_type({{1,1},{2,2},{98,98}}));

  test.insert_equal({3,3});
  test.insert_equal({3,3});
  test.insert_equal({100,100});
  assert(test == test_type({{1,1},{2,2},{3,3},{3,3},{98,98},{100,100}}));

  res = test.emplace_unique(1,1);
  assert(!res.second);
  res = test.emplace_unique(2,2);
  assert(!res.second);
  res = test.emplace_unique(3,3);
  assert(!res.second);

  test.emplace_equal(4,4);
  test.emplace_equal(5,5);
  test.emplace_equal(6,6);
  assert(test == test_type({{1,1},{2,2},{3,3},{3,3},{4,4},{5,5},{6,6},{98,98},{100,100}}));

  unsigned long rec = test.insert_unique(__ins.begin(), __ins.end());
  assert(rec == 0);

  test.insert_equal(__ins.begin(), __ins.end());
  assert(test == test_type({{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{100,100},{1,1},{2,2},{3,3},{3,3},{4,4},{5,5},{6,6},{98,98},{100,100}}));

  printf("Test insert passes\n");
  return;
}

void test_insert_unique_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::container::pair;
  using test_type = hash_table<long, int>;

  test_type test;
  unsigned long __fail = 0;
  for(unsigned long __i = 0; __i != __size; ++__i)
  {
    if(!test.insert_unique({rand(), rand()}).second)
    { ++__fail;}
  }

  assert((test.size()+__fail) == __size);

  printf("fail count:%lu\n", __fail);
  printf("Test insert_unique(huge) passed\n");
}

void test_insert_equal_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::container::pair;
  using test_type = hash_table<long, int>;

  test_type test;
  for(unsigned long __i = 0; __i != __size; ++__i)
  { test.insert_equal({rand(), rand()});}

  assert(test.size() == __size);

  printf("Test insert_equal(huge) passed\n");
}

void test_emplace_unique_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::container::pair;
  using test_type = hash_table<long, int>;

  test_type test;
  unsigned long __fail = 0;
  for(unsigned long __i = 0; __i != __size; ++__i)
  {
    if(!test.emplace_unique(rand(), rand()).second)
    { ++__fail;}
  }

  assert((test.size()+__fail) == __size);

  printf("fail count:%lu\n", __fail);
  printf("Test emplace_unique(huge) passed\n");
}

void test_emplace_equal_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::container::pair;
  using test_type = hash_table<long, int>;

  test_type test;
  for(unsigned long __i = 0; __i != __size; ++__i)
  { test.emplace_equal(rand(), rand());}

  assert(test.size() == __size);

  printf("Test emplace_equal(huge) passed\n");
}

void test_serach()
{
  using std::printf;
  using utility::algorithm::all_of;
  using utility::container::pair;
  using test_type = hash_table<long, int>;
  typedef hash_table<long, int>::iterator iterator;
  typedef hash_table<long, int>::const_iterator const_iterator;
  utility::miscellaneous::ignore_unused<iterator>();
  typedef pair<const long, int> pair_type;


  test_type test{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}};

  assert(test.count(3) == 4);
  assert(test.count(1) == 2);
  assert(test.count(2) == 2);
  assert(test.count(4) == 1);
  pair<const_iterator, const_iterator> res = test.equal_range(3);
  assert(all_of(
    res.first, res.second, [](const pair<long, int>& __tmp)->bool{ return __tmp.first == 3L;}
  ));
  assert(all_of(
    res.second, test.cend(), [](const pair<long, int>& __tmp)->bool{ return __tmp.first != 3L;}
  ));

  const_iterator rec = test.find(3);
  assert(all_of(
    test.cbegin(), rec, [](const pair<long, int>& __tmp)->bool{ return __tmp.first != 3L;}
  ));
  assert(*rec == pair_type({3, 3}));

  printf("Test search passes\n");

  return;
}

void test_erase()
{
  using std::printf;
  using utility::algorithm::all_of;
  using utility::container::pair;
  using test_type = hash_table<long, int>;
  typedef hash_table<long, int>::iterator iterator;
  typedef hash_table<long, int>::const_iterator const_iterator;

  utility::miscellaneous::ignore_unused<iterator>();

  test_type test{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}};

  test.erase(test.begin());
  assert(test == test_type({{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}}));
  assert(test.size() == 14);

  unsigned long res = test.erase(3);
  assert(res == 4);
  assert(test.size() == 10);
  assert(test == test_type({{2,2},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2}}));

  const_iterator __bit = test.find(5);
  const_iterator __eit = test.find(7);
  test.erase(__bit, __eit);
  assert(test.size() == 8);
  assert(test == test_type({{2,2},{4,4},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2}}));

  test.erase(test.begin(), test.end());
  assert(test.size() == 0);
  assert(test == test_type{});

  printf("Test erase passes\n");
}

int main()
{
  using std::srand;
  using std::time;

  srand(time(0));

  test_attribute();
  test_construct();
  test_insert();
  test_insert_unique_huge();
  test_insert_equal_huge();
  test_emplace_unique_huge();
  test_emplace_equal_huge();
  test_serach();
  test_erase();
}
