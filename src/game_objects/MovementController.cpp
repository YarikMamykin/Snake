#include "MovementController.hpp"
#include "Exceptions.hpp"
#include "Snake.hpp"

namespace game_objects {

  MovementController::MovementController(Snake& snake, xlib::X11_Window* x_window) 
  : snake(snake)
  , x_window(x_window) { }

  bool MovementController::validate_snake_head_with_window_bounds() const {
    auto&& snake_head_frame = snake.parts.front().frame;
    auto&& x_window_frame = x_window->get_frame();

    return snake_head_frame.belongs_to(x_window_frame);
  }

  bool MovementController::validate_snake_head_with_snake_tail() const {
    /*
     * BUG: BUGS FOR NOW!!!!
     * RETURNS FALSE ON SIMPLE MOVEMENT!!!!
     * NEED TO CHECK ONLY FORWARD PART OF SNAKE HEAD!
     */
    auto&& snake_head_frame = snake.parts.front().frame;
    auto snake_parts_it = snake.parts.begin();
    while((snake_parts_it = std::next(snake_parts_it)) != snake.parts.end()) {
      if(snake_parts_it->frame.crosses(snake_head_frame)) {
        return false;
      }
    }

    return true;
  }

  bool MovementController::validate() const {
    return validate_snake_head_with_window_bounds() 
           &&
           validate_snake_head_with_snake_tail();
  }
}
