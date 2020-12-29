#include "X11_Menu.hpp"

namespace xlib {
  X11_Menu::X11_Menu(const ::ui::LayoutType& layout, 
                     const geometry::Rectangle& frame, 
                     const abstractions::ui::COLOR_SCHEME_TYPE& color_scheme, 
                     const unsigned int& spacing)
    : abstractions::ui::Menu(layout, frame, color_scheme, spacing) {}

  X11_Menu::~X11_Menu() {}
}
