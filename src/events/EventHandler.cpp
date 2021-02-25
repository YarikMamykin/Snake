#include "EventHandler.hpp"
#include <iostream>
#include <algorithm>
#include "Exceptions.hpp"
#include "X11_Window.hpp"
#include "XlibWrapper.hpp"

namespace events {

  EventHandler::EventHandler(std::shared_ptr<abstractions::ui::AWindow> window) 
  : window(std::move(std::dynamic_pointer_cast<EventHandlingObject>(window))) {
  }

  void EventHandler::event_handler_loop() {
    using namespace events;
    xlib::XlibWrapper::self()->select_events_to_process();
    try {
      for (;;) {
        xlib::XlibWrapper::self()->next_event(&event);
        switch(event.type) {
          case Expose: handle_expose_event(); break;
          case KeyPress: handle_key_press(XLookupKeysym(&event.xkey, 0), std::move(event.xkey.state)); break; 
          case ButtonPress: handle_button_press(event.xmotion.x, event.xmotion.y, event.xbutton.button); break;
          case MotionNotify: handle_mouse_motion(event.xmotion.x, event.xmotion.y); break;
          case ClientMessage:  handle_client_message(event.xclient.data.l); break; 
          default:break;
        }
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void EventHandler::handle_expose_event() {
    if(window_contains_event_handling_mask(events::HandlersMask::ExposeEventHandlerMask)) {
      auto listener_as_event_handler = window_as_concrete_event_handler<ExposeEventHandler>();
      if(listener_as_event_handler) {
        listener_as_event_handler->handle_expose_event();
      }
    }
  }

  void EventHandler::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    if(window_contains_event_handling_mask(events::HandlersMask::KeyPressHandlerMask)) {
      auto* listener_as_event_handler = window_as_concrete_event_handler<KeyPressHandler>();
      if(listener_as_event_handler) {
        listener_as_event_handler->handle_key_press(std::move(key_sym), std::move(mask));
      }
    }
  }

  void EventHandler::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    if(window_contains_event_handling_mask(events::HandlersMask::MouseButtonPressHandlerMask)) {
      auto* listener_as_event_handler = window_as_concrete_event_handler<MouseButtonPressHandler>();
      listener_as_event_handler->handle_button_press(x,y,button);
    }
  }

  void EventHandler::handle_mouse_motion(const int& x, const int& y) {
    if(window_contains_event_handling_mask(events::HandlersMask::MouseMotionHandlerMask)) {
      auto* listener_as_event_handler = window_as_concrete_event_handler<MouseMotionHandler>();
      listener_as_event_handler->handle_mouse_motion(x,y);
    }
  }

  void EventHandler::handle_client_message(const long* data) {
    if(window_contains_event_handling_mask(events::HandlersMask::ClientMessageHandlerMask)) {
      auto* listener_as_event_handler = window_as_concrete_event_handler<ClientMessageHandler>();
      listener_as_event_handler->handle_client_message(data);
    }

    switch(data[0]) {
      case AdditionalEvents::ExitApplication: 
        {
          throw exceptions::ExitApplication(); 
          break;
        }
      default: return;
    }
  }

  bool EventHandler::window_contains_event_handling_mask(HandlersMask&& mask) const {
    return mask & window->get_event_handling_mask();
  }
}
