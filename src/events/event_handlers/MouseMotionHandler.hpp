#pragma once

#include "types/enums/HandlerKeys.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class MouseMotionHandler : virtual public EventHandlingObject {
    protected:
      MouseMotionHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::MouseMotionHandlerMask); }
    public:
      virtual void handle_mouse_motion(const int& x, const int& y) = 0;
      virtual ~MouseMotionHandler() {};
  };

}

