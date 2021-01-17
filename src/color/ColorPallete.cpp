#include "ColorPallete.hpp"
#include <algorithm>

namespace {
  const std::list<color::Color> default_colors = { 
    color::Color("#ff0000"), 
    color::Color("#00ff00"), 
    color::Color("#0000ff") 
  };
}

namespace color {
  ColorPallete::ColorPallete() 
    : colors(default_colors) 
    , current_color(colors.begin()) { }

  ColorPallete::ColorPallete(const std::string& hex_color)
    : ColorPallete(Color(hex_color)) { }

  ColorPallete::ColorPallete(const Color& color)
    : ColorPallete() {
      set_current_color(color);
    }

  ColorPallete::ColorPallete(const ColorPallete& color_pallete)
    : colors(color_pallete.colors)
      , current_color(colors.begin()) {
        set_current_color(color_pallete.get_current_color());
      }

  ColorPallete::ColorPallete(ColorPallete&& color_pallete)
    : colors(std::move(color_pallete.colors))
    , current_color(colors.begin()) { }

  ColorPallete::ColorPallete(const std::list<Color>& user_defined_colors) 
    : colors(user_defined_colors) 
    , current_color(colors.begin()) { }

  ColorPallete& ColorPallete::operator ++() {
    if(current_color == std::prev(colors.end())) {
      current_color = colors.begin();
    } else {
      current_color = std::next(current_color);
    }
    return *this;
  }

  ColorPallete& ColorPallete::operator --() {
    if(current_color == colors.begin()) {
      current_color = std::prev(colors.end());
    } else { 
      current_color = std::prev(current_color);
    }
    return *this;
  }

  ColorPallete& ColorPallete::operator = (const ColorPallete& color_pallete) {
    this->colors = color_pallete.colors;
    this->set_current_color(color_pallete.get_current_color());
    return *this;
  }

  const Color& ColorPallete::get_current_color() const {
    return *current_color;
  }

  void ColorPallete::set_current_color(const Color& color) {
    current_color = std::find(colors.begin(), colors.end(), color);
    if(current_color == colors.end()) {
      colors.push_front(color);
      current_color = colors.begin();
    }
  }
}
