
#include"keyboard.hpp"

#if defined(__linux__)
#include<cstdio>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

namespace utility
{
  namespace system
  {
    namespace keyboard
    {
      char read_one_char() noexcept
      {
        using std::getchar;

        static termios __old, __new;
        tcgetattr(STDIN_FILENO, &__old);
        __new = __old;
        __new.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &__new);
        char __res = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &__old);

        return __res;
      }

      int kbhit() noexcept
      {
        using std::ungetc;
        using std::getchar;

        struct termios __old, __new;
        int __res;
        int __old_fcntl;

        tcgetattr(STDIN_FILENO, &__old);
        __new = __old;
        __new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &__new);
        __old_fcntl = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, __old_fcntl | O_NONBLOCK);

        __res = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &__old);
        fcntl(STDIN_FILENO, F_SETFL, __old_fcntl);

        if(__res != EOF)
        {
          ungetc(__res, stdin);
          return 1;
        }

        return 0;
      }

    }

  }

}

#elif defined(__WIN32) || defined(__WIN64)
#include<conio.h>
#include<cstdio>

namespace utility
{
  namespace system
  {
    namespace keyboard
    {
      int kbhit() noexcept
      {
        return ::_kbhit();
      }

      char read_one_char() noexcept
      {
        while(!keyboard::kbhit())
        { }
        return getch();
      }

    }

  }

}

#endif // ! system specific

namespace utility
{
  namespace system
  {
    namespace keyboard
    {
      keyboard_key keyboard_one_step() noexcept
      {
        char __char = read_one_char();
        if(__char == char{0x1B})
        {
          if(!keyboard::kbhit())
          { return keyboard_key::esc;}
          if(keyboard::read_one_char() == '[')
          {
            if(!keyboard::kbhit())
            { return keyboard_key::unknown;}
            __char = keyboard::read_one_char();
            switch(__char)
            {
              case 'A':
                return keyboard_key::up_arrow;
              case 'B':
                return keyboard_key::down_arrow;
              case 'C':
                return keyboard_key::right_arrow;
              case 'D':
                return keyboard_key::left_arrow;
              case 'F':
                return keyboard_key::end;
              case 'H':
                return keyboard_key::home;
              case '2':
                if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
                { return keyboard_key::unknown;}
                return keyboard_key::insert;
              case '3':
                if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
                { return keyboard_key::unknown;}
                return keyboard_key::del;
              case '5':
                if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
                { return keyboard_key::unknown;}
                return keyboard_key::page_up;
              case '6':
                if(!keyboard::kbhit() || keyboard::read_one_char() != '~')
                { return keyboard_key::unknown;}
                return keyboard_key::page_down;
              default:
                return keyboard_key::unknown;
            }
          }
        }

        return static_cast<keyboard_key>(__char);
      }
    }
  }
}
