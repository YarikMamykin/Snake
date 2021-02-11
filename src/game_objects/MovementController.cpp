#include "MovementController.hpp"
#include "Exceptions.hpp"
#include "Snake.hpp"
#include "Food.hpp"

namespace game_objects {

  MovementController::MovementController(Snake& snake, xlib::X11_Window* x_window) 
  : snake(snake)
  , x_window(x_window) { }

  bool MovementController::validate_snake_head_with_window_bounds() const {
    return snake.parts.front().frame.belongs_to(x_window->get_frame());
  }

  bool MovementController::validate_snake_head_with_snake_tail() const {
    auto& snake_head_frame = snake.parts.front().frame;
    auto snake_parts_it = snake.parts.begin();
    while((snake_parts_it = std::next(snake_parts_it)) != snake.parts.end()) {
      if(!snake_parts_it->frame.do_not_cross(snake_head_frame)) {
        return false;
      }
    }
    return true;
  }

  bool MovementController::validate() const {
    return validate_snake_head_with_window_bounds() && validate_snake_head_with_snake_tail();
  }

  bool MovementController::food_eaten() const {
    return !snake.parts.front().frame.do_not_cross(current_food->frame);
  }

  void MovementController::set_current_food(Food* food) {
    current_food.reset(food);
  }

  Food& MovementController::get_current_food() {
    return *this->current_food;
  }

}
