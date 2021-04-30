#include "game_objects/MovementController.hpp"
#include "exceptions/Exceptions.hpp"
#include "game_objects/Snake.hpp"
#include "game_objects/Food.hpp"

namespace game_objects {

  MovementController::MovementController(Snake& snake, const unsigned int& window_width, const unsigned int& window_height) 
  : snake(snake) 
  , window_width(window_width)
  , window_height(window_height) { }

  bool MovementController::validate_snake_head_with_window_bounds() const {
    geometry::Rectangle&& win_frame = {0,0,window_width, window_height};
    return snake.parts.front().frame.belongs_to(win_frame);
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

  void MovementController::set_current_food(std::unique_ptr<Food> food) {
    current_food = std::move(food);
  }

  void MovementController::increase_snake() {
    snake.increase();
  }

}
