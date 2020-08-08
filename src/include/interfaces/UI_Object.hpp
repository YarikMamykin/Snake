#ifndef SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP

#include "XHeaders.hpp"

namespace ui {

  class UI_Object {
    public:
      virtual void on_event(const XEvent& event);
      virtual ~UI_Object() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP */
