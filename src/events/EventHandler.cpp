#include "EventHandler.hpp"
#include <iostream>

namespace events {

  void EventHandler::event_handler_loop(xlib::X11_Window& x_window) {
    // select kind of events we are interested in
    XSelectInput(x_window.x_display.display, x_window.window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask);
    try {
      for (;;) {
        XNextEvent(x_window.x_display.display, &event);
        switch(event.type) {
          case Expose: { x_window.expose(); break; }
          case KeyPress: { handle_key_press(XLookupKeysym(&event.xkey, 0)); break; }
          case ButtonPress: { handle_button_press(event.xbutton.button); break; }
          case MotionNotify: { handle_mouse_motion(event.xmotion.x, event.xmotion.y); break; }
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
                        throw ExitApplication(); 
                        break; 
                      }
      default: {
                 for(auto& listener : key_press_listeners) {
                   listener->handle_key_press(std::move(key_sym));
                 }
                 break;
               };
    }
  }

  void EventHandler::handle_button_press(const unsigned int& button) {
    switch(button) {
      case Button1: { std::cout << "LBM PRESSED" << std::endl; break; }
      case Button2: { std::cout << "MBM PRESSED" << std::endl; break; }
      case Button3: { std::cout << "RBM PRESSED" << std::endl; break; }
      default:return;
    }

    for(auto& listener : mouse_button_press_listeners) {
      listener->handle_button_press(button);
    }
  }

  void EventHandler::handle_mouse_motion(const int& x, const int& y) {
    for(auto& listener : mouse_motion_listeners) {
      listener->handle_mouse_motion(x,y);
    }
  }

  void EventHandler::add_mouse_motion_listener(ui::MouseMotionHandler* listener) {
    mouse_motion_listeners.push_back(listener);
  }

  void EventHandler::add_mouse_button_press_listener(ui::MouseButtonPressHandler* listener) {
    mouse_button_press_listeners.push_back(listener);
  }

  void EventHandler::add_key_press_listener(ui::KeyPressHandler* listener) {
    key_press_listeners.push_back(listener);
  }
}
