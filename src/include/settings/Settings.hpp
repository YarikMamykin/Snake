#ifndef SRC_INCLUDE_SETTINGS_SETTINGS_HPP
#define SRC_INCLUDE_SETTINGS_SETTINGS_HPP

#include "X11_Window.hpp"

namespace settings {
  class Settings final {
    Settings() 
    : win_sets({ 
        .x = 10,
        .y = 10,
        .w = 200U,
        .h = 200U,
        .border_width = 1U,
        .border_color = (255L << 16),
        .backgnd_color = (0L),
        .font_color = (255L << 8),
        .name = "Snake",
        .font_name = "*-courier-*-24-*"
        })
    , snake_speed(10U)
    {

    }

    public:
    const xlib::WindowSettings win_sets;
    const unsigned int snake_speed;

    static Settings& settings() {
      static Settings sets;
      return sets;
    }
  };
}
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
