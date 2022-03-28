#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_KEYPRESSHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_KEYPRESSHANDLER_HPP

#include "constants/Constants.hpp"
#include "abstractions/event_handling/EventHandlingObject.hpp"

namespace events {

  class KeyPressHandler : virtual public EventHandlingObject {
    protected:
      KeyPressHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::KeyPressHandlerMask); }
    public:
      virtual void handle_key_press(const KeySym& key_sym, const unsigned int& mask) = 0;
      virtual ~KeyPressHandler() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_KEYPRESSHANDLER_HPP */
