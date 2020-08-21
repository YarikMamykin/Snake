#ifndef SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP

#include "XHeaders.hpp"
#include <memory>

namespace events {

  class MouseMotionHandler {
    public:
      virtual void handle_mouse_motion(const int& x, const int& y) = 0;
      virtual ~MouseMotionHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP */
