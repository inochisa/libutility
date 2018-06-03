

#ifndef __UTILITY_SYSTEM_KEYBOARD__
#define __UTILITY_SYSTEM_KEYBOARD__

extern "C++"
{

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace system
  {
    namespace keyboard
    {
      enum class keyboard_key : wchar_t
      {
        tab = '\t',
        esc = 033,
        space = ' ',
        exclamation_mark = '!',
        double_quote = '\"',
        number_sign = '#',
        dollar_sign = '$',
        percent_sign  = '%',
        ampersand = '&',
        single_quote = '\'',
        left_parenthese = '(',
        right_parenthese = ')',
        asterisk = '*',
        add = '+',
        comma = ',',
        dash = '-',
        dot = '.',
        slash = '/',
        char_0 = '0',
        char_1 = '1',
        char_2 = '2',
        char_3 = '3',
        char_4 = '4',
        char_5 = '5',
        char_6 = '6',
        char_7 = '7',
        char_8 = '8',
        char_9 = '9',
        colon = ':',
        semicolon = ';',
        lt = '<',
        equal = '=',
        gt = '>',
        question_mark = '?',
        at_sign = '@',
        char_A = 'A',
        char_B = 'B',
        char_C = 'C',
        char_D = 'D',
        char_E = 'E',
        char_F = 'F',
        char_G = 'G',
        char_H = 'H',
        char_I = 'I',
        char_J = 'J',
        char_K = 'K',
        char_L = 'L',
        char_M = 'M',
        char_N = 'N',
        char_O = 'O',
        char_P = 'P',
        char_Q = 'Q',
        char_R = 'R',
        char_S = 'S',
        char_T = 'T',
        char_U = 'U',
        char_V = 'V',
        char_W = 'W',
        char_X = 'X',
        char_Y = 'Y',
        char_Z = 'Z',
        left_square_brace = '[',
        backslash	 = '\\',
        right_square_brace = ']',
        circumflex = '^',
        underscore = '_',
        grave_accent = '`',
        char_a = 'a',
        char_b = 'b',
        char_c = 'c',
        char_d = 'd',
        char_e = 'e',
        char_f = 'f',
        char_g = 'g',
        char_h = 'h',
        char_i = 'i',
        char_j = 'j',
        char_k = 'k',
        char_l = 'l',
        char_m = 'm',
        char_n = 'n',
        char_o = 'o',
        char_p = 'p',
        char_q = 'q',
        char_r = 'r',
        char_s = 's',
        char_t = 't',
        char_u = 'u',
        char_v = 'v',
        char_w = 'w',
        char_x = 'x',
        char_y = 'y',
        char_z = 'z',
        left_curly_brace = '{',
        vbar = '|',
        right_curly_brace = '}',
        tilde = '~',
        backspace = 127,
        up_arrow,
        down_arrow,
        left_arrow,
        right_arrow,
        insert,
        home,
        end,
        page_up,
        page_down,
        del,
        unknown
      };

      int kbhit() noexcept;
      keyboard_key keyboard_one_step() noexcept;
    }
  }
}

}

#endif // ! __UTILITY_SYSTEM_KEYBOARD__
