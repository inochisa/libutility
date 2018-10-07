

#ifndef __UTILITY_CHARS_IMPL_STRING_FIND__
#define __UTILITY_CHARS_IMPL_STRING_FIND__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/max.hpp>


namespace utility
{
  namespace charS
  {
    namespace impl
    {
      // Two ways algorithm
      template<typename _CharT, typename _Trait, typename _Size>
      _Size __str_left_suffix(
        const _CharT* _str, _Size _len, _Size& _plen
      ) noexcept
      {
        _Size __i = -1;
        _Size __j = 0;
        _Size __k = (_plen = 1);
        for(; __j+__k < _len;)
        {
          _CharT __x = _str[__j+__k];
          _CharT __y = _str[__i+__k];
          if(_Trait::lt(__x, __y))
          {
            __j += __k;
            __k = 1;
            _plen =  __j-__i;
          }
          else if(_Trait::eq(__x, __y))
          {
            if(__k != _plen)
            { ++__k;}
            else
            {
              __j += _plen;
              __k = 1;
            }
          }
          else
          {
            __i = __j;
            __j = __i+1;
            __k = _plen = 1;
          }
        }

        return __i;
      }
      template<typename _CharT, typename _Trait, typename _Size>
      _Size __str_right_suffix(
        const _CharT* _str, _Size _len, _Size& _plen
      ) noexcept
      {
        _Size __i = -1;
        _Size __j = 0;
        _Size __k = (_plen = 1);
        for(; __j+__k < _len;)
        {
          _CharT __x = _str[__j+__k];
          _CharT __y = _str[__i+__k];
          if(_Trait::lt(__y, __x))
          {
            __j += __k;
            __k = 1;
            _plen =  __j-__i;
          }
          else if(_Trait::eq(__x, __y))
          {
            if(__k != _plen)
            { ++__k;}
            else
            {
              __j += _plen;
              __k = 1;
            }
          }
          else
          {
            __i = __j;
            __j = __i+1;
            __k = _plen = 1;
          }
        }

        return __i;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __string_find(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen
      ) noexcept
      {
        using algorithm::max;

        if(_patlen == 0)
        { return 0U;}

        if(_len < _patlen)
        { return _npos;}

        _Size __left, __right;
        _Size __pos, __plen;
        _Size __i =
          __str_left_suffix<_CharT, _Trait, _Size>(_pat, _patlen, __left);
        _Size __j =
          __str_right_suffix<_CharT, _Trait, _Size>(_pat, _patlen, __right);

        if(__i > __j && __i != static_cast<_Size>(-1))
        {
          __pos = __left;
          __plen = __i;
        }
        else
        {
          __pos = __right;
          __plen = __j;
        }

        if(_Trait::compare(_pat, _pat+__pos, __plen+1) == 0)
        {
          __j = 0;
          _Size __cache = 0;
          for(; __j+_patlen <= _len;)
          {
            __i = max(__plen+1, __cache);
            for(; __i < _patlen && _pat[__i] == _str[__i+__j]; ++__i)
            { }
            if(__i >= _patlen)
            {
              __i = __plen;
              for(; __i >=__cache && ~__i && _pat[__i] == _str[__i+__j]; --__i)
              { }
              if(__i < __cache || !(~__i))
              { return __j;}
              __j += __pos;
              __cache = _patlen-__pos;
            }
            else
            {
              __j += (__i-__plen);
              __cache = 0;
            }
          }
        }
        else
        {
          __pos = max(__plen+2, _patlen-__plen);
          __j = 0;
          for(; __j+_patlen <= _len; )
          {
            __i = __plen+1;
            for(; __i < _patlen && _pat[__i] == _str[__i+__j]; ++__i)
            { }
            if(__i >= _patlen)
            {
              __i = __plen;
              while(~__i && _pat[__i] == _str[__i+__j])
              { --__i;}
              if(!(~__i))
              { return __j;}
              __j += __pos;
            }
            else
            { __j += (__i-__plen);}
          }
        }

        return _npos;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find(
        const _CharT* _str, _Size _len, _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_pos >= _len)
        { return _npos;}

        const _CharT* __ptr = _Trait::find(_str+_pos, _len-_pos, _ch);
        if(__ptr == nullptr)
        { return _npos;}
        return static_cast<_Size>(__ptr-_str);
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        if(_pos >= _len)
        { return _npos;}

        _Size __res = __string_find<_CharT, _Trait, _Size, _npos>(
          _str+_pos, _len-_pos, _pat, _patlen
        );

        if(__res == _npos)
        { return _npos;}
        return __res+_pos;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __rfind(
        const _CharT* _str, _Size _len, _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_len < 1)
        { return _npos;}
        if(_pos < _len)
        { ++_pos;}
        else
        { _pos = _len;}

        for(const _CharT* __ss = _str + _pos; __ss != _str;)
        {
          if(_Trait::eq(*--__ss, _ch))
          { return static_cast<_Size>(__ss - _str);}
        }

        return _npos;
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __rfind(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        _pos = _pos > _len ? _len : _pos;
        if(_patlen == 0)
        { return _pos;}
        if(_len < _patlen)
        { return _npos;}

        if(_patlen > _len - _pos)
        { _pos = _len;}
        else
        { _pos += _patlen;}
        const _CharT* __ptr = _str + (_patlen-1);
        const _CharT* __end = _str + _pos;
        const _CharT* __pend = _pat + _patlen;
        --__pend;
        for(;;)
        {
          for(;;)
          {
            if(__ptr == __end)
            { return _npos;}
            if(_Trait::eq(*--__end, *__pend))
            { break;}
          }

          const _CharT* __pos = __end;
          const _CharT* __ppos = __pend;

          for(;;)
          {
            if(__ppos == _pat)
            { return static_cast<_Size>(__pos - _str);}
            if(!_Trait::eq(*--__pos, *--__ppos))
            { break;}
          }
        }
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_first_of(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        if(_pos < _len && _patlen != 0)
        {
          const _CharT* __stre = _str + _len;
          for(const _CharT* __pos = _str + _pos; __pos != __stre; ++__pos)
          {
            const _CharT* __res = _Trait::find(_pat, _patlen, *__pos);
            if(__res)
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_first_of(
        const _CharT* _str, _Size _len,
        _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_pos < _len)
        {
          const _CharT* __stre = _str + _len;
          for(const _CharT* __pos = _str + _pos; __pos != __stre; ++__pos)
          {
            if(_Trait::eq(_ch, *__pos))
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_last_of(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        if(_patlen != 0)
        {
          if(_pos < _len)
          { ++_pos;}
          else
          { _pos = _len;}

          for(const _CharT* __pos = _str + _pos; __pos != _str;)
          {
            const _CharT* __res = _Trait::find(_pat, _patlen, *--__pos);
            if(__res)
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_last_of(
        const _CharT* _str, _Size _len,
        _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_pos < _len)
        { ++_pos;}
        else
        { _pos = _len;}

        for(const _CharT* __pos = _str + _pos; __pos != _str;)
        {
          if(_Trait::eq(_ch, *--__pos))
          { return static_cast<_Size>(__pos - _str);}
        }
        return _npos;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_first_not_of(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        if(_pos < _len)
        {
          const _CharT* __stre = _str + _len;
          for(const _CharT* __pos = _str + _pos; __pos != __stre; ++__pos)
          {
            const _CharT* __res = _Trait::find(_pat, _patlen, *__pos);
            if(!__res)
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_first_not_of(
        const _CharT* _str, _Size _len,
        _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_pos < _len)
        {
          const _CharT* __stre = _str + _len;
          for(const _CharT* __pos = _str + _pos; __pos != __stre; ++__pos)
          {
            if(!_Trait::eq(_ch, *__pos))
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }

      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_last_not_of(
        const _CharT* _str, _Size _len,
        const _CharT* _pat, _Size _patlen,
        _Size _pos
      ) noexcept
      {
        if(_patlen != 0)
        {
          if(_pos < _len)
          { ++_pos;}
          else
          { _pos = _len;}

          for(const _CharT* __pos = _str + _pos; __pos != _str;)
          {
            const _CharT* __res = _Trait::find(_pat, _patlen, *--__pos);
            if(!__res)
            { return static_cast<_Size>(__pos - _str);}
          }
        }
        return _npos;
      }
      template<typename _CharT, typename _Trait, typename _Size, _Size _npos>
      inline _Size __find_last_not_of(
        const _CharT* _str, _Size _len,
        _CharT _ch, _Size _pos
      ) noexcept
      {
        if(_pos < _len)
        { ++_pos;}
        else
        { _pos = _len;}

        for(const _CharT* __pos = _str + _pos; __pos != _str;)
        {
          if(!_Trait::eq(_ch, *--__pos))
          { return static_cast<_Size>(__pos - _str);}
        }
        return _npos;
      }
    }
  }
}

#endif // ! __UTILITY_CHARS_IMPL_STRING_FIND__
