#pragma once

#include <memory>
#include <map>
#include <functional>
#include <xlib/XHeaders.hpp>
#include "abstractions/ui/Window.hpp"
#include <threads/UI_Event.hpp>

namespace events {

  class EventDispatcher {

    public:

      EventDispatcher() = default;
      ~EventDispatcher() = default;

      threads::UI_Event dispatch_event(std::shared_ptr<abstractions::ui::AWindow> window, XEvent& event);
  };
}
