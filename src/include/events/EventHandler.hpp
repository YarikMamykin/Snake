#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "X11_Window.hpp"
#include <memory>
#include <map>
#include "UI_Object.hpp"
#include "IEventHandler.hpp"

namespace events {

  struct EventHandler : public IEventHandler {

    std::map<int, MouseMotionHandler*> mouse_motion_listeners;
    std::map<int, MouseButtonPressHandler*> mouse_button_press_listeners;
    std::map<int, KeyPressHandler*> key_press_listeners;
    XEvent event;

    explicit EventHandler() = default;
    ~EventHandler() {};

    void event_handler_loop(xlib::X11_Window& x_window);

    void handle_key_press(const KeySym&& key_sym) override;
    void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data, xlib::X11_Window& x_window);

    void add_mouse_motion_listener(int key, std::shared_ptr<ui::UI_Object> listener);
    void add_mouse_button_press_listener(int key, std::shared_ptr<ui::UI_Object> listener);
    void add_key_press_listener(int key, std::shared_ptr<ui::UI_Object> listener);

    private:
      template <class EventHandlerType> static EventHandlerType* as_event_handler(std::shared_ptr<ui::UI_Object> object) {
        return dynamic_cast<EventHandlerType*>(object.get());
      }
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
