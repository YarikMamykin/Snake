#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "IWindow.hpp"
#include <memory>
#include <map>
#include "UI_Object.hpp"
#include "IEventHandler.hpp"

namespace events {

  struct EventHandler : public IEventHandler {

    std::map<constants::HandlerKeys, std::weak_ptr<ui::UI_Object>> listeners;
    XEvent event;

    explicit EventHandler() = default;
    ~EventHandler() {};

    void event_handler_loop(interfaces::IWindow* x_window) override;

    void handle_key_press(const KeySym&& key_sym) override;
    void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;

    void add_listener(constants::HandlerKeys key, std::shared_ptr<ui::UI_Object> listener);

    private:
      template <class EventHandlerType> static EventHandlerType* as_event_handler(std::shared_ptr<ui::UI_Object> object) {
        return dynamic_cast<EventHandlerType*>(object.get());
      }
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
