#!/bin/sh

function printf_format
{
  echo
  echo "#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__"
  echo "#define __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__"
  echo

  echo "#define ___CHAR_DIGITAL ${1}"
  echo "/*the digital of one char, the same as CHAR_BIT.*/"
  echo

  echo "#define ___CHAR_IS_SIGNED ${2}"
  echo "/*the char is whether signed. the same as CHAR_MIN != 0*/"
  echo

  echo "#define ___UCHAR_MAX ${3}"
  echo "/*the max value of unsigned char.*/"
  echo

  echo "#define ___USHORT_MAX ${4}"
  echo "/*the max value of unsigned short int.*/"
  echo

  echo "#define ___UINT_MAX ${5}"
  echo "/*the max value of unsigned int.*/"
  echo

  echo "#define ___ULONG_MAX ${6}"
  echo "/*the max value of unsigned long int.*/"
  echo

  echo "#define ___LONG_DIGITAL ${7}"
  echo "/*the digital of long, the same as LONG_BIT.*/"
  echo

  echo "#define ___WORD_DIGITAL ${8}"
  echo "/*the digital of int, the same as WORD_BIT.*/"
  echo

  echo "#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__"
}

if test -e "/usr/bin/getconf"
then
  echo "checking getconf... Yes"
else
  echo "checking getconf... No"
  echo "getconf can not found. Please generate the \"int_base.hpp\" manually."
  echo "The format of the \"int_base.hpp\" is:"
  printf_format
  exit 1
fi
echo

function get_pre_conf
{
  local value=$(getconf ${1})
  if [ ${value} = "undefined" ]
  then
    echo "undefined"
  else
    echo "${value}"
  fi
}

function test_pre_conf
{
  if [ ${2} = "undefined" ]
  then
    echo "checking ${1}... undefined"
    echo "${1} not defined, generate error, Please generate the \"int_base.hpp\" manually."
    echo "The format of the \"int_base.hpp\" is:"
    printf_format
    exit 1
  else
    echo "checking ${1}... ${2}"
  fi
}

char_bit=$(get_pre_conf CHAR_BIT)
char_min=$(get_pre_conf CHAR_MIN)
char_max=$(get_pre_conf CHAR_MAX)
uchar_max=$(get_pre_conf UCHAR_MAX)
ushrt_max=$(get_pre_conf USHRT_MAX)
uint_max=$(get_pre_conf UINT_MAX)
ulong_max=$(get_pre_conf ULONG_MAX)
long_bit=$(get_pre_conf LONG_BIT)
word_bit=$(get_pre_conf WORD_BIT)

test_pre_conf CHAR_BIT ${char_bit}
test_pre_conf CHAR_MIN ${char_min}
test_pre_conf CHAR_MAX ${char_max}
test_pre_conf UCHAR_MAX ${uchar_max}
test_pre_conf USHRT_MAX ${ushrt_max}
test_pre_conf UINT_MAX ${uint_max}
test_pre_conf ULONG_MAX ${ulong_max}
test_pre_conf LONG_BIT ${long_bit}
test_pre_conf WORD_BIT ${word_bit}

char_is_signed="true"

if [ ${char_min} = 0 ]
then
  char_is_signed="false"
else
  char_is_signed="true"
fi

echo
echo "The result is:"
printf_format ${char_bit} ${char_is_signed} ${uchar_max} ${ushrt_max} ${uint_max} ${ulong_max}UL "${long_bit}" ${word_bit}

exec 3>int_base.hpp

echo >&3

exec 3>>int_base.hpp

echo "#ifndef __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__" >&3
echo "#define __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__" >&3
echo >&3

echo "#define ___CHAR_DIGITAL ${char_bit}" >&3
echo "/*the digital of one char, the same as CHAR_BIT.*/" >&3
echo >&3

echo "#define ___CHAR_IS_SIGNED ${char_is_signed}" >&3
echo "/*the char is whether signed. the same as CHAR_MIN != 0*/" >&3
echo >&3

echo "#define ___UCHAR_MAX ${uchar_max}" >&3
echo "/*the max value of unsigned char.*/" >&3
echo >&3

echo "#define ___USHORT_MAX ${ushrt_max}" >&3
echo "/*the max value of unsigned short int.*/" >&3
echo >&3

echo "#define ___UINT_MAX ${uint_max}" >&3
echo "/*the max value of unsigned int.*/" >&3
echo >&3

echo "#define ___ULONG_MAX ${ulong_max}UL" >&3
echo "/*the max value of unsigned long int.*/" >&3
echo >&3

echo "#define ___LONG_DIGITAL ${long_bit}" >&3
echo "/*the digital of long, the same as LONG_BIT.*/" >&3
echo >&3

echo "#define ___WORD_DIGITAL ${word_bit}" >&3
echo "/*the digital of int, the same as WORD_BIT.*/" >&3
echo >&3

echo "#endif // ! __UTILITY_DETAIL_STANDARD_LIBRARY_INT_BASE__" >&3
