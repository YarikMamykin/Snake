#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "X11_Display.hpp"
#include "ViewID.hpp"
#include "MouseMotionHandler.hpp"
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
    std::string font_name;
  };

  struct X11_Window : public ui::MouseMotionHandler {
    X11_Window(X11_Display& x_display, 
               int screen, 
               views::ViewID viewID, 
               const WindowSettings& win_sets);
    ~X11_Window();
    void show();
    void expose();

    int get_x();
    int get_y();
    int get_width();
    int get_height();

    void handle_mouse_motion(const int& x, const int& y) override;

    Window window;
    X11_Display& x_display;
    int screen;
    std::shared_ptr<views::View> view;
    WindowSettings win_sets;
    std::string msg;
    GC graphical_context;
    XFontStruct* font_info;
  };
}

#endif
