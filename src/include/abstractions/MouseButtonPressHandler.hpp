#ifndef SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"

namespace events {

  class MouseButtonPressHandler {
    public:
      virtual void handle_button_press(const int& x, const int& y, const unsigned int& button) = 0;
      virtual ~MouseButtonPressHandler() {};

      static const HandlersMask mask = HandlersMask::MouseButtonPressHandlerMask;
  };

}
#endif /* SRC_INCLUDE_INTERFACES_MOUSEBUTTONPRESSHANDLER_HPP */
