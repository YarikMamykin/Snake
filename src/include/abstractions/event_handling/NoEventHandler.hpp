#ifndef SRC_INCLUDE_ABSTRACTIONS_NOEVENTHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_NOEVENTHANDLER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class NoEventHandler : virtual public EventHandlingObject {
    public:
      virtual const int get_event_handling_mask() const { return HandlersMask::NoEventHandlerMask; }
      virtual ~NoEventHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_NOEVENTHANDLER_HPP */
