#ifndef SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP

#include <list>
#include <queue> 
#include <memory>
#include "X11_Window.hpp"
#include "Constants.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "ObservableValue.hpp"

namespace game_objects {

  class MovementController;

  class Snake {
    public:
    explicit Snake(xlib::X11_Window* x_window, 
                   const color::Color& value,
                   geometry::Rectangle&& head_shape,
                   const SnakeDirection&& direction = SnakeDirection::Right);
    ~Snake();

    void move(const SnakeDirection& direction);

    friend class MovementController;

    private:
      struct SnakeHead {
        const unsigned int step;
        const unsigned int spacing;
        geometry::Rectangle frame;
        color::Color head_color;
        SnakeHead(const color::Color color, geometry::Rectangle&& frame, const unsigned int& spacing);
        SnakeHead(SnakeHead&&) = default;
        void show(xlib::X11_Window* x_window);
        void hide(xlib::X11_Window* x_window);
        void move(const SnakeDirection& new_direction, const RotationDirection& rotation_direction);

        inline void handle_none_rotation(const SnakeDirection& new_direction);
        inline geometry::Point get_counter_clockwize_rotation_point(const SnakeDirection& new_direction);
        inline geometry::Point get_clockwize_rotation_point(const SnakeDirection& new_direction);  

        inline void handle_shift_after_clockwize_rotation(const SnakeDirection& old_direction);
        inline void handle_shift_after_counter_clockwize_rotation(const SnakeDirection& old_direction);
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
