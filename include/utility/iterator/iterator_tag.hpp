
#ifndef __UTILITY_ITERATOR_ITERATOR_TAG__
#define __UTILITY_ITERATOR_ITERATOR_TAG__

#include<utility/config/utility_config.hpp>

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
    struct contiguous_iterator_tag : public random_access_iterator_tag
    { };

  }
}

#endif // ! __UTILITY_ITERATOR_ITERATOR_TAG__
