#ifndef SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP
#define SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP

#include "XHeaders.hpp"

namespace constants {
  enum class HandlerKeys {
    WINDOW,
    WINDOW_VIEW
  };
}

namespace events {
  enum AdditionalEvents {
    ExitApplication = LASTEvent + 1,
    ChangeView = LASTEvent + 2
  };

  enum HandlersMask {
    KeyPressHandlerMask = 2,
    MouseMotionHandlerMask = 2 << 1,
    MouseButtonPressHandlerMask = 2 << 2
  };
}

namespace views {
  enum ViewID {
    MENU,
    ACTION,
    OVER,
    NONE
  };
}

namespace timing {
  enum class TimerType {
    SingleShot,
    Simple
  };
} 

namespace game_objects {
  enum class SnakeDirection {
    Up,
    Down,
    Left,
    Right
  };

  enum class RotationDirection {
    NONE,
    Clockwize,
    Counterclockwize
  };
}

#endif /* SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP */
