#include "game_objects/Snake.hpp"
#include "exceptions/Exceptions.hpp"
#include "configuration/Settings.hpp"
#include <vector>
#include <algorithm>
#include "commands/graphics_commands/FillRectangle.hpp"

namespace game_objects {
  class MovementController;
  class Snake;
  class SnakeHead;

  Snake::SnakeHead::SnakeHead(geometry::Rectangle&& frame, SnakeDirection&& direction, RotationDirection&& rotation_direction) 
  : frame(frame) 
  , direction(std::forward<SnakeDirection>(direction))
  , rotation_direction(std::forward<RotationDirection>(rotation_direction)) 
  , old_direction(direction) {}

  void Snake::SnakeHead::hide() {
    commands::Command::push_xlib_command(new commands::FillRectangle(frame, background_color));
  }

  void Snake::SnakeHead::show() {
    commands::Command::push_xlib_command(new commands::FillRectangle(frame, head_color));
  }

  void Snake::SnakeHead::move() {
    switch(rotation_direction) {
      case RotationDirection::Clockwize: 
        {
          this->frame.rotate(rotation_direction, get_clockwize_rotation_point());
          this->handle_shift_after_clockwize_rotation();
          break;
        }
      case RotationDirection::Counterclockwize: 
        {
          this->frame.rotate(rotation_direction, get_counter_clockwize_rotation_point());
          this->handle_shift_after_counter_clockwize_rotation();
          break;
        }
      case RotationDirection::NONE: 
        {
          handle_none_rotation(); 
          break;
        }
    }
    old_direction = direction;
  }

  void Snake::SnakeHead::handle_none_rotation() {
      switch(direction) {
        case SnakeDirection::Up:    this->frame.move(0, -step); break;
        case SnakeDirection::Down:  this->frame.move(0, step); break;
        case SnakeDirection::Left:  this->frame.move(-step, 0); break;
        case SnakeDirection::Right: this->frame.move(step, 0); break;
      }
  }

  void Snake::SnakeHead::handle_shift_after_clockwize_rotation() {
      switch(direction) {
        case SnakeDirection::Up:    this->frame.move(-step,shift); break;
        case SnakeDirection::Down:  this->frame.move(step,-shift); break;
        case SnakeDirection::Left:  this->frame.move(shift,step); break;
        case SnakeDirection::Right: this->frame.move(-shift, -step); break;
      }
  }

  void Snake::SnakeHead::handle_shift_after_counter_clockwize_rotation() {
      switch(direction) {
        case SnakeDirection::Up:    this->frame.move(step,shift); break;
        case SnakeDirection::Down:  this->frame.move(-step,-shift); break;
        case SnakeDirection::Left:  this->frame.move(shift,-step); break;
        case SnakeDirection::Right: this->frame.move(-shift,step); break;
      }
  }

  geometry::Point Snake::SnakeHead::get_counter_clockwize_rotation_point() {
      switch(old_direction) {
        case SnakeDirection::Up:    return this->frame.bottom_left(); break;
        case SnakeDirection::Down:  return this->frame.top_right(); break;
        case SnakeDirection::Left:  return this->frame.bottom_right(); break;
        case SnakeDirection::Right: return this->frame.top_left(); break;
      }
  }

  geometry::Point Snake::SnakeHead::get_clockwize_rotation_point() {
      switch(old_direction) {
        case SnakeDirection::Up:    return this->frame.bottom_right(); break;
        case SnakeDirection::Down:  return this->frame.top_left(); break;
        case SnakeDirection::Left:  return this->frame.top_right(); break;
        case SnakeDirection::Right: return this->frame.bottom_left(); break;
      }
  }


  Snake::Snake(const color::Color& color,
               geometry::Rectangle&& head_shape,
               const SnakeDirection&& direction) 
  : current_direction(direction) {

    SnakeHead::step = std::max(head_shape.width, head_shape.height) + SnakeHead::spacing;
    SnakeHead::shift = std::min(head_shape.width, head_shape.height);
    SnakeHead::head_color = color;
    SnakeHead::background_color = config::get_concrete_ref<color::COLOR_SCHEME_TYPE>(config_id::WINDOW_COLOR_SCHEME).at(color::ColorSchemeID::BackgroundColor);
    parts.emplace_back(SnakeHead(std::move(head_shape), SnakeDirection(current_direction), RotationDirection::NONE));
  }

