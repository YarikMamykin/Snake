#ifndef SRC_INCLUDE_COLOR_COLORPALLETE_HPP
#define SRC_INCLUDE_COLOR_COLORPALLETE_HPP

#include "Color.hpp"
#include <list>
#include <string>

namespace color {
  struct ColorPallete {
    ColorPallete();
    ColorPallete(const std::string& hex_color);
    ColorPallete(const Color& color);
    ColorPallete(const ColorPallete& color_pallete);
    ColorPallete& operator ++();
    void set_current_color(const Color& color);
    const Color& get_current_color() const;
    ColorPallete& operator --();

    private:
    std::list<Color> colors;
    std::list<Color>::iterator current_color;
  };
}
#endif /* SRC_INCLUDE_COLOR_COLORPALLETE_HPP */
