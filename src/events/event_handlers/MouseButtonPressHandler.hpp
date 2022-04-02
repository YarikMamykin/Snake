#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP

#include "constants/Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class MouseButtonPressHandler : virtual public EventHandlingObject {
    protected:
      MouseButtonPressHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::MouseButtonPressHandlerMask); }
    public:
      virtual void handle_button_press(const int& x, const int& y, const unsigned int& button) = 0;
      virtual ~MouseButtonPressHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP */
