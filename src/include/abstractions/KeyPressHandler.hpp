#ifndef SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP

#include "XHeaders.hpp"
#include <memory>

namespace events {

  class KeyPressHandler {
    public:
      virtual void handle_key_press(const KeySym&& key_sym) = 0;
      virtual ~KeyPressHandler() {};
  };

}
#endif /* SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP */
