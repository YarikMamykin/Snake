#include "Food.hpp"
#include "FillCircle.hpp"

namespace game_objects {

  Food::Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame) 
  : background_color(background_color) 
  , color(color) 
  , frame(std::move(frame)) { 
    commands::Command::push_xlib_command(new commands::FillCircle(frame, color));
  }

  Food::~Food() {
    commands::Command::push_xlib_command(new commands::FillCircle(frame, background_color));
  }
}
