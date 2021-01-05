#ifndef SRC_INCLUDE_XLIB_X11_MENU_HPP
#define SRC_INCLUDE_XLIB_X11_MENU_HPP

#include "Menu.hpp"
#include "X11_Window.hpp"

namespace xlib {
  class X11_Menu : public abstractions::ui::Menu {
    protected:
      xlib::X11_Window* x_window;
      unsigned int margin;

    public:
      X11_Menu(const ::ui::LayoutType& layout, 
               const geometry::Rectangle& frame, 
               const constants::COLOR_SCHEME_TYPE& color_scheme, 
               xlib::X11_Window* x_window,
               const unsigned int& spacing = 20U);

      virtual void show(bool show_flag) override;
      virtual void show_frame(bool show_flag) override;

      virtual ~X11_Menu();
  };
}
#endif /* SRC_INCLUDE_XLIB_X11_MENU_HPP */
