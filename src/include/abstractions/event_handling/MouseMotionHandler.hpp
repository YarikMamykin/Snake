#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class MouseMotionHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_mouse_motion(const int& x, const int& y) = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::MouseMotionHandlerMask; }
      virtual ~MouseMotionHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEMOTIONHANDLER_HPP */
