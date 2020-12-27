#ifndef SRC_INCLUDE_SETTINGS_SETTINGS_HPP
#define SRC_INCLUDE_SETTINGS_SETTINGS_HPP

#include "X11_Window.hpp"
#include <chrono>

namespace settings {
  class Settings final {
    Settings() 
    : win_sets({ 
        { 
          .x = 0,
          .y = 0,
          .width = 200U,
          .height = 200U
        },
        {
          { ui::ColorSchemeID::FrameColor, (255L << 16) },
          { ui::ColorSchemeID::BackgroundColor, (0L) },
          { ui::ColorSchemeID::FontColor, (255L << 8) },
        },
        .border_width = 1U,
        .name = "Snake",
        .font_name = "*-courier-*-24-*"
      })
    , snake_speed(10U)
    , snake_color((255U << 8))
    , snake_timeout(50u)
    {

    }

    public:
    xlib::WindowSettings win_sets;
    unsigned int snake_speed;
    unsigned int snake_color;
    std::chrono::milliseconds snake_timeout;

    static Settings& settings() {
      static Settings sets;
      return sets;
    }
  };
}
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
