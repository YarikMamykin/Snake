#ifndef SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class KeyPressHandler : virtual public EventHandlingObject {
    public:
      virtual void handle_key_press(const KeySym&& key_sym) = 0;
      virtual const int get_event_handling_mask() const { return HandlersMask::KeyPressHandlerMask; }
      virtual ~KeyPressHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP */
