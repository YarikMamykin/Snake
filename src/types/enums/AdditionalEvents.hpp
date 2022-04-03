#pragma once
#include "xlib/XHeaders.hpp"

namespace events {
  enum AdditionalEvents {
    ExitApplication = LASTEvent + 1,
    ChangeView = LASTEvent + 2,
  };
}

