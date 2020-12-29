#ifndef SRC_INCLUDE_XLIB_X11_MENU_HPP
#define SRC_INCLUDE_XLIB_X11_MENU_HPP

#include "Menu.hpp"

namespace xlib {
  class X11_Menu : public abstractions::ui::Menu {
    public:
      X11_Menu(const ::ui::LayoutType& layout, 
               const geometry::Rectangle& frame, 
               const abstractions::ui::COLOR_SCHEME_TYPE& color_scheme, 
               const unsigned int& spacing = 20U);

      virtual ~X11_Menu();
  };
}
#endif /* SRC_INCLUDE_XLIB_X11_MENU_HPP */
