#include "X11_Window.hpp"
#include "ViewFactory.hpp"
#include "Helper.hpp"
#include <iostream>

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
            this->color_scheme.at(ui::ColorSchemeID::FrameColor), 
            this->color_scheme.at(ui::ColorSchemeID::BackgroundColor));

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

  void X11_Window::expose() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(x_display.display, this->window, &win_attr);
    this->frame.width = win_attr.width;
    this->frame.height = win_attr.height;

    if (view) {
      view->activate();
    }
  }

  void X11_Window::redraw_background() const {
    XFlushGC(x_display.display, graphical_context);
    XFlush(x_display.display);
    XSetForeground(x_display.display, graphical_context, this->color_scheme.at(ui::ColorSchemeID::BackgroundColor));
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
    const auto&& text_width = XTextWidth(this->font_info, coords_text.c_str(), coords_text.size()); 
    const auto&& text_height = this->font_info->ascent + this->font_info->descent;

    XSetForeground(this->x_display.display, this->graphical_context, 0L);
    XFillRectangle(this->x_display.display, 
        this->window, 
        this->graphical_context, 
        win_attr.width - text_width - 30, 
        50-text_height,
        win_attr.width,
        text_height);

    XSetForeground(this->x_display.display, this->graphical_context, ~0L);
    XDrawString(this->x_display.display, 
        this->window, 
        this->graphical_context, 
        win_attr.width - text_width - 10, 
        50, 
        coords_text.c_str(), 
        coords_text.size()); 
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
