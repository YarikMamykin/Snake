#include "FoodGenerator.hpp"

namespace game_objects {
  FoodGenerator::FoodGenerator() {
  }

  Food FoodGenerator::generate(xlib::X11_Window* x_window) {
    return Food(x_window, {/* food color*/ }, {/* generated frame */ });
  }
}
