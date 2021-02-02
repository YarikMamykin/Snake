#ifndef SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP

#include "X11_Window.hpp"
#include "Color.hpp"

namespace game_objects {
  class Food final {
    color::Color background_color, color; 
    geometry::Rectangle frame;

    public:
    explicit Food(const color::Color&& background_color, const color::Color&& color, geometry::Rectangle&& frame);
    ~Food();

    void show();
  };
}
#endif /* SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP */
