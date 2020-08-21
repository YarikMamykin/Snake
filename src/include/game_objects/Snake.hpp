#ifndef SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP

#include <list>
#include "X11_Window.hpp"
#include "Constants.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

namespace game_objects {
  class Snake {
    public:
    explicit Snake(xlib::X11_Window* x_window, 
                   const SnakeDirection&& direction = SnakeDirection::Up);
    ~Snake();

    void move(const SnakeDirection&& direction);

    private:
      struct SnakePart {
        virtual void show(xlib::X11_Window* x_window) = 0;
        virtual void move(const SnakeDirection&& direction, const int& rotation_angle) = 0;
        virtual ~SnakePart();
      };

      struct SnakeHead : public SnakePart {
        // geometry::Triangle frame;
        geometry::Rectangle frame;
        SnakeHead(geometry::Rectangle&& frame);
        void show(xlib::X11_Window* x_window) override;
        void move(const SnakeDirection&& direction, const int& rotation_angle) override;
      };

      struct SnakeTailPart : public SnakePart {
        geometry::Rectangle frame;
        SnakeTailPart(geometry::Rectangle&& frame);
        void show(xlib::X11_Window* x_window) override;
        void move(const SnakeDirection&& direction, const int& rotation_angle) override;
      };

      void show(xlib::X11_Window* x_window);
      void hide(xlib::X11_Window* x_window);
      inline bool has_same_axis(const SnakeDirection&& direction);

      std::list<SnakePart&&> parts;
      xlib::X11_Window* x_window;
      SnakeDirection current_direction;
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECT_SNAKE_HPP */
