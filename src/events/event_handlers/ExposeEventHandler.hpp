#pragma once

#include "types/enums/HandlerKeys.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class ExposeEventHandler : virtual public EventHandlingObject {
    protected:
      ExposeEventHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::ExposeEventHandlerMask); }
    public:
      virtual void handle_expose_event() = 0;
      virtual ~ExposeEventHandler() {};
  };

}
