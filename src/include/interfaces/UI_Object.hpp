#ifndef SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP

#include "XHeaders.hpp"
#include <memory>

namespace ui {

  class UI_Object {
    public:
      template <class EventHandlerType> static EventHandlerType* as_event_handler(std::shared_ptr<UI_Object> object) {
        return dynamic_cast<EventHandlerType*>(object.get());
      }
      virtual ~UI_Object() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP */
