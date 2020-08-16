#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "X11_Window.hpp"
#include <memory>
#include <map>
#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"


namespace events {

  struct EventHandler {
    std::map<int, ui::MouseMotionHandler*> mouse_motion_listeners;
    std::map<int, ui::MouseButtonPressHandler*> mouse_button_press_listeners;
    std::map<int, ui::KeyPressHandler*> key_press_listeners;
    XEvent event;


    explicit EventHandler() = default;
    void event_handler_loop(xlib::X11_Window& x_window);

    void handle_key_press(const KeySym&& key_sym);
    void handle_button_press(const int& x, const int& y, const unsigned int& button);
    void handle_mouse_motion(const int& x, const int& y);
    void handle_client_message(const long* data, xlib::X11_Window& x_window);

    void add_mouse_motion_listener(int key, ui::MouseMotionHandler* listener);
    void add_mouse_button_press_listener(int key, ui::MouseButtonPressHandler* listener);
    void add_key_press_listener(int key, ui::KeyPressHandler* listener);
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
