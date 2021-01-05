#ifndef SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP
#define SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP

#include <chrono>
#include "Rectangle.hpp"
#include "Constants.hpp"

namespace configuration {
  struct Settings final {
    public:
    geometry::Rectangle window_frame { .x = 0, .y = 0, .width = 200U, .height = 200U };
    constants::COLOR_SCHEME_TYPE window_color_scheme = {
      { ui::ColorSchemeID::FrameColor, color::Color("#ff0000") },
      { ui::ColorSchemeID::BackgroundColor, color::Color("#000000") },
      { ui::ColorSchemeID::FontColor, color::Color("#00ff00") },
    };
    unsigned int border_width = 1U;
    std::string window_name = "Snake";
    std::string font_name = "*-courier-*-24-*";
    unsigned int snake_speed = 10u;
    color::Color snake_color = std::string("#00ff00");
    std::chrono::milliseconds snake_timeout = std::chrono::milliseconds(50u);
  };
}
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
