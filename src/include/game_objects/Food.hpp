#ifndef SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP

#include "X11_Window.hpp"
#include "Color.hpp"

namespace game_objects {
  class Food final {
    xlib::X11_Window* x_window;
    color::Color color; 
    geometry::Rectangle frame;

    public:
    explicit Food(xlib::X11_Window* x_window, const color::Color&& color, geometry::Rectangle&& frame);
    ~Food();

    void show();
  };
}
#endif /* SRC_INCLUDE_GAME_OBJECTS_FOOD_HPP */
