#include "X11_TextLabel.hpp"
#include "commands/synchronous_commands/QueryTextWidth/QueryTextWidth.hpp"
#include "commands/synchronous_commands/QueryTextHeight/QueryTextHeight.hpp"
#include "commands/graphics_commands/FillRectangle/FillRectangle.hpp"
#include "commands/graphics_commands/DrawRectangle/DrawRectangle.hpp"
#include "commands/graphics_commands/DrawText/DrawText.hpp"
#include <condition_variable>
#include <mutex>
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

  X11_TextLabel::~X11_TextLabel() = default;

  void X11_TextLabel::show(bool show_flag) {
    if(show_flag) { 
      update();
    }

    if(!show_flag) { 
      commands::Command::push_xlib_command(std::make_unique<commands::FillRectangle>(frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
    }
  }

  void X11_TextLabel::show_frame(bool show_flag) {
    if(show_flag) {
      commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme.at(color::ColorSchemeID::FrameColor)));
    }

    if(!show_flag) {
      commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
    }
  }

  void X11_TextLabel::update() {
    update_frame();
    hide_prev_frame();

    commands::Command::push_xlib_command(std::make_unique<commands::DrawRectangle>(frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
    commands::Command::push_xlib_command(std::make_unique<commands::DrawText>( text, geometry::Point{ frame.x + left_text_margin, frame.y + (get_text_graphical_height() + top_text_margin / 2)}, color_scheme.at(color::ColorSchemeID::TextColor)));

    this->show_frame(focused());
  }

  const unsigned int X11_TextLabel::get_text_graphical_width() const {
    unsigned int width = 0u;
    {
      commands::QueryLock ql;
      commands::Command::push_xlib_command(std::make_unique<commands::QueryTextWidth>(text, width, ql));
    }
    return width;
  }

  const unsigned int X11_TextLabel::get_text_graphical_height() const {
    unsigned int height = 0u;
    {
      commands::QueryLock ql;
      commands::Command::push_xlib_command(std::make_unique<commands::QueryTextHeight>(height, ql));
    }
    return height;
  }

  void X11_TextLabel::update_frame() {
    this->prev_frame = this->frame;
    this->frame.width = get_text_graphical_width() + left_text_margin * 2;
    this->frame.height = get_text_graphical_height() + top_text_margin * 2;
  }

  void X11_TextLabel::hide_prev_frame() {
    commands::Command::push_xlib_command(std::make_unique<commands::FillRectangle>(prev_frame, color_scheme.at(color::ColorSchemeID::BackgroundColor)));
  }
}
