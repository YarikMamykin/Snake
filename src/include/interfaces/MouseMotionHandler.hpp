#ifndef SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP

#include "XHeaders.hpp"
#include "UI_Object.hpp"
#include <memory>

namespace ui {

  class MouseMotionHandler : public UI_Object {
    public:
      virtual void handle_mouse_motion(const int& x, const int& y) = 0;
      virtual ~MouseMotionHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_MOUSEMOTIONHANDLER_HPP */
