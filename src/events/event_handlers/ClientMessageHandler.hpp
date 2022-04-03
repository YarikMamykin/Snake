#pragma once

#include "types/enums/HandlerKeys.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class ClientMessageHandler : virtual public EventHandlingObject {
    protected:
      ClientMessageHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::ClientMessageHandlerMask); }
    public:
      virtual void handle_client_message(const long* data) = 0;
      virtual ~ClientMessageHandler() {};
  };

}
