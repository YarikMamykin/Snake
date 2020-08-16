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
        std::cout << "EVENT CODE: " << event.type << std::endl;
        switch(event.type) {
          case Expose: { x_window.expose(); break; }
          case KeyPress: { handle_key_press(XLookupKeysym(&event.xkey, 0)); break; }
          case ButtonPress: { handle_button_press(event.xmotion.x, event.xmotion.y, event.xbutton.button); break; }
          case MotionNotify: { handle_mouse_motion(event.xmotion.x, event.xmotion.y); break; }
          case ClientMessage: { handle_client_message(event.xclient.data.l, x_window); break; }
          default:break;
        }
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void EventHandler::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Delete: { 
                        throw exceptions::ExitApplication(); 
                        break; 
                      }
      default: {
                 for(auto& listener : key_press_listeners) {
                   listener.second->handle_key_press(std::move(key_sym));
                 }
                 break;
               };
    }
  }

  void EventHandler::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    switch(button) {
      case Button1: { std::cout << "LBM PRESSED" << std::endl; break; }
      case Button2: { std::cout << "MBM PRESSED" << std::endl; break; }
      case Button3: { std::cout << "RBM PRESSED" << std::endl; break; }
      default:return;
    }

    for(auto& listener : mouse_button_press_listeners) {
      listener.second->handle_button_press(x,y,button);
    }
  }

  void EventHandler::handle_mouse_motion(const int& x, const int& y) {
    for(auto& listener : mouse_motion_listeners) {
      listener.second->handle_mouse_motion(x,y);
    }
  }

  void EventHandler::handle_client_message(const long* data, xlib::X11_Window& x_window) {
    switch(data[0]) {
      case AdditionalEvents::ExitApplication: { throw exceptions::ExitApplication(); break; }
      case AdditionalEvents::ChangeView: { x_window.change_view(static_cast<views::ViewID>(data[1])); 
                                           switch(data[1]) {
                                             case views::ViewID::ACTION: { this->add_key_press_listener(static_cast<int>(HandlerKeys::WINDOW_VIEW), views::View::as_event_handler<ui::KeyPressHandler>(x_window.view)); 
                                                                           break; 
                                                                         }
                                             case views::ViewID::MENU: { this->add_mouse_button_press_listener(static_cast<int>(HandlerKeys::WINDOW_VIEW), views::View::as_event_handler<ui::MouseButtonPressHandler>(x_window.view)); 
                                                                         this->add_mouse_motion_listener(static_cast<int>(HandlerKeys::WINDOW_VIEW), views::View::as_event_handler<ui::MouseMotionHandler>(x_window.view));
                                                                         break;
                                                                       }
                                           }
                                           break; 
                                         }
    }
  }

  void EventHandler::add_mouse_motion_listener(int key, ui::MouseMotionHandler* listener) {
    const auto existing_listener = mouse_motion_listeners.find(key);
    if(existing_listener != mouse_motion_listeners.end()) {
      mouse_motion_listeners.erase(key);
    }
    mouse_motion_listeners.insert({key, listener});
  }

  void EventHandler::add_mouse_button_press_listener(int key, ui::MouseButtonPressHandler* listener) {
    const auto existing_listener = mouse_button_press_listeners.find(key);
    if(existing_listener != mouse_button_press_listeners.end()) {
      mouse_button_press_listeners.erase(key);
    }
    mouse_button_press_listeners.insert({key, listener});
  }

  void EventHandler::add_key_press_listener(int key, ui::KeyPressHandler* listener) {
    const auto existing_listener = key_press_listeners.find(key);
    if(existing_listener != key_press_listeners.end()) {
      key_press_listeners.erase(key);
    }
    key_press_listeners.insert({key, listener});
  }
}
