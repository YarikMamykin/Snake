#ifndef SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP

#include "XHeaders.hpp"
#include <memory>

namespace ui {

  class UI_Object {
    public:
      virtual const int get_event_handling_mask() const = 0;
      virtual ~UI_Object() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP */
