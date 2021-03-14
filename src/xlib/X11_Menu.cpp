#include "X11_Menu.hpp"
#include "DrawRectangle.hpp"

namespace xlib {
  X11_Menu::X11_Menu(const ::ui::LayoutType& layout, 
                     const geometry::Rectangle& frame, 
                     const color::COLOR_SCHEME_TYPE& color_scheme,
                     const unsigned int& spacing)
    : abstractions::ui::Menu(layout, frame, color_scheme, spacing) 
    , margin(20U) {}

  void X11_Menu::show(bool show_flag) {
    abstractions::ui::Menu::show(show_flag);
    show_frame(focused());
  }

  void X11_Menu::show_frame(bool show_flag) {
    prev_frame = frame;
    update_menu_frame();
    if(show_flag) {

      commands::Command::push_xlib_command(new commands::DrawRectangle(prev_frame, color_scheme[color::ColorSchemeID::BackgroundColor]));
      commands::Command::push_xlib_command(new commands::DrawRectangle({
        frame.x - margin,
        frame.y - margin,
        frame.width + margin * 2,
        frame.height + margin * 2
      }, color_scheme[color::ColorSchemeID::FrameColor]));
    }

    if(!show_flag) {
      commands::Command::push_xlib_command(new commands::DrawRectangle({
        frame.x - margin,
        frame.y - margin,
        frame.width + margin * 2,
        frame.height + margin * 2
      }, color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  X11_Menu::~X11_Menu() {}
}
