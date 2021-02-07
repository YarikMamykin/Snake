#ifndef SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP

#include "Rectangle.hpp"
#include "Color.hpp"

namespace game_objects {
  struct Food final {
    color::Color background_color, color; 
    geometry::Rectangle frame;

    public:
    Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame);
    ~Food();

    void show();
  };
}
#endif /* SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP */
