#ifndef SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP
#define SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP

#include "ColorLabel.hpp"

namespace xlib {

  class X11_ColorLabel : public abstractions::ui::ColorLabel {
    public:
      X11_ColorLabel(const color::ColorPallete& color_pallete,
                     geometry::Rectangle&& frame, 
                     const color::COLOR_SCHEME_TYPE& color_scheme);
      ~X11_ColorLabel();

      void show(bool show_flag) override;
      void show_frame(bool show_flag) override;
  };
}
#endif /* SRC_INCLUDE_XLIB_X11_COLORLABEL_HPP */
