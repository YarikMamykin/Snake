#ifndef SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP
#define SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP

#include "XHeaders.hpp"
#include <map>
#include "Color.hpp"

namespace constants {
  enum class HandlerKeys {
    WINDOW,
    WINDOW_VIEW
  };

  typedef std::map<unsigned char, color::Color> COLOR_SCHEME_TYPE;
}

namespace events {
  enum AdditionalEvents {
    ExitApplication = LASTEvent + 1,
    ChangeView = LASTEvent + 2,
    ResubscribeView = LASTEvent + 3
  };

  enum HandlersMask {
    NoEventHandlerMask = 0,
    KeyPressHandlerMask = 1,
    MouseMotionHandlerMask = 1 << 1,
    MouseButtonPressHandlerMask = 1 << 2,
    ClientMessageHandlerMask = 1 << 3
  };
}

namespace views {
  enum ViewID {
    MENU,
    ACTION,
    OVER,
    SETTINGS,
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

  enum ColorSchemeID : unsigned char { 
    BackgroundColor,
    TextColor,
    FrameColor,
    FontColor
  };
}

#endif /* SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP */
