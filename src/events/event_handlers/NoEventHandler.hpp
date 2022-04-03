#pragma once

#include "EventHandlingObject.hpp"

namespace events {

  class NoEventHandler : virtual public EventHandlingObject {
    protected:
      NoEventHandler() : EventHandlingObject() {}
    public:
      virtual ~NoEventHandler() {};
  };

}
