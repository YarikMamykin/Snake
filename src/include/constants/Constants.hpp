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
}

namespace views {
  enum ViewID {
    MENU,
    ACTION
  };
}

namespace timing {
  enum class TimerType {
    SingleShot,
    Simple
  };
} 
#endif /* SRC_INCLUDE_CONSTANTS_CONSTANTS_HPP */
