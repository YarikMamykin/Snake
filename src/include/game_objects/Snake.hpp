#ifndef SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP

#include <list>
#include <memory>
#include "constants/Constants.hpp"
#include "geometry/Rectangle.hpp"
#include "geometry/Triangle.hpp"
#include "color/Color.hpp"

namespace game_objects {

  class MovementController;

  class Snake {
    public:
    explicit Snake(const color::Color& value,
                   geometry::Rectangle&& head_shape,
                   const SnakeDirection&& direction = SnakeDirection::Right);
    ~Snake();

    void move(const SnakeDirection& direction);
    geometry::Rectangle head_frame() const;
    const size_t size() const;

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
        void show();
        void hide();
        void move();

        inline void handle_none_rotation();
        inline geometry::Point get_counter_clockwize_rotation_point();
        inline geometry::Point get_clockwize_rotation_point();  

        inline void handle_shift_after_clockwize_rotation();
        inline void handle_shift_after_counter_clockwize_rotation();
      };

      void show();
      void hide();
      inline bool is_opposite_to_current(const SnakeDirection& direction);
      void increase();

      std::list<SnakeHead> parts;
      SnakeDirection current_direction;
  };
}


#endif /* SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP */
