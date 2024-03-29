#include "EventDispatcher.hpp"
#include "events/event_handlers/ClientMessageHandler.hpp"
#include "events/event_handlers/ExposeEventHandler.hpp"
#include "events/event_handlers/KeyPressHandler.hpp"
#include "events/event_handlers/MouseButtonPressHandler.hpp"
#include "events/event_handlers/MouseMotionHandler.hpp"
#include "events/event_handlers/NoEventHandler.hpp"

namespace events {

  std::function<void()> EventDispatcher::dispatch_event(std::shared_ptr<abstractions::ui::AWindow> window, XEvent& event) {
    switch(event.type) {
      case Expose:
        {
          auto expose_event_handler = std::dynamic_pointer_cast<ExposeEventHandler>(window);
          return(std::bind(&ExposeEventHandler::handle_expose_event, expose_event_handler));
        }
      case KeyPress: 
        {
          auto key_press_handler = std::dynamic_pointer_cast<KeyPressHandler>(window);
          return(std::bind(&KeyPressHandler::handle_key_press, key_press_handler, XLookupKeysym(&event.xkey, 0), event.xkey.state));
        }
      case ButtonPress:
        {
          auto button_press_event_handler = std::dynamic_pointer_cast<MouseButtonPressHandler>(window);
          return(std::bind(&MouseButtonPressHandler::handle_button_press, button_press_event_handler, event.xmotion.x, event.xmotion.y, event.xbutton.button));
        }
      case MotionNotify:
        {
          auto mouse_motion_handler = std::dynamic_pointer_cast<MouseMotionHandler>(window);
          return(std::bind(&MouseMotionHandler::handle_mouse_motion, mouse_motion_handler, event.xmotion.x, event.xmotion.y));
        }
      case ClientMessage:
        {
          auto client_message_handler = std::dynamic_pointer_cast<ClientMessageHandler>(window);
          return(std::bind(&ClientMessageHandler::handle_client_message, client_message_handler, event.xclient.data.l));
        }
    }

    return std::function<void()>();
  }
}
