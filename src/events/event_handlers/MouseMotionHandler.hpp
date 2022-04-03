#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP

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

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP */
