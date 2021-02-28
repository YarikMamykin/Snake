#include "Snake.hpp"
#include "Exceptions.hpp"
#include "XlibWrapper.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

namespace game_objects {
  class MovementController;
  class Snake;
  class SnakeHead;

  Snake::SnakeHead::SnakeHead(const color::Color color, 
                              geometry::Rectangle&& frame, 
                              SnakeDirection&& direction, 
                              RotationDirection&& rotation_direction, 
                              const unsigned int& spacing) 
  : frame(frame) 
  , direction(std::forward<SnakeDirection>(direction))
  , rotation_direction(std::forward<RotationDirection>(rotation_direction))
  , spacing(spacing) 
  , step(std::max(frame.width, frame.height) + spacing) 
  , shift(std::min(frame.width, frame.height))
  , head_color(color) { this->old_direction = direction; }

  void Snake::SnakeHead::hide(xlib::X11_Window *x_window) {
    auto background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    xlib::XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), std::forward<color::Color>(background_color));
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void Snake::SnakeHead::show(xlib::X11_Window *x_window) {
    xlib::XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), std::forward<color::Color>(head_color));
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void Snake::SnakeHead::move() {
    switch(rotation_direction) {
      case RotationDirection::Clockwize: 
        {
          this->frame.rotate(RotationDirection(rotation_direction), std::move(get_clockwize_rotation_point()));
          this->handle_shift_after_clockwize_rotation();
          break;
        }
      case RotationDirection::Counterclockwize: 
        {
          this->frame.rotate(RotationDirection(rotation_direction), std::move(get_counter_clockwize_rotation_point()));
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


  Snake::Snake(xlib::X11_Window* x_window, 
               const color::Color& color,
               geometry::Rectangle&& head_shape,
               const SnakeDirection&& direction) 
  : x_window(x_window)
  , current_direction(direction) {

    constexpr unsigned int spacing = 10u;

    parts.emplace_back(SnakeHead(color, std::move(head_shape), SnakeDirection(current_direction), RotationDirection::NONE, spacing));
    parts.back().frame.set_center(x_window->get_width()/2u, x_window->get_height()/2u);
  }

  Snake::~Snake() {
  }

  void Snake::move(const game_objects::SnakeDirection& direction) {
    
    RotationDirection rotation_direction = RotationDirection::NONE;
    const bool direction_opposite_to_current = is_opposite_to_current(direction);

    if (direction != current_direction && !direction_opposite_to_current) {
      switch(direction) {
        case SnakeDirection::Up: 
          rotation_direction = (current_direction == SnakeDirection::Left ? RotationDirection::Clockwize
                                                              : RotationDirection::Counterclockwize); break;
        case SnakeDirection::Down: 
          rotation_direction = (current_direction == SnakeDirection::Left ? RotationDirection::Counterclockwize
                                                              : RotationDirection::Clockwize); break;
        case SnakeDirection::Left: 
          rotation_direction = (current_direction == SnakeDirection::Up ? RotationDirection::Counterclockwize
                                                            : RotationDirection::Clockwize); break;
        case SnakeDirection::Right: 
          rotation_direction = (current_direction == SnakeDirection::Up ? RotationDirection::Clockwize 
                                                            : RotationDirection::Counterclockwize); break;
      }
    }

    this->hide(x_window);

    for(auto& part : parts) {
      part.move();
    }

    for(auto parts_iter = std::next(parts.rbegin()); parts_iter != parts.rend(); ++parts_iter) {
      std::prev(parts_iter)->direction = parts_iter->direction;
      std::prev(parts_iter)->rotation_direction = parts_iter->rotation_direction;
    }

    this->show(x_window);

    if(!direction_opposite_to_current) {
      parts.front().old_direction = current_direction;
      current_direction = direction;
    }

    parts.front().direction = current_direction;
    parts.front().rotation_direction = rotation_direction;
  }

  geometry::Rectangle Snake::head_frame() const {
    return this->parts.front().frame;
  }


  void Snake::hide(xlib::X11_Window* x_window) {
    for(auto& part : parts) {
      part.hide(x_window);
    }
  }

  void Snake::show(xlib::X11_Window* x_window) {
    for(auto& part : parts) {
      part.show(x_window);
    }
  }

  bool Snake::is_opposite_to_current(const game_objects::SnakeDirection& direction) {
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

  void Snake::increase() {
    const auto& tail_end = parts.back();
    const auto& tail_end_color = tail_end.head_color;
    const auto& tail_end_frame = tail_end.frame;
    const auto& tail_end_direction = tail_end.old_direction;
    const auto& tail_end_rotation_direction = tail_end.rotation_direction;
    const auto& spacing = tail_end.spacing;
    geometry::Rectangle&& new_part_frame {};

    switch(tail_end_direction) {
      case SnakeDirection::Down: 
        {
          new_part_frame.x = tail_end_frame.x;
          new_part_frame.y = tail_end_frame.y - tail_end_frame.height - spacing;
          break;
        }
      case SnakeDirection::Up:
        {
          new_part_frame.x = tail_end_frame.x;
          new_part_frame.y = tail_end_frame.y + tail_end_frame.height + spacing;
          break;
        }
      case SnakeDirection::Left:
        {
          new_part_frame.x = tail_end_frame.x + tail_end_frame.width + spacing;
          new_part_frame.y = tail_end_frame.y;
          break;
        }
      case SnakeDirection::Right:
        {
          new_part_frame.x = tail_end_frame.x - tail_end_frame.width - spacing;
          new_part_frame.y = tail_end_frame.y;
          break;
        }
    }

    new_part_frame.width = tail_end_frame.width;
    new_part_frame.height = tail_end_frame.height;


    parts.emplace_back(SnakeHead(tail_end_color,
          std::move(new_part_frame),
          SnakeDirection(tail_end_direction),
          RotationDirection::NONE,
          spacing));
  }

  const size_t Snake::size() const {
    return parts.size();
  }
}
