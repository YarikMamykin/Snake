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
    { ConfigID::SNAKE_SPEED, (new abstractions::ObservableValue<RESTRICTED_ULONG>(5ul, 1ul, 5ul))->wrap() },
    { ConfigID::SNAKE_COLOR, (new abstractions::ObservableValue<color::ColorPallete>("#00ff00"))->wrap() },
    { ConfigID::SNAKE_TIMEOUT, (new abstractions::ObservableValue<std::chrono::milliseconds>(50u))->wrap() },
    { ConfigID::GAME_OVER_TIMEOUT, (new abstractions::ObservableValue<std::chrono::milliseconds>(80u))->wrap() },
    { ConfigID::SNAKE_HEAD_WIDTH, (new abstractions::ObservableValue<RESTRICTED_UINT>(20u, 5u, 50u))->wrap() },
    { ConfigID::SNAKE_HEAD_HEIGHT, (new abstractions::ObservableValue<RESTRICTED_UINT>(10u, 5u, 50u))->wrap() },
    { ConfigID::RANDOM_ENGINE_ALGORITHM, (new abstractions::ObservableValue<RANDOM_ENGINE_ALGORITHM_TYPE>())->wrap() },
    { ConfigID::RANDOM_ENGINE_SEED_SEQUENCE, (new abstractions::ObservableValue<RANDOM_ENGINE_SEED_SEQUENCE_TYPE>(std::list<unsigned int>{1u,2u,3u,4u,5u,6u,7u,8u}))->wrap() },
    { ConfigID::FOOD_COLOR, (new abstractions::ObservableValue<color::Color>("#ffff00"))->wrap() },
    { ConfigID::FOOD_SIZE, (new abstractions::ObservableValue<RESTRICTED_UINT>(10u, 5u, 20u))->wrap() },
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
