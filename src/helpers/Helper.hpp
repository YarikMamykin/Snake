#pragma once

#include "types/enums/ViewID.hpp"
#include <xlib/XHeaders.hpp>

namespace xlib {
  class XProxy;
}

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent();
    static XEvent ConstructChangeViewEvent(const views::ViewID& viewID);
    static void SendExitApplicationEvent(xlib::XProxy& proxy);
    static void SendChangeViewEvent(xlib::XProxy& proxy, const views::ViewID& viewID);
  };
}
