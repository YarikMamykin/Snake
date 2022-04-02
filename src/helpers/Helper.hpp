#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "constants/Constants.hpp"

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

#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
