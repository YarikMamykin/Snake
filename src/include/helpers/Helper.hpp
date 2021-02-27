#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"
#include "X11_Window.hpp"

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent();
    static XEvent ConstructChangeViewEvent(const views::ViewID& viewID);
    static XEvent ConstructResubscribeViewEvent();
    static void SendExitApplicationEvent();
    static void SendChangeViewEvent(const views::ViewID& viewID);
    static void SendResubscribeViewEvent();
  };
}
#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
