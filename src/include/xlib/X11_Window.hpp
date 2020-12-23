#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "X11_Display.hpp"
#include "MouseMotionHandler.hpp"
#include "ClientMessageHandler.hpp"
#include <memory>
#include "View.hpp"
#include "Constants.hpp"
#include "UI_Object.hpp"
#include "Rectangle.hpp"
#include "IWindow.hpp"

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

  struct X11_Window : public interfaces::IWindow, 
                      public events::ClientMessageHandler,
                      public events::MouseMotionHandler {

    X11_Window(views::ViewID viewID, const WindowSettings& win_sets);
    ~X11_Window() override;

    private:
    void redraw_background() const;

    public:
    void show() const override;
    void expose() override;
    const int get_x() const override;
    const int get_y() const override;
    const unsigned int get_width() const override;
    const unsigned int get_height() const override;
    void change_view(const int viewID) override;
    std::shared_ptr<views::View> get_view() const override;

    geometry::Rectangle get_frame() const;

    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;
    const int get_event_handling_mask() const override;

    Window window;
    X11_Display x_display;
    std::shared_ptr<views::View> view;
    WindowSettings win_sets;
    std::string msg;
    GC graphical_context;
    XFontStruct* font_info;
  };
}

#endif
