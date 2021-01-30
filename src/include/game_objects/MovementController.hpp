#ifndef SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP
#define SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP

#include <list>
#include <queue> 
#include <memory>
#include "X11_Window.hpp"
#include "Rectangle.hpp"


namespace game_objects {

  class Snake;

  class MovementController final {
    Snake& snake;
    xlib::X11_Window* x_window;

    public:
      explicit MovementController(Snake& snake, xlib::X11_Window* x_window);
      ~MovementController() = default;

      bool validate() const;
      bool validate_snake_head_with_window_bounds() const;
      bool validate_snake_head_with_snake_tail() const;
  };
}


#endif /* SRC_INCLUDE_GAME_OBJECTS_MOVEMENTCONTROLLER_HPP */
