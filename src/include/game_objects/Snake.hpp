#ifndef SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP

#include <list>
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
      struct SnakePart {
        virtual void show(xlib::X11_Window* x_window) = 0;
        virtual void move(const SnakeDirection& direction, const RotationDirection& rotation_direction) = 0;
        virtual ~SnakePart() {}
      };

      struct SnakeHead : public SnakePart {
        // geometry::Triangle frame;
        geometry::Rectangle frame;
        SnakeHead(geometry::Rectangle&& frame);
        void show(xlib::X11_Window* x_window) override;
        void hide(xlib::X11_Window* x_window);
        void move(const SnakeDirection& direction, const RotationDirection& rotation_direction) override;
      };

      struct SnakeTailPart : public SnakePart {
        geometry::Rectangle frame;
        SnakeTailPart(geometry::Rectangle&& frame);
        void show(xlib::X11_Window* x_window) override;
        void move(const SnakeDirection& direction, const RotationDirection& rotation_direction) override;
      };

      void show(xlib::X11_Window* x_window);
      void hide(xlib::X11_Window* x_window);
      inline bool is_opposite_to_current(const SnakeDirection& direction);

      std::list<SnakeHead> parts;
      xlib::X11_Window* x_window;
      SnakeDirection current_direction;
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP */
