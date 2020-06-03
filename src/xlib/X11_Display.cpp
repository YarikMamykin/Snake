#include "X11_Display.hpp"


namespace xlib {
  X11_Display::X11_Display() {
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
      error_msg = "Cannot open display";
    }
  }

  X11_Display::~X11_Display() {
    XCloseDisplay(display);
  }
}
