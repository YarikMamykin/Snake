#ifndef SRC_INCLUDE_HELPERS_HELPER_HPP
#define SRC_INCLUDE_HELPERS_HELPER_HPP

#include "XHeaders.hpp"
#include "Constants.hpp"
#include "X11_Window.hpp"

namespace helpers {
  struct Helper {
    static XEvent ConstructExitApplicationEvent(const xlib::X11_Window* x_window);
    static XEvent ConstructChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID);
    static XEvent ConstructResubscribeViewEvent(const xlib::X11_Window* x_window);
    static void SendExitApplicationEvent(const xlib::X11_Window* x_window);
    static void SendChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID);
    static void SendResubscribeViewEvent(const xlib::X11_Window* x_window);
  };
}
#endif /* SRC_INCLUDE_HELPERS_HELPER_HPP */
