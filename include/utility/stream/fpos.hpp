
#ifndef __UTILITY_CHARS_FPOS__
#define __UTILITY_CHARS_FPOS__

/**
 * \file fpos.hpp
 * \author Inochi Amaoto
 *
 */

#include<utility/config/utility_config.hpp>
#include<utility/stream/streamoff.hpp>
#include<utility/sstd/cstring.hpp>

namespace utility
{
  namespace stream
  {
    template<typename _Status>
    class fpos
    {
      private:
        _Status __status;
        streamoff __off;

      public:
        inline fpos(streamoff __n_off = streamoff()):
          __status(), __off(__n_off)
        { }

      public:
        inline operator streamoff() const noexcept
        { return this->__off;}
        inline _Status state() const noexcept
        { return __status;}

      public:
        fpos& operator+=(const fpos& __other)
        {
          this->__off += __other.__off;
          return *this;
        }
        fpos& operator-=(const fpos& __other)
        {
          this->__off -= __other.__off;
          return *this;
        }
        fpos operator+(const fpos& __other) const
        {
          fpos __tmp(*this);
          __tmp += __other;
          return __tmp;
        }
        fpos operator-(const fpos& __other) const
        {
          fpos __tmp(*this);
          __tmp -= __other;
          return __tmp;
        }
    };

    template<typename _Status>
    inline streamoff operator-(
      const fpos<_Status>& __x, const fpos<_Status>& __y
    )
    { return static_cast<streamoff>(__x) - static_cast<streamoff>(__y);}
    template<typename _Status>
    inline streamoff operator==(
      const fpos<_Status>& __x, const fpos<_Status>& __y
    )
    { return static_cast<streamoff>(__x) == static_cast<streamoff>(__y);}
    template<typename _Status>
    inline streamoff operator!=(
      const fpos<_Status>& __x, const fpos<_Status>& __y
    )
    { return static_cast<streamoff>(__x) != static_cast<streamoff>(__y);}

    typedef fpos<sstd::mbstate_t> streampos;
    typedef fpos<sstd::mbstate_t> wstreampos;
    typedef fpos<sstd::mbstate_t> u16streampos;
    typedef fpos<sstd::mbstate_t> u32streampos;
  }
}

#endif // ! __UTILITY_CHARS_FPOS__
