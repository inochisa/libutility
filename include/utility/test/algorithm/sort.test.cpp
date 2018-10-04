#define UTILITY_DEBUG

#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<ctime>
#include<utility/container/vector.hpp>
#include<utility/algorithm/is_sorted.hpp>
#include<utility/algorithm/sort.hpp>

template<
  typename _Tag = utility::algorithm::sort_tag::introspective_sort_tag
>
void sort_test(utility::size_t __size = 10000)
{
  using std::rand;
  using std::clock;
  using std::clock_t;
  using utility::size_t;
  using utility::container::vector;
  using utility::algorithm::is_sorted;
  using utility::algorithm::sort;

  vector<int> rec;

  for(size_t __i = 0; __i < __size; ++__i)
  { rec.push_back((rand()&1?1:-1) * rand());}

  clock_t begin = clock();
  sort<_Tag>(rec.begin(), rec.end());
  clock_t end = clock();
  double ti = end - begin;
  ti /= CLOCKS_PER_SEC;

  assert(is_sorted(rec.begin(), rec.end()));
  printf("Sort test %lu passes. Time: %lfs\n", __size, ti);
  return;
}


int main()
{
  using std::time;
  using std::srand;
  using namespace utility::algorithm::sort_tag;

  srand(time(0));

  printf("select_sort_tag\n");
  sort_test<select_sort_tag>(10);
  sort_test<select_sort_tag>(100);
  sort_test<select_sort_tag>(1000);
  sort_test<select_sort_tag>(10000);
  sort_test<select_sort_tag>(100000);
  sort_test<select_sort_tag>(1000000);

  printf("bubble_sort_tag\n");
  sort_test<bubble_sort_tag>(10);
  sort_test<bubble_sort_tag>(100);
  sort_test<bubble_sort_tag>(1000);
  sort_test<bubble_sort_tag>(10000);
  sort_test<bubble_sort_tag>(100000);
  sort_test<bubble_sort_tag>(1000000);

  printf("cocktail_shaker_sort_tag\n");
  sort_test<cocktail_shaker_sort_tag>(10);
  sort_test<cocktail_shaker_sort_tag>(100);
  sort_test<cocktail_shaker_sort_tag>(1000);
  sort_test<cocktail_shaker_sort_tag>(10000);
  sort_test<cocktail_shaker_sort_tag>(100000);
  sort_test<cocktail_shaker_sort_tag>(1000000);

  printf("odd_even_sort_tag\n");
  sort_test<odd_even_sort_tag>(10);
  sort_test<odd_even_sort_tag>(100);
  sort_test<odd_even_sort_tag>(1000);
  sort_test<odd_even_sort_tag>(10000);
  sort_test<odd_even_sort_tag>(100000);
  sort_test<odd_even_sort_tag>(1000000);

  printf("comb_sort_tag\n");
  sort_test<comb_sort_tag>(10);
  sort_test<comb_sort_tag>(100);
  sort_test<comb_sort_tag>(1000);
  sort_test<comb_sort_tag>(10000);
  sort_test<comb_sort_tag>(100000);
  sort_test<comb_sort_tag>(1000000);

  printf("gnome_sort_tag\n");
  sort_test<gnome_sort_tag>(10);
  sort_test<gnome_sort_tag>(100);
  sort_test<gnome_sort_tag>(1000);
  sort_test<gnome_sort_tag>(10000);
  sort_test<gnome_sort_tag>(100000);
  sort_test<gnome_sort_tag>(1000000);

  printf("insertion_sort_tag\n");
  sort_test<insertion_sort_tag>(10);
  sort_test<insertion_sort_tag>(100);
  sort_test<insertion_sort_tag>(1000);
  sort_test<insertion_sort_tag>(10000);
  sort_test<insertion_sort_tag>(100000);
  sort_test<insertion_sort_tag>(1000000);

  printf("shell_sort_tag\n");
  sort_test<shell_sort_tag>(10);
  sort_test<shell_sort_tag>(100);
  sort_test<shell_sort_tag>(1000);
  sort_test<shell_sort_tag>(10000);
  sort_test<shell_sort_tag>(100000);
  sort_test<shell_sort_tag>(1000000);

  printf("cycle_sort_tag\n");
  sort_test<cycle_sort_tag>(10);
  sort_test<cycle_sort_tag>(100);
  sort_test<cycle_sort_tag>(1000);
  sort_test<cycle_sort_tag>(10000);
  sort_test<cycle_sort_tag>(100000);
  sort_test<cycle_sort_tag>(1000000);

  printf("heap_sort_tag\n");
  sort_test<heap_sort_tag>(10);
  sort_test<heap_sort_tag>(100);
  sort_test<heap_sort_tag>(1000);
  sort_test<heap_sort_tag>(10000);
  sort_test<heap_sort_tag>(100000);
  sort_test<heap_sort_tag>(1000000);

  printf("quick_sort_tag\n");
  sort_test<quick_sort_tag>(10);
  sort_test<quick_sort_tag>(100);
  sort_test<quick_sort_tag>(1000);
  sort_test<quick_sort_tag>(10000);
  sort_test<quick_sort_tag>(100000);
  sort_test<quick_sort_tag>(1000000);

  printf("introspective_sort_tag\n");
  sort_test<introspective_sort_tag>(10);
  sort_test<introspective_sort_tag>(100);
  sort_test<introspective_sort_tag>(1000);
  sort_test<introspective_sort_tag>(10000);
  sort_test<introspective_sort_tag>(100000);
  sort_test<introspective_sort_tag>(1000000);

}
