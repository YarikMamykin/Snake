#include "X11_TextLabel.hpp"

namespace xlib {

  X11_TextLabel::X11_TextLabel(X11_Window* parent_window)
  : parent_window(parent_window) 
  , color_scheme() 
  , frame() 
  , text()
  , active(false) { }

  X11_TextLabel::X11_TextLabel(const std::string& text, const geometry::Rectangle& frame, const ColorScheme& color_scheme, X11_Window* parent_window) 
  : frame(frame)
  , text(text)
  , color_scheme(color_scheme)
  , parent_window(parent_window) {
    this->frame = frame;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
  }

  X11_TextLabel::~X11_TextLabel() { }

  void X11_TextLabel::show() {
    update();
  }

  void X11_TextLabel::hide() {
    auto& display = parent_window->x_display.display;
    auto& graphical_context = parent_window->graphical_context;
    auto& window = parent_window->window;

    XSetForeground(display, graphical_context, this->color_scheme.background);
    XFillRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
  }

  void X11_TextLabel::show_frame() {
    auto& display = parent_window->x_display.display;
    auto& graphical_context = parent_window->graphical_context;
    auto& window = parent_window->window;

    XSetLineAttributes(display, graphical_context, frame_weight,0,0,0);
    XSetForeground(display, graphical_context, this->color_scheme.frame);
    XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
  }

  void X11_TextLabel::hide_frame() {
    auto& display = parent_window->x_display.display;
    auto& graphical_context = parent_window->graphical_context;
    auto& window = parent_window->window;

    XSetForeground(display, graphical_context, this->color_scheme.background);
    XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
  }

  void X11_TextLabel::set_text(const std::string& text) {
    this->text = text;
  }

  const std::string X11_TextLabel::get_text() {
    return this->text;
  }

  void X11_TextLabel::set_background_color(unsigned long color) {
    this->color_scheme.background = color;
  }

  void X11_TextLabel::set_frame_color(unsigned long color) {
    this->color_scheme.frame = color;
  }

  void X11_TextLabel::set_text_color(unsigned long color) {
    this->color_scheme.text = color;
  }

  bool X11_TextLabel::focused(const int& x, const int& y) const {
    return (x >= this->frame.x && (x <= this->frame.x + this->frame.width)) &&
           (y >= this->frame.y && (y <= this->frame.y + this->frame.height));
  }

  void X11_TextLabel::set_frame(const int& x, const int& y, const unsigned int& width, const unsigned int& height) {
    this->frame = {.x = x, .y = y, .width = width, .height = height};
  }

  const int X11_TextLabel::get_x() const {
    return this->frame.x;
  }

  const int X11_TextLabel::get_y() const {
    return this->frame.y;
  }

  const unsigned int X11_TextLabel::get_width() const {
    return this->frame.width;
  }

  const unsigned int X11_TextLabel::get_height() const {
    return this->frame.height;
  }

  void X11_TextLabel::update() {
    auto display = parent_window->x_display.display;
    auto graphical_context = parent_window->graphical_context;
    auto window = parent_window->window;

    update_frame();

    XSetForeground(display, graphical_context, this->color_scheme.background);
    XFillRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);

    XSetForeground(display, graphical_context, this->color_scheme.text);
    XDrawString(display, window, graphical_context, 
        this->frame.x + left_text_margin, 
        this->frame.y + (get_text_graphical_height() + top_text_margin / 2), 
        this->text.c_str(), 
        this->text.length());

    XSetLineAttributes(display, graphical_context, frame_weight,0,0,0);
    XSetForeground(display, graphical_context, this->color_scheme.frame);
    XDrawRectangle(display, window, graphical_context, this->frame.x, this->frame.y, this->frame.width, this->frame.height);
  }

  const unsigned int X11_TextLabel::get_text_graphical_width() const {
    return XTextWidth(parent_window->font_info, text.c_str(), text.size());
  }

  const unsigned int X11_TextLabel::get_text_graphical_height() const {
    return parent_window->font_info->ascent + parent_window->font_info->descent;
  }

  void X11_TextLabel::update_frame() {
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
  }
}