  Snake::~Snake() {
  }

  void Snake::move(const game_objects::SnakeDirection& direction) {
    
    RotationDirection rotation_direction = define_rotation_direction(direction);

    SnakeDirection direction_buffer = SnakeDirection::Down;
    RotationDirection rotation_direction_buffer = RotationDirection::NONE;

    for(auto& part : parts) {
      part.hide();
      part.move();
      part.show();
      std::swap(part.direction, direction_buffer);
      std::swap(part.rotation_direction, rotation_direction_buffer);
    }

    if(!is_opposite_to_current(direction)) {
      parts.front().old_direction = current_direction;
      current_direction = direction;
    }

    parts.front().direction = current_direction;
    parts.front().rotation_direction = rotation_direction;
  }

  geometry::Rectangle Snake::head_frame() const {
    return this->parts.front().frame;
  }


  bool Snake::is_opposite_to_current(const game_objects::SnakeDirection& direction) const {
    const auto&& up_down = (current_direction == SnakeDirection::Up && 
                            direction == SnakeDirection::Down);
    const auto&& down_up = (current_direction == SnakeDirection::Down && 
                            direction == SnakeDirection::Up);
    const auto&& left_right = (current_direction == SnakeDirection::Left && 
                            direction == SnakeDirection::Right);
    const auto&& right_left = (current_direction == SnakeDirection::Right && 
                            direction == SnakeDirection::Left);


    return up_down || down_up || left_right || right_left;
  }

  RotationDirection Snake::define_rotation_direction(const SnakeDirection& direction) const {
    if(is_opposite_to_current(direction)) return RotationDirection::NONE; 
    if(direction == current_direction) return RotationDirection::NONE; 

    switch(direction) {
      case SnakeDirection::Up:
        return current_direction == SnakeDirection::Left ? RotationDirection::Clockwize : RotationDirection::Counterclockwize; 
      case SnakeDirection::Down:
        return current_direction == SnakeDirection::Left ? RotationDirection::Counterclockwize : RotationDirection::Clockwize;
      case SnakeDirection::Left:
        return current_direction == SnakeDirection::Up ? RotationDirection::Counterclockwize : RotationDirection::Clockwize;
      case SnakeDirection::Right:
        return current_direction == SnakeDirection::Up ? RotationDirection::Clockwize : RotationDirection::Counterclockwize;
    }

    return RotationDirection::NONE; 
  }

  void Snake::increase() {
    const auto& tail_end = parts.back();
    const auto& tail_end_frame = tail_end.frame;
    const auto& tail_end_direction = tail_end.old_direction;
    const auto& tail_end_rotation_direction = tail_end.rotation_direction;
    geometry::Rectangle&& new_part_frame {};

    switch(tail_end_direction) {
      case SnakeDirection::Down: 
        {
          new_part_frame.x = tail_end_frame.x;
          new_part_frame.y = tail_end_frame.y - tail_end_frame.height - SnakeHead::spacing;
          break;
        }
      case SnakeDirection::Up:
        {
          new_part_frame.x = tail_end_frame.x;
          new_part_frame.y = tail_end_frame.y + tail_end_frame.height + SnakeHead::spacing;
          break;
        }
      case SnakeDirection::Left:
        {
          new_part_frame.x = tail_end_frame.x + tail_end_frame.width + SnakeHead::spacing;
          new_part_frame.y = tail_end_frame.y;
          break;
        }
      case SnakeDirection::Right:
        {
          new_part_frame.x = tail_end_frame.x - tail_end_frame.width - SnakeHead::spacing;
          new_part_frame.y = tail_end_frame.y;
          break;
        }
    }

    new_part_frame.width = tail_end_frame.width;
    new_part_frame.height = tail_end_frame.height;

    parts.emplace_back(SnakeHead(std::move(new_part_frame), SnakeDirection(tail_end_direction), RotationDirection::NONE));
  }

  const size_t Snake::size() const {
    return parts.size();
  }
}
