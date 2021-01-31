#ifndef SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP

#include "Food.hpp"

namespace game_objects {

  class FoodGenerator final {
    public:
    explicit FoodGenerator();
    ~FoodGenerator() = default;

    Food generate(xlib::X11_Window* x_window);
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP */
