#ifndef SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP

#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"
#include "ClientMessageHandler.hpp"
#include "IWindow.hpp"

namespace events {
  class IEventHandler : public MouseButtonPressHandler,
                        public MouseMotionHandler,
                        public KeyPressHandler,
                        public ClientMessageHandler {

    public:
      virtual void event_handler_loop(interfaces::IWindow* x_window) = 0;
      virtual ~IEventHandler() {};
  };
}

#endif /* SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP */
