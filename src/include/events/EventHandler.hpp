#ifndef SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP
#define SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP

#include "Window.hpp"
#include <memory>
#include <map>
#include "EventHandlingObject.hpp"
#include "IEventHandler.hpp"

namespace events {

  struct EventHandler : public IEventHandler {

    std::shared_ptr<EventHandlingObject> window;
    XEvent event;

    explicit EventHandler(std::shared_ptr<abstractions::ui::AWindow> window);
    ~EventHandler() {};

    void event_handler_loop() override;

    void handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) override;
    void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;
    void handle_expose_event() override;

    private:
      bool window_contains_event_handling_mask(HandlersMask&& mask) const;

      template <typename EventHandlerType> EventHandlerType* window_as_concrete_event_handler() {
        return dynamic_cast<EventHandlerType*>(window.get());
      }
  };
}
#endif /* SRC_INCLUDE_EVENTS_EVENTHANDLER_HPP */
