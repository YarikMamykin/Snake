#include "xlib/X11_TextLabel.hpp"
#include "commands/synchronous_commands/QueryTextWidth.hpp"
#include "commands/synchronous_commands/QueryTextHeight.hpp"
#include "commands/graphics_commands/FillRectangle.hpp"
#include "commands/graphics_commands/DrawRectangle.hpp"
#include "commands/graphics_commands/DrawText.hpp"
#include <thread>

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
      commands::Command::push_xlib_command(std::make_unique<commands::FillRectangle>(frame, color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  void X11_TextLabel::show_frame(bool show_flag) {
    if(show_flag) {
      commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme[color::ColorSchemeID::FrameColor]));
    }

    if(!show_flag) {
      commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  void X11_TextLabel::update() {
    update_frame();
    hide_prev_frame();

    commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme[color::ColorSchemeID::BackgroundColor]));
    commands::Command::push_xlib_command(std::make_unique<commands::DrawText>( text, geometry::Point{ frame.x + left_text_margin, frame.y + (get_text_graphical_height() + top_text_margin / 2)}, color_scheme[color::ColorSchemeID::TextColor]));

    this->show_frame(focused());
  }

  const unsigned int X11_TextLabel::get_text_graphical_width() const {
    std::atomic<bool> trigger(false);
    unsigned int width = 0u;
    commands::Command::push_xlib_command(std::make_unique<commands::QueryTextWidth>(text, width, trigger));
    while(!trigger.load());
    return width;
  }

  const unsigned int X11_TextLabel::get_text_graphical_height() const {
    std::atomic<bool> trigger(false);
    unsigned int height = 0u;
    commands::Command::push_xlib_command(std::make_unique<commands::QueryTextHeight>(height, trigger));
    while(!trigger.load());
    return height;
  }

  void X11_TextLabel::update_frame() {
    this->prev_frame = this->frame;
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
  }

  void X11_TextLabel::hide_prev_frame() {
    commands::Command::push_xlib_command(std::make_unique<commands::FillRectangle>(prev_frame, color_scheme[color::ColorSchemeID::BackgroundColor]));
  }
}
