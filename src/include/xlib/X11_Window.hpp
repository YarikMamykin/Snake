#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "X11_Display.hpp"
#include "MouseMotionHandler.hpp"
#include <memory>
#include "View.hpp"
#include "Constants.hpp"
#include "UI_Object.hpp"

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

  struct X11_Window : public ui::UI_Object, public events::MouseMotionHandler {
    X11_Window(X11_Display& x_display, 
               int screen, 
               views::ViewID viewID, 
               const WindowSettings& win_sets);
    ~X11_Window();
    void show() const;
    void expose() const;
    void redraw_background() const;

    int get_x() const;
    int get_y() const;
    int get_width() const;
    int get_height() const;

    void change_view(const views::ViewID viewID);

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
