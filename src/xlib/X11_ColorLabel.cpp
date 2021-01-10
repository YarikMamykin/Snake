#include "X11_ColorLabel.hpp"
#include "Constants.hpp"

namespace {
  const unsigned int margin = 10u;
}

namespace xlib {

  X11_ColorLabel::X11_ColorLabel(const color::ColorPallete& color_pallete,
                   const geometry::Rectangle& frame, 
                   const color::COLOR_SCHEME_TYPE& color_scheme,
                   xlib::X11_Window* x_window) 
  : abstractions::ui::ColorLabel(color_pallete, frame, color_scheme) 
  , x_window(x_window) { }

  X11_ColorLabel::X11_ColorLabel(const color::Color& color,
                   const geometry::Rectangle& frame, 
                   const color::COLOR_SCHEME_TYPE& color_scheme,
                   xlib::X11_Window* x_window) 
  : abstractions::ui::ColorLabel(color, frame, color_scheme) 
  , x_window(x_window) { }

  X11_ColorLabel::~X11_ColorLabel() {}

  void X11_ColorLabel::show(bool show_flag) {
    auto& display = x_window->x_display.display;
    auto& graphical_context = x_window->graphical_context;
    auto& window = x_window->window;

    // hide
    XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::BackgroundColor].to_long());
    XFillRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);

    if(show_flag) {
      show_frame(focused());
      XSetForeground(display, graphical_context, this->color_pallete.get_current_color().to_long());
      XFillRectangle(display, window, graphical_context, 
          this->frame.x + margin,
          this->frame.y + margin,
          this->frame.width - margin * 2,
          this->frame.height - margin * 2);
    }
  }

  void X11_ColorLabel::show_frame(bool show_flag) {
    if(show_flag) {
      auto& display = x_window->x_display.display;
      auto& graphical_context = x_window->graphical_context;
      auto& window = x_window->window;
      XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::FrameColor].to_long());
      XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
    }
  }
}
