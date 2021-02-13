#ifndef SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP

#include <list>
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
    geometry::Rectangle head_frame() const;

    friend class MovementController;

    private:
      struct SnakeHead {
        const unsigned int step;
        const unsigned int shift;
        const unsigned int spacing;
        geometry::Rectangle frame;
        color::Color head_color;
        SnakeDirection direction;
        SnakeDirection old_direction;
        RotationDirection rotation_direction;

        SnakeHead(const color::Color color, 
                  geometry::Rectangle&& frame, 
                  SnakeDirection&& direction,
                  RotationDirection&& rotation_direction,
                  const unsigned int& spacing);
        SnakeHead(SnakeHead&&) = default;
        void show(xlib::X11_Window* x_window);
        void hide(xlib::X11_Window* x_window);
        void move();

        inline void handle_none_rotation();
        inline geometry::Point get_counter_clockwize_rotation_point();
        inline geometry::Point get_clockwize_rotation_point();  

        inline void handle_shift_after_clockwize_rotation();
        inline void handle_shift_after_counter_clockwize_rotation();
      };

      void show(xlib::X11_Window* x_window);
      void hide(xlib::X11_Window* x_window);
      inline bool is_opposite_to_current(const SnakeDirection& direction);
      void increase();

      std::list<SnakeHead> parts;
      xlib::X11_Window* x_window;
      SnakeDirection current_direction;
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP */
