#include "Snake.hpp"
#include <iostream>
#include <vector>

namespace game_objects {
  class MovementController;
  class Snake;
  class SnakeHead;

  const unsigned int Snake::SnakeHead::offset = 1u;
  const unsigned int Snake::SnakeHead::spacing = 10u;

  Snake::SnakeHead::SnakeHead(geometry::Rectangle&& frame) 
  : frame(frame) {
  }

  void Snake::SnakeHead::hide(xlib::X11_Window *x_window) {
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context, 3,0,0,0);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.backgnd_color);
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
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.backgnd_color);
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.font_color);
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
    geometry::Point rotation_point;

    switch(new_direction) {
      case SnakeDirection::Up: 
        {
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.move(0, -offset);
          } else {
            this->frame.move(0, -(this->frame.height + offset));
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.bottom_left() 
              : this->frame.bottom_right();
          }
          break;
        } 
      case SnakeDirection::Down: 
        {
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.move(0, offset);
          } else {
            this->frame.move(0, (this->frame.height + offset));
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.top_right() 
              : this->frame.top_left();
          }
          break;
        }
      case SnakeDirection::Left: 
        {
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.move(-offset, 0);
          } else {
            this->frame.move(-(this->frame.width + offset), 0);
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.bottom_right() 
              : this->frame.top_right();
          }
          break;
        } 
      case SnakeDirection::Right: 
        {
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.move(offset, 0);
          } else {
            this->frame.move((this->frame.width + offset), 0);
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.top_left() 
              : this->frame.bottom_left();
          }
          break;
        }
    }

    if(RotationDirection::NONE != rotation_direction) {
      this->frame.rotate(std::move(rotation_direction), std::move(rotation_point));
    }
  }

  Snake::Snake(xlib::X11_Window* x_window, const game_objects::SnakeDirection&& direction) 
  : x_window(x_window)
  , current_direction(direction) 
  , window_frame(x_window->get_frame()) {

    const unsigned int head_size = 20u;
    const int head_pos = 100;
    parts.push_back(SnakeHead({ .x = head_pos, .y = head_pos, .width = head_size + head_size, .height = head_size }));
    parts.push_back(SnakeHead({ .x = parts.back().frame.x - parts.back().frame.width - SnakeHead::spacing, .y = parts.back().frame.y, .width = head_size + head_size, .height = head_size }));
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
    for(auto& part : parts) {
      auto prev_part_frame = part.frame;
      part.move(current_direction, rotation_direction);

      // don't let snake to go out of window borders
      mcontroller.validate(part.frame, prev_part_frame, window_frame);
    }
    this->show(x_window);

    if(!direction_opposite_to_current) {
      current_direction = direction;
    }
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

  bool Snake::MovementController::validate(geometry::Rectangle& frame, 
                                           const geometry::Rectangle& prev_frame, 
                                           const geometry::Rectangle& x_window_frame) {
    if(!frame.belongs_to(x_window_frame)) {
      frame = prev_frame;
      return false;
    }

    return true;
  }
}
