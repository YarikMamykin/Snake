#include "Food.hpp"
#include "FillCircle.hpp"
#include "Settings.hpp"

namespace game_objects {

  Food::Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame) 
  : background_color(background_color) 
  , color(color) 
  , frame(std::move(frame)) {
    timer.timeout = config::get_concrete<std::chrono::milliseconds>(config_id::SNAKE_TIMEOUT); 
    timer.callback = [this]() {
      commands::Command::push_xlib_command(new commands::FillCircle(this->frame, this->color));
    };
    timer.launch();
  }

  Food::~Food() {
    timer.stop();
    commands::Command::push_xlib_command(new commands::FillCircle(frame, background_color));
  }
}
