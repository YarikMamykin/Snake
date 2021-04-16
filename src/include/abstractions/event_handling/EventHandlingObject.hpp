#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EVENTHANDLINGOBJECT_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EVENTHANDLINGOBJECT_HPP

#include <type_traits>

namespace events {

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



#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENT_HANDLING_EVENTHANDLINGOBJECT_HPP */
