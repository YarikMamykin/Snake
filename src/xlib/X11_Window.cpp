#include "X11_Window.hpp"
#include "ViewFactory.hpp"
#include <iostream>

namespace xlib {

  X11_Window::X11_Window(X11_Display& x_display, int screen, views::ViewID viewID, const WindowSettings& win_sets) 
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
        font_info = XLoadQueryFont(x_display.display, win_sets.font_name.c_str());
        if(!font_info) {
          std::cerr << "FONT NOT LOADED!!!!" << std::endl;
        } else {
          XSetFont(x_display.display, graphical_context, font_info->fid);
        }

        view = views::ViewFactory::get_view(viewID, this);
      }

  X11_Window::~X11_Window() {
    XFreeFont(x_display.display, font_info);
    XDestroyWindow(x_display.display, window);
  }

  void X11_Window::show() const {
    // map (show) the window
    XMapWindow(x_display.display, window);
  }

  void X11_Window::expose() const {
    if (view) {
      view->activate();
    }
  }

  int X11_Window::get_x() const {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.x;
  }

  int X11_Window::get_y() const {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.y;
  }

  int X11_Window::get_width() const {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.width;
  }

  int X11_Window::get_height() const {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    return win_attr.height;
  }

  void X11_Window::redraw_background() const {
    XFlushGC(x_display.display, graphical_context);
    XFlush(x_display.display);
    XSetForeground(x_display.display, graphical_context, win_sets.backgnd_color);
    XFillRectangle(x_display.display,
        window,
        graphical_context,
        0,
        0,
        get_width(),
        get_height());
  }

  void X11_Window::change_view(const views::ViewID viewID) {
    redraw_background();
    this->view = views::ViewFactory::get_view(viewID, this);
    this->view->activate();
  }


  void X11_Window::handle_mouse_motion(const int& x, const int& y) {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);

    std::string coords_text = std::to_string(x) + std::string(" : ") + std::to_string(y);
    const auto&& text_width = XTextWidth(this->font_info, coords_text.c_str(), coords_text.size()); 
    const auto&& text_height = this->font_info->ascent + this->font_info->descent;

    XSetForeground(this->x_display.display, this->graphical_context, 0L);
    XFillRectangle(this->x_display.display, 
        this->window, 
        this->graphical_context, 
        win_attr.width - text_width - 30, 
        50-text_height,
        win_attr.width,
        text_height);

    XSetForeground(this->x_display.display, this->graphical_context, ~0L);
    XDrawString(this->x_display.display, 
        this->window, 
        this->graphical_context, 
        win_attr.width - text_width - 10, 
        50, 
        coords_text.c_str(), 
        coords_text.size()); 
  }
}
