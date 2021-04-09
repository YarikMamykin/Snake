#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class ExposeEventHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_expose_event() = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::ExposeEventHandlerMask; }
      virtual ~ExposeEventHandler() {};
  };

}


#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EXPOSEEVENTHANDLER_HPP */
