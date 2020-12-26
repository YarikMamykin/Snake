#include "EventHandler.hpp"
#include <iostream>
#include <algorithm>
#include "Exceptions.hpp"
#include "X11_Window.hpp"

namespace events {

  void EventHandler::event_handler_loop(abstractions::ui::AWindow* x_window) {
    using namespace events;
    // select kind of events we are interested in
    xlib::X11_Window* x11_window = dynamic_cast<xlib::X11_Window*>(x_window); // OH YES -> FIX IT!
    XSelectInput(x11_window->x_display.display, 
                 x11_window->window, 
                 ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask );
    try {
      for (;;) {
        XNextEvent(x11_window->x_display.display, &event);
        switch(event.type) {
          case Expose: { 
                         x_window->expose(); 
                         break; 
                       }
          case KeyPress: { 
                           handle_key_press(XLookupKeysym(&event.xkey, 0)); 
                           break; 
                         }
          case ButtonPress: { 
                              handle_button_press(event.xmotion.x, event.xmotion.y, event.xbutton.button); 
                              break; 
                            }
          case MotionNotify: { 
                               handle_mouse_motion(event.xmotion.x, event.xmotion.y); 
                               break; 
                             }
          case ClientMessage: { 
                                handle_client_message(event.xclient.data.l); 
                                break; 
                              }
          default:break;
        }
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void EventHandler::handle_key_press(const KeySym&& key_sym) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto listener_pointer = listener.second.lock();
      if(events::HandlersMask::KeyPressHandlerMask & listener_pointer->get_event_handling_mask()) {
        auto listener_as_event_handler = as_event_handler<KeyPressHandler>(listener_pointer);
        if(listener_as_event_handler) {
          listener_as_event_handler->handle_key_press(std::move(key_sym));
        }
      }
    }
  }

  void EventHandler::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto listener_pointer = listener.second.lock();
      if(events::HandlersMask::MouseButtonPressHandlerMask & listener_pointer->get_event_handling_mask()) {
        auto listener_as_event_handler = as_event_handler<MouseButtonPressHandler>(listener_pointer);
        listener_as_event_handler->handle_button_press(x,y,button);
      }
    }
  }

  void EventHandler::handle_mouse_motion(const int& x, const int& y) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto listener_pointer = listener.second.lock();
      if(events::HandlersMask::MouseMotionHandlerMask & listener_pointer->get_event_handling_mask()) {
        auto listener_as_event_handler = as_event_handler<MouseMotionHandler>(listener_pointer);
        listener_as_event_handler->handle_mouse_motion(x,y);
      }
    }
  }

  void EventHandler::handle_client_message(const long* data) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto listener_pointer = listener.second.lock();
      if(events::HandlersMask::ClientMessageHandlerMask & listener_pointer->get_event_handling_mask()) {
        auto listener_as_event_handler = as_event_handler<ClientMessageHandler>(listener_pointer);
        listener_as_event_handler->handle_client_message(data);
      }
    }

    switch(data[0]) {
      case AdditionalEvents::ExitApplication: 
        {
          throw exceptions::ExitApplication(); 
          break;
        }
      case AdditionalEvents::ResubscribeView:
        {
          auto x_window_ptr = listeners.find(constants::HandlerKeys::WINDOW);
          auto x_window = std::dynamic_pointer_cast<abstractions::ui::AWindow>(x_window_ptr->second.lock());
          std::shared_ptr<EventHandlingObject> view_as_ui_object = std::dynamic_pointer_cast<EventHandlingObject>(x_window->get_view());
          this->add_listener(constants::HandlerKeys::WINDOW_VIEW, view_as_ui_object); // Resubscribe view as new-created
          break;
        }
      default: return;
    }
  }

  void EventHandler::add_listener(constants::HandlerKeys key, std::shared_ptr<EventHandlingObject> listener) {
    const auto&& existing_listener = listeners.find(key);
    if(existing_listener != listeners.end()) {
      listeners.erase(key);
    }
    listeners.insert({key, listener});
  }
}
