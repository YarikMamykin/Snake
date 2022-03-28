#ifndef SRC_INCLUDE_VIEWS_GAMENONE_HPP
#define SRC_INCLUDE_VIEWS_GAMENONE_HPP
#include "abstractions/event_handling/NoEventHandler.hpp"
#include "abstractions/views/View.hpp"

namespace views {

  class GameNone final :  public View,
                          public events::NoEventHandler {
    public:
      explicit GameNone();
      virtual ~GameNone();

    public:
      virtual void activate() override;
  };
}



#endif /* SRC_INCLUDE_VIEWS_GAMENONE_HPP */
