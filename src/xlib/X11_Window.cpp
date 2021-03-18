#include "X11_Window.hpp"
#include "X11_TextLabel.hpp"
#include "ViewFactory.hpp"
#include "Helper.hpp"
#include <iostream>
#include <utility>
#include "XlibWrapper.hpp"
#include "Settings.hpp"
#include "DrawCircle.hpp"
#include "DrawRectangle.hpp"
#include "FillRectangle.hpp"
#include "QueryWindowAttributes.hpp"

namespace {
  color::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, color::Color(0UL) },
    { color::ColorSchemeID::TextColor, color::Color(~0UL) },
    { color::ColorSchemeID::FrameColor, color::Color(0UL) }
  };
}

namespace xlib {

  X11_Window::X11_Window(views::ViewID viewID) 
    : abstractions::ui::AWindow(configuration::Settings::get_concrete<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME), 
        configuration::Settings::get_concrete<color::COLOR_SCHEME_TYPE>(configuration::ConfigID::WINDOW_COLOR_SCHEME)) {
        view = views::ViewFactory::get_view(viewID);
    }

  X11_Window::~X11_Window() { }

  void X11_Window::show(bool) {
    if (view) {
      view->activate();
    }
  }

  void X11_Window::show_frame(bool) { }

  void X11_Window::update_window_frame() {
    commands::Command::push_xlib_command(new commands::QueryWindowAttributes());
    std::unique_ptr<commands::Command> query_win_attr_command = commands::Command::get_command_with_result(commands::CommandID::QueryWindowAttributes);
    auto&& win_attr = dynamic_cast<commands::QueryWindowAttributes*>(query_win_attr_command.get())->get_window_attributes();
    this->frame = {0, 0, win_attr.width, win_attr.height};
    configuration::Settings::get_concrete_ptr<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME)->change_value(this->frame);
  }

  void X11_Window::expose() {
    update_window_frame();
    redraw_background();
    if (view) {
      view->activate();
    }
  }

  void X11_Window::redraw_background() const {
    commands::Command::push_xlib_command(new commands::FillRectangle(frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
  }

  void X11_Window::change_view(const int viewID) {
    this->view = views::ViewFactory::get_view(static_cast<views::ViewID>(viewID));
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
          throw -1;
          break;
        }
      case events::AdditionalEvents::ChangeView: 
        {
          redraw_background();
          this->change_view(data[1]);
          this->view->activate();
        }
    }
  }

  void X11_Window::handle_expose_event() {
    this->expose();
  }

  void X11_Window::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    dynamic_cast<KeyPressHandler*>(this->view.get())->handle_key_press(key_sym, mask);
  }

  const int X11_Window::get_event_handling_mask() const {
    return dynamic_cast<EventHandlingObject*>(this->view.get())->get_event_handling_mask() 
           | events::HandlersMask::ClientMessageHandlerMask 
           | events::HandlersMask::MouseMotionHandlerMask 
           | events::HandlersMask::ExposeEventHandlerMask;
  }
}
