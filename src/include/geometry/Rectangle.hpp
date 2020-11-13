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
  };
}
#endif /* SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP */
