#ifndef SRC_INCLUDE_EVENTS_EVENTDISPATCHER_HPP
#define SRC_INCLUDE_EVENTS_EVENTDISPATCHER_HPP

#include <memory>
#include <map>
#include <functional>
#include "abstractions/ui/Window.hpp"

namespace events {

  struct EventDispatcher {

    explicit EventDispatcher() = default;
    ~EventDispatcher() = default;

    /*
     * event ref is non-const because of XCheckMaskEvent
     */
    std::function<void()> dispatch_event(abstractions::ui::AWindow* window, XEvent& event);
  };
}


#endif /* SRC_INCLUDE_EVENTS_EVENTDISPATCHER_HPP */
