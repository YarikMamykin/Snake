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
#include "Object.hpp"
#include "Rectangle.hpp"
#include "Window.hpp"

namespace xlib {

  struct WindowSettings {
    geometry::Rectangle frame;
    constants::COLOR_SCHEME_TYPE color_scheme;
    const unsigned int border_width;
    std::string name;
    std::string font_name;
  };

  struct X11_Window : public abstractions::ui::AWindow,
                      public events::ClientMessageHandler,
                      public events::MouseMotionHandler {

    X11_Window(views::ViewID viewID, const WindowSettings& win_sets);
    ~X11_Window() override;

    private:
    void redraw_background() const;

    public:
    void show(bool) override;
    void show_frame(bool) override;
    void expose() override;
    void change_view(const int viewID) override;
    std::shared_ptr<views::View> get_view() const override;
    void update_window_frame();

    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;
    const int get_event_handling_mask() const override;

    Window window;
    X11_Display x_display;
    std::shared_ptr<views::View> view;
    GC graphical_context;
    XFontStruct* font_info;
  };
}

#endif
