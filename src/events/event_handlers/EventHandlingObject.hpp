#pragma once

#include <type_traits>

namespace events {
  enum class HandlersMask : unsigned char {
    NoEventHandlerMask = 0,
    KeyPressHandlerMask = 1,
    MouseMotionHandlerMask = 1 << 1,
    MouseButtonPressHandlerMask = 1 << 2,
    ClientMessageHandlerMask = 1 << 3,
    ExposeEventHandlerMask = 1 << 4
  };

  class EventHandlingObject {
    protected:
      static HandlersMask make_mask(HandlersMask m1, HandlersMask m2) {
         return static_cast<HandlersMask>(
             static_cast<std::underlying_type_t<HandlersMask>>(m1) | 
             static_cast<std::underlying_type_t<HandlersMask>>(m2));
      }

    protected:
      HandlersMask mask;
      EventHandlingObject() : mask(HandlersMask::NoEventHandlerMask) {}

    public:
      virtual const int get_event_handling_mask() const { return static_cast<const int>(this->mask); }
      virtual ~EventHandlingObject() {};
  };

}



