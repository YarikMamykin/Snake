#include "X11_Window.hpp"
#include "xlib/X11_TextLabel/X11_TextLabel.hpp"
#include "views/ViewFactory.hpp"
#include "helpers/Helper.hpp"
#include <iostream>
#include <utility>
#include "configuration/Settings.hpp"
#include "commands/ChangeView/ChangeView.hpp"
#include "commands/graphics_commands/DrawCircle/DrawCircle.hpp"
#include "commands/graphics_commands/DrawRectangle/DrawRectangle.hpp"
#include "commands/graphics_commands/FillRectangle/FillRectangle.hpp"
#include "commands/synchronous_commands/QueryWindowFrame/QueryWindowFrame.hpp"
#include <types/enums/AdditionalEvents.hpp>
#include <mutex>
#include <condition_variable>

namespace {
  color::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, color::Color(0UL) },
    { color::ColorSchemeID::TextColor, color::Color(~0UL) },
    { color::ColorSchemeID::FrameColor, color::Color(0UL) }
  };
}

namespace xlib {

  X11_Window::X11_Window(views::ViewID viewID) 
    : abstractions::ui::AWindow(config::get_concrete<geometry::Rectangle>(config_id::WINDOW_FRAME), 
        config::get_concrete<color::COLOR_SCHEME_TYPE>(config_id::WINDOW_COLOR_SCHEME)) 
    , m_closing(false) {
        view = views::ViewFactory::get_view(viewID);
    }

  X11_Window::~X11_Window() = default;

  bool X11_Window::closing() const noexcept {
    return m_closing;
  }

  void X11_Window::show(bool) {
    if (view) {
      view->activate();
    }
  }

  void X11_Window::show_frame(bool) { }

  void X11_Window::update_window_frame() {
    commands::QueryLock ql;
    commands::Command::push_xlib_command(std::make_unique<commands::QueryWindowFrame>(this, ql));
  }

  void X11_Window::expose() {
    update_window_frame();
    redraw_background();
    if (view) {
      view->activate();
    }
  }

  void X11_Window::redraw_background() const {
    commands::Command::push_xlib_command(std::make_unique<commands::FillRectangle>(frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
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
          m_closing = true;
          break;
        }
      case events::AdditionalEvents::ChangeView: 
        {
          // Wait till additional threads ended their part 
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
}
