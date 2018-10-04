
#ifndef __UTILITY_CHARS_ITOA__
#define __UTILITY_CHARS_ITOA__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace charS
  {
    /**
     * \brief convert integer to string
     *
     * Converts an integer \a _val to a null-terminated string using
     * the specified \a _base and stores the result in the array
     * given by \a _buf parameter.<br/>
     * \a _buf should be an array long enough to contain any possible value
     *
     * \param _val  value to be converted
     * \param _buf  buffer where to store the result string
     * \param _base numerical base used to represent the value
     * \param _sign whether add '+' when \c _val is postive
     *
     * \return a pointer to the end of the resulting string
     * \note the \a _base only accept value in [2, 36]
     * @{
     */
    char* itoa(long long _val, char* _buf, int _base, bool _sign)
    {
      static const char* __num = "0123456789abcdefghijklmnopqrstuvwxyz";

      if(_base < 2 || _base > 36)
      {
        *_buf = '\0';
        return _buf;
      }

      long long __tmp;
      bool __negative = _val < 0;
      bool __sign = _val == 0 ? false : _sign;
      _val = _val < 0 ? -_val : _val;
      char* __ptr = _buf;
      do
      {
        __tmp = _val;
        _val /= _base;
        *__ptr++ = __num[__tmp - _val*_base];
      }
      while(_val);
      if(__negative)
      { *__ptr++ = '-';}
      else if(__sign)
      { *__ptr++ = '+';}

      char* __res = __ptr;
      char __tmpc;
      *__ptr-- = '\0';
      for(; _buf < __ptr;)
      {
        __tmpc = *__ptr;
        *__ptr-- = *_buf;
        *_buf++ = __tmpc;
      }

      return __res;
    }

    char16_t* itoa(long long _val, char16_t* _buf, int _base, bool _sign)
    {
      static const char16_t* __num = u"0123456789abcdefghijklmnopqrstuvwxyz";

      if(_base < 2 || _base > 36)
      {
        *_buf = u'\0';
        return _buf;
      }

      long long __tmp;
      bool __negative = _val < 0;
      bool __sign = _val == 0 ? false : _sign;
      _val = _val < 0 ? -_val : _val;
      char16_t* __ptr = _buf;
      do
      {
        __tmp = _val;
        _val /= _base;
        *__ptr++ = __num[__tmp - _val*_base];
      }
      while(_val);
      if(__negative)
      { *__ptr++ = u'-';}
      else if(__sign)
      { *__ptr++ = u'+';}

      char16_t* __res = __ptr;
      char16_t __tmpc;
      *__ptr-- = u'\0';
      for(; _buf < __ptr;)
      {
        __tmpc = *__ptr;
        *__ptr-- = *_buf;
        *_buf++ = __tmpc;
      }

      return __res;
    }

    char32_t* itoa(long long _val, char32_t* _buf, int _base, bool _sign)
    {
      static const char32_t* __num = U"0123456789abcdefghijklmnopqrstuvwxyz";

      if(_base < 2 || _base > 36)
      {
        *_buf = U'\0';
        return _buf;
      }

      long long __tmp;
      bool __negative = _val < 0;
      bool __sign = _val == 0 ? false : _sign;
      _val = _val < 0 ? -_val : _val;
      char32_t* __ptr = _buf;
      do
      {
        __tmp = _val;
        _val /= _base;
        *__ptr++ = __num[__tmp - _val*_base];
      }
      while(_val);
      if(__negative)
      { *__ptr++ = U'-';}
      else if(__sign)
      { *__ptr++ = U'+';}

      char32_t* __res = __ptr;
      char32_t __tmpc;
      *__ptr-- = U'\0';
      for(; _buf < __ptr;)
      {
        __tmpc = *__ptr;
        *__ptr-- = *_buf;
        *_buf++ = __tmpc;
      }

      return __res;
    }

    wchar_t* itoa(long long _val, wchar_t* _buf, int _base, bool _sign)
    {
      static const wchar_t* __num = L"0123456789abcdefghijklmnopqrstuvwxyz";

      if(_base < 2 || _base > 36)
      {
        *_buf = L'\0';
        return _buf;
      }

      long long __tmp;
      bool __negative = _val < 0;
      bool __sign = _val == 0 ? false : _sign;
      _val = _val < 0 ? -_val : _val;
      wchar_t* __ptr = _buf;
      do
      {
        __tmp = _val;
        _val /= _base;
        *__ptr++ = __num[__tmp - _val*_base];
      }
      while(_val);
      if(__negative)
      { *__ptr++ = L'-';}
      else if(__sign)
      { *__ptr++ = L'+';}

      wchar_t* __res = __ptr;
      wchar_t __tmpc;
      *__ptr-- = L'\0';
      for(; _buf < __ptr;)
      {
        __tmpc = *__ptr;
        *__ptr-- = *_buf;
        *_buf++ = __tmpc;
      }

      return __res;
    }
    /** @}*/
  }
}

#endif // ! __UTILITY_CHARS_ITOA__
