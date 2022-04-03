#pragma once

#include <string>
#include <sstream>
#include "types/enums/RotationDirection.hpp"

namespace geometry {
  struct Point {
    int x,y;

    friend bool operator < (const Point& a, const Point& b) {
      bool&& x_equal = a.x == b.x;
      bool&& y_equal = a.y == b.y;
      bool&& x_lesser = a.x < b.x;
      bool&& y_lesser = a.y < b.y;
      return (x_equal && y_lesser) || (y_equal && x_lesser) || (x_lesser && y_lesser);
    }

    friend bool operator > (const Point& a, const Point& b) {
      bool&& x_equal = a.x == b.x;
      bool&& y_equal = a.y == b.y;
      bool&& x_greater = a.x > b.x;
      bool&& y_greater = a.y > b.y;
      return (x_equal && y_greater) || (y_equal && x_greater) || (y_greater && x_greater);
    }

    friend bool operator == (const Point& a, const Point& b) {
      return (a.x == b.x) && (a.y == b.y);
    }

    friend bool operator >= (const Point& a, const Point& b) {
      bool equal = a == b;
      bool greater = a > b;
      return equal || greater;
    }

    const std::string to_string() const {
      std::ostringstream point_data;
      point_data << "Point(" << this->x << ":" << this->y << ")" << std::endl;
      return point_data.str();
    }

    void rotate(const game_objects::RotationDirection&& rotation_direction, const Point& p) {
      if(rotation_direction == game_objects::RotationDirection::NONE) {
        return;
      }

      int x_rotated, y_rotated;

      switch(rotation_direction) {
        case game_objects::RotationDirection::Counterclockwize:
          {
            x_rotated = p.x + (y - p.y);
            y_rotated = p.y - (x - p.x);
            break;
          }
        case game_objects::RotationDirection::Clockwize:
          {
            x_rotated = p.x - (y - p.y);
            y_rotated = p.y + (x - p.x);
            break;
          }
        default: break;
      }

      this->x = x_rotated;
      this->y = y_rotated;
    }
  };
}
