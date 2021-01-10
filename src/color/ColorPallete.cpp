#include "ColorPallete.hpp"
#include <algorithm>
#include <iostream>

namespace color {
  ColorPallete::ColorPallete() 
    : colors({ Color("#ff0000"), Color("#00ff00"), Color("#0000ff") }) 
    , current_color(colors.begin()) { }

  ColorPallete::ColorPallete(const std::string& hex_color)
    : ColorPallete() {
      set_current_color(Color(hex_color));
    }

  ColorPallete::ColorPallete(const Color& color)
    : ColorPallete() {
      set_current_color(color);
    }

  ColorPallete::ColorPallete(const ColorPallete& color_pallete) 
    : colors(color_pallete.colors) 
      , current_color(colors.begin()) {
        set_current_color(color_pallete.get_current_color());
      }

  ColorPallete& ColorPallete::operator ++() {
    if(current_color == std::prev(colors.end()) || current_color == colors.end()) {
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

  const Color& ColorPallete::get_current_color() const {
    return *current_color;
  }

  void ColorPallete::set_current_color(const Color& color) {
    current_color = std::find(colors.begin(), colors.end(), color);
    if(current_color == colors.end()) {
      std::cout << "NEW COLOR ADDED! " << color.to_string() << std::endl;
      colors.push_front(color);
      current_color = colors.begin();
    }

    std::cout << "COLOR_PALLETE SIZE: " << colors.size() << std::endl;
    for(auto& color : colors) {
      std::cout << "COLOR: " << color.to_string() << std::endl;
    }
  }
}
