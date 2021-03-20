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
    ChangeView = LASTEvent + 2,
  };

  enum HandlersMask {
    NoEventHandlerMask = 0,
    KeyPressHandlerMask = 1,
    MouseMotionHandlerMask = 1 << 1,
    MouseButtonPressHandlerMask = 1 << 2,
    ClientMessageHandlerMask = 1 << 3,
    ExposeEventHandlerMask = 1 << 4
  };
}

namespace views {
  enum ViewID {
    MENU,
    ACTION,
    OVER,
    SETTINGS,
    ABOUT,
    NONE
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

namespace ui {
  enum class AnchorType {
    CENTER,
    LEFT,
    RIGHT
  };

  enum class LayoutType {
    HORIZONTAL,
    VERTICAL
  };
}

#endif /* SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP */
