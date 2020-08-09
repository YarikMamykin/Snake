#ifndef SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP

#include "XHeaders.hpp"

namespace ui {

  class UI_Object {
    public:
      virtual void handle_key_press(const KeySym&& key_sym) = 0;
      virtual void handle_button_press(const unsigned int& button) = 0;
      virtual void handle_mouse_position(const int& x, const int& y) = 0;
      virtual ~UI_Object() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_UI_OBJECT_HPP */
