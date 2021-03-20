#include "Settings.hpp"
#include "ColorPallete.hpp"
#include <exception>

namespace configuration {
  std::map<ConfigID, std::shared_ptr<abstractions::ObservableValueContainerWrapper>> Settings::settings_map = {
    { ConfigID::WINDOW_FRAME, (new abstractions::ObservableValue<geometry::Rectangle>(0, 0, 200U, 200U))->wrap() },
    { ConfigID::WINDOW_COLOR_SCHEME, (new abstractions::ObservableValue<color::COLOR_SCHEME_TYPE>(color::COLOR_SCHEME_TYPE({ 
            { color::ColorSchemeID::FrameColor, color::Color("#ff0000") }, 
            { color::ColorSchemeID::BackgroundColor, color::Color("#000000") }, 
            { color::ColorSchemeID::FontColor, color::Color("#00ff00") } 
            })))->wrap()
    },
    { ConfigID::WINDOW_BORDER_WIDTH, (new abstractions::ObservableValue<unsigned int>(1u))->wrap() },
    { ConfigID::WINDOW_NAME, (new abstractions::ObservableValue<std::string>("Snake"))->wrap() },
    { ConfigID::WINDOW_FONT_NAME, (new abstractions::ObservableValue<std::string>("*-courier-*-24-*"))->wrap() },
    { ConfigID::SNAKE_SPEED, (new abstractions::ObservableValue<RESTRICTED_ULONG>(10ul, 1ul, 10ul))->wrap() },
    { ConfigID::SNAKE_SPEED_MULTIPLIER, (new abstractions::ObservableValue<std::chrono::milliseconds>(3u))->wrap() },
    { ConfigID::SNAKE_COLOR, (new abstractions::ObservableValue<color::ColorPallete>("#00ff00"))->wrap() },
    { ConfigID::SNAKE_TIMEOUT, (new abstractions::ObservableValue<std::chrono::milliseconds>(25u))->wrap() },
    { ConfigID::SNAKE_SIZE, (new abstractions::ObservableValue<RESTRICTED_UINT>(1u, 1u, 10u))->wrap() },
    { ConfigID::GAME_OVER_TIMEOUT, (new abstractions::ObservableValue<std::chrono::milliseconds>(80u))->wrap() },
    { ConfigID::RANDOM_ENGINE_ALGORITHM, (new abstractions::ObservableValue<RANDOM_ENGINE_ALGORITHM_TYPE>())->wrap() },
    { ConfigID::SIZE_MULTIPLIER, (new abstractions::ObservableValue<const unsigned int>(20u))->wrap() },
    { ConfigID::FOOD_COLOR, (new abstractions::ObservableValue<color::ColorPallete>("#ffff00"))->wrap() },
  };
  
  std::shared_ptr<abstractions::ObservableValueContainerWrapper> Settings::get(ConfigID id) {
    std::shared_ptr<abstractions::ObservableValueContainerWrapper> result;

    try {
      result = settings_map.at(id);
    } catch(const std::out_of_range&) {
      result = nullptr;
    }

    return result;
  }
}
