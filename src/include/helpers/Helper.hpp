#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent();
    static XEvent ConstructChangeViewEvent(const views::ViewID& viewID);
    static void SendExitApplicationEvent();
    static void SendChangeViewEvent(const views::ViewID& viewID);
  };
}
#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
