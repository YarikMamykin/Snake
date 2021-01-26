#ifndef SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP
#define SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP

#include <chrono>
#include <map>
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
    SNAKE_HEAD_X,
    SNAKE_HEAD_Y,
    SNAKE_HEAD_WIDTH,
    SNAKE_HEAD_HEIGHT
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
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
