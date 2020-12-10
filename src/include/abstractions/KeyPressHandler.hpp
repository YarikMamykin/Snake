#ifndef SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"

namespace events {

  class KeyPressHandler {
    public:
      virtual void handle_key_press(const KeySym&& key_sym) = 0;
      virtual ~KeyPressHandler() {};

      static const HandlersMask mask = HandlersMask::KeyPressHandlerMask;
  };

}
#endif /* SRC_INCLUDE_INTERFACES_KEYPRESSHANDLER_HPP */
