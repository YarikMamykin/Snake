#ifndef SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP
#define SRC_INCLUDE_CONFIGURATION_SETTINGS_HPP

#include <chrono>
#include <map>
#include "Rectangle.hpp"
#include "ObservableValue.hpp"

namespace configuration {
  enum class ConfigID {
    WINDOW_FRAME,
    WINDOW_COLOR_SCHEME,
    WINDOW_BORDER_WIDTH,
    WINDOW_NAME,
    WINDOW_FONT_NAME,
    SNAKE_SPEED,
    SNAKE_COLOR,
    SNAKE_TIMEOUT
  };

  struct Settings final {
    static std::map<ConfigID, std::shared_ptr<abstractions::ObservableValueContainerWrapper>> settings_map;
    static std::shared_ptr<abstractions::ObservableValueContainerWrapper> get(ConfigID id);
  };
}
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
