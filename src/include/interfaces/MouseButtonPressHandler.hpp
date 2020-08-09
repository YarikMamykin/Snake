#ifndef SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP

#include "XHeaders.hpp"
#include "UI_Object.hpp"
#include <memory>

namespace ui {

  class MouseButtonPressHandler : public UI_Object {
    public:
      virtual void handle_button_press(const unsigned int& button) = 0;
      virtual ~MouseButtonPressHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP */
