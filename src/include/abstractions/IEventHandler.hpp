#ifndef SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP
#define SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP

#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"

namespace events {
  class IEventHandler : public MouseButtonPressHandler,
                        public MouseMotionHandler,
                        public KeyPressHandler {

    public:
      virtual ~IEventHandler() {};
  };
}

#endif /* SRC_INCLUDE_INTERFACES_IEVENTHANDLER_HPP */
