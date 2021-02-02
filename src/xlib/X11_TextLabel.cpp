#include "X11_TextLabel.hpp"
#include "XlibWrapper.hpp"

namespace xlib {

  X11_TextLabel::X11_TextLabel() : abstractions::ui::TextLabel() { }

  X11_TextLabel::X11_TextLabel(const std::string& text, 
                               const geometry::Rectangle& frame, 
                               const color::COLOR_SCHEME_TYPE& color_scheme) 
  : abstractions::ui::TextLabel(text, frame, color_scheme) {
    update_frame();
    this->prev_frame = this->frame;
  }

  X11_TextLabel::~X11_TextLabel() { }

  void X11_TextLabel::show(bool show_flag) {
    if(show_flag) { 
      update();
    }

    if(!show_flag) { 
      XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), 
                                   std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  void X11_TextLabel::show_frame(bool show_flag) {
    if(show_flag) {
      XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(frame), 
                                   std::forward<color::Color>(color_scheme[color::ColorSchemeID::FrameColor]));
    }

    if(!show_flag) {
      XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(frame), 
                                   std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  void X11_TextLabel::update() {
    update_frame();
    hide_prev_frame();

    XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), 
        std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));

    XlibWrapper::self()->draw_text({ frame.x + left_text_margin,
                              frame.y + (get_text_graphical_height() + top_text_margin / 2)},
                              std::forward<color::Color>(color_scheme[color::ColorSchemeID::TextColor]),
                              text);

    this->show_frame(focused());
  }

  const unsigned int X11_TextLabel::get_text_graphical_width() const {
    return XlibWrapper::self()->get_text_width(text);
  }

  const unsigned int X11_TextLabel::get_text_graphical_height() const {
    return XlibWrapper::self()->get_text_height();
  }

  void X11_TextLabel::update_frame() {
    this->prev_frame = this->frame;
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
  }

  void X11_TextLabel::hide_prev_frame() {
    XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(prev_frame), 
        std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));
  }
}
