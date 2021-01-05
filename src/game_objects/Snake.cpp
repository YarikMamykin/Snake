#include "Snake.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

namespace game_objects {
  class MovementController;
  class Snake;
  class SnakeHead;

  Snake::SnakeHead::SnakeHead(geometry::Rectangle&& frame, const unsigned int& spacing) 
  : frame(frame) 
  , spacing(spacing) 
  , step(std::max(frame.width, frame.height) + spacing) { }

  void Snake::SnakeHead::hide(xlib::X11_Window *x_window) {
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context, 3,0,0,0);
    const auto& window_color_scheme = x_window->get_color_scheme();
    XSetForeground(x_window->x_display.display, x_window->graphical_context, window_color_scheme.at(ui::ColorSchemeID::BackgroundColor).to_long());
    XFillRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
    XFlush(x_window->x_display.display);
  }

  void Snake::SnakeHead::show(xlib::X11_Window *x_window) {
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context, 3,0,0,0);
    const auto& window_color_scheme = x_window->get_color_scheme();
    XSetForeground(x_window->x_display.display, x_window->graphical_context, window_color_scheme.at(ui::ColorSchemeID::BackgroundColor).to_long());
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, window_color_scheme.at(ui::ColorSchemeID::FontColor).to_long());
    XFillRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
    XFlush(x_window->x_display.display);
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


  Snake::Snake(xlib::X11_Window* x_window, const game_objects::SnakeDirection&& direction) 
  : x_window(x_window)
  , current_direction(direction) 
  , window_frame(x_window->get_frame()) {

    geometry::Rectangle head_shape = { 
      .x = 100 * 3, 
      .y = 100,
      .width = 20 * 2,
      .height = 20
    };
    constexpr unsigned int spacing = 10u;

    parts.emplace_back(SnakeHead(std::move(head_shape), spacing));

    for(auto&& i : {1,2,3}) {
      const auto& last_frame = parts.back().frame;
      parts.emplace_back(SnakeHead({ 
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

    // don't let snake to go out of window borders
    mcontroller.validate(parts.begin()->frame, window_frame);

    this->show(x_window);

    if(!direction_opposite_to_current) {
      current_direction = direction;
    }

    movement_queue.pop_back();
    movement_queue.push_front(std::pair<SnakeDirection, RotationDirection>(current_direction, rotation_direction));
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

  void Snake::MovementController::validate(geometry::Rectangle& frame, 
                                           const geometry::Rectangle& x_window_frame) {
    if(!frame.belongs_to(x_window_frame)) {
      throw exceptions::GameOver();
    }
  }
}
