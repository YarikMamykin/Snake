#include "Food.hpp"
#include "commands/graphics_commands/FillCircle/FillCircle.hpp"
#include "configuration/Settings.hpp"

namespace game_objects {

  Food::Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame) 
  : background_color(background_color) 
  , color(color) 
  , frame(std::move(frame)) 
  , timer(
      config::get_concrete<std::chrono::milliseconds>(config_id::SNAKE_TIMEOUT), 
      [frame, color]() {
        commands::Command::push_xlib_command(std::make_unique<commands::FillCircle>(frame, color));
      }) 
  {
    timer.launch();
  }

  Food::~Food() {
    timer.stop();
    commands::Command::push_xlib_command(std::make_unique<commands::FillCircle>(frame, background_color));
  }
}
