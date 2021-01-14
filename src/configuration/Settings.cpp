#include "Settings.hpp"
#include "ColorPallete.hpp"
#include <exception>

namespace configuration {
  std::map<ConfigID, std::shared_ptr<abstractions::ObservableValueContainerWrapper>> Settings::settings_map = {
    { ConfigID::WINDOW_FRAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<geometry::Rectangle>({ .x = 0, .y = 0, .width = 200U, .height = 200U })))) },
    { ConfigID::WINDOW_COLOR_SCHEME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<color::COLOR_SCHEME_TYPE>({ 
              { color::ColorSchemeID::FrameColor, color::Color("#ff0000") }, 
              { color::ColorSchemeID::BackgroundColor, color::Color("#000000") }, 
              { color::ColorSchemeID::FontColor, color::Color("#00ff00") } 
              })))) 
    },
    { ConfigID::WINDOW_BORDER_WIDTH, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<unsigned int>(1u)))) },
    { ConfigID::WINDOW_NAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::string>("Snake")))) },
    { ConfigID::WINDOW_FONT_NAME, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::string>("*-courier-*-24-*")))) },
    { ConfigID::SNAKE_SPEED, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<SNAKE_SPEED_TYPE>(SNAKE_SPEED_TYPE(1ul, 1ul, 5ul))))) },
    { ConfigID::SNAKE_COLOR, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<color::ColorPallete>(std::string("#00ff00"))))) },
    { ConfigID::SNAKE_TIMEOUT, std::shared_ptr<abstractions::ObservableValueContainerWrapper>(static_cast<abstractions::ObservableValueContainerWrapper*>((new abstractions::ObservableValue<std::chrono::milliseconds>(std::chrono::milliseconds(50u))))) }
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
