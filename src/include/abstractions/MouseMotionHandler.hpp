#ifndef SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class MouseMotionHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_mouse_motion(const int& x, const int& y) = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::MouseMotionHandlerMask; }
      virtual ~MouseMotionHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP */
