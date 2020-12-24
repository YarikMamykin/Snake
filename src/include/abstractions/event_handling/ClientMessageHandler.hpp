#ifndef SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP

#include "Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class ClientMessageHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_client_message(const long* data) = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::ClientMessageHandlerMask; }
      virtual ~ClientMessageHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP */