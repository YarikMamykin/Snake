#include "X11_Window.hpp"

namespace xlib {

  X11_Window::X11_Window(X11_Display& x_display, int screen, std::unique_ptr<views::View> view, const WindowSettings& win_sets) 
    : x_display(x_display)
      , screen(screen) 
      , view(std::move(view))
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
    view->activate();
  }
}
