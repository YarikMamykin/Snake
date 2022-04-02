#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP

#include "constants/Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class NoEventHandler : virtual public EventHandlingObject {
    protected:
      NoEventHandler() : EventHandlingObject() {}
    public:
      virtual ~NoEventHandler() {};
  };

}


#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_NOEVENTHANDLER_HPP */
