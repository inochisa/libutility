#define UTILITY_DEBUG

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<utility/container/white_black_tree.hpp>
#include<utility/container/vector.hpp>
#include<utility/algorithm/all_of.hpp>
#include<utility/algorithm/is_sorted.hpp>
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
  using utility::iterator::bidirectional_iterator_tag;
  typedef white_black_tree<long, int>::iterator iterator;
  typedef white_black_tree<long, int>::const_iterator const_iterator;

  static_assert(is_same<typename white_black_tree<long, int>::key_type, long>::value, "key_type");
  static_assert(is_same<typename white_black_tree<long, int>::mapped_type, int>::value, "mapped_type");
  static_assert(is_same<typename white_black_tree<long, int>::value_type, ::utility::container::pair<const long, int>>::value, "value_type");
  static_assert(is_same<typename white_black_tree<long, int>::key_compare, ::utility::algorithm::less<long>>::value, "key_compare");
  static_assert(is_same<typename white_black_tree<long, int>::size_type, decltype(sizeof('0'))>::value, "size_type");
  static_assert(is_same<typename white_black_tree<long, int>::difference_type, long>::value, "difference_type");
  static_assert(is_same<typename white_black_tree<long, int>::reference, ::utility::container::pair<const long, int>&>::value, "reference");
  static_assert(is_same<typename white_black_tree<long, int>::const_reference, const ::utility::container::pair<const long, int>&>::value, "const_reference");
  static_assert(is_same<typename white_black_tree<long, int>::allocator_type, allocator<utility::container::pair<const long, int>>>::value, "allocator_type");
  static_assert(is_same<typename white_black_tree<long, int>::allocator_traits_type, allocator_traits<allocator<utility::container::pair<const long, int>>>>::value, "allocator_type");
  static_assert(is_same<typename white_black_tree<long, int>::pointer, ::utility::container::pair<const long, int>*>::value, "pointer");
  static_assert(is_same<typename white_black_tree<long, int>::const_pointer, const ::utility::container::pair<const long, int>*>::value, "const_pointer");

  static_assert(is_same<typename iterator::iterator_category, bidirectional_iterator_tag>::value, "iterator::iterator_category");
  static_assert(is_same<typename iterator::key_type, long>::value, "iterator::key_type");
  static_assert(is_same<typename iterator::mapped_type, int>::value, "iterator::mapped_type");
  static_assert(is_same<typename iterator::value_type, ::utility::container::pair<const long, int>>::value, "iterator::value_type");
  static_assert(is_same<typename iterator::reference, ::utility::container::pair<const long, int>&>::value, "iterator::reference");
  static_assert(is_same<typename iterator::pointer, ::utility::container::pair<const long, int>*>::value, "iterator::pointer");
  static_assert(is_same<typename iterator::difference_type, decltype(0L)>::value, "iterator::difference_type");
  static_assert(is_same<typename iterator::self, iterator>::value, "iterator::self");

  static_assert(is_same<typename const_iterator::iterator_category, bidirectional_iterator_tag>::value, "const_iterator::iterator_category");
  static_assert(is_same<typename const_iterator::key_type, long>::value, "const_iterator::key_type");
  static_assert(is_same<typename const_iterator::mapped_type, int>::value, "const_iterator::mapped_type");
  static_assert(is_same<typename const_iterator::value_type, ::utility::container::pair<const long, int>>::value, "const_iterator::value_type");
  static_assert(is_same<typename const_iterator::const_value_type, const ::utility::container::pair<const long, int>>::value, "const_iterator::const_value_type");
  static_assert(is_same<typename const_iterator::reference, const ::utility::container::pair<const long, int>&>::value, "const_iterator::reference");
  static_assert(is_same<typename const_iterator::pointer, const ::utility::container::pair<const long, int>*>::value, "const_iterator::pointer");
  static_assert(is_same<typename const_iterator::difference_type, decltype(0L)>::value, "const_iterator::difference_type");
  static_assert(is_same<typename const_iterator::self, const_iterator>::value, "const_iterator::self");

  return;
}

