#ifndef SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP
#define SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP

#include <memory>
#include "X11_Window.hpp"
#include "Rectangle.hpp"


namespace game_objects {

  class Snake;
  class Food;

  class MovementController final {
    Snake& snake;
    std::unique_ptr<Food> current_food;
    xlib::X11_Window* x_window;

    public:
      explicit MovementController(Snake& snake, xlib::X11_Window* x_window);
      ~MovementController() = default;

      bool validate() const;
      bool validate_snake_head_with_window_bounds() const;
      bool validate_snake_head_with_snake_tail() const;
      bool food_eaten() const;

      void set_current_food(Food* food);
      Food& get_current_food();

      void increase_snake();
  };
}


#endif /* SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP */
