#include "FoodGenerator.hpp"

namespace game_objects {
  FoodGenerator::FoodGenerator() {
  }

  Food FoodGenerator::generate(xlib::X11_Window* x_window) {
    return Food({/* background color*/ }, {/* food color*/ }, {/* generated frame */ });
  }
}
