#ifndef SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP
#define SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP

#include <list>
#include <memory>
#include "constants/Constants.hpp"
#include "geometry/Rectangle.hpp"
#include "geometry/Triangle.hpp"
#include "color/Color/Color.hpp"

namespace game_objects {

  class MovementController;

  class Snake {
    public:
    explicit Snake(const color::Color& value,
                   geometry::Rectangle&& head_shape,
                   const SnakeDirection&& direction = SnakeDirection::Right);
    ~Snake();

    void move(SnakeDirection direction);
    geometry::Rectangle head_frame() const;
    const size_t size() const;

    friend class MovementController;

    private:
      struct SnakeHead {
        static inline unsigned int step;
        static inline unsigned int shift;
        static constexpr inline unsigned int spacing = 10u;
        static inline color::Color head_color;
        static inline color::Color background_color;

        geometry::Rectangle frame;
        SnakeDirection direction;
        SnakeDirection old_direction;
        RotationDirection rotation_direction;

        SnakeHead(geometry::Rectangle&& frame, 
                  SnakeDirection&& direction,
                  RotationDirection&& rotation_direction);
        SnakeHead(SnakeHead&&) noexcept = default;
        inline void show();
        inline void hide();
        inline void move();

        inline void handle_none_rotation();
        inline geometry::Point get_counter_clockwize_rotation_point();
        inline geometry::Point get_clockwize_rotation_point();  

        inline void handle_shift_after_clockwize_rotation();
        inline void handle_shift_after_counter_clockwize_rotation();
      };

      inline bool is_opposite_to_current(const SnakeDirection& direction) const;
      RotationDirection define_rotation_direction(const SnakeDirection& direction) const;
      void increase();

      std::list<SnakeHead> parts;
      SnakeDirection current_direction;
  };
}


#endif /* SRC_INCLUDE_GAME_OBJECTS_SNAKE_HPP */
