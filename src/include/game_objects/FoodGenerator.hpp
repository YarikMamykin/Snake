#ifndef SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP

#include "Food.hpp"
#include <random>
#include <list>
#include "Settings.hpp"
#include "X11_Window.hpp"

namespace game_objects {

  class RandomEngine {
    configuration::RANDOM_ENGINE_ALGORITHM_TYPE algorithm;

    public:
      RandomEngine();
      geometry::Point generate_point(geometry::Rectangle&& region);
  };

  class FoodGenerator final {
    RandomEngine points_generator;
    geometry::Point&& prev_point;

    public:
    explicit FoodGenerator();
    ~FoodGenerator() = default;

    Food* generate(xlib::X11_Window* x_window);
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP */
