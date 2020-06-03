#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "X11_Display.hpp"

namespace xlib {
  struct X11_Window {
    X11_Window(X11_Display& x_display, int screen);
    ~X11_Window();
    void show();
    void expose();

    Window window;
    X11_Display& x_display;
    int screen;
    std::string msg;
    GC graphical_context;
  };
}

#endif
