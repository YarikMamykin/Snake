#include "X11_Window.hpp"
#include "ViewFactory.hpp"
#include <iostream>

namespace xlib {

  X11_Window::X11_Window(X11_Display& x_display, int screen, views::ViewID viewID, const WindowSettings& win_sets) 
    : x_display(x_display)
      , screen(screen) 
      , viewID(viewID)
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
        font_info = XLoadQueryFont(x_display.display, win_sets.font_name.c_str());
        if(!font_info) {
          std::cerr << "FONT NOT LOADED!!!!" << std::endl;
        } else {
          XSetFont(x_display.display, graphical_context, font_info->fid);
        }
      }

  X11_Window::~X11_Window() {
    XFreeFont(x_display.display, font_info);
    XDestroyWindow(x_display.display, window);
  }

  void X11_Window::show() {
    // map (show) the window
    XMapWindow(x_display.display, window);
  }

  void X11_Window::expose() {
    auto view = views::ViewFactory::get_view(viewID, this);
    view->activate();
  }

  int X11_Window::get_x() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.x;
  }

  int X11_Window::get_y() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.y;
  }

  int X11_Window::get_width() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.width;
  }

  int X11_Window::get_height() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.height;
  }
}
