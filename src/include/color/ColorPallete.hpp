#ifndef SRC_INCLUDE_COLOR_COLORPALLETE_HPP
#define SRC_INCLUDE_COLOR_COLORPALLETE_HPP

#include "Color.hpp"
#include <list>
#include <string>

namespace color {
  struct ColorPallete {
    ColorPallete();
    ColorPallete(const char* hex_color);
    ColorPallete(const std::string& hex_color);
    ColorPallete(const Color& color);
    ColorPallete(const ColorPallete& color_pallete);
    ColorPallete(ColorPallete&& color_pallete);
    ColorPallete(const std::list<Color>& colors);
    ColorPallete& operator ++();
    ColorPallete& operator --();
    ColorPallete& operator = (const ColorPallete& color_pallete);
    void set_current_color(const Color& color);
    Color get_current_color() const;

    private:
    std::list<Color> colors;
    std::list<Color>::iterator current_color;
  };
}
#endif /* SRC_INCLUDE_COLOR_COLORPALLETE_HPP */
