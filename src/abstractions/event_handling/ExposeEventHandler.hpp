#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class ExposeEventHandler : virtual public EventHandlingObject {
    protected:
      ExposeEventHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::ExposeEventHandlerMask); }
    public:
      virtual void handle_expose_event() = 0;
      virtual ~ExposeEventHandler() {};
  };

}


#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP */
