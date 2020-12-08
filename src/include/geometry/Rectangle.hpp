#ifndef SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP
#define SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP

#include "Point.hpp"
#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

namespace geometry {
  /*
   * This structure replaces original XRectangle
   *   as soon as 'x' and 'y' params there are of 'short' type!
   */
  struct Rectangle {
    int x,y;
    unsigned int width, height;

    Point bottom_right() const {
      return { .x = x + width, .y = y + height };
    }

    Point top_right() const {
      return { .x = x + width, .y = y };
    }

    Point bottom_left() const {
      return { .x = x , .y = y + height };
    }

    Point top_left() const {
      return { .x = x, .y = y };
    }

    void move(const int& x, const int& y) {
      this->x += x;
      this->y += y;
    }

    const std::string to_string() const {
      return std::string(std::to_string(this->x) + "  " +
          std::to_string(this->y) + "  " +
          std::to_string(this->width) + "  " +
          std::to_string(this->height) + "\n" );
    }

    bool belongs_to(const Rectangle& rect) const {
      const auto&& tr = top_right();
      const auto&& tl = top_left();
      const auto&& bl = bottom_left();
      const auto&& br = bottom_right();

      bool result = true;
      for(auto& point : { tr, tl, bl, br }) {
        result &= (point.x >= rect.x && point.x <= rect.x + rect.width 
            && point.y >= rect.y && point.y <= rect.y + rect.height);
      }

      return result;
    }

    void rotate(const game_objects::RotationDirection&& rotation_direction, const Point&& rotation_point) {
      std::cout << this->to_string() << std::endl;

      std::vector<Point> current_points = {top_right(), top_left(), bottom_left(), bottom_right()};
      std::function<Point (const Point& p)> rotate_point;

      switch(rotation_direction) {
        case game_objects::RotationDirection::Counterclockwize: 
          {
            rotate_point = [&rotation_point](const Point& p) -> Point { return { rotation_point.x - p.y + rotation_point.y, rotation_point.y + p.x - rotation_point.x }; };
            std::transform(current_points.begin(), current_points.end(), current_points.begin(), rotate_point);
            break;
          }
        case game_objects::RotationDirection::Clockwize: 
          {
            rotate_point = [&rotation_point](const Point& p) -> Point { return { rotation_point.x + p.y - rotation_point.y, rotation_point.y - p.x + rotation_point.x }; };
            std::transform(current_points.begin(), current_points.end(), current_points.begin(), rotate_point);
            break;
          }
        default: break;
      }

      const auto&& new_top_left = std::min_element(current_points.cbegin(), current_points.cend());
      const auto&& new_bottom_right = std::max_element(current_points.cbegin(), current_points.cend());

      this->x = new_top_left->x;
      this->y = new_top_left->y;
      this->width = new_bottom_right->x - new_top_left->x;
      this->height = new_bottom_right->y - new_top_left->y;

      std::cout << this->to_string() << std::endl;
    }
  };
}
#endif /* SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP */
