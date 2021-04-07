#ifndef SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP
#define SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP

#include <chrono>
#include <map>
#include <random>
#include <any>
#include "Rectangle.hpp"
#include "RestrictedValue.hpp"

namespace configuration {
  enum class ConfigID {
    WINDOW_FRAME,
    WINDOW_COLOR_SCHEME,
    WINDOW_BORDER_WIDTH,
    WINDOW_NAME,
    WINDOW_FONT_NAME,
    SNAKE_SPEED,
    SNAKE_SPEED_MULTIPLIER,
    SNAKE_COLOR,
    SNAKE_TIMEOUT,
    SNAKE_SIZE,
    GAME_OVER_TIMEOUT,
    RANDOM_ENGINE_ALGORITHM,
    SIZE_MULTIPLIER,
    FOOD_COLOR,
    THREADS_SLEEP_TIMEOUT
  };

  struct Settings final {
    static std::map<ConfigID, std::any> settings_map;
    static std::any get(ConfigID id);
    template<typename T> static T get_concrete(ConfigID id) {
      return std::any_cast<T>(settings_map.at(id));
    }
    template<typename T> static T& get_concrete_ref(ConfigID id) {
      return std::any_cast<T&>(settings_map.at(id));
    }
  };
}

namespace configuration {
  typedef std::linear_congruential_engine<std::uint_fast32_t, 1u, 300u, 700u> RANDOM_ENGINE_ALGORITHM_TYPE;
}

using config = configuration::Settings;
using config_id = configuration::ConfigID;
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
