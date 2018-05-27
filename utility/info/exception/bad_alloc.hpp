
#ifndef __UTILITY_INFO_EXCEPTION_BAD_ALLOC__
#define __UTILITY_INFO_EXCEPTION_BAD_ALLOC__

#include<utility/config/utility_config.hpp>
#include<utility/info/exception/exception.hpp>

namespace utility
{
  namespace info
  {
    namespace exception
    {
      /*!
      * \brief Allocate failed exception
      *
      * This exception will be throwed when allocating memory is failed
      */
      class bad_alloc : public exception
      {
        public:
          /*1
          * \brief Default constructor
          */
          bad_alloc() noexcept
          { }
          /*!
          * \brief Default deconstructor
          */
          virtual ~bad_alloc() noexcept
          { }
          /*!
          * \brief Provide the id of this exception
          */
          virtual const char* whar() const noexcept
          {
            static const char __me[] =
              "info::exception::bad_alloc";
            return __me;
          }
      };
    }
  }
}

#endif // ! __UTILITY_INFO_EXCEPTION_BAD_ALLOC__
