#include "Settings.hpp"
#include "ColorPallete.hpp"
#include <exception>

namespace configuration {
  std::map<ConfigID, std::shared_ptr<abstractions::ObservableValueContainerWrapper>> Settings::settings_map = {
    { ConfigID::WINDOW_FRAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<geometry::Rectangle>(0, 0, 200U, 200U)))) },
    { ConfigID::WINDOW_COLOR_SCHEME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<color::COLOR_SCHEME_TYPE>(color::COLOR_SCHEME_TYPE({ 
              { color::ColorSchemeID::FrameColor, color::Color("#ff0000") }, 
              { color::ColorSchemeID::BackgroundColor, color::Color("#000000") }, 
              { color::ColorSchemeID::FontColor, color::Color("#00ff00") } 
              })))))
    },
    { ConfigID::WINDOW_BORDER_WIDTH, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<unsigned int>(1u)))) },
    { ConfigID::WINDOW_NAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::string>("Snake")))) },
    { ConfigID::WINDOW_FONT_NAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::string>("*-courier-*-24-*")))) },
    { ConfigID::SNAKE_SPEED, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<RESTRICTED_ULONG>(5ul, 1ul, 5ul)))) },
    { ConfigID::SNAKE_COLOR, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<color::ColorPallete>("#00ff00")))) },
    { ConfigID::SNAKE_TIMEOUT, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::chrono::milliseconds>(std::chrono::milliseconds(50u))))) },
    { ConfigID::GAME_OVER_TIMEOUT, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::chrono::milliseconds>(std::chrono::milliseconds(80u))))) },
    { ConfigID::SNAKE_HEAD_X, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<RESTRICTED_INT>(80, 10, 2000)))) },
    { ConfigID::SNAKE_HEAD_Y, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<RESTRICTED_INT>(80, 10, 2000)))) },
    { ConfigID::SNAKE_HEAD_WIDTH, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<RESTRICTED_UINT>(20ul, 5ul, 50ul)))) },
    { ConfigID::SNAKE_HEAD_HEIGHT, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<RESTRICTED_UINT>(10ul, 5ul, 50ul)))) },
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
