#ifndef SRC_INCLUDE_ABSTRACTIONS_EVENTHANDLINGOBJECT_HPP
#define SRC_INCLUDE_ABSTRACTIONS_EVENTHANDLINGOBJECT_HPP

namespace events {

  class EventHandlingObject {
    public:
      virtual const int get_event_handling_mask() const = 0;
      virtual ~EventHandlingObject() {};
  };

}

#endif /* SRC_INCLUDE_ABSTRACTIONS_EVENTHANDLINGOBJECT_HPP */
