#include "X11_TextLabel.hpp"

namespace xlib {

  X11_TextLabel::X11_TextLabel(X11_Window* parent_window)
  : abstractions::ui::TextLabel()
  , parent_window(parent_window) { }

  X11_TextLabel::X11_TextLabel(const std::string& text, 
                               const geometry::Rectangle& frame, 
                               const color::COLOR_SCHEME_TYPE& color_scheme, 
                               X11_Window* parent_window) 
  : abstractions::ui::TextLabel(text, frame, color_scheme)
  , parent_window(parent_window) {
    update_frame();
    this->prev_frame = this->frame;
  }

  X11_TextLabel::~X11_TextLabel() { }

  void X11_TextLabel::show(bool show_flag) {
    if(show_flag) { 
      update();
    }

    if(!show_flag) { 
      auto& display = parent_window->x_display.display;
      auto& graphical_context = parent_window->graphical_context;
      auto& window = parent_window->window;

      XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::BackgroundColor].to_long());
      XFillRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
    }
  }

  void X11_TextLabel::show_frame(bool show_flag) {
    if(show_flag) {
      auto& display = parent_window->x_display.display;
      auto& graphical_context = parent_window->graphical_context;
      auto& window = parent_window->window;

      XSetLineAttributes(display, graphical_context, frame_weight,0,0,0);
      XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::FrameColor].to_long());
      XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
    }

    if(!show_flag) {
      auto& display = parent_window->x_display.display;
      auto& graphical_context = parent_window->graphical_context;
      auto& window = parent_window->window;

      XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::BackgroundColor].to_long());
      XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
    }
  }

  void X11_TextLabel::update() {
    auto display = parent_window->x_display.display;
    auto graphical_context = parent_window->graphical_context;
    auto window = parent_window->window;

    update_frame();
    hide_prev_frame();

    XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::BackgroundColor].to_long());
    XFillRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);

    XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::TextColor].to_long());
    XDrawString(display, window, graphical_context, 
        this->frame.x + left_text_margin, 
        this->frame.y + (get_text_graphical_height() + top_text_margin / 2), 
        this->text.c_str(), 
        this->text.length());

    this->show_frame(focused());
  }

  const unsigned int X11_TextLabel::get_text_graphical_width() const {
    return XTextWidth(parent_window->font_info, text.c_str(), text.size());
  }

  const unsigned int X11_TextLabel::get_text_graphical_height() const {
    return parent_window->font_info->ascent + parent_window->font_info->descent;
  }

  void X11_TextLabel::update_frame() {
    this->prev_frame = this->frame;
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
  }

  void X11_TextLabel::hide_prev_frame() {
    auto display = parent_window->x_display.display;
    auto graphical_context = parent_window->graphical_context;
    auto window = parent_window->window;

    XSetForeground(display, graphical_context, this->color_scheme[color::ColorSchemeID::BackgroundColor].to_long());
    XFillRectangle(display, window, graphical_context, this->prev_frame.x, this->prev_frame.y, this->prev_frame.width, this->prev_frame.height);
    XDrawRectangle(display, window, graphical_context, this->prev_frame.x, this->prev_frame.y, this->prev_frame.width, this->prev_frame.height);
  }
}
