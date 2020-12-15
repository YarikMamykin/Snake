#ifndef SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP

#include "Constants.hpp"

namespace events {

  class ClientMessageHandler {
    public:
      virtual void handle_client_message(const long* data) = 0;
      virtual ~ClientMessageHandler() {};

      static const HandlersMask mask = HandlersMask::ClientMessageHandlerMask;
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_CLIENTMESSAGEHANDLER_HPP */
