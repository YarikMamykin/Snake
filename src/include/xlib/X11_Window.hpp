#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "X11_Display.hpp"
#include "View.hpp"
#include <memory>

namespace xlib {

  struct WindowSettings {
    int x;
    int y;
    unsigned int w;
    unsigned int h;
    unsigned int border_width;
    unsigned long border_color;
    unsigned long backgnd_color;
    unsigned long font_color;
    std::string name;
  };

  struct X11_Window {
    X11_Window(X11_Display& x_display, int screen, std::unique_ptr<views::View> view, const WindowSettings& win_sets);
    ~X11_Window();
    void show();
    void expose();

    Window window;
    X11_Display& x_display;
    int screen;
    std::unique_ptr<views::View> view;
    WindowSettings win_sets;
    std::string msg;
    GC graphical_context;
  };
}

#endif
