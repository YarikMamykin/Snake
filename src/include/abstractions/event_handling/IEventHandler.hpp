#ifndef SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP

#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"
#include "ClientMessageHandler.hpp"
#include "ExposeEventHandler.hpp"
#include "Window.hpp"

namespace events {
  class IEventHandler : public MouseButtonPressHandler,
                        public MouseMotionHandler,
                        public KeyPressHandler,
                        public ClientMessageHandler,
                        public ExposeEventHandler {

    public:
      virtual const int get_event_handling_mask() const { return MouseButtonPressHandler::get_event_handling_mask() 
                                                                 | MouseMotionHandler::get_event_handling_mask() 
                                                                 | KeyPressHandler::get_event_handling_mask() 
                                                                 | ClientMessageHandler::get_event_handling_mask()
                                                                 | ExposeEventHandler::get_event_handling_mask(); }
      virtual void event_handler_loop() = 0;
      virtual ~IEventHandler() {};
  };
}

#endif /* SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP */
