#ifndef SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP

#include "Food.hpp"
#include <random>
#include <list>
#include "Settings.hpp"

namespace game_objects {

  class RandomEngine {
    configuration::RANDOM_ENGINE_ALGORITHM_TYPE algorithm;

    public:
      RandomEngine(const unsigned int& min, const unsigned int& max, std::list<unsigned int>&& seed_sequence);
      geometry::Point generate_point();
  };

  class FoodGenerator final {
    RandomEngine points_generator;

    public:
    explicit FoodGenerator();
    ~FoodGenerator() = default;

    Food generate(xlib::X11_Window* x_window);
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP */
