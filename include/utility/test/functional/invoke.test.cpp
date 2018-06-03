#define UTILITY_DEBUG true

#include<utility/trait/type/property/is_empty.hpp>
#include<utility/trait/type/releations/is_same.hpp>
#include<utility/functional/invoke.hpp>

struct __test
{
  public:
    int x;

    int operator()() noexcept
    { return 3;}

    int sp() const
    { return 4;}
};

int re(int q) noexcept
{ return q;}

void test()
{
  using utility::trait::type::property_query::belong_to;
  using utility::trait::type::releations::is_same;
  using utility::trait::type::property::is_empty;
  using utility::functional::invoke;
  using utility::trait::type::miscellaneous::invoke_result;

  __test __tmp;
  __tmp.x = 2;

  int q = invoke(__tmp);
  q = invoke(&__test::x, __tmp);
  q = invoke(&__test::sp, __tmp);
  q = invoke(re, q);

  return;
}


int main()
{
  test();

  return 0;
}
