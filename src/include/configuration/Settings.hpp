#ifndef SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP
#define SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP

#include <chrono>
#include <map>
#include <random>
#include "Rectangle.hpp"
#include "ObservableValue.hpp"
#include "RestrictedValue.hpp"

namespace configuration {
  enum class ConfigID {
    WINDOW_FRAME,
    WINDOW_COLOR_SCHEME,
    WINDOW_BORDER_WIDTH,
    WINDOW_NAME,
    WINDOW_FONT_NAME,
    SNAKE_SPEED,
    SNAKE_COLOR,
    SNAKE_TIMEOUT,
    GAME_OVER_TIMEOUT,
    SNAKE_HEAD_WIDTH,
    SNAKE_HEAD_HEIGHT,
    RANDOM_ENGINE_ALGORITHM,
    RANDOM_ENGINE_SEED_SEQUENCE,
    FOOD_COLOR,
    FOOD_SIZE
  };

  struct Settings final {
    static std::map<ConfigID, std::shared_ptr<abstractions::ObservableValueContainerWrapper>> settings_map;
    static std::shared_ptr<abstractions::ObservableValueContainerWrapper> get(ConfigID id);
    template <typename ValueType>
    static std::shared_ptr<abstractions::ObservableValue<ValueType>> get_concrete_ptr(ConfigID id);
    template <typename ValueType>
    static ValueType get_concrete(ConfigID id);
  };
}

namespace configuration {
  template <typename ValueType>
  std::shared_ptr<abstractions::ObservableValue<ValueType>> Settings::get_concrete_ptr(ConfigID id) {
    return abstractions::ObservableValueContainerWrapper::to_concrete_value<ValueType>(settings_map.at(id));
  }

  template <typename ValueType>
  ValueType Settings::get_concrete(ConfigID id) {
    return get_concrete_ptr<ValueType>(id)->get_value();
  }
}

namespace configuration {
  typedef std::linear_congruential_engine<std::uint_fast32_t, 1u, 10u, 700u> RANDOM_ENGINE_ALGORITHM_TYPE;
  typedef std::list<unsigned int> RANDOM_ENGINE_SEED_SEQUENCE_TYPE;
}

#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