void test_construct()
{
  using std::printf;
  using utility::memory::allocator;
  using utility::container::pair;
  using utility::algorithm::less;
  using test_type = white_black_tree<long, int>;

  allocator<pair<const long, int>> __alloc;
  vector<pair<const long, int>> __ins{{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{7,7}};

  test_type test1;
  assert(test1 == test_type{});
  assert(test1.empty());
  test_type test2{less<long>()};
  assert(test2 == test_type{});
  assert(test2.empty());
  test_type test3(__alloc);
  assert(test3 == test_type{});
  assert(test3.empty());

  test_type test4(__ins.begin(), __ins.end());
  assert(test4 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));
  test_type test5(__ins.begin(), __ins.end(), __alloc);
  assert(test5 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));

  test_type test6(test4);
  assert(test6 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));
  test_type test7(test4, __alloc);
  assert(test7 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));

  test_type test8{{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{7,7}};
  assert(test8 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));

  test_type test9(::utility::algorithm::move(test4));
  assert(test9 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));
  test_type test10(::utility::algorithm::move(test5), __alloc);
  assert(test10 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));

  test4 = {{4,4},{2,2},{1,1},{3,3},{6,6},{5,5},{7,7}};
  assert(test4 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));
  test5 = test4;
  assert(test5 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));
  test3 = ::utility::algorithm::move(test4);
  assert(test3 == test_type({{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}}));

  printf("Test construct passes\n");

  return;
}

void test_insert()
{
  using std::printf;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;
  typedef white_black_tree<long, int>::iterator iterator;
  typedef white_black_tree<long, int>::const_iterator const_iterator;

  utility::miscellaneous::ignore_unused<const_iterator>();

  test_type test;
  assert(test == test_type{});
  assert(test.empty());

  test.insert_equal({65677,65677});
  test.insert_equal({83362,83362});
  test.insert_equal({36602,36602});
  test.insert_equal({17537,17537});
  assert(test == test_type({{17537,17537},{36602,36602},{65677,65677},{83362,83362}}));
  test.insert_equal({65677,65677});
  assert(test == test_type({{17537,17537},{36602,36602},{65677,65677},{65677,65677},{83362,83362}}));

  pair<iterator, bool> __res = test.insert_unique({65677,65677});
  assert(!__res.second);
  assert(test == test_type({{17537,17537},{36602,36602},{65677,65677},{65677,65677},{83362,83362}}));
  __res = test.insert_unique({1177,1177});
  assert(__res.second);
  assert(test == test_type({{1177,1177},{17537,17537},{36602,36602},{65677,65677},{65677,65677},{83362,83362}}));
  __res = test.insert_unique({1177,15414});
  assert(!__res.second);
  assert(test == test_type({{1177,1177},{17537,17537},{36602,36602},{65677,65677},{65677,65677},{83362,83362}}));
  __res = test.insert_unique({98684,15414});
  assert(__res.second);
  assert(test == test_type({{1177,1177},{17537,17537},{36602,36602},{65677,65677},{65677,65677},{83362,83362},{98684,15414}}));

  test.emplace_equal(65677,65677);
  test.emplace_equal(83362,83362);
  test.emplace_equal(36602,36602);
  test.emplace_equal(17537,17537);
  assert(test == test_type({{1177,1177},{17537,17537},{17537,17537},{36602,36602},{36602,36602},{65677,65677},{65677,65677},{65677,65677},{83362,83362},{83362,83362},{98684,15414}}));

  test.clear();
  assert(test == test_type{});
  __res = test.emplace_unique(1177,1177);
  assert(__res.second);
  assert(test == test_type({{1177,1177}}));
  __res = test.emplace_unique(1177,1177);
  assert(!__res.second);
  assert(test == test_type({{1177,1177}}));
  __res = test.emplace_unique(17537,17537);
  assert(__res.second);
  assert(test == test_type({{1177,1177},{17537,17537}}));
  __res = test.emplace_unique(17537,1177);
  assert(!__res.second);
  assert(test == test_type({{1177,1177},{17537,17537}}));

  printf("Test insert emplace passes\n");

  return;
}

void test_insert_unique_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::algorithm::is_sorted;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;

  test_type test;
  unsigned long __fail = 0;
  for(unsigned long __i = 0; __i != __size; ++__i)
  {
    if(!test.insert_unique({rand(), rand()}).second)
    { ++__fail;}
  }

  assert((test.size()+__fail) == __size);
  assert(is_sorted(test.begin(), test.end()));

  printf("Test insert_unique(huge) passed\n");
}

