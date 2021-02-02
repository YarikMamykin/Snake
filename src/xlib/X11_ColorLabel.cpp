#include "X11_ColorLabel.hpp"
#include "XlibWrapper.hpp"
#include "Constants.hpp"

namespace {
  const unsigned int margin = 10u;
}

namespace xlib {

  X11_ColorLabel::X11_ColorLabel(const color::ColorPallete& color_pallete,
                   geometry::Rectangle&& frame, 
                   const color::COLOR_SCHEME_TYPE& color_scheme) 
  : abstractions::ui::ColorLabel(color_pallete, std::move(frame), color_scheme) { }

  X11_ColorLabel::~X11_ColorLabel() {}

  void X11_ColorLabel::show(bool show_flag) {
    // hide
    XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), 
                                 std::forward<color::Color>(color_scheme[color::ColorSchemeID::BackgroundColor]));

    if(show_flag) {
      show_frame(focused());
      XlibWrapper::self()->fill_rectangle({
          frame.x + margin,
          frame.y + margin,
          frame.width - margin * 2,
          frame.height - margin * 2},
          (color_pallete.get_current_color()));

    }
  }

  void X11_ColorLabel::show_frame(bool show_flag) {
    if(show_flag) {
      XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(frame), 
                                   std::forward<color::Color>(color_scheme[color::ColorSchemeID::FrameColor]));
    }
  }
}
