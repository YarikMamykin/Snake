#include "ColorPallete.hpp"
#include <algorithm>

namespace color {
  ColorPallete::ColorPallete() 
    : m_colors({ 
        color::Color("#ff0000"), 
        color::Color("#00ff00"), 
        color::Color("#0000ff") }) 
    , m_current_color(m_colors.begin()) { }

  ColorPallete::ColorPallete(const Color& color)
    : ColorPallete() {
      set_color(color);
    }

  ColorPallete::ColorPallete(const ColorPallete& color_pallete)
    : m_colors(color_pallete.m_colors)
      , m_current_color(m_colors.begin()) {
        set_color(color_pallete.current_color());
      }

  ColorPallete::ColorPallete(ColorPallete&& color_pallete)
    : m_colors(std::move(color_pallete.m_colors))
    , m_current_color(m_colors.begin()) { }

  ColorPallete::ColorPallete(const std::list<Color>& user_defined_m_colors) 
    : m_colors(user_defined_m_colors) 
    , m_current_color(m_colors.begin()) { }

  ColorPallete& ColorPallete::operator ++() {
    if(m_current_color == std::prev(m_colors.end())) {
      m_current_color = m_colors.begin();
    } else {
      m_current_color = std::next(m_current_color);
    }
    return *this;
  }

  ColorPallete& ColorPallete::operator --() {
    if(m_current_color == m_colors.begin()) {
      m_current_color = std::prev(m_colors.end());
    } else { 
      m_current_color = std::prev(m_current_color);
    }
    return *this;
  }

  ColorPallete& ColorPallete::operator = (const ColorPallete& color_pallete) {
    this->m_colors = color_pallete.m_colors;
    this->set_color(color_pallete.current_color());
    return *this;
  }

  Color ColorPallete::current_color() const noexcept {
    return *m_current_color;
  }

  void ColorPallete::set_color(const Color& color) noexcept {
    m_current_color = std::find(m_colors.begin(), m_colors.end(), color);
    if(m_current_color == m_colors.end()) {
      m_colors.push_front(color);
      m_current_color = m_colors.begin();
    }
  }
}
