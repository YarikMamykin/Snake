#pragma once

#include <xlib/XHeaders.hpp>
#include "types/enums/HandlerKeys.hpp"
#include "EventHandlingObject.hpp"

namespace events {

  class KeyPressHandler : virtual public EventHandlingObject {
    protected:
      KeyPressHandler() : EventHandlingObject() { mask = make_mask(mask, HandlersMask::KeyPressHandlerMask); }
    public:
      virtual void handle_key_press(const KeySym& key_sym, const unsigned int& mask) = 0;
      virtual ~KeyPressHandler() {};
  };

}
