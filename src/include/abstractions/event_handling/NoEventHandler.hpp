#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class NoEventHandler : virtual public EventHandlingObject {
    public:
      virtual const int get_event_handling_mask() const { return HandlersMask::NoEventHandlerMask; }
      virtual ~NoEventHandler() {};
  };

}


#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP */
