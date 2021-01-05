#include "X11_Window.hpp"
#include "X11_TextLabel.hpp"
#include "ViewFactory.hpp"
#include "Helper.hpp"
#include <iostream>

namespace {
  constants::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, color::Color(0UL) },
    { ui::ColorSchemeID::TextColor, color::Color(~0UL) },
    { ui::ColorSchemeID::FrameColor, color::Color(0UL) }
  };
}

namespace xlib {

  X11_Window::X11_Window(views::ViewID viewID, const WindowSettings& win_sets) 
    : abstractions::ui::AWindow(win_sets.frame, win_sets.color_scheme)
    , x_display()
    , graphical_context(DefaultGC(x_display.display, XDefaultScreen(x_display.display))) {

        // create window
        window = XCreateSimpleWindow(x_display.display,
            RootWindow(x_display.display, XDefaultScreen(x_display.display)),
            this->frame.x, this->frame.y, this->frame.width, this->frame.height,
            win_sets.border_width, 
            this->color_scheme.at(ui::ColorSchemeID::FrameColor).to_long(), 
            this->color_scheme.at(ui::ColorSchemeID::BackgroundColor).to_long());

        XStoreName(x_display.display, window, win_sets.name.c_str());
        font_info = XLoadQueryFont(x_display.display, win_sets.font_name.c_str());
        if(!font_info) {
          std::cerr << "FONT NOT LOADED!!!!" << std::endl;
        } else {
          XSetFont(x_display.display, graphical_context, font_info->fid);
        }

        view = views::ViewFactory::get_view(viewID, this);
        this->frame.x = this->frame.y = 0;
      }

  X11_Window::~X11_Window() {
    XFreeFont(x_display.display, font_info);
    XDestroyWindow(x_display.display, window);
  }

  void X11_Window::show(bool) {
    // map (show) the window
    XMapWindow(x_display.display, window);
  }

  void X11_Window::show_frame(bool) { }

  void X11_Window::update_window_frame() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
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
    XFlushGC(x_display.display, graphical_context);
    XFlush(x_display.display);
    XSetForeground(x_display.display, graphical_context, this->color_scheme.at(ui::ColorSchemeID::BackgroundColor).to_long());
    XFillRectangle(x_display.display, window, graphical_context, frame.x, frame.y, frame.width, frame.height);
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
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);

    std::string coords_text = std::to_string(x) + std::string(" : ") + std::to_string(y);

    X11_TextLabel text_label(coords_text, {}, text_label_color_scheme, this);
    text_label.set_position(win_attr.width - text_label.get_width() - 30, 50-text_label.get_height());
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

  const int X11_Window::get_event_handling_mask() const {
    return events::MouseMotionHandler::get_event_handling_mask() | events::ClientMessageHandler::get_event_handling_mask();
  }
}
