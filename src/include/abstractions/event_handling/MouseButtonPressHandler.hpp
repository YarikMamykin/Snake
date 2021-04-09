#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class MouseButtonPressHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_button_press(const int& x, const int& y, const unsigned int& button) = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::MouseButtonPressHandlerMask; }
      virtual ~MouseButtonPressHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_MOUSEBUTTONPRESSHANDLER_HPP */
