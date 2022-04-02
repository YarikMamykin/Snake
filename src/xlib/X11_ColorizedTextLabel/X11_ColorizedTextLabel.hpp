#ifndef SRC_INCLUDE_XLIB_X11_COLORIZEDTEXTLABEL_HPP
#define SRC_INCLUDE_XLIB_X11_COLORIZEDTEXTLABEL_HPP
#include <xlib/X11_TextLabel/X11_TextLabel.hpp>
#include "color/ColorPallete/ColorPallete.hpp"
#include <list>

namespace xlib {
  class X11_ColorizedTextLabel : public abstractions::ui::TextLabel {
    std::list<xlib::X11_TextLabel> char_labels;
		color::ColorPallete char_color_sequence;

    public:
      X11_ColorizedTextLabel();
      X11_ColorizedTextLabel(const std::string& text, 
                            const geometry::Rectangle& frame, 
                            const color::COLOR_SCHEME_TYPE& color_scheme, 
														color::ColorPallete&& char_color_sequence);
      ~X11_ColorizedTextLabel();
    
      void show(bool show_flag) override;
      void show_frame(bool show_flag) override;
			void set_center(const int& x, const int& y) override;

      void shift_colors();
      void update_char_colors();
  };
}


#endif /* SRC_INCLUDE_XLIB_X11_COLORIZEDTEXTLABEL_HPP */
