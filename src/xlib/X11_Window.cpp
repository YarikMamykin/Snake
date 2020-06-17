#include "X11_Window.hpp"

namespace xlib {

  X11_Window::X11_Window(X11_Display& x_display, int screen) 
    : x_display(x_display)
      , screen(screen) 
      , msg("Hello, World!") 
      , graphical_context(DefaultGC(x_display.display, screen)) {

        long int border_color = 255L;
        border_color = (border_color << 16);
        long int background_color = 255L;
        background_color = (background_color << 8);
        // create window
        window = XCreateSimpleWindow(x_display.display, RootWindow(x_display.display, screen), 10, 10, 200, 200, 10,
            border_color, background_color);
      }

  X11_Window::~X11_Window() {
    XDestroyWindow(x_display.display, window);
  }

  void X11_Window::show() {
    // map (show) the window
    XMapWindow(x_display.display, window);
  }

  void X11_Window::expose() {
    long font_color = 255L << 16;
    XSetForeground(x_display.display, graphical_context, font_color);
    XFillRectangle(x_display.display, window, graphical_context, 20, 200, 200, 30);
    XDrawString(x_display.display, window, graphical_context, 50, 50, msg.c_str(), msg.length());
  }
}
