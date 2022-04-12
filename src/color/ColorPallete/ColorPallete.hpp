#pragma once

#include "color/Color/Color.hpp"
#include <list>
#include <string>

namespace color {
  class ColorPallete {
    std::list<Color> m_colors;
    std::list<Color>::iterator m_current_color;

    public:
    ColorPallete();
    ColorPallete(const Color& color);
    ColorPallete(const ColorPallete& color_pallete);
    ColorPallete(ColorPallete&& color_pallete);
    ColorPallete(const std::list<Color>& colors);
    ColorPallete& operator ++();
    ColorPallete& operator --();
    ColorPallete& operator = (const ColorPallete& color_pallete);

    Color current_color() const noexcept;
    void set_color(const Color& color) noexcept;
  };
}
