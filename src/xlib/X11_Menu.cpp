#include "X11_Menu.hpp"
#include "XlibWrapper.hpp"

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
      XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(prev_frame), 
      std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));
      XlibWrapper::self()->draw_rectangle({
        frame.x - margin,
        frame.y - margin,
        frame.width + margin * 2,
        frame.height + margin * 2
      }, 
      std::forward<color::Color>(color_scheme[color::ColorSchemeID::FrameColor]));
    }

    if(!show_flag) {
      XlibWrapper::self()->draw_rectangle({
        frame.x - margin,
        frame.y - margin,
        frame.width + margin * 2,
        frame.height + margin * 2
      }, 
      std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));
    }
  }

  X11_Menu::~X11_Menu() {}
}
