#include "X11_Window.hpp"
#include "X11_TextLabel.hpp"
#include "ViewFactory.hpp"
#include "Helper.hpp"
#include <iostream>
#include <utility>
#include "XlibWrapper.hpp"

namespace {
  color::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, color::Color(0UL) },
    { color::ColorSchemeID::TextColor, color::Color(~0UL) },
    { color::ColorSchemeID::FrameColor, color::Color(0UL) }
  };
}

namespace xlib {

  X11_Window::X11_Window(views::ViewID viewID, const WindowSettings& win_sets) 
    : abstractions::ui::AWindow(win_sets.frame, win_sets.color_scheme)
    , x_font(win_sets.font_name.c_str()) {
        XlibWrapper::self()->create_window(std::forward<decltype(frame)>(frame), 
                                    std::forward<decltype(color_scheme)>(color_scheme), 
                                    win_sets.name.c_str());
        view = views::ViewFactory::get_view(viewID, this);
      }

  X11_Window::~X11_Window() {
    XlibWrapper::self()->destroy_window();
  }

  void X11_Window::show(bool) {
    if (view) {
      view->activate();
    }
  }

  void X11_Window::show_frame(bool) { }

  void X11_Window::update_window_frame() {
    auto&& win_attr = XlibWrapper::self()->get_window_attributes();
    this->frame.width = win_attr.width;
    this->frame.height = win_attr.height;
  }

  void X11_Window::expose() {
    update_window_frame();
    if (view) {
      view->activate();
    }
  }

  void X11_Window::redraw_background() const {
    XlibWrapper::self()->redraw_window_background();
  }

  void X11_Window::change_view(const int viewID) {
    this->view = views::ViewFactory::get_view(static_cast<views::ViewID>(viewID), this);

    redraw_background();
    this->view->activate();
  }

  std::shared_ptr<views::View> X11_Window::get_view() const {
    return this->view;
  }

  void X11_Window::handle_mouse_motion(const int& x, const int& y) {
    update_window_frame();
    std::string coords_text = std::to_string(x) + std::string(" : ") + std::to_string(y);

    X11_TextLabel text_label(coords_text, {}, text_label_color_scheme);
    text_label.set_position(frame.width - text_label.get_width() - 30, 50-text_label.get_height());
    text_label.show(true);
  }

  void X11_Window::handle_client_message(const long* data) {
    switch(data[0]) {
      case events::AdditionalEvents::ExitApplication: 
        {
          this->change_view(views::ViewID::NONE);
          break;
        }
      case events::AdditionalEvents::ChangeView: 
        {
          this->change_view(data[1]);
          helpers::Helper::SendResubscribeViewEvent(this);
        }
    }
  }

  void X11_Window::handle_expose_event() {
    this->expose();
  }

  const int X11_Window::get_event_handling_mask() const {
    return events::MouseMotionHandler::get_event_handling_mask() 
          | events::ClientMessageHandler::get_event_handling_mask() 
          | events::ExposeEventHandler::get_event_handling_mask();
  }
}
