#include "configuration/Settings.hpp"
#include "color/ColorPallete/ColorPallete.hpp"
#include <color/ColorSchemeID.hpp>
#include <color/ColorScheme.hpp>
#include "abstractions/values/RestrictedValue.hpp"
#include <exception>

namespace configuration {
  std::map<ConfigID, std::any>& Settings::settings_map() {
    static std::map<ConfigID, std::any> sets_map = {
      { ConfigID::WINDOW_FRAME, geometry::Rectangle{ 0, 0, 200U, 200U } },
      { ConfigID::WINDOW_COLOR_SCHEME, color::COLOR_SCHEME_TYPE({ 
          { color::ColorSchemeID::FrameColor, color::Color("#ff0000") }, 
          { color::ColorSchemeID::BackgroundColor, color::Color("#000000") }, 
          { color::ColorSchemeID::FontColor, color::Color("#00ff00") } 
          })
      },
      { ConfigID::WINDOW_BORDER_WIDTH, 1u },
      { ConfigID::WINDOW_NAME, std::string("Snake") },
      { ConfigID::WINDOW_FONT_NAME, std::string("*-courier-*-24-*") },
      { ConfigID::SNAKE_SPEED, abstractions::values::RestrictedValue(10ul, 1ul, 10ul) },
      { ConfigID::SNAKE_SPEED_MULTIPLIER, std::chrono::milliseconds(3u) },
      { ConfigID::SNAKE_COLOR, color::ColorPallete(color::Color("#00ff00")) },
      { ConfigID::SNAKE_TIMEOUT, std::chrono::milliseconds(20u) },
      { ConfigID::SNAKE_SIZE, abstractions::values::RestrictedValue(1u, 1u, 10u) },
      { ConfigID::GAME_OVER_TIMEOUT, std::chrono::milliseconds(80u) },
      { ConfigID::RANDOM_ENGINE_ALGORITHM, RANDOM_ENGINE_ALGORITHM_TYPE() },
      { ConfigID::SIZE_MULTIPLIER, 20u },
      { ConfigID::FOOD_COLOR, color::ColorPallete(color::Color("#ffff00")) },
      { ConfigID::THREADS_SLEEP_TIMEOUT, std::chrono::microseconds(50u) },
    };
    return sets_map;
  }

  std::any Settings::get(ConfigID id) {
    return settings_map().at(id);
  }
}
