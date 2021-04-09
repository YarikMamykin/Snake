#ifndef SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP
#define SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP

#include "game_objects/Food.hpp"
#include <random>
#include <list>
#include "configuration/Settings.hpp"

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
    const unsigned int window_width, window_height;

    public:
    explicit FoodGenerator(const unsigned int& window_width, const unsigned int& window_height);
    ~FoodGenerator() = default;

    Food* generate();
  };
}


#endif /* SRC_INCLUDE_GAME_OBJECTS_FOODGENERATOR_HPP */
