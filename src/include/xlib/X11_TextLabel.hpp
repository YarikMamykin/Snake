#ifndef SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP
#define SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP

#include "X11_Window.hpp"
#include "Rectangle.hpp"
#include "TextLabel.hpp"
#include <string>

namespace xlib {

  class X11_TextLabel : public abstractions::ui::TextLabel { 
    public:
      static const unsigned int left_text_margin = 10U;
      static const unsigned int top_text_margin = 10U;
      static const unsigned int frame_weight = 3U;

    public:
      X11_TextLabel(X11_Window* parent_window);
      X11_TextLabel(const std::string& text, 
                    const geometry::Rectangle& frame, 
                    const constants::COLOR_SCHEME_TYPE& color_scheme, 
                    X11_Window* parent_window);
      ~X11_TextLabel();

      void show(bool show_flag) override;
      void show_frame(bool show_flag) override;

    private:
      void update();
      void update_frame();
      const unsigned int get_text_graphical_width() const;
      const unsigned int get_text_graphical_height() const;
      void hide_prev_frame();

    private:
      X11_Window* parent_window;
      geometry::Rectangle prev_frame;
  };
}

#endif /* SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP */
