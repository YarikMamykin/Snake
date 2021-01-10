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
    template <typename ValueType>
    static std::shared_ptr<abstractions::ObservableValue<ValueType>> get_concrete_ptr(ConfigID id);
    template <typename ValueType>
    static ValueType get_concrete(ConfigID id);
  };
}

namespace configuration {
  template <typename ValueType>
  std::shared_ptr<abstractions::ObservableValue<ValueType>> Settings::get_concrete_ptr(ConfigID id) {
    using namespace abstractions;
    std::shared_ptr<ObservableValue<ValueType>> result;

    try {
      result = ObservableValueContainerWrapper::to_concrete_value<ValueType>(settings_map.at(id));
    } catch(const std::out_of_range&) {
      result = nullptr;
    }
    return result;
  }

  template <typename ValueType>
  ValueType Settings::get_concrete(ConfigID id) {
    using namespace abstractions;
    ValueType result;

    try {
      result = get_concrete_ptr<ValueType>(id)->get_value();
    } catch(const std::out_of_range&) { }
    return result;
  }
}
#endif /* SRC_INCLUDE_SETTINGS_SETTINGS_HPP */
