#ifndef SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP

#include <list>
#include <queue> 
#include <memory>
#include "X11_Window.hpp"
#include "Constants.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

namespace game_objects {
  class Snake {
    public:
    explicit Snake(xlib::X11_Window* x_window, 
                   const SnakeDirection&& direction = SnakeDirection::Right);
    ~Snake();

    void move(const SnakeDirection& direction);

    private:
      struct MovementController {
        void validate( geometry::Rectangle& frame, 
                       const geometry::Rectangle& x_window_frame);
      } mcontroller;

      struct SnakeHead {
        const unsigned int step;
        const unsigned int spacing;
        geometry::Rectangle frame;
        SnakeHead(geometry::Rectangle&& frame, const unsigned int& spacing);
        SnakeHead(SnakeHead&&) = default;
        void show(xlib::X11_Window* x_window);
        void hide(xlib::X11_Window* x_window);
        void move(const SnakeDirection& new_direction, const RotationDirection& rotation_direction);

        void handle_none_rotation(const SnakeDirection& new_direction);
        geometry::Point get_counter_clockwize_rotation_point(const SnakeDirection& new_direction);
        geometry::Point get_clockwize_rotation_point(const SnakeDirection& new_direction);  
      };

      void show(xlib::X11_Window* x_window);
      void hide(xlib::X11_Window* x_window);
      inline bool is_opposite_to_current(const SnakeDirection& direction);

      std::list<SnakeHead> parts;
      xlib::X11_Window* x_window;
      SnakeDirection current_direction;
      geometry::Rectangle window_frame;
      std::deque<std::pair<SnakeDirection, RotationDirection>> movement_queue;
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP */
