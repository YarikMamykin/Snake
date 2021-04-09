#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "xlib/XHeaders.hpp"
#include "constants/Constants.hpp"

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent();
    static XEvent ConstructChangeViewEvent(const views::ViewID& viewID);
    static void SendExitApplicationEvent();
    static void SendChangeViewEvent(const views::ViewID& viewID);
  };
}

#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
