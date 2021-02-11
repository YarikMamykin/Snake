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

  Snake::SnakeHead::SnakeHead(const color::Color color, geometry::Rectangle&& frame, const unsigned int& spacing) 
  : frame(frame) 
  , spacing(spacing) 
  , step(std::max(frame.width, frame.height) + spacing) 
  , head_color(color) { }

  void Snake::SnakeHead::hide(xlib::X11_Window *x_window) {
    auto background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    xlib::XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), std::forward<color::Color>(background_color));
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void Snake::SnakeHead::show(xlib::X11_Window *x_window) {
    xlib::XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(frame), std::forward<color::Color>(head_color));
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void Snake::SnakeHead::move(const SnakeDirection& new_direction, const RotationDirection& rotation_direction) { 
    switch(rotation_direction) {
      case RotationDirection::Clockwize: 
        {
          this->frame.rotate(std::move(rotation_direction), std::move(get_clockwize_rotation_point(new_direction)));
          this->handle_shift_after_clockwize_rotation(new_direction);
          break;
        }
      case RotationDirection::Counterclockwize: 
        {
          this->frame.rotate(std::move(rotation_direction), std::move(get_counter_clockwize_rotation_point(new_direction)));
          this->handle_shift_after_counter_clockwize_rotation(new_direction);
          break;
        }
      case RotationDirection::NONE: 
        {
          handle_none_rotation(new_direction); 
          break;
        }
    }
  }

  void Snake::SnakeHead::handle_none_rotation(const SnakeDirection& new_direction) {
      switch(new_direction) {
        case SnakeDirection::Up:    this->frame.move(0, -step); break;
        case SnakeDirection::Down:  this->frame.move(0, step); break;
        case SnakeDirection::Left:  this->frame.move(-step, 0); break;
        case SnakeDirection::Right: this->frame.move(step, 0); break;
      }
  }

  void Snake::SnakeHead::handle_shift_after_clockwize_rotation(const SnakeDirection& old_direction) {
      switch(old_direction) {
        case SnakeDirection::Up:    this->frame.move(spacing, 0); break;
        case SnakeDirection::Down:  this->frame.move(-spacing, 0); break;
        case SnakeDirection::Left:  this->frame.move(0, -spacing); break;
        case SnakeDirection::Right: this->frame.move(0, spacing); break;
      }
  }

  void Snake::SnakeHead::handle_shift_after_counter_clockwize_rotation(const SnakeDirection& old_direction) {
      switch(old_direction) {
        case SnakeDirection::Up:    this->frame.move(-spacing, 0); break;
        case SnakeDirection::Down:  this->frame.move(spacing, 0); break;
        case SnakeDirection::Left:  this->frame.move(0, spacing); break;
        case SnakeDirection::Right: this->frame.move(0, -spacing); break;
      }
  }

  geometry::Point Snake::SnakeHead::get_counter_clockwize_rotation_point(const SnakeDirection& new_direction) {
      switch(new_direction) {
        case SnakeDirection::Up:    return this->frame.bottom_left(); break;
        case SnakeDirection::Down:  return this->frame.top_right(); break;
        case SnakeDirection::Left:  return this->frame.bottom_right(); break;
        case SnakeDirection::Right: return this->frame.top_left(); break;
      }
  }

  geometry::Point Snake::SnakeHead::get_clockwize_rotation_point(const SnakeDirection& new_direction) {
      switch(new_direction) {
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

    parts.emplace_back(SnakeHead(color, std::move(head_shape), spacing));

    for(auto&& i : {1,2,3}) {
      const auto& last_frame = parts.back().frame;
      parts.emplace_back(SnakeHead(color,
            { 
            .x = last_frame.x - last_frame.width - spacing, 
            .y = last_frame.y, 
            .width = last_frame.width,
            .height = last_frame.height }, 
            spacing));
    }

    for(const auto& part : parts) {
      movement_queue.push_back(std::pair<game_objects::SnakeDirection, RotationDirection>(current_direction, RotationDirection::NONE));
    }
  }

  Snake::~Snake() {
  }

  void Snake::move(const game_objects::SnakeDirection& direction) {
    
    RotationDirection rotation_direction = RotationDirection::NONE;
    const bool direction_opposite_to_current = is_opposite_to_current(direction);

    if (direction != current_direction && !direction_opposite_to_current) {
      switch(direction) {
        case SnakeDirection::Up: 
          rotation_direction = (current_direction == SnakeDirection::Left ? RotationDirection::Counterclockwize 
                                                              : RotationDirection::Clockwize); break;
        case SnakeDirection::Down: 
          rotation_direction = (current_direction == SnakeDirection::Left ? RotationDirection::Clockwize 
                                                              : RotationDirection::Counterclockwize); break;
        case SnakeDirection::Left: 
          rotation_direction = (current_direction == SnakeDirection::Up ? RotationDirection::Clockwize 
                                                            : RotationDirection::Counterclockwize); break;
        case SnakeDirection::Right: 
          rotation_direction = (current_direction == SnakeDirection::Up ? RotationDirection::Counterclockwize 
                                                            : RotationDirection::Clockwize); break;
      }
    }

    this->hide(x_window);
    auto parts_iter = parts.begin();
    auto movements_iter = movement_queue.begin();

    for(; parts_iter != parts.end() && movements_iter != movement_queue.end(); ++parts_iter, ++movements_iter) {
      auto&& part_direction = movements_iter->first;
      auto&& part_rotation_direction = movements_iter->second;
      parts_iter->move(part_direction, part_rotation_direction);
    }

    this->show(x_window);

    if(!direction_opposite_to_current) {
      current_direction = direction;
    }

    movement_queue.pop_back();
    movement_queue.emplace_front(std::pair<SnakeDirection, RotationDirection>(current_direction, rotation_direction));
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
    const auto& tail_end_movement = movement_queue.back();
    const auto& spacing = tail_end.spacing;
    geometry::Point&& new_top_left {};

    switch(tail_end_movement.first) {
      case SnakeDirection::Down: 
        {
          new_top_left.x = tail_end_frame.x;
          new_top_left.y = tail_end_frame.y - tail_end_frame.height - spacing;
          break;
        }
      case SnakeDirection::Up:
        {
          new_top_left.x = tail_end_frame.x;
          new_top_left.y = tail_end_frame.y + tail_end_frame.height + spacing;
          break;
        }
      case SnakeDirection::Left:
        {
          new_top_left.x = tail_end_frame.x + tail_end_frame.width + spacing;
          new_top_left.y = tail_end_frame.y;
          break;
        }
      case SnakeDirection::Right:
        {
          new_top_left.x = tail_end_frame.x - tail_end_frame.width - spacing;
          new_top_left.y = tail_end_frame.y;
          break;
        }
    }

    parts.emplace_back(SnakeHead(tail_end_color,
          { 
          .x = new_top_left.x,
          .y = new_top_left.y,
          .width = tail_end_frame.width,
          .height = tail_end_frame.height }, 
          spacing));
    movement_queue.emplace_back(std::pair<SnakeDirection, RotationDirection>{ tail_end_movement.first, RotationDirection::NONE });
  }

}
