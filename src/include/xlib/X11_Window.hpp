#ifndef SRC_INCLUDE_XLIB_X11_WINDOW_HPP
#define SRC_INCLUDE_XLIB_X11_WINDOW_HPP

#include "XHeaders.hpp"
#include <string>
#include "MouseMotionHandler.hpp"
#include "ClientMessageHandler.hpp"
#include "ExposeEventHandler.hpp"
#include "KeyPressHandler.hpp"
#include <memory>
#include "View.hpp"
#include "Constants.hpp"
#include "Object.hpp"
#include "Rectangle.hpp"
#include "Window.hpp"

namespace xlib {

  struct X11_Window : public abstractions::ui::AWindow,
                      public events::ClientMessageHandler,
                      public events::MouseMotionHandler, 
                      public events::KeyPressHandler, 
                      public events::ExposeEventHandler {

    X11_Window(views::ViewID viewID);
    ~X11_Window() override;

    private:
    void redraw_background() const;
    void change_view(const int viewID);

    public:
    void show(bool) override;
    void show_frame(bool) override;
    void expose();
    void update_window_frame();

    void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;
    void handle_mouse_motion(const int& x, const int& y) override;
    void handle_client_message(const long* data) override;
    void handle_expose_event() override;
    const int get_event_handling_mask() const override;

    std::unique_ptr<views::View> view;
  };
}

#endif
