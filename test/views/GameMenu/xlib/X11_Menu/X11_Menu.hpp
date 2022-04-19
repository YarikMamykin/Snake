#pragma once
#include <color/ColorScheme.hpp>
#include <abstractions/ui/Menu.hpp>

namespace xlib {
  struct X11_Menu : public abstractions::ui::Menu {
    public:
      X11_Menu(const ::ui::LayoutType& layout, 
               const geometry::Rectangle& frame, 
               const color::COLOR_SCHEME_TYPE& color_scheme, 
               const unsigned int& spacing = 20U) 
      : abstractions::ui::Menu(layout, frame, color_scheme, spacing) {} 

      virtual ~X11_Menu() = default;
  };
}
