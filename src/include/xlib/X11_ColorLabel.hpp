#ifndef SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP
#define SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP

#include "ColorLabel.hpp"
#include "X11_Window.hpp"

namespace xlib {

  class X11_ColorLabel : public abstractions::ui::ColorLabel {
    private:
      xlib::X11_Window* x_window;
    public:
      X11_ColorLabel(const color::ColorPallete& color_pallete,
                     const geometry::Rectangle& frame, 
                     const color::COLOR_SCHEME_TYPE& color_scheme,
                     xlib::X11_Window* x_window);
      ~X11_ColorLabel();

      void show(bool show_flag) override;
      void show_frame(bool show_flag) override;
  };
}
#endif /* SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP */
