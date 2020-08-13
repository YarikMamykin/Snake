#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "XHeaders.hpp"
#include "EventHandler.hpp"
#include "ViewID.hpp"

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent(const xlib::X11_Window* x_window);
    static XEvent ConstructChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID);
  };
}
#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
