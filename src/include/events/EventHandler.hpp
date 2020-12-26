#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "Window.hpp"
#include <memory>
#include <map>
#include "EventHandlingObject.hpp"
#include "IEventHandler.hpp"

namespace events {

  struct EventHandler : public IEventHandler {

    std::map<constants::HandlerKeys, std::weak_ptr<EventHandlingObject>> listeners;
    XEvent event;

    explicit EventHandler() = default;
    ~EventHandler() {};

    void event_handler_loop(abstractions::ui::AWindow* x_window) override;

    void handle_key_press(const KeySym&& key_sym) override;
    void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;

    void add_listener(constants::HandlerKeys key, std::shared_ptr<EventHandlingObject> listener);

    private:
      template <class EventHandlerType> 
        static std::shared_ptr<EventHandlerType> 
          as_event_handler(std::shared_ptr<EventHandlingObject> object) {
            return std::dynamic_pointer_cast<EventHandlerType>(object);
      }
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
