#include "EventHandler.hpp"
#include <iostream>
#include <algorithm>
#include "Exceptions.hpp"

namespace events {

  void EventHandler::event_handler_loop(xlib::X11_Window& x_window) {
    using namespace events;
    // select kind of events we are interested in
    XSelectInput(x_window.x_display.display, x_window.window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask );
    try {
      for (;;) {
        XNextEvent(x_window.x_display.display, &event);
        switch(event.type) {
          case Expose: { 
                         x_window.expose(); 
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
      auto&& listener_pointer = listener.second.lock();
      auto&& listener_as_event_handler = as_event_handler<KeyPressHandler>(listener_pointer);
      if(events::KeyPressHandler::mask & listener_pointer->get_event_handling_mask()) {
        listener_as_event_handler->handle_key_press(std::move(key_sym));
      }
    }
  }

  void EventHandler::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto&& listener_pointer = listener.second.lock();
      auto&& listener_as_event_handler = as_event_handler<MouseButtonPressHandler>(listener_pointer);
      if(events::MouseButtonPressHandler::mask & listener_pointer->get_event_handling_mask()) {
        listener_as_event_handler->handle_button_press(x,y,button);
      }
    }
  }

  void EventHandler::handle_mouse_motion(const int& x, const int& y) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto&& listener_pointer = listener.second.lock();
      auto&& listener_as_event_handler = as_event_handler<MouseMotionHandler>(listener_pointer);
      if(events::MouseMotionHandler::mask & listener_pointer->get_event_handling_mask()) {
        listener_as_event_handler->handle_mouse_motion(x,y);
      }
    }
  }

  void EventHandler::handle_client_message(const long* data) {
    for(auto& listener : listeners) {
      if(listener.second.expired()) {
        continue;
      }
      auto&& listener_pointer = listener.second.lock();
      auto&& listener_as_event_handler = as_event_handler<ClientMessageHandler>(listener_pointer);
      if(events::ClientMessageHandler::mask & listener_pointer->get_event_handling_mask()) {
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
          auto x_window = std::dynamic_pointer_cast<interfaces::IWindow>(x_window_ptr->second.lock());
          std::shared_ptr<ui::UI_Object> view_as_ui_object = std::dynamic_pointer_cast<ui::UI_Object>(x_window->get_view());
          this->add_listener(constants::HandlerKeys::WINDOW_VIEW, view_as_ui_object); // Resubscribe view as new-created
          break;
        }
      default: return;
    }
  }

  void EventHandler::add_listener(constants::HandlerKeys key, std::shared_ptr<ui::UI_Object> listener) {
    const auto&& existing_listener = listeners.find(key);
    if(existing_listener != listeners.end()) {
      listeners.erase(key);
    }
    listeners.insert({key, listener});
  }
}
