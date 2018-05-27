
#ifndef __UTILITY_LOGIC_TRIBOOL__
#define __UTILITY_LOGIC_TRIBOOL__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace logic
  {
    namespace boolean
    {
      /*!
      * \brief the indeterminate tag
      *
      * the stuct is on the behalf of the indeterminate value
      * \see logic::boolean::tribool
      */
      struct indeterminate_tag
      {
        constexpr indeterminate_tag()=default;
      };

      /*!
      * \relates logic::boolean::tribool
      * a helper variable
      */
      constexpr indeterminate_tag unknown;

      /*!
      * \brief the three-state boolean
      *
      * this boolean container has an unique meaning : indeterminate<br/>
      *         which means the boolean value is maybe true or false.
      *
      *
      */
      class tribool
      {
        public:
          enum value_t : signed short
          {
            true_value = 1,     ///< this value means the boolean value is true
            false_value = 0,    ///< this value means the boolean value is false
            indeterminate = -1  ///< this value means the boolean value is indeterminate
          };
        public:
          value_t bool_value; ///< the tribool value

        public:
          /*! default constructor will initializate a indeterminate tribool */
          constexpr tribool() noexcept
            :bool_value(tribool::indeterminate)
          { }
          /*! boolean value constructor */
          constexpr tribool(bool __bool) noexcept
            :bool_value(__bool ? tribool::true_value : tribool::false_value)
          { }
          /*! basic constructor */
          constexpr tribool(value_t __bool) noexcept
            :bool_value(__bool)
          { }

#ifdef UTILITY_ONLY_USE_UNIFORM_INITIALIZATION
          /*!
          * \bug this constructor must use uniform initialization
          */
          constexpr tribool(const indeterminate_tag&) noexcept
            :bool_value(tribool::indeterminate)
          { }
          /*!
          * \bug this constructor must use uniform initialization
          */
          constexpr tribool(indeterminate_tag&&) noexcept
            :bool_value(tribool::indeterminate)
          { }
#endif

        public:
          /*! show whether the boolean value is indeterminate */
          constexpr bool is_indeterminate() const noexcept
          { return this->bool_value == tribool::indeterminate;}

          /*! show whether the boolean value is determinate */
          constexpr bool is_determinate() const noexcept
          { return this->bool_value != tribool::indeterminate;}

          /*! show whether the boolean value is the \a true_value */
          constexpr bool is_true() const noexcept
          { return this->bool_value == tribool::true_value;}

          /*! show whether the boolean value is the \a false_value */
          constexpr bool is_false() const noexcept
          { return this->bool_value == tribool::false_value;}

          /*!
          * \brief show whether the boolean value is the true_value
          * \return return 1 if the boolean value is \a true_value.<br/>
          *         return 0 if the boolean value is \a false_value.<br/>
          *         return -1 if the boolean value is indeterminate.<br/>
          */
          constexpr operator int() noexcept
          { return static_cast<int>(this->bool_value);}

        public:
          constexpr tribool operator!() noexcept
          {
            return
              this->bool_value == tribool::false_value ? tribool(true)
              : (this->bool_value == tribool::true_value ? tribool(false)
              : tribool(tribool::indeterminate));
          }
      };

      /*!
      * \relates logic::boolean::tribool
      *
      * show whether the boolean value is indeterminate
      */
      inline bool is_indeterminate(const tribool& __tb) noexcept
      { return __tb.is_indeterminate();}

      /*!
      * \relates logic::boolean::tribool
      *
      *show whether the boolean value is determinate
      */
      inline bool is_determinate(const tribool& __tb) noexcept
      { return __tb.is_determinate();}

      // namespace ops
      // {

      inline tribool operator==(tribool __x, tribool __y) noexcept
      {
        return (__x.is_indeterminate() || __y.is_indeterminate()) ?
          tribool(tribool::indeterminate) :
          tribool(__x.bool_value == __y.bool_value);
      }
      inline tribool operator==(tribool __x, bool __y) noexcept
      { return __x == tribool(__y);}
      inline tribool operator==(bool __x, tribool __y) noexcept
      { return __y == tribool(__x);}
      inline tribool operator==(tribool, indeterminate_tag) noexcept
      { return tribool(tribool::indeterminate);}
      inline tribool operator==(indeterminate_tag, tribool) noexcept
      { return tribool(tribool::indeterminate);}

      inline tribool operator!=(tribool __x, tribool __y) noexcept
      {
        return (__x.is_indeterminate() || __y.is_indeterminate()) ?
        tribool(tribool::indeterminate) :
        tribool(__x.bool_value != __y.bool_value);
      }
      inline tribool operator!=(tribool __x, bool __y) noexcept
      { return __x != tribool(__y);}
      inline tribool operator!=(bool __x, tribool __y) noexcept
      { return __y != tribool(__x);}
      inline tribool operator!=(tribool, indeterminate_tag) noexcept
      { return tribool(tribool::indeterminate);}
      inline tribool operator!=(indeterminate_tag, tribool) noexcept
      { return tribool(tribool::indeterminate);}

      inline tribool operator&&(tribool __x, tribool __y) noexcept
      {
        return __x.is_false() || __y.is_false() ? tribool(false) :
          __x.is_indeterminate() || __y.is_indeterminate() ?
          tribool(tribool::indeterminate) : tribool(true);
      }
      inline tribool operator&&(tribool __x, bool __y) noexcept
      { return __x && tribool(__y);}
      inline tribool operator&&(bool __x, tribool __y) noexcept
      { return __y && tribool(__x);}
      inline tribool operator&&(tribool __x, indeterminate_tag) noexcept
      {
        return __x.is_false() ? tribool(false) :
          tribool(tribool::indeterminate);
      }
      inline tribool operator&&(indeterminate_tag, tribool __y) noexcept
      {
        return __y.is_false() ? tribool(false) :
          tribool(tribool::indeterminate);
      }

      inline tribool operator||(tribool __x, tribool __y) noexcept
      {
        return __x.is_true() || __y.is_true() ? tribool(true) :
          __x.is_indeterminate() || __y.is_indeterminate() ?
          tribool(tribool::indeterminate) : tribool(false);
      }
      inline tribool operator||(tribool __x, bool __y) noexcept
      { return __x || tribool(__y);}
      inline tribool operator||(bool __x, tribool __y) noexcept
      { return __y || tribool(__x);}
      inline tribool operator||(tribool __x, indeterminate_tag) noexcept
      {
        return __x.is_true() ? tribool(true) :
          tribool(tribool::indeterminate);
      }
      inline tribool operator||(indeterminate_tag, tribool __y) noexcept
      {
        return __y.is_true() ? tribool(true) :
          tribool(tribool::indeterminate);
      }

      // }
    }
  }

  namespace literals
  {
    /*!
    * \relates logic::boolean::tribool
    */
    inline constexpr logic::boolean::tribool operator"" _u_tri(unsigned long long __mark)
    {
      using logic::boolean::tribool;
      return __mark > 1 ? tribool(tribool::indeterminate) :
        (__mark ? tribool(true) : tribool(false));
    }

    /*!
    * \relates logic::boolean::tribool
    */
    inline constexpr logic::boolean::tribool operator"" _u_tribool(unsigned long long __mark)
    {
      using logic::boolean::tribool;
      return __mark > 1 ? tribool(tribool::indeterminate) :
        (__mark ? tribool(true) : tribool(false));
    }

  }
}


#endif // ! __UTILITY_LOGIC_TRIBOOL__
