#ifndef SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP
#define SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP

#include "Point.hpp"

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
  };
}
#endif /* SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP */
