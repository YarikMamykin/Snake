#ifndef SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP

#include "Rectangle.hpp"
#include "Color.hpp"
#include "Timer.hpp"

namespace game_objects {
  struct Food final {
    color::Color background_color, color; 
    geometry::Rectangle frame;
    timing::Timer timer;

    public:
    Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame);
    ~Food();
  };
}
#endif /* SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP */
