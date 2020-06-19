#include "X11_Window.hpp"

namespace xlib {

  X11_Window::X11_Window(X11_Display& x_display, int screen, const WindowSettings& win_sets) 
    : x_display(x_display)
      , screen(screen) 
      , win_sets(win_sets)
      , msg("Hello, World!") 
      , graphical_context(DefaultGC(x_display.display, screen)) {

        // create window
        window = XCreateSimpleWindow(x_display.display,
            RootWindow(x_display.display, screen),
            win_sets.x,
            win_sets.y,
            win_sets.w,
            win_sets.h,
            win_sets.border_width, 
            win_sets.border_color, 
            win_sets.backgnd_color);
        XStoreName(x_display.display, window, win_sets.name.c_str());
      }

  X11_Window::~X11_Window() {
    XDestroyWindow(x_display.display, window);
  }

  void X11_Window::show() {
    // map (show) the window
    XMapWindow(x_display.display, window);
  }

  void X11_Window::expose() {
    XSetForeground(x_display.display, graphical_context, win_sets.font_color);
    XDrawString(x_display.display, window, graphical_context, 50, 50, msg.c_str(), msg.length());

    XRectangle rectangle = {.x = 20, .y = 200, .width = 200, .height = 30};
    XSetForeground(x_display.display, graphical_context, win_sets.border_color);
    XFillRectangle(x_display.display, window, graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_display.display, graphical_context, 255L);
    XSetLineAttributes(x_display.display, graphical_context,5,0,0,0);
    XDrawRectangle(x_display.display, window, graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_display.display, graphical_context, ~0L);
    XSetLineAttributes(x_display.display, graphical_context,2,0,0,0);
    XDrawLine(x_display.display, window, graphical_context, 10,10,772,10);
  }
}
