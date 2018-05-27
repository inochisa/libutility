
#ifndef __UTILITY_ITERATOR_ITERATOR_TAG__
#define __UTILITY_ITERATOR_ITERATOR_TAG__

#include<utility/config/utility_config.hpp>

#ifdef ___UTILITY__CHECK__USE__STD___

#include<iterator>

namespace utility
{
  namespace iterator
  {
    using std::input_iterator_tag;
    using std::output_iterator_tag;
    using std::forward_iterator_tag;
    using std::bidirectional_iterator_tag;
    using std::random_access_iterator_tag;
  }
}

#else // ! ___UTILITY__CHECK__USE__STD___

namespace utility
{
  namespace iterator
  {
    struct input_iterator_tag
    { };
    struct output_iterator_tag
    { };
    struct forward_iterator_tag : public input_iterator_tag
    { };
    struct bidirectional_iterator_tag : public forward_iterator_tag
    { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    { };

  }
}

#endif // ! ___UTILITY__CHECK__USE__STD___

namespace utility
{
  namespace iterator
  {
    struct contiguous_iterator_tag : public random_access_iterator_tag
    { };

  }
}

#endif // ! __UTILITY_ITERATOR_ITERATOR_TAG__
