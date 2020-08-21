#include "Snake.hpp"

namespace game_objects {

  Snake::SnakeHead::SnakeHead(geometry::Rectangle&& frame) 
  : frame(frame) {
  }

  void Snake::SnakeHead::show(xlib::X11_Window *x_window) {
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        frame.x,
        frame.y,
        frame.width,
        frame.height);
  }

  void Snake::SnakeHead::move(const SnakeDirection&& current_direction, const int& rotation_angle) { 
    switch(current_direction) {
      case SnakeDirection::Up: 
        {
          geometry::Point rotation_point = { .x = (rotation_angle < 0 ? frame.x : frame.x + frame.width), 
                                             .y = frame.y + frame.height};
          break;
        } 
      case SnakeDirection::Down: 
        {
          geometry::Point rotation_point = { .x = (rotation_angle > 0 ? frame.x : frame.x + frame.width), 
                                             .y = frame.y};
          break;
        }
      case SnakeDirection::Left: 
        {
          break;
        } 
      case SnakeDirection::Right: 
        {
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

  Snake::Snake(xlib::X11_Window* x_window, const game_objects::SnakeDirection&& direction) 
  : x_window(x_window)
  , current_direction(direction) {

    const unsigned int head_size = 50u;
    const int head_pos = 500;
    SnakePart&& head = SnakeHead({ .x = head_pos, .y = head_pos, .width = head_size, .height = head_size });
    parts.push_back(head);

  }

  void Snake::move(const game_objects::SnakeDirection&& direction) {
    if(has_same_axis(std::move(direction))) {
      return;
    }

    int rotation_angle = 0;
    switch(direction) {
      case SnakeDirection::Up: rotation_angle = (direction == SnakeDirection::Left ? -90 : 90); break;
      case SnakeDirection::Down: rotation_angle = (direction == SnakeDirection::Left ? 90 : -90); break;
      case SnakeDirection::Left: rotation_angle = (direction == SnakeDirection::Up ? 90 : -90); break;
      case SnakeDirection::Right: rotation_angle = (direction == SnakeDirection::Up ? -90 : 90); break;
    }

    this->hide(x_window);
    for(auto& part : parts) {
      part.move(current_direction, rotation_angle);
    }
    this->show(x_window);

    current_direction = direction;
  }

  void Snake::hide(xlib::X11_Window* x_window) {
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.backgnd_color);
    for(auto& part : parts) {
      part.show(x_window);
    }
  }

  void Snake::show(xlib::X11_Window* x_window) {
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.font_color);
    for(auto& part : parts) {
      part.show(x_window);
    }
  }

  bool Snake::has_same_axis(const game_objects::SnakeDirection&& direction) {
    if(current_direction == direction) {
      return true;
    }

    if((current_direction == SnakeDirection::Up || current_direction == SnakeDirection::Down) &&
       (direction == SnakeDirection::Up || direction == SnakeDirection::Down)) {
      return true;
    }

    if((current_direction == SnakeDirection::Left || current_direction == SnakeDirection::Right) &&
       (direction == SnakeDirection::Left || direction == SnakeDirection::Right)) {
      return true;
    }

    return false;
  }
}
