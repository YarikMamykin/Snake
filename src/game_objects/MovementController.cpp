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
    using namespace geometry;

    
    auto snake_head_crosses_tail = [this](Point&& forward_p1, Point&& forward_p2) -> bool { 
      auto snake_parts_it = snake.parts.begin();
      while((snake_parts_it = std::next(snake_parts_it)) != snake.parts.end()) {
        if(snake_parts_it->frame.has_point(std::move(forward_p1)) || snake_parts_it->frame.has_point(std::move(forward_p2))) {
          return true;
        }
      }

      return false;
    };

    auto& snake_head_frame = snake.parts.front().frame;
    switch(snake.current_direction) {
      case SnakeDirection::Down: { return !snake_head_crosses_tail(snake_head_frame.bottom_left(), snake_head_frame.bottom_right()); }
      case SnakeDirection::Up:   { return !snake_head_crosses_tail(snake_head_frame.top_left(),    snake_head_frame.top_right()); }
      case SnakeDirection::Left: { return !snake_head_crosses_tail(snake_head_frame.top_left(),    snake_head_frame.bottom_left()); } 
      case SnakeDirection::Right:{ return !snake_head_crosses_tail(snake_head_frame.top_right(),   snake_head_frame.bottom_right()); } 
    }

    return true;
  }

  bool MovementController::validate() const {
    return validate_snake_head_with_window_bounds() && validate_snake_head_with_snake_tail();
  }

  bool MovementController::food_eaten() const {
    auto& snake_head_frame = snake.parts.front().frame;
    return current_food->frame.has_point(snake_head_frame.top_left()) ||
           current_food->frame.has_point(snake_head_frame.top_right()) ||
           current_food->frame.has_point(snake_head_frame.bottom_left()) ||
           current_food->frame.has_point(snake_head_frame.bottom_right());
  }

  void MovementController::set_current_food(Food* food) {
    current_food.reset(food);
  }

  Food& MovementController::get_current_food() {
    return *this->current_food;
  }

}
