#include "Snake.hpp"
#include <iostream>

namespace game_objects {

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

  void Snake::SnakeHead::move(const SnakeDirection& current_direction, const RotationDirection& rotation_direction) { 
    switch(current_direction) {
      case SnakeDirection::Up: 
        {
          geometry::Point rotation_point;
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.y -= 10;
          } else {
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.bottom_left() 
              : this->frame.bottom_right();
          }
          break;
        } 
      case SnakeDirection::Down: 
        {
          geometry::Point rotation_point;
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.y += 10;
          } else {
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.top_right() 
              : this->frame.top_left();
          }
          break;
        }
      case SnakeDirection::Left: 
        {
          geometry::Point rotation_point;
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.x -= 10;
          } else {
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.bottom_right() 
              : this->frame.top_right();
          }
          break;
        } 
      case SnakeDirection::Right: 
        {
          geometry::Point rotation_point;
          if(rotation_direction == RotationDirection::NONE) {
            this->frame.x += 10;
          } else {
            rotation_point = rotation_direction == RotationDirection::Counterclockwize 
              ? this->frame.top_left() 
              : this->frame.bottom_left();
          }
          break;
        }
    }
  }

  Snake::SnakeTailPart::SnakeTailPart(geometry::Rectangle&& frame) 
  : frame(frame) {
  }

  void Snake::SnakeTailPart::show(xlib::X11_Window *x_window) {
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
  }

  void Snake::SnakeTailPart::move(const SnakeDirection &direction, const RotationDirection& rotation_direction) {
  }

  Snake::Snake(xlib::X11_Window* x_window, const game_objects::SnakeDirection&& direction) 
  : x_window(x_window)
  , current_direction(direction) {

    const unsigned int head_size = 20u;
    const int head_pos = 50;
    parts.push_back(SnakeHead({ .x = head_pos, .y = head_pos, .width = head_size, .height = head_size }));
  }

  Snake::~Snake() {
  }

  void Snake::move(const game_objects::SnakeDirection& direction) {
    if(is_opposite_to_current(direction)) {
      return;
    }

    RotationDirection rotation_direction = RotationDirection::NONE;
    if (direction != current_direction) {
      switch(direction) {
        case SnakeDirection::Up: 
          rotation_direction = (direction == SnakeDirection::Left ? RotationDirection::Counterclockwize 
                                                              : RotationDirection::Clockwize); break;
        case SnakeDirection::Down: 
          rotation_direction = (direction == SnakeDirection::Left ? RotationDirection::Clockwize 
                                                              : RotationDirection::Counterclockwize); break;
        case SnakeDirection::Left: 
          rotation_direction = (direction == SnakeDirection::Up ? RotationDirection::Clockwize 
                                                            : RotationDirection::Counterclockwize); break;
        case SnakeDirection::Right: 
          rotation_direction = (direction == SnakeDirection::Up ? RotationDirection::Counterclockwize 
                                                            : RotationDirection::Clockwize); break;
      }
    }

    this->hide(x_window);
    for(auto& part : parts) {
      part.move(current_direction, rotation_direction);
    }
    this->show(x_window);

    current_direction = direction;
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
}
