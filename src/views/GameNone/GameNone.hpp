#pragma once
#include "events/event_handlers/NoEventHandler.hpp"
#include "abstractions/views/View.hpp"

namespace views {

  class GameNone :  public View,
                    public events::NoEventHandler {
    public:
      explicit GameNone();
      virtual ~GameNone();

    public:
      virtual void activate() override;
  };
}



