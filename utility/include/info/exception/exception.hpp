
#ifndef ___UTILITY__INFO__EXCEPTION___
#define ___UTILITY__INFO__EXCEPTION___

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace info
  {
    namespace exception
    {
      /*!
      * \brief Basic exception class
      *
      * The base of the utility library exception
      *
      * \callgraph
      */
      class exception
      {
        public:
          /*1
          * \brief Default constructor
          */
          exception() noexcept
          { }
          /*!
          * \brief Default deconstructor
          */
          virtual ~exception() noexcept
          { }
          /*!
          * \brief Provide the id of this exception
          */
          virtual const char* what() const noexcept
          {
            static const char __me[] =
              "info::exception::exception";
            return __me;
          }
      };
    }
  }
}

#endif // ! ___UTILITY__INFO__EXCEPTION___
