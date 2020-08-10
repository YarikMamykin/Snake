#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "X11_Window.hpp"
#include <memory>
#include <list>
#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"

namespace events {

  struct EventHandler {
    std::list<ui::MouseMotionHandler*> mouse_motion_listeners;
    std::list<ui::MouseButtonPressHandler*> mouse_button_press_listeners;
    std::list<ui::KeyPressHandler*> key_press_listeners;
    XEvent event;


    explicit EventHandler() = default;
    void event_handler_loop(xlib::X11_Window& x_window);

    void handle_key_press(const KeySym&& key_sym);
    void handle_button_press(const int& x, const int& y, const unsigned int& button);
    void handle_mouse_motion(const int& x, const int& y);

    void add_mouse_motion_listener(ui::MouseMotionHandler* listener);
    void add_mouse_button_press_listener(ui::MouseButtonPressHandler* listener);
    void add_key_press_listener(ui::KeyPressHandler* listener);
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
