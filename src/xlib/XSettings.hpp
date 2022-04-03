#pragma once
#include <string>
#include <color/Color/Color.hpp>
#include <color/ColorScheme.hpp>

namespace xlib {
  struct XSettings {
    std::string font_name;
    std::string window_name;
    struct {
      int x;
      int y;
      unsigned int w;
      unsigned int h;
    } window_geometry;
    unsigned int border_width;
    color::COLOR_SCHEME_TYPE window_color_scheme;
  };
}
