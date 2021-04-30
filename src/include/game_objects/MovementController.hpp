#ifndef SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP
#define SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP

#include <memory>
#include "geometry/Rectangle.hpp"


namespace game_objects {

  class Snake;
  class Food;

  class MovementController final {
    Snake& snake;
    const unsigned int window_width, window_height;
    std::unique_ptr<Food> current_food;

    public:
      explicit MovementController(Snake& snake, const unsigned int& window_width, const unsigned int& window_height);
      ~MovementController() = default;

      bool validate() const;
      bool validate_snake_head_with_window_bounds() const;
      bool validate_snake_head_with_snake_tail() const;
      bool food_eaten() const;

      void set_current_food(Food* food);

      void increase_snake();
  };
}



#endif /* SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP */
