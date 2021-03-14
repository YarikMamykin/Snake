#include "EventDispatcher.hpp"
#include "XlibWrapper.hpp"
#include "ClientMessageHandler.hpp"
#include "ExposeEventHandler.hpp"
#include "KeyPressHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "MouseMotionHandler.hpp"
#include "NoEventHandler.hpp"

namespace events {

  std::function<void()> EventDispatcher::dispatch_event(abstractions::ui::AWindow* window, XEvent& event) {
    switch(event.type) {
      case Expose:
        {
          auto* expose_event_handler = dynamic_cast<ExposeEventHandler*>(window);
          return(std::bind(&ExposeEventHandler::handle_expose_event, expose_event_handler));
        }
      case KeyPress: 
        {
          auto* key_press_handler = dynamic_cast<KeyPressHandler*>(window);
          return(std::bind(&KeyPressHandler::handle_key_press, key_press_handler, XLookupKeysym(&event.xkey, 0), event.xkey.state));
        }
      case ButtonPress:
        {
          auto* button_press_event_handler = dynamic_cast<MouseButtonPressHandler*>(window);
          return(std::bind(&MouseButtonPressHandler::handle_button_press, button_press_event_handler, event.xmotion.x, event.xmotion.y, event.xbutton.button));
        }
      case MotionNotify:
        {
          auto* mouse_motion_handler = dynamic_cast<MouseMotionHandler*>(window);
          return(std::bind(&MouseMotionHandler::handle_mouse_motion, mouse_motion_handler, event.xmotion.x, event.xmotion.y));
        }
      case ClientMessage:
        {
          auto* client_message_handler = dynamic_cast<ClientMessageHandler*>(window);
          return(std::bind(&ClientMessageHandler::handle_client_message, client_message_handler, event.xclient.data.l));
        }
    }

    return std::function<void()>();
  }
}
