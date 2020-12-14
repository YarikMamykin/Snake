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
#include "Rectangle.hpp"

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
    X11_Window(views::ViewID viewID, 
               const WindowSettings& win_sets);
    ~X11_Window();
    void show() const;
    void expose();
    void redraw_background() const;

    const int get_x() const;
    const int get_y() const;
    const unsigned int get_width() const;
    const unsigned int get_height() const;
    geometry::Rectangle get_frame() const;

    void change_view(const views::ViewID viewID);

    void handle_mouse_motion(const int& x, const int& y) override;
    const int get_event_handling_mask() const override;

    Window window;
    X11_Display x_display;
    int screen;
    std::shared_ptr<views::View> view;
    WindowSettings win_sets;
    std::string msg;
    GC graphical_context;
    XFontStruct* font_info;
  };
}

#endif