void test_insert_equal_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::algorithm::is_sorted;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;

  test_type test;
  for(unsigned long __i = 0; __i != __size; ++__i)
  { test.insert_equal({rand(), rand()});}

  assert(test.size() == __size);
  assert(is_sorted(test.begin(), test.end()));

  printf("Test insert_equal(huge) passed\n");
}

void test_emplace_unique_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::algorithm::is_sorted;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;

  test_type test;
  unsigned long __fail = 0;
  for(unsigned long __i = 0; __i != __size; ++__i)
  {
    if(!test.emplace_unique(rand(), rand()).second)
    { ++__fail;}
  }

  assert((test.size()+__fail) == __size);
  assert(is_sorted(test.begin(), test.end()));

  printf("Test emplace_unique(huge) passed\n");
}

void test_emplace_equal_huge(unsigned long __size = 1000)
{
  using std::rand;
  using std::printf;
  using utility::algorithm::is_sorted;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;

  test_type test;
  for(unsigned long __i = 0; __i != __size; ++__i)
  { test.emplace_equal(rand(), rand());}

  assert(test.size() == __size);
  assert(is_sorted(test.begin(), test.end()));

  printf("Test emplace_equal(huge) passed\n");
}

void test_serach()
{
  using std::printf;
  using utility::algorithm::all_of;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;
  typedef white_black_tree<long, int>::iterator iterator;
  typedef white_black_tree<long, int>::const_iterator const_iterator;
  utility::miscellaneous::ignore_unused<iterator>();

  test_type test{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}};

  assert(test.count(3) == 4);
  assert(test.count(1) == 2);
  assert(test.count(2) == 2);
  assert(test.count(4) == 1);
  pair<const_iterator, const_iterator> res = test.equal_range(3);
  assert(all_of(
    res.first, res.second, [](const pair<const long, int>& __tmp)->bool{ return __tmp.first == 3L;}
  ));
  assert(all_of(
    res.second, test.cend(), [](const pair<const long, int>& __tmp)->bool{ return __tmp.first > 3L;}
  ));

  const_iterator rec = test.upper_bound(4);
  assert(all_of(
    test.cbegin(), rec, [](const pair<const long, int>& __tmp)->bool{ return __tmp.first < 5L;}
  ));
  rec = test.lower_bound(5);
  assert(all_of(
    rec, test.cend(), [](const pair<const long, int>& __tmp)->bool{ return __tmp.first > 4L;}
  ));

  rec = test.find(3);
  assert(all_of(
    test.cbegin(), rec, [](const pair<const long, int>& __tmp)->bool{ return __tmp.first < 3L;}
  ));
  assert(all_of(
    rec, test.cend(), [](const pair<const long, int>& __tmp)->bool{ return __tmp.first > 2L;}
  ));

  printf("Test search passes\n");

  return;
}

void test_erase()
{
  using std::printf;
  using utility::algorithm::all_of;
  using utility::container::pair;
  using test_type = white_black_tree<long, int>;
  typedef white_black_tree<long, int>::iterator iterator;
  typedef white_black_tree<long, int>::const_iterator const_iterator;

  utility::miscellaneous::ignore_unused<iterator>();

  test_type test{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}};

  test.erase(test.begin());
  assert(test == test_type({{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{1,1},{2,2},{3,3},{3,4},{3,5}}));

  test.erase(3);
  assert(all_of(
    test.begin(), test.end(), [](const pair<const long, int>& __tmp)->bool{return __tmp.first != 3;}
  ));

  const_iterator __bit = test.lower_bound(5);
  const_iterator __eit = test.upper_bound(7);
  test.erase(__bit, __eit);
  assert(all_of(
    test.begin(), test.end(), [](const pair<const long, int>& __tmp)->bool{return __tmp.first < 5 || __tmp.first > 7;}
  ));

  test.erase(test.begin(), test.end());
  assert(test.size() == 0);
  assert(test == test_type{});

  printf("Test erase passes\n");
}

int main()
{
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
